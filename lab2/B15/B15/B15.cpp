#include <stdio.h>
#include "memallocator.h"

#define TRUE 1
#define FALSE 0

typedef struct node {
	struct node* prev;
	struct node* next;
	int size;
	int is_ready;
} descriptor_t;

static struct {
	descriptor_t* list;
	int full_size;
} mem_struct = { (descriptor_t*)NULL,0 };

int memgetminimumsize() {
	return sizeof(descriptor_t);
}

int memgetblocksize() {
	return sizeof(descriptor_t);
}

void memdone() {
	mem_struct.list = NULL;
	mem_struct.full_size = 0;
}


int meminit(void* memUnit, int size) {
	int desc_size = memgetblocksize();
	int min_size = memgetminimumsize();
	if ((size < min_size + 1) || (!memUnit)) {
		return 0;
	}
	else {
		mem_struct.list = (descriptor_t*)memUnit;
		mem_struct.list->is_ready = TRUE;
		mem_struct.list->prev = NULL;
		mem_struct.list->next = NULL;
		mem_struct.list->size = size - desc_size;
		mem_struct.full_size = size;
		return 1;
	}
}

void* memalloc(int size) {
	descriptor_t* tmp;
	descriptor_t* new_node;
	descriptor_t* best_fit = NULL;
	int node_size = memgetblocksize();
	void* result = NULL;
	if ((!mem_struct.list) || (size <= 0)) {
		return NULL;
	}
	if (mem_struct.list) {
		tmp = mem_struct.list;

		while (tmp) {
			if ((tmp->size >= size) && ((best_fit == NULL) || (tmp->size < best_fit->size)) && (tmp->is_ready == TRUE)) {
				best_fit = tmp;
			}
			tmp = tmp->next;
		}
		if (best_fit) {
			if (best_fit->size <= size + memgetblocksize()) {
				best_fit->is_ready = FALSE;
			}
			else {
				new_node = (descriptor_t*)((char*)best_fit + size + node_size);
				new_node->prev = best_fit;
				new_node->next = best_fit->next;
				if (best_fit->next) {
					best_fit->next->prev = new_node;
				}
				best_fit->next = new_node;
				best_fit->is_ready = FALSE;
				new_node->is_ready = TRUE;
				new_node->size = best_fit->size - size - node_size;
				best_fit->size = size;
			}
			result = (void*)((char*)best_fit + node_size);
		}
		else {
			result = NULL;
		}
	}
	return result;
}

void memfree(void* ptr) {
	descriptor_t* first_free = NULL;
	descriptor_t* new_free = NULL;
	int node_size = memgetblocksize();
	if (ptr && mem_struct.list) {
		new_free = (descriptor_t*)((char*)ptr - node_size);
		if (new_free >= mem_struct.list && new_free <= mem_struct.list + mem_struct.full_size && (new_free->is_ready == FALSE)) {
			new_free->is_ready = TRUE;
			if (new_free->next) {
				if (new_free->next->is_ready) {
					first_free = new_free;
					first_free->size += first_free->next->size + node_size;
					if (first_free->next->next) {
						first_free->next->next->prev = first_free;
						first_free->next = first_free->next->next;
					}
					else {
						first_free->next = NULL;
					}
					if (first_free->prev) {
						first_free->prev->next = first_free;
					}
					else {
						first_free->prev = NULL;
					}
				}
			}
			if (new_free->prev) {
				if (new_free->prev->is_ready) {
					first_free = new_free->prev;
					first_free->size += first_free->next->size + node_size;
					if (first_free->next->next) {
						first_free->next->next->prev = first_free;
						first_free->next = first_free->next->next;
					}
					else {
						first_free->next = NULL;
					}
				}
			}
		}
	}
}