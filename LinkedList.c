//
// Created by Samuel Benichou on 2019-12-07.
//

#include "LinkedList.h"

// ********* Structures *********

struct List{
    int size;
    node* head;
    node* tail;

    // Pointers functions
    freeFunction freeFunction;
    printFunction printFunction;
    getCategoryFunction CategoryFunction;
};

struct Node{
    element data;
    node* next;
};

// ********* Functions *********

list* createLinkedList(freeFunction freeFunction,printFunction printFunction,getCategoryFunction CategoryFunction){
    list *myList = (list*) malloc(sizeof(struct List));
    if (myList == NULL){
        printf("No memory available.\n");
        free(myList);
        return NULL;
    }
    myList->size = 0;

    /* Set head and tail nodes */
    myList->head = NULL;
    myList->tail = NULL;

    /* Set Pointers functions */
    myList->freeFunction = freeFunction;
    myList->printFunction = printFunction;
    myList->CategoryFunction = CategoryFunction;

    return myList;
}

node* createNode(element data){
    node* newNode = (node*) malloc(sizeof(struct Node));
    if (newNode == NULL){
        printf("No memory available.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

status appendNode(list *list,element data){
    if (list == NULL || data == NULL) return failure;

    node* nodeToAppend = createNode(data);
    if (list->head == NULL && list->tail == NULL){
        list->head = nodeToAppend;
        list->tail = nodeToAppend;
    } else{
        list->tail->next = nodeToAppend;
        list->tail = nodeToAppend;
    }
    list->size++;

    return sucess;
}

status deleteNode(list *list,element data){
    if (list == NULL || data == NULL) return failure;

    node *current = list->head;
    while (current != NULL){
        if (current->data == data) break;
        current = current->next;
    }
    if (current == NULL) return failure;

    if (list->head == current) {
        list->head = list->head->next;
        list->freeFunction(current->data);
        free(current);
    }else{
        node *temp = list->head;
        while (temp->next != current)
            temp = temp->next;
        if (temp->next != NULL && temp->next == current){
            temp->next = current->next;
            list->freeFunction(current->data);
            free(current);
        }
    }
    list->size--;
    return sucess;
}

status destroyList(list *list) {
    if (list == NULL) return failure;

    node *current = list->head;
    while (current != NULL){
        list->freeFunction(current->data);
        node *temp = current;
        temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
    return sucess;
}

status displayList(list *list){
    node *current = list->head;
    while (current != NULL){
        list->printFunction(current->data);
        current = current->next;
    }
    return sucess;
}

element searchByKeyInList(list *list,element data){
    if (list == NULL || data == NULL) return NULL;

    node *current = list->head;
    while (current != NULL){
        if (strcmp(list->CategoryFunction(current->data),data) == 0) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

int getListSize(list *list){
    return list->size;
}

void displayNode(list *list,element data){
    list->printFunction(data);
}

node* getHead(list *list){
    return list->head;
}

node* getNext(element elem){
    node *temp = (node*)elem;
    return temp->next;
}

element getData(element elem){
    node *temp = (node*)elem;
    return temp->data;
}
