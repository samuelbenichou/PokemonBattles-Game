//
// Created by Samuel Benichou on 2019-12-07.
//

#include "MaxHeap.h"

// ********* Structures *********

struct MaxHeap{
    int maxSize;
    int currentSize;
    char *name;
    element* array; // Maybe **

    // Pointers Functions
    freeFunction freeFunction;
    equalFunction equalFunction;
    printFunction printFunction;
    copyFunction copyFunction;

};

// ********* Functions *********

maxHeap* CreateHeap(int maxSize,char *name,freeFunction free,printFunction print,equalFunction equal,copyFunction copy){
    if (maxSize < 0 || name == NULL || free == NULL || print == NULL || equal == NULL) return NULL;

    maxHeap *myHeap = (maxHeap*) malloc(sizeof(struct MaxHeap));
    if (myHeap == NULL){
        printf("No memory available.\n");
        free(myHeap);
        return NULL;
    }
    myHeap->name = (char*) malloc(strlen(name)+1);
    if (myHeap->name == NULL){
        printf("No memory available.\n");
        free(myHeap->name);
        return NULL;
    }
    strcpy(myHeap->name,name);
    myHeap->maxSize = maxSize;
    myHeap->currentSize = 0;
    myHeap->array = malloc(sizeof(element)*myHeap->maxSize);
    if (myHeap->array == NULL){
        printf("No memory available.\n");
        free(myHeap->array);
        return NULL;
    }

    /* Set Functions Pointers */
    myHeap->printFunction = print;
    myHeap->freeFunction = free;
    myHeap->equalFunction = equal;
    myHeap->copyFunction = copy;

    return myHeap;
}

status destroyHeap(maxHeap *heap){
    if (heap == NULL) return failure;

    for (int i = 0; i < heap->currentSize; ++i) {
        heap->freeFunction(heap->array[i]);
    }
    free(heap->array);
    if(heap->name != NULL){
        free(heap->name);
    }
    free(heap);
    return sucess;
}

status printHeap(maxHeap *heap){
    if (heap == NULL) return failure;

    printf("%s:\n",heap->name);
    if (heap->currentSize == 0){
        printf("No elements.\n\n");
        return sucess;
    } else{
        int count= heap->currentSize;
        maxHeap *copy = copyHeap(heap,heap->currentSize);
        int i = 1;
        while(count > 0)
        {
            element toPrint = PopMaxHeap(copy);
            printf("%d. ",i);
            heap->printFunction(toPrint);
            count--;
            i++;
        }
        destroyHeap(copy);
    }
    return sucess;
}

status insertToHeap(maxHeap *heap,element data){
    if (heap == NULL || data == NULL) return failure;

    if (heap->currentSize >= heap->maxSize) {
        printf("Type at full capacity.\n");
        return failure;
    }
    else{
        heap->array[heap->currentSize] = data;
        heap->currentSize++;
        HeapIncreaseKey(heap,data);
    }
    return sucess;
}

element PopMaxHeap(maxHeap *heap){
    if (heap->currentSize == 0) return NULL;

    element temp = heap->array[0];
    heap->array[0] = heap->array[heap->currentSize-1];
    heap->currentSize--;
    // Heapify the root node
    MaxHeapify(heap,0);
    return temp;
}

char* getHeapId(maxHeap *heap){
    return heap->name;
}

int getHeapCurrentSize(maxHeap *heap){
    return heap->currentSize;
}

element TopMaxHeap(maxHeap *heap){
    if (heap->currentSize == 0) return NULL;

    return heap->array[0];
}

status BuildMaxHeap(maxHeap *heap){
    int size = heap->currentSize;
    for (int i = (size/2); i>=0 ; i--) {
        MaxHeapify(heap,i);
    }
    return sucess;
}

void MaxHeapify(maxHeap *heap,int size){
    int largest;
    element temp;
    int left = (2*size+1);
    int right = ((2*size)+2);
    if (left >= heap->currentSize)
        return;
    else{
        if (left < heap->currentSize && heap->equalFunction(heap->array[left],heap->array[size]) == 1)
            largest = left;
        else{
            largest = size;
        }

        if (right < heap->currentSize && heap->equalFunction(heap->array[right],heap->array[largest]) == 1)
            largest = right;

        if (largest != size){
            temp = heap->array[size];
            heap->array[size] = heap->array[largest];
            heap->array[largest] = temp;
            MaxHeapify(heap,largest);
        }
    }
}

void HeapIncreaseKey(maxHeap *heap,element data){
    if (heap == NULL || data == NULL) return;
    int i = heap->currentSize-1;
    element temp;
    while (i > 0 && heap->equalFunction(heap->array[(i-1)/2],heap->array[i]) == -1){
        temp = heap->array[i];
        heap->array[i] = heap->array[(i-1)/2];
        heap->array[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

char* getName(maxHeap *heap){
    return heap->name;
}

char* getHeapCategory(element elem){
    if (elem == NULL)
        return NULL;
    maxHeap *heap = (maxHeap*)elem;
    return heap->name;
}

status printHeapPokemon(element elem){
    if (elem == NULL)
        return failure;
    maxHeap *heap = (maxHeap*)elem;
    printHeap(heap);
    return sucess;
}

status freeHeapPokemon(element elem){
    if (elem == NULL) return failure;

    maxHeap *heap = (maxHeap*)elem;
    destroyHeap(heap);
    return sucess;
}

maxHeap* copyHeap(maxHeap *mHeap,int currentSize){

    if(mHeap == NULL)return NULL;
    maxHeap *copy = CreateHeap(mHeap->maxSize,mHeap->name,mHeap->freeFunction,mHeap->printFunction,mHeap->equalFunction,mHeap->copyFunction);
    if(copy == NULL)return NULL;

    mHeap->currentSize = currentSize;
    for(int i=0;i<currentSize;i++){
        insertToHeap(copy,mHeap->array[i]);
    }
    return copy;
}