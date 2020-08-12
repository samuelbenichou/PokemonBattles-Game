#include "Pokemon.h"

Pokemon* createPokemon(char *name,char *specie, struct pokemonType_t *type,int num1,double num2,double num3){
    if (name == NULL || specie == NULL || type == NULL )
        return NULL;
    Pokemon *poke = (Pokemon*) malloc(sizeof(struct Pokemon_t));
    if (poke == NULL) {
        exit(1);
    }
    poke->bioData = PokemonBilogicalDataCreation(num2,num3,num1);
    poke->pokemonType = type;
    poke->name = (char*) malloc(strlen(name)+1);
    if (poke->name == NULL)
        exit(1);
    poke->specie = (char*) malloc(strlen(specie)+1);
    if (poke->specie == NULL)
        exit(1);
    strcpy(poke->name,name);
    strcpy(poke->specie,specie);
    poke->pokemonType->size = poke->pokemonType->size + 1;
    return poke;
}

pokemonType* pokemonTypeCreation(char *name){
    if (name == NULL)
        return NULL;
    pokemonType *pokemon = (struct pokemonType_t*) malloc(sizeof(struct pokemonType_t));
    if (pokemon == NULL) {
        exit(1);
    }
    pokemon->size = 0;
    pokemon->types = (char*) malloc(strlen(name)+1);
    if (pokemon->types == NULL)
        exit(1);
    strcpy(pokemon->types,name);
    pokemon->effectiveAgainstMeCount = 0;
    pokemon->effectiveAgainstOtherCount = 0;
    pokemon->effective_against_me = NULL;
    pokemon->effective_against_other = NULL;
    return pokemon;
}

bioData* PokemonBilogicalDataCreation(double height, double weight,int attack){
    struct bioData_t *new = (struct bioData_t*) malloc(sizeof(struct bioData_t));
    if (new == NULL) {
        exit(1);
    }
    new->height = height;
    new->weight = weight;
    new->attack = attack;
    return new;
}

status addTypeOfPokemonToEffectiveAgainstMe(pokemonType *A,pokemonType *B){
    if (A == NULL || B == NULL)
        return failure;
    pokemonType *poke = B;
    if (A->effectiveAgainstMeCount == 0){
        A->effective_against_me = (struct pokemonType_t**) malloc(sizeof(struct pokemonType_t*));
        if (A->effective_against_me == NULL) {
            exit(1);
        }
        A->effective_against_me[A->effectiveAgainstMeCount] = poke;
    }else{ //effectiveAgainstMeCount>0
        A->effective_against_me = (struct pokemonType_t**) realloc(A->effective_against_me, sizeof(struct pokemonType_t*)*(A->effectiveAgainstMeCount+1));//
        if (A->effective_against_me == NULL) {
            exit(1);
        }
        A->effective_against_me[A->effectiveAgainstMeCount] = poke;
    }
    A->effectiveAgainstMeCount++;
    return sucess;
}

status addTypeOfPokemonToEffectiveAgainstOther(pokemonType *A,pokemonType *B){
    if (A == NULL || B == NULL)
        return failure;
    pokemonType *poke = B;
    if (A->effectiveAgainstOtherCount == 0){
        A->effective_against_other = (struct pokemonType_t**) malloc(sizeof(struct pokemonType_t*));
        if (A->effective_against_other == NULL) {
            exit(1);
        }
        A->effective_against_other[A->effectiveAgainstOtherCount] = poke;
    }else{ //effectiveAgainstOtherCount > 0
        A->effective_against_other = (struct pokemonType_t**) realloc(A->effective_against_other, sizeof(struct pokemonType_t*)*(A->effectiveAgainstOtherCount+1));
        if (A->effective_against_other == NULL) {
            exit(1);
        }
        A->effective_against_other[A->effectiveAgainstOtherCount] = poke;
    }
    A->effectiveAgainstOtherCount++;
    return sucess;
}

