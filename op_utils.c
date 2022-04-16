// Copyright 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op_utils.h"
#include "doubly_linked_list.h"

void get_op(char *input, char *op)
{
    char tmp[STRING_MAX_LEN];

    strcpy(tmp, input);
    strcpy(op, strtok(tmp, "\n "));

    strcpy(tmp, input + strlen(op) + 1);
    strcpy(input, tmp);
}

int check_card(card_t *entry)
{
    if (entry->value < 1 || entry->value > 14) {
        printf("The provided card is not a valid one.\n");
        return 0;
    }
    if (strcmp(entry->symbol, "HEART") && strcmp(entry->symbol, "SPADE") &&
       strcmp(entry->symbol, "CLUB") && strcmp(entry->symbol, "DIAMOND")) {
        printf("The provided card is not a valid one.\n");
        return 0;
    }
    return 1;
}

int add_deck(char *input, doubly_linked_list_t *deck_list)
{
    int cards_number;  // the number of cards that are going to be read
    char junk;  // some junk flag, in case the command is not valid
    // if we read more than the cards number it means the command is invalid
    if (sscanf(input, "%d %c", &cards_number, &junk) != 1) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    // creating the new deck
    doubly_linked_list_t *new_deck = dll_create(sizeof(card_t));

    if (!new_deck)
        return -1;

    for (int i = 0; i < cards_number; ++i) {
        char buffer[STRING_MAX_LEN];
        // we now read line by line we'll later use sscanf() to parse the line,
        // extracting the info we actually need
        fgets(buffer, STRING_MAX_LEN, stdin);

        card_t entry;
        char j;
        // if the card is not valid we decrement i, awaiting for a valid one
        if (sscanf(buffer, "%d %s %c", &entry.value, entry.symbol, &j) != 2) {
            printf("The provided card is not a valid one.\n");
            --i;
        } else if (!check_card(&entry)) {
            --i;
        } else {
            // we add the valid entry to the deck
            dll_add_nth_node(new_deck, i, &entry, sizeof(entry));
        }
    }

    // we add the newly created deck to the deck list
    dll_add_nth_node(deck_list, deck_list->size, new_deck, sizeof(*new_deck));
    printf("The deck was successfully created with %d cards.\n", cards_number);

    free(new_deck);
    return 1;
}

