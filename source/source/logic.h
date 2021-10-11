#ifndef LOGIC_H
#define LOGIC_H

#define WORD_LENGTH 21

typedef struct Node {
	char word[WORD_LENGTH];
	struct Node* next;
} Node;

void add_sorted(Node** head_p, char new_word[]);
Node* sorted_merge(Node* a, Node* b);

#endif