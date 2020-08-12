//
// Created by Samuel Benichou on 2019-12-07.
//

#ifndef POKEMONBATTLE_MAXHEAP_H
#define POKEMONBATTLE_MAXHEAP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Defs.h"
#include "LinkedList.h"

typedef struct MaxHeap maxHeap;

maxHeap* CreateHeap(int,char*,freeFunction,printFunction,equalFunction,copyFunction);

status destroyHeap(maxHeap*);

status printHeap(maxHeap*);

status insertToHeap(maxHeap* ,element);

element PopMaxHeap(maxHeap*);

char* getHeapId(maxHeap*);

int getHeapCurrentSize(maxHeap*);

element TopMaxHeap(maxHeap*);

void MaxHeapify(maxHeap*,int);

status BuildMaxHeap(maxHeap*);

void HeapIncreaseKey(maxHeap*,element);

char* getHeapCategory(element);

status printHeapPokemon(element elem);

status freeHeapPokemon(element elem);

int equalDataAttack(element,element);

maxHeap* copyHeap(maxHeap *mHeap,int );


#endif //POKEMONBATTLE_MAXHEAP_H