int del_deck(char *input, doubly_linked_list_t *deck_list)
{
    int index;
    char junk;
    // sscanf() and junk to verify whether the input is valid
    if (sscanf(input, "%d %c", &index, &junk) != 1) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    // print the error message if the index is out of bounds
    if (index < 0 || index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    // getting the deck that is now deleted (we removed its links to the prev
    // and next one)
    dll_node_t *deck = dll_remove_nth_node(deck_list, index);
    // we, nevertheless, free its space
    dll_free((doubly_linked_list_t **)&deck->data);
    free(deck);

    printf("The deck %d was successfully deleted.\n", index);
    return 1;
}

int del_card(char *input, doubly_linked_list_t *deck_list)
{
    int d_index, card_index;
    char junk;
    if (sscanf(input, "%d %d %c", &d_index, &card_index, &junk) != 2) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (d_index < 0 || d_index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    // we get the deck from which we'll delete the card
    doubly_linked_list_t *deck = (dll_get_nth_node(deck_list, d_index))->data;

    if (card_index < 0 || card_index >= deck->size) {
        printf("The provided index is out of bounds for deck %d.\n", d_index);
        return 0;
    }

    // we now delete the card and free it
    dll_node_t *card = dll_remove_nth_node(deck, card_index);

    free(card->data);
    free(card);

    // if, after the card removal, the deck is empty, we'll delete it too
    if (!deck->size) {
        dll_node_t *removed = dll_remove_nth_node(deck_list, d_index);
        dll_free((doubly_linked_list_t **)&removed->data);
        free(removed);
    }

    printf("The card was successfully deleted from deck %d.\n", d_index);
    return 1;
}

int add_cards(char *input, doubly_linked_list_t *deck_list)
{
    int deck_index, cards_number;
    char junk;
    if (sscanf(input, "%d %d %c", &deck_index, &cards_number, &junk) != 2) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (deck_index < 0 || deck_index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    // finding the exact deck that will get new cards
    doubly_linked_list_t *updated_deck = (dll_get_nth_node(deck_list,
                                         deck_index))->data;

    for (int i = 0; i < cards_number; ++i) {
        char buffer[STRING_MAX_LEN];
        fgets(buffer, STRING_MAX_LEN, stdin);

        card_t entry;
        char j;
        if (sscanf(buffer, "%d %s %c", &entry.value, entry.symbol, &j) != 2) {
            printf("The provided card is not a valid one.\n");
            --i;
        } else if (!check_card(&entry)) {
            --i;
        } else {
            // for a valid entry, the deck is updated
            dll_add_nth_node(updated_deck, updated_deck->size, &entry,
                            sizeof(entry));
        }
    }

    printf("The cards were successfully added to deck %d.\n", deck_index);
    return 1;
}

int deck_number(char *input, doubly_linked_list_t *deck_list)
{
    char junk;
    // string parsing check
    if (sscanf(input, "%c", &junk) != EOF) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    // we'll simply access the struct field specifically created for this task
    int len = deck_list->size;
    printf("The number of decks is %d.\n", len);
    return 1;
}

int deck_len(char *input, doubly_linked_list_t *deck_list)
{
    int deck_index;
    char junk;
    if (sscanf(input, "%d %c", &deck_index, &junk) != 1) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (deck_index < 0 || deck_index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    // getting the desired deck, after checking whether it actually exists
    doubly_linked_list_t *deck = (dll_get_nth_node(deck_list,
                                 deck_index))->data;
    // similar with deck_number, we get the length stored in the struct for
    // the doubly linked list
    int len = deck->size;

    printf("The length of deck %d is %d.\n", deck_index, len);
    return 1;
}

int shuffle_deck(char *input, doubly_linked_list_t *deck_list)
{
    int deck_index;
    char junk;
    if (sscanf(input, "%d %c", &deck_index, &junk) != 1) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (deck_index < 0 || deck_index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    // we first find the deck to be shuffled
    doubly_linked_list_t *deck = (dll_get_nth_node(deck_list,
                                 deck_index))->data;
    // create a new deck that will store the result
    doubly_linked_list_t *shuffled_deck = dll_create(sizeof(card_t));

    // every card that's before the middle of the deck will be added in such a
    // manner that after the completion of the operation they'll be the last
    // ones
    dll_node_t *node = deck->head;
    for (int i = 0; i < deck->size / 2; ++i) {
        dll_add_nth_node(shuffled_deck, i, node->data, sizeof(card_t));
        node = node->next;
    }
    // the cards after the middle of the deck we'll be inserted at the front
    int j = 0;
    for (int i = deck->size / 2; i < deck->size; ++i) {
        dll_add_nth_node(shuffled_deck, j, node->data, sizeof(card_t));
        ++j;
        node = node->next;
    }

    // we add the shuffled deck to the list of decks
    dll_add_nth_node(deck_list, deck_index + 1, shuffled_deck,
                    sizeof(*shuffled_deck));

    // removing the old, redundant deck
    dll_node_t *removed = dll_remove_nth_node(deck_list, deck_index);
    dll_free((doubly_linked_list_t **)&removed->data);

    free(removed);
    free(shuffled_deck);

    printf("The deck %d was successfully shuffled.\n", deck_index);
    return 1;
}

void max_swap(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int merge_decks(char *input, doubly_linked_list_t *deck_list)
{
    int index1, index2;
    char junk;
    if (sscanf(input, "%d %d %c", &index1, &index2, &junk) != 2) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (index1 < 0 || index1 >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    if (index2 < 0 || index2 >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    doubly_linked_list_t *deck1 = (dll_get_nth_node(deck_list, index1))->data;
    doubly_linked_list_t *deck2 = (dll_get_nth_node(deck_list, index2))->data;
    doubly_linked_list_t *merged_deck = dll_create(sizeof(card_t));

    dll_node_t *node1 = deck1->head;
    dll_node_t *node2 = deck2->head;

    // we take one card from each deck, as long as there are still entries in
    // both of them
    while (node1 && node2) {
        dll_add_nth_node(merged_deck, merged_deck->size, node1->data,
                        sizeof(card_t));
        node1 = node1->next;
        dll_add_nth_node(merged_deck, merged_deck->size, node2->data,
                        sizeof(card_t));
        node2 = node2->next;
    }

    // if the first deck still has cards, we add them to the result
    while (node1) {
        dll_add_nth_node(merged_deck, merged_deck->size, node1->data,
                        sizeof(card_t));
        node1 = node1->next;
    }

    // if the second deck is the one still not empty, we add its cards
    while (node2) {
        dll_add_nth_node(merged_deck, merged_deck->size, node2->data,
                        sizeof(card_t));
        node2 = node2->next;
    }

    dll_add_nth_node(deck_list, deck_list->size, merged_deck,
                    sizeof(*merged_deck));

    // in order to have a safe deck deletion, we determine the maximum
    // of the indeces
    int is_swapped = 0;
    if (index1 < index2) {
        max_swap(&index1, &index2);
        is_swapped = 1;
    }

    // we remove the maximum index, so the first to be deleted deck won't have
    // a change of index
    dll_node_t *removed = dll_remove_nth_node(deck_list, index1);
    dll_free((doubly_linked_list_t **)&removed->data);
    free(removed);

    // we now, safely, delete the closest to 0 deck
    removed = dll_remove_nth_node(deck_list, index2);
    dll_free((doubly_linked_list_t **)&removed->data);
    free(removed);

    free(merged_deck);

    // swap back the indeces for a correct success message
    if (is_swapped)
        max_swap(&index1, &index2);

    printf("The deck %d and the deck %d were successfully merged.\n",
          index1, index2);
    return 1;
}

int split_deck(char *input, doubly_linked_list_t *deck_list)
{
    int deck_index;
    int split_index;
    char junk;
    if (sscanf(input, "%d %d %c", &deck_index, &split_index, &junk) != 2) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (deck_index < 0 || deck_index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    if (!split_index) {
        printf("The deck %d was successfully split by index %d.\n",
              deck_index, split_index);
        return 1;
    }

    // get the deck we want to split
    doubly_linked_list_t *deck = (dll_get_nth_node(deck_list,
                                 deck_index))->data;

    if (split_index < 0 || split_index >= deck->size) {
        printf("The provided index is out of bounds for deck %d.\n",
              deck_index);
        return 0;
    }

    // create the split decks that will result from the desired deck
    doubly_linked_list_t *split1 = dll_create(sizeof(card_t));
    doubly_linked_list_t *split2 = dll_create(sizeof(card_t));

    // populate the split decks
    dll_node_t *node = deck->head;
    for (int i = 0; i < split_index; ++i) {
        dll_add_nth_node(split1, i, node->data, sizeof(card_t));
        node = node->next;
    }
    int j = 0;
    for (int i = split_index; i < deck->size; ++i) {
        dll_add_nth_node(split2, j, node->data, sizeof(card_t));
        ++j;
        node = node->next;
    }

    // add the resulted decks after the parent one
    dll_add_nth_node(deck_list, deck_index + 1, split1, sizeof(*split1));
    dll_add_nth_node(deck_list, deck_index + 2, split2, sizeof(*split2));

    // remove the parent
    dll_node_t *removed = dll_remove_nth_node(deck_list, deck_index);
    dll_free((doubly_linked_list_t **)&removed->data);
    free(removed);
    free(split1);
    free(split2);

    printf("The deck %d was successfully split by index %d.\n", deck_index,
          split_index);
    return 1;
}

int reverse_deck(char *input, doubly_linked_list_t *deck_list)
{
    int deck_index;
    char junk;
    if (sscanf(input, "%d %c", &deck_index, &junk) != 1) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (deck_index < 0 || deck_index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    doubly_linked_list_t *deck = (dll_get_nth_node(deck_list,
                                 deck_index))->data;

    // we'll work with 2 pointers, one which will start from the head
    // and one that will start from the last node
    dll_node_t *last_node = deck->head;
    for (int i = 0; i < deck->size - 1; ++i)
        last_node = last_node->next;

    dll_node_t *first_node = deck->head;

    // coming from the front and from the back, we swap values
    for (int i = 0; i < deck->size / 2; ++i) {
        card_t aux;
        memcpy(&aux, first_node->data, sizeof(card_t));
        memcpy(first_node->data, last_node->data, sizeof(card_t));
        memcpy(last_node->data, &aux, sizeof(card_t));

        first_node = first_node->next;
        last_node = last_node->prev;
    }

    printf("The deck %d was successfully reversed.\n", deck_index);
    return 1;
}

int show_deck(char *input, doubly_linked_list_t *deck_list)
{
    int deck_index;
    char junk;
    if (sscanf(input, "%d %c", &deck_index, &junk) != 1) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (deck_index < 0 || deck_index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    // find the deck we want to print
    doubly_linked_list_t *deck_node = (dll_get_nth_node(deck_list,
                                 deck_index))->data;

    printf("Deck %d:\n", deck_index);

    // for every card stored in the list, print the value and the symbol
    dll_node_t *card_node = deck_node->head;
    while (card_node) {
        card_t *tmp = card_node->data;
        printf("\t%d %s\n", tmp->value, tmp->symbol);
        card_node = card_node->next;
    }

    return 1;
}

int show_all(char *input, doubly_linked_list_t *deck_list)
{
    char junk;
    if (sscanf(input, "%c", &junk) != EOF) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    // we'll follow the same steps as with de show_deck, this time for every
    // deck in the list
    dll_node_t *deck_node = deck_list->head;
    for (int i = 0; i < deck_list->size; ++i) {
        dll_node_t *card_node = ((doubly_linked_list_t *)deck_node->data)->head;

        printf("Deck %d:\n", i);
        while (card_node) {
            card_t *tmp = card_node->data;
            printf("\t%d %s\n", tmp->value, tmp->symbol);
            card_node = card_node->next;
        }

        deck_node = deck_node->next;
    }
    return 1;
}

int cmp(dll_node_t *node1, dll_node_t *node2)
{
    card_t *card1 = (card_t *)node1->data, *card2 = (card_t *)node2->data;

    if (card1->value < card2->value) {
        return 1;
    } else if (card1->value == card2->value) {
        if (!strcmp(card2->symbol, "CLUB"))
            return 1;

        if (!strcmp(card2->symbol, "DIAMOND") && strcmp(card1->symbol, "CLUB"))
            return 1;

        if (!strcmp(card2->symbol, "SPADE") && strcmp(card1->symbol, "CLUB")
           && strcmp(card1->symbol, "DIAMOND"))
            return 1;

        return 0;
    }

    return 0;
}

doubly_linked_list_t *insert_sort(doubly_linked_list_t *deck)
{
    // create a sorted list
    doubly_linked_list_t *sorted_deck = dll_create(sizeof(card_t));
    dll_node_t *node = deck->head;

    for (int i = 0; i < deck->size; ++i) {
        // for every node in the list, find the first node "bigger" than it
        // and insert in a sorted manner in the result list
        if (!sorted_deck->head) {
            dll_add_nth_node(sorted_deck, 0, node->data, sizeof(card_t));
        } else {
            dll_node_t *sorted_node = sorted_deck->head;

            // determine the first less prioritised node
            int j;
            for (j = 0; j < sorted_deck->size && !cmp(node, sorted_node); ++j)
                sorted_node = sorted_node->next;

            // insert the node before the first less prioritised node
            dll_add_nth_node(sorted_deck, j, node->data, sizeof(card_t));
        }

        // repeat for every node in the list
        node = node->next;
    }
    return sorted_deck;
}

int sort_deck(char *input, doubly_linked_list_t *deck_list)
{
    int deck_index;
    char junk;
    if (sscanf(input, "%d %c", &deck_index, &junk) != 1) {
        printf("Invalid command. Please try again.\n");
        return 0;
    }

    if (deck_index < 0 || deck_index >= deck_list->size) {
        printf("The provided index is out of bounds for the deck list.\n");
        return 0;
    }

    doubly_linked_list_t *deck = (dll_get_nth_node(deck_list,
                                 deck_index))->data;
    doubly_linked_list_t *sorted_deck = insert_sort(deck);  // sort the deck

    // insert the sorted deck
    dll_add_nth_node(deck_list, deck_index + 1, sorted_deck,
                    sizeof(*sorted_deck));

    // delete the unsorted deck
    dll_node_t *removed = dll_remove_nth_node(deck_list, deck_index);
    dll_free((doubly_linked_list_t **)&removed->data);
    free(removed);
    free(sorted_deck);

    printf("The deck %d was successfully sorted.\n", deck_index);
    return 1;
}

int exit_op(doubly_linked_list_t **deck_list)
{
    dll_node_t *tmp, *node;
    int size = 0;
    if (!deck_list || !*deck_list)
        return 0;

    node = (*deck_list)->head;
    while (size < (*deck_list)->size) {
        ++size;
        tmp = node;
        node = node->next;
        dll_free((doubly_linked_list_t **)tmp);
        free(tmp);
    }

    free(*deck_list);
    deck_list = NULL;

    return 1;
}

int apply_op(char *operation, char *input, doubly_linked_list_t *deck_list)
{
    if (!strcmp(operation, "ADD_DECK"))
        return add_deck(input, deck_list);

    if (!strcmp(operation, "DEL_DECK"))
        return del_deck(input, deck_list);

    if (!strcmp(operation, "DEL_CARD"))
        return del_card(input, deck_list);

    if (!strcmp(operation, "ADD_CARDS"))
        return add_cards(input, deck_list);

    if (!strcmp(operation, "DECK_NUMBER"))
        return deck_number(input, deck_list);

    if (!strcmp(operation, "DECK_LEN"))
        return deck_len(input, deck_list);

    if (!strcmp(operation, "SHUFFLE_DECK"))
        return shuffle_deck(input, deck_list);

    if (!strcmp(operation, "MERGE_DECKS"))
        return merge_decks(input, deck_list);

    if (!strcmp(operation, "SPLIT_DECK"))
        return split_deck(input, deck_list);

    if (!strcmp(operation, "REVERSE_DECK"))
        return reverse_deck(input, deck_list);

    if (!strcmp(operation, "SHOW_DECK"))
        return show_deck(input, deck_list);

    if (!strcmp(operation, "SHOW_ALL"))
        return show_all(input, deck_list);

    if (!strcmp(operation, "SORT_DECK"))
        return sort_deck(input, deck_list);

    if (!strcmp(operation, "EXIT"))
        return exit_op(&deck_list);

    printf("Invalid command. Please try again.\n");
    return 0;
}
