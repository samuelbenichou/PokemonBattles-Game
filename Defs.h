//
// Created by Samuel Benichou on 2019-11-19.
//

#ifndef UNTITLED_DEFS_H
#define UNTITLED_DEFS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum e_bool {false,true} bool;
typedef enum e_status{sucess,failure} status;

typedef void * element;
typedef element(*copyFunction) (element);
typedef status(*freeFunction) (element);
typedef status(*printFunction) (element);
typedef int(*equalFunction) (element, element);//1 first bigger, 0 - same, -1 second bigger
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond); // return the first attack - second attack . also produce the attack of each element.

#endif //UNTITLED_DEFS_H