status delTypeOfPokemonToEffectiveAgainstMe(pokemonType *A,char *name){
    if (A == NULL || name == NULL)
        return failure;

    for (int i = 0; i < A->effectiveAgainstMeCount; ++i) {
        if (strcmp(name,A->effective_against_me[i]->types) == 0) {
            int j = 0;
            for (j = i+1; j < A->effectiveAgainstMeCount; ++j) {
                A->effective_against_me[i] = A->effective_against_me[j];
                i++;
            }
            if (j == 1){
                free(A->effective_against_me);
                A->effective_against_me = NULL;
                A->effectiveAgainstMeCount--;
            }
            else{
                A->effective_against_me = (struct pokemonType_t**) realloc(A->effective_against_me, sizeof(struct pokemonType_t*)*(A->effectiveAgainstMeCount-1));
                A->effectiveAgainstMeCount = A->effectiveAgainstMeCount - 1;
            }
            return sucess;
        }
    }
    return failure;
}

status delTypeOfPokemonToEffectiveAgainstOther(pokemonType *A,char *name){
    if (A == NULL || name == NULL)
        return failure;

    for (int i = 0; i < A->effectiveAgainstOtherCount; ++i) {
        if (strcmp(name,A->effective_against_other[i]->types) == 0) {
            int j = 0;
            for (j = i+1; j < A->effectiveAgainstOtherCount; ++j) {
                A->effective_against_other[i] = A->effective_against_other[j];
                i++;
            }
            if (j == 1){
                free(A->effective_against_other);
                A->effective_against_other = NULL;
                A->effectiveAgainstOtherCount--;
            }
            else{
                A->effective_against_other = realloc(A->effective_against_other, sizeof(struct pokemonType_t*)*(A->effectiveAgainstOtherCount-1));
                A->effectiveAgainstOtherCount = A->effectiveAgainstOtherCount - 1;
            }
            return sucess;
        }
    }
    return failure;
}

void printPokemon(Pokemon *poke){
    if (poke != NULL){
        printf("%s :\n",poke->name);
        printf("%s, %s Type.\n",poke->specie,poke->pokemonType->types);
        printBioData(poke->bioData);
    }
}

void printBioData(bioData *poke){
    if (poke != NULL){
        printf("Height: %.2f m    Weight: %.2f kg    Attack: %d \n\n"
                ,poke->height,poke->weight,poke->attack);
    }
}

void printPokemonType(pokemonType *poke){
    if(poke != NULL){
        printf("Type %s -- %d pokemons\n",poke->types,poke->size);

        if (poke->effectiveAgainstMeCount > 0) {
            printf("\tThese types are super-effective against %s:", poke->types);
            for (int i = 0; i < poke->effectiveAgainstMeCount; ++i) {
                if (i == poke->effectiveAgainstMeCount - 1) {
                    printf("%s \n", poke->effective_against_me[i]->types);
                }
                else {
                    printf("%s ,",poke->effective_against_me[i]->types);
                }
            }
        }
        if (poke->effectiveAgainstOtherCount > 0) {
            printf("\t%s moves are super-effective against:",poke->types);
            for (int j = 0; j < poke->effectiveAgainstOtherCount; ++j) {
                if (j == poke->effectiveAgainstOtherCount - 1) {
                    printf("%s \n\n",poke->effective_against_other[j]->types);
                }
                else {
                    printf("%s ,",poke->effective_against_other[j]->types);
                }
            }
        }else
            printf("\n");
    }
}

int isTypeNameExist(pokemonType **array,char *name,int size){
    int res = -1;
    for (int i = 0; i < size; ++i) {
        if (strcmp((array[i])->types,name) == 0)
            return i;
    }
    return res;
}

bool isTypeNameExistInListAgainstMe(struct pokemonType_t **array,char *name,int size){
    for (int i = 0; i < size; ++i) {
        if (strcmp(array[i]->types,name) == 0)
            return true;
    }
    return false;
}

bool isTypeNameExistInListAgainstOther(pokemonType **array,char *name,int size){
    for (int i = 0; i < size; ++i) {
        if (strcmp(array[i]->types,name) == 0)
            return true;
    }
    return false;
}

void freePokemon(Pokemon *poke)
{
    free(poke->bioData);
    free(poke->specie);
    free(poke->name);
    free(poke);
}

void freeType(pokemonType *type)
{
    free(type->effective_against_me);
    free(type->effective_against_other);
    free(type->types);
    free(type);
}

