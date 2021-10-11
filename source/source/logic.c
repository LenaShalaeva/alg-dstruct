#include <stdio.h>
#include "logic.h"


int check_order(char w1[], char w2[]) {
    int i;
    for (i = 0; w1[i]; i++) {
        if (w1[i] < w2[i]) return 1;
        if (w1[i] > w2[i]) return 0;

    }
    return 1;
}

void insert_beginning(Node** head_p, char new_word[]) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory");
        abort();
    }
    memcpy(&(new_node->word), new_word, 21);
    new_node->next = *head_p;

    *head_p = new_node;
}

void insert_after(Node* node, char new_word[]) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory");
        abort();
    }
    memcpy(&(new_node->word), new_word, 21);
    new_node->next = node->next;
    node->next = new_node;
}

void insert_end(Node* node, char new_word[]) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed to allocate memory");
        abort();
    }
    memcpy(&(new_node->word), new_word, 21);
    new_node->next = NULL;

    node->next = new_node;
}


void add_sorted(Node** head_p, char new_word[]) {
    if (*head_p == NULL || check_order(new_word, &((**head_p).word))) {
        insert_beginning(head_p, new_word);
        return;
    }



    Node* curr_node = *head_p;
    while (curr_node->next != NULL) {
        if (check_order(new_word, &(curr_node->next->word)))
            break;
        curr_node = curr_node->next;
    }

    if (curr_node->next == NULL)
        insert_end(curr_node, new_word);
    else {
        insert_after(curr_node, new_word);
    }
}

Node* sorted_merge(Node* a, Node* b) {
    Node* result = NULL;

    if (a == NULL)
        return(b);
    else if (b == NULL)
        return(a);

    if (check_order(&(*a).word, &(*b).word))
    {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return result;
}