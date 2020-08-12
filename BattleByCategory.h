//
// Created by samuel Benichou on 2019-12-07.
//

#ifndef POKEMONBATTLE_BATTLEBYCATEGORY_H
#define POKEMONBATTLE_BATTLEBYCATEGORY_H

#include "Defs.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#define BufferSize 300

typedef struct battle_s* Battle;

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement);
status destroyBattleByCategory(Battle b);
status insertObject(Battle b, element elem);
void displayObjectsByCategories(Battle b);
element removeMaxByCategory(Battle b,char* category);
int getNumberOfObjectsInCategory(Battle b,char* category);
element fight(Battle b,element elem);

#endif //POKEMONBATTLE_BATTLEBYCATEGORY_H
