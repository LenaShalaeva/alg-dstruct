#pragma warning(disable:4996)
#include <stdio.h>
#include "logic.h"

#define LINE_LENGTH 22

int main(void) {
    int i;
    Node* list1 = NULL;

    FILE* input1 = fopen("input1.txt", "r");
    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), input1)) {
        for (i = 0; i < LINE_LENGTH; i++)
            if (line[i] == '\n')
                line[i] = '\0';
        add_sorted(&list1, line);
    }
    fclose(input1);


    Node* list2 = NULL;
    FILE* input2 = fopen("input2.txt", "r");
    while (fgets(line, sizeof(line), input2)) {
        for (i = 0; i < LINE_LENGTH; i++)
            if (line[i] == '\n')
                line[i] = '\0';
        add_sorted(&list2, line);
    }
    fclose(input2);



    FILE* output = fopen("output.txt", "w");
    Node* new_list = sorted_merge(list1, list2);
    Node* curr = new_list;
    while (curr != NULL) {
        if (curr->next)
            fprintf(output, "%s\n", curr->word);
        else
            fprintf(output, "%s", curr->word);
        curr = curr->next;
    }
    fclose(output);

    return 0;
}