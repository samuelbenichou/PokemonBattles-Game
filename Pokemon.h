//
// Created by Samuel Benichou on 2019-11-19.
//

#ifndef UNTITLED_POKEMON_H
#define UNTITLED_POKEMON_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"

#define Max_Name_lenght 30

//   ******* Structures *******

/* Definition of pokemon type */
typedef struct pokemonType_t{
    char *types;
    int size;
    int effectiveAgainstMeCount;
    int effectiveAgainstOtherCount;
    struct pokemonType_t **effective_against_me;
    struct pokemonType_t **effective_against_other;
}pokemonType;

/* Definition of a Pokemon */
typedef struct Pokemon_t{
    char *name;
    char *specie;
    struct bioData_t *bioData;
    struct pokemonType_t *pokemonType;
} Pokemon;

/* Definition of the biological data of the pokemon */
typedef struct bioData_t{
    double height;
    double weight;
    int attack;
}bioData;

//   ******* Functions *******

/**
 * Creation of pokemon
 * @param pokemon's parameter
 * @return Pointer to a new pokemon
 */
Pokemon* createPokemon(char *name,char *specie, struct pokemonType_t *type,int num1,double num2,double num3);

/**
 * Creation of pokemon type
 * @param Name of pokemon type (ex : Fire)
 * @return pointer to the new pokemon type
 */
pokemonType* pokemonTypeCreation(char *name);

/**
 * Creation of biologic data of pokemon
 * @param Data of the pokemon
 * @return pointer to the new pokemon data
 */
bioData* PokemonBilogicalDataCreation(double height, double weight,int attack);

/**
 * Append new type of pokemon A to the list effective_against_me B
 * @param typeOfPokemon A  and typeOfPokemon B
 * @return success or failure
 */
status addTypeOfPokemonToEffectiveAgainstMe(pokemonType *A,pokemonType *B);

/**
 * Append new type of pokemon A to the list effective_against_other B
 * @param typeOfPokemon A  and typeOfPokemon B
 * @return success or failure
 */
status addTypeOfPokemonToEffectiveAgainstOther(pokemonType *A,pokemonType *B);

/**
 * Delete the typeOfPokemon B from the typeOfPokemon A
 * in his effective_against_me list
 * @param typeOfPokemon A  and typeOfPokemon B
 * @return success or failure
 */
status delTypeOfPokemonToEffectiveAgainstMe(pokemonType *A,char *name);

/**
 * Delete the typeOfPokemon B from the typeOfPokemon A
 * in his effective_against_other list
 * @param typeOfPokemon A  and typeOfPokemon B
 * @return success or failure
 */
status delTypeOfPokemonToEffectiveAgainstOther(pokemonType *A,char *name);

/**
 * Print the given pokemon data
 * @param pointer to the pokemon
 */
void printPokemon(Pokemon *poke);

/**
 * Print the given pokemon biological data
 * @param pointer to the biological data pokemon
 */
void printBioData(bioData* poke);

/**
 * Print the given pokemon type
 * @param pointer to the pokemon type
 */
void printPokemonType(pokemonType *poke);

/**
 * Check if the type name exist in the array and return his index
 * @param array ,name and size
 * @return the index or -1
 */
int isTypeNameExist(pokemonType **array,char *name,int size);

/**
 * Check if type name exists in the list effective against me
 * @param array ,name and size
 * @return true or false
 */
bool isTypeNameExistInListAgainstMe(struct pokemonType_t **array,char *name,int size);

/**
 * Check if type name exists in the list effective against other
 * @param array ,name and size
 * @return true or false
 */
bool isTypeNameExistInListAgainstOther(pokemonType **array,char *name,int size);

/**
 * Free the dynamic allocated memory
 * @param pokemon pointer
 */
void freePokemon(Pokemon *poke);

/**
 * Free the dynamic allocated memory
 * @param pokemon pointer
 */
void freeType(pokemonType *type);
status printValuePokemon(element elem);
status freeValuePokemon(element elem);
int equalDataAttack(element,element);
char* getPokemonCategory(element);
element copyPoke(element elem);
int AttackFunction(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond);

#endif //UNTITLED_POKEMON_H
