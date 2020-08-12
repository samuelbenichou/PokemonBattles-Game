//
// Created by Samuel Benichou on 2019-12-07.
//

#ifndef POKEMONBATTLE_LINKEDLIST_H
#define POKEMONBATTLE_LINKEDLIST_H

#include "Defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct List list;

typedef struct Node node;

list* createLinkedList(freeFunction,printFunction,getCategoryFunction);

node* createNode(element);

status appendNode(list*,element);

status destroyList(list*);

status deleteNode(list*,element);

status displayList(list*);

element searchByKeyInList(list*,element);

node* getHead(list*);

node* getNext(element);

element getData(element);

int getListSize(list*);

void displayNode(list*,element);


#endif //POKEMONBATTLE_LINKEDLIST_H