status printValuePokemon(element elem){
    Pokemon *poke = (Pokemon*)elem;
    if (poke == NULL) return failure;

    printPokemon(poke);
    return sucess;
}

status freeValuePokemon(element elem){
    Pokemon *poke = (Pokemon*)elem;
    if (poke == NULL) return failure;

    poke->pokemonType->size--;
    freePokemon(poke);
    return sucess;
}

int equalDataAttack(element elem1,element elem2){
    Pokemon *poke1 = (Pokemon*)elem1;
    Pokemon *poke2 = (Pokemon*)elem2;

    if (poke1->bioData->attack == poke2->bioData->attack) return 0;
    else if (poke1->bioData->attack < poke2->bioData->attack) return -1;
    else return 1;
}

char* getPokemonCategory(element elem){
    Pokemon *poke = (Pokemon*)elem;
    return poke->pokemonType->types;
}

int AttackFunction(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond){
    Pokemon *poke1 = (Pokemon*)firstElem;
    Pokemon *poke2 = (Pokemon*)secondElem;
    if (poke1 == NULL || poke2 == NULL){
        return -1000;
    }
    int first = 0;
    int second = 0;
    int count = -1000;
    if(strcmp(poke1->pokemonType->types,poke2->pokemonType->types) == 0) {
        *attackFirst = poke1->bioData->attack;
        *attackSecond = poke2->bioData->attack;
        return poke1->bioData->attack - poke2->bioData->attack;
    }else{
        if(isTypeNameExistInListAgainstMe(poke1->pokemonType->effective_against_me,poke2->pokemonType->types,poke1->pokemonType->effectiveAgainstMeCount)){
            first = poke1->bioData->attack-10;
            second = poke2->bioData->attack;
            if(first - second > count){
                *attackFirst = first;
                *attackSecond = second;
                count = first - second;
            }
        }
        if(isTypeNameExistInListAgainstOther(poke2->pokemonType->effective_against_other,poke1->pokemonType->types,poke2->pokemonType->effectiveAgainstOtherCount)){
            first = poke1->bioData->attack-10;
            second = poke2->bioData->attack;
            if(first - second > count){
                *attackFirst = first;
                *attackSecond = second;
                count = first - second;
            }
        }
        if(isTypeNameExistInListAgainstMe(poke2->pokemonType->effective_against_me,poke1->pokemonType->types,poke2->pokemonType->effectiveAgainstMeCount)){
            first = poke1->bioData->attack;
            second = poke2->bioData->attack-10;
            if(first - second > count){
                *attackFirst = first;
                *attackSecond = second;
                count = first - second;
            }
        }
        if(isTypeNameExistInListAgainstOther(poke1->pokemonType->effective_against_other,poke2->pokemonType->types,poke1->pokemonType->effectiveAgainstOtherCount)){
            first = poke1->bioData->attack;
            second = poke2->bioData->attack-10;
            if(first - second > count){
                *attackFirst = first;
                *attackSecond = second;
                count = first - second;
            }
        }
        if(isTypeNameExistInListAgainstMe(poke1->pokemonType->effective_against_me,poke2->pokemonType->types,poke1->pokemonType->effectiveAgainstMeCount)== false &&
           isTypeNameExistInListAgainstOther(poke2->pokemonType->effective_against_other,poke1->pokemonType->types,poke2->pokemonType->effectiveAgainstOtherCount)==false
           && isTypeNameExistInListAgainstMe(poke2->pokemonType->effective_against_me,poke1->pokemonType->types,poke2->pokemonType->effectiveAgainstMeCount)==false &&
           isTypeNameExistInListAgainstOther(poke1->pokemonType->effective_against_other,poke2->pokemonType->types,poke1->pokemonType->effectiveAgainstOtherCount)==false){
            first = poke1->bioData->attack;
            second = poke2->bioData->attack;
            if(first - second > count){
                *attackFirst = first;
                *attackSecond = second;
                count = first - second;
            }
        }
        if(count == -1000){
            *attackFirst = poke1->bioData->attack;
            *attackSecond = poke2->bioData->attack;
        }
    }
    return count;
}


element copyPoke(element elem){
    return elem;
}

