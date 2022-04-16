// Copyright 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "op_utils.h"
#include "doubly_linked_list.h"

int main(void)
{
    char operation[STRING_MAX_LEN], input[STRING_MAX_LEN];
    int mem_ups;  // a flag in case we have memory allocation errors

    // we create a list for decks, each deck being a list by itself
    doubly_linked_list_t *deck_list = dll_create(sizeof(doubly_linked_list_t));

    do {
        // reading from stdin line by line
        fgets(input, STRING_MAX_LEN, stdin);

        // if the line is empty => junk, we print the invalid command error
        if (!strcmp(input, "\n"))
            strcpy(input, "garbage");

        // separating the op keyword from the rest of the input
        get_op(input, operation);

        // we execute the now decoded command
        mem_ups = apply_op(operation, input, deck_list);
        if (mem_ups == -1)
            exit(-1);
    } while (strcmp(operation, "EXIT"));
    return 0;
}
