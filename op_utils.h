// Copyright 2022 Maria Sfiraiala (maria.sfiraiala@stud.acs.upb.ro)

#ifndef OP_UTILS_H_
#define OP_UTILS_H_

#include "doubly_linked_list.h"

/*
* @brief -> divides the input in 2, the operation keyword and everything else
* @param -> input = the line read from stdin, it needs to be interpreted
* @param -> op = stores the operation keyword
* @return -> none, the op will be modified inside the function
*/
void get_op(char *input, char *op);

/*
* @brief -> checks if a card is valid
* @param -> entry = the card that needs to be validated
* @return -> 1 for success, 0 for failure
*/
int check_card(card_t *entry);

/*
* @brief -> adds a deck to the deck list
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure (when the command is invalid)
*/
int add_deck(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> deletes a deck from the deck list
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int del_deck(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> deletes a card from the deck list
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int del_card(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> adds cards to an existing deck
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int add_cards(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> determines the number of decks
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int deck_number(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> determines the length of a specific deck from the deck list
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int deck_len(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> shuffles a deck (the first half becomes the last and viceversa)
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int shuffle_deck(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> interchanges two values
* @param -> a = the first value
* @oaram -> b = the second value
* @return -> none, the changes are persistent
*/
void max_swap(int *a, int *b);

/*
* @brief -> merges 2 (unsorted) decks from the deck list, value by value
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int merge_decks(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> splits a deck from the deck list; the 2 resulted decks will take
            its place in the list
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int split_deck(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> reverses a deck from the deck list (it mirrors it)
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int reverse_deck(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> prints a deck from the deck list, card by card
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int show_deck(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> prints the entire deck list, deck by deck, card by card
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int show_all(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> sets the priority of the cards based on their value and symbol, in
            order to sort them
* @param -> node1 = the first node, which will be evaluated to node2
* @param -> node2 = the second node
* @return -> 1 if node1 < node2, 0 otherwise
*/
int cmp(dll_node_t *node1, dll_node_t *node2);

/*
* @brief -> sorts a deck from the deck list
* @param -> deck = the deck that we want to sort
* @return -> a new, sorted deck
*/
doubly_linked_list_t *insert_sort(doubly_linked_list_t *deck);

/*
* @brief -> sorts a deck from the deck list
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int sort_deck(char *input, doubly_linked_list_t *deck_list);

/*
* @brief -> exites programme, frees all dynamically allocated memory
* @param -> deck_list = stores all information related to decks
* @return -> 1 for success, 0 for failure
*/
int exit_op(doubly_linked_list_t **deck_list);

/*
* @brief -> applies operations, the base function of the project\
* @param -> operation = the keyword of the command
* @param -> input = the rest of the line, it contains vital parameters to the
*           operation
* @param -> deck_list = the list in which we store all the information related
            to decks and cards
* @return -> 1 for success, 0 for failure
*/
int apply_op(char *operation, char *input, doubly_linked_list_t *deck_list);

#endif  // OP_UTILS_H_
