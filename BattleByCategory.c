//
// Created by samuel Benichou on 2019-12-07.
//

#include "BattleByCategory.h"

// ********* Structures *********

struct battle_s{
    int numOfCategories;
    list *battleOfPokemons;
    int MaxSize;

    /* Pointers Functions */
    equalFunction equalElement;
    copyFunction copyElement;
    freeFunction freeElement;
    getCategoryFunction getCategory;
    getAttackFunction getAttack;
    printFunction printElement;
};

// ********* Functions *********

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement
        ,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,
                              getAttackFunction getAttack,printFunction printElement){
    if (categories == NULL || equalElement == NULL || copyElement == NULL || freeElement == NULL
        || getCategory == NULL || getAttack == NULL || printElement == NULL){
        return NULL;
    }

    Battle myBattle = (Battle) malloc(sizeof(struct battle_s));
    if (myBattle == NULL){
        printf("No memory available.\n");
        return NULL;
    }
    myBattle->numOfCategories = numberOfCategories;
    myBattle->MaxSize = capacity;

    /* Set Pointers Functions */
    myBattle->copyElement = copyElement;
    myBattle->equalElement = equalElement;
    myBattle->freeElement = freeElement;
    myBattle->getAttack = getAttack;
    myBattle->getCategory = getCategory;
    myBattle->printElement = printElement;

    /* Create the Linked List of Pokemons Heap */
    myBattle->battleOfPokemons = createLinkedList(freeHeapPokemon,printHeapPokemon,getHeapCategory);
    int i = 1;
    char typesToSplit[BufferSize];
    strcpy(typesToSplit,categories);
    char *token = strtok(typesToSplit,",");
    maxHeap *heap = CreateHeap(myBattle->MaxSize,token,myBattle->freeElement,myBattle->printElement,myBattle->equalElement,myBattle->copyElement);
    appendNode(myBattle->battleOfPokemons,heap);
    while (i < myBattle->numOfCategories){
        if (i == myBattle->numOfCategories-1)
            token = strtok(NULL, "\n");
        else
            token = strtok(NULL, ",");
        maxHeap *heapTemp = CreateHeap(myBattle->MaxSize,token,myBattle->freeElement,myBattle->printElement,myBattle->equalElement,myBattle->copyElement);
        appendNode(myBattle->battleOfPokemons,heapTemp);
        i++;
    }
    return myBattle;
}

void displayObjectsByCategories(Battle b){
    displayList(b->battleOfPokemons);
}

element removeMaxByCategory(Battle b,char* category){
    return PopMaxHeap(searchByKeyInList(b->battleOfPokemons,category));
}

int getNumberOfObjectsInCategory(Battle b,char* category){
    return getHeapCurrentSize(searchByKeyInList(b->battleOfPokemons,category));
}

status destroyBattleByCategory(Battle b){
    if(b == NULL) return failure;
    destroyList(b->battleOfPokemons);
    free(b);
    return sucess;
}

status insertObject(Battle b, element elem){
    maxHeap *temp = searchByKeyInList(b->battleOfPokemons,b->getCategory(elem));
    if (temp == NULL)
        return failure;
    insertToHeap(temp,elem);
    return sucess;
}

element fight(Battle b,element elem){ 
    int ans = -1000;
    int res;
    int attack1,attack2 = 0;
    printf("you choose to fight with:\n");
    b->printElement(elem);
    element toFace = NULL;
    node *temp = getHead(b->battleOfPokemons);
    for (int i = 0; i < b->numOfCategories; ++i) {
        if (TopMaxHeap(getData(temp)) != NULL) {
            int first,second = 0;
            res = b->getAttack(TopMaxHeap(getData(temp)), elem, &first, &second);
            if (res > ans || i == 0) {
                attack1 = first;
                attack2 = second;
                ans = res;
                toFace = TopMaxHeap(getData(temp));
            }
        }
        if (i == b->numOfCategories-1) break;
        temp = getNext(temp);
    }
    if(toFace == NULL){
        printf("There are no Pokemons to fight against you.\n");
        b->freeElement(elem);
        return NULL;
    }
    printf("The final battle between:\n");
    b->printElement(elem);
    printf("In this battle his attack is :%d\n\n",attack2);
    printf("against ");
    b->printElement(toFace);

    printf("In this battle his attack is :%d\n\n",attack1);
    if (attack1 == attack2)
        printf("IT IS A DRAW.\n");
    else if (attack1 >attack2){
        printf("THE WINNER IS:\n");
        b->printElement(toFace);
    }else{
        printf("THE WINNER IS:\n");
        b->printElement(elem);
    }
    b->freeElement(elem);
    return toFace;
}
