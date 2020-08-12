/*
 ==============================================================================
 Name        : My Pokedex
 Author      : Samuel Benichou && Izar Chernov
 Version     : 2.0
 Copyright   : BGU ,Read Only
 Description : My Pokedex in C, implements pokemons with their characteristics
 ==============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Pokemon.h"
#include "Defs.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "BattleByCategory.h"

#define Max_Name_lenght 30
#define BufferSize 300

int main(int argc, char *argv[]) {
    int choice;
    int typeSize = atoi(argv[1]);
    int maxCapacities = atoi(argv[2]);
    char *configuration = argv[3];
    char  parsing1[BufferSize],parsing2[BufferSize];
    pokemonType *arrayOfType[typeSize];
    int index1;
    char pokemonName[Max_Name_lenght],pokeType[Max_Name_lenght],pokemonSpecie[Max_Name_lenght];
    int attack;
    double height,weight;
    char* token;
    char* helper1 = token;
    char* helper2 = token;


    int temp1,temp2;

    FILE *file;
    file = fopen (configuration, "r");
    if (file == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%s", parsing1);
    fscanf(file, "%s", parsing1);
    Battle catchThemAll = createBattleByCategory(maxCapacities,typeSize,parsing1,equalDataAttack,copyPoke,freeValuePokemon,getPokemonCategory,AttackFunction,printValuePokemon);
    while ( ! feof(file)){
        if (strcmp(parsing1, "Pokemons") != 0) {
        	helper1 = strtok(parsing1, ",");
        	int i = 0;
        	while(i < typeSize && helper1 != NULL){
        		arrayOfType[i] = pokemonTypeCreation(helper1);
        		helper1 = strtok(NULL, ",");
        		i++;
        	}
            fscanf(file, "%s", parsing1);
            while (strcmp(parsing1, "Pokemons") != 0){
                temp1 = isTypeNameExist(arrayOfType,parsing1,typeSize);
                fscanf(file, "%s", parsing2);
                token = strstr(parsing2, "effective-against-me:");
                if (token != NULL &&  temp1 != -1){
                	helper1 = strstr(token, ":");
                	helper1++;
                	helper2 = strtok(helper1, ",");
                    while (helper2 != NULL && token != NULL){
                        temp2 = isTypeNameExist(arrayOfType,helper2,typeSize);
                        if(isTypeNameExist(arrayOfType[temp1]->effective_against_me,helper2,arrayOfType[temp1]->effectiveAgainstMeCount)==-1)
                        {
                            addTypeOfPokemonToEffectiveAgainstMe(arrayOfType[temp1],arrayOfType[temp2]);
                        }
                        helper2 = strtok(NULL, ",");
                    }
                }
                else {
                    token = strstr(parsing2, "effective-against-other:");
                    if (token != NULL)
                    {
                    	helper1 = strstr(token, ":");
                    	helper1++;
                    	helper2 = strtok(helper1, ",");
                        while (helper2 != NULL && token != NULL) {
                            temp2 = isTypeNameExist(arrayOfType,helper2,typeSize);
                            if(isTypeNameExist(arrayOfType[temp1]->effective_against_other,helper2,arrayOfType[temp1]->effectiveAgainstOtherCount)==-1)
                            {
                                addTypeOfPokemonToEffectiveAgainstOther(arrayOfType[temp1],arrayOfType[temp2]);
                            }
                            helper2 = strtok(NULL, ",");
                        }
                    }
                }
                fscanf(file, "%s", parsing1);
            }
        }
        if (strcmp(parsing1, "Pokemons") == 0) {
            while (fscanf(file,"%s", parsing1) != EOF){
                char name[30],specie[30],typename[30];
                int attackFromFile;
                double weightFromFile,heightFromFile;
                helper1 = strtok(parsing1, ",");
                strcpy(name,helper1);
                helper1 = strtok(NULL, ",");
                strcpy(specie,helper1);
                helper1 = strtok(NULL, ",");
                heightFromFile = atof(helper1);
                helper1 = strtok(NULL, ",");
                weightFromFile = atof(helper1);
                helper1 = strtok(NULL, ",");
                attackFromFile = atoi(helper1);
                helper1 = strtok(NULL, "\n");
                strcpy(typename,helper1);
                temp1 = isTypeNameExist(arrayOfType,typename,typeSize);
                Pokemon *poke = createPokemon(name,specie,arrayOfType[temp1],attackFromFile,heightFromFile,weightFromFile);
                insertObject(catchThemAll,poke);
            }
        }
    }

    fclose (file);


    while (1) {
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons by types\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Insert Pokemon to battles training camp\n");
        printf("4 : Remove stronger Pokemon by type\n");
        printf("5 : Fight\n");
        printf("6 : Exit\n");
        int x = scanf("%d", &choice);
        if (x < 1) {
            char temp;
            scanf("%c", &temp);
            printf("Please choose a valid number.\n");
        }
        if (x > 0){
            switch (choice) {

                case 1:
                    displayObjectsByCategories(catchThemAll);
                    break;

                case 2:
                    for (int i = 0; i < typeSize; ++i) {
                        printPokemonType(arrayOfType[i]);
                    }
                    break;

                case 3:
                    printf("Please enter Pokemon type name:\n");
                    scanf("%s", pokeType);
                    int index = isTypeNameExist(arrayOfType, pokeType, typeSize);
                    if (index != -1) {
                        if (getNumberOfObjectsInCategory(catchThemAll,arrayOfType[index]->types) == maxCapacities){
                            printf("Type at full capacity.\n");
                            break;
                        }
                        printf("Please enter Pokemon name:\n");
                        scanf("%s", pokemonName);
                        printf("Please enter Pokemon species:\n");
                        scanf("%s", pokemonSpecie);
                        printf("Please enter Pokemon height:\n");
                        scanf("%lf", &height);
                        printf("Please enter Pokemon weight:\n");
                        scanf("%lf", &weight);
                        printf("Please enter Pokemon attack:\n");
                        scanf("%d", &attack);
                        Pokemon *poke = createPokemon(pokemonName,pokemonSpecie,arrayOfType[index],attack,height,weight);
                        if (insertObject(catchThemAll,poke) == sucess){
                            printf("The Pokemon was successfully added.\n");
                            printPokemon(poke);
                        }
                    } else
                        printf("Type name doesn't exist.\n");
                    break;

                case 4:
                    printf("Please enter type name:\n");
                    scanf("%s", pokeType);
                    int index1 = isTypeNameExist(arrayOfType, pokeType, typeSize);
                    if (index1 != -1) {
                        element temp = removeMaxByCategory(catchThemAll,pokeType);
                        if (temp != NULL) {
                            printf("the strongest Pokemon was removed:\n");
                            printValuePokemon(temp);
                            freeValuePokemon(temp);
                        }else{
                            printf("There is no Pokemon to remove.\n");
                        }

                    }else{
                        printf("Type name doesn't exist.\n");
                    }
                    break;


                case 5:
                    printf("Please enter Pokemon type name:\n");
                    scanf("%s", pokeType);
                    index = isTypeNameExist(arrayOfType, pokeType, typeSize);
                    if(index == -1){
                        printf("Type name doesn't exist.\n");
                        break;
                    }
                    printf("Please enter Pokemon name:\n");
                    scanf("%s", pokemonName);
                    printf("Please enter Pokemon species:\n");
                    scanf("%s", pokemonSpecie);
                    printf("Please enter Pokemon height:\n");
                    scanf("%lf", &height);
                    printf("Please enter Pokemon weight:\n");
                    scanf("%lf", &weight);
                    printf("Please enter Pokemon attack:\n");
                    scanf("%d", &attack);
                    Pokemon *poke = createPokemon(pokemonName,pokemonSpecie,arrayOfType[index],attack,height,weight);
                    element pokemon = poke;
                    element temp = fight(catchThemAll,pokemon);
                    break;


                case 6:
                    destroyBattleByCategory(catchThemAll);
                    for (int i = typeSize - 1; i >= 0; i--) {
                    	freeType(arrayOfType[i]);
                    }
                    printf("All the memory cleaned and the program is safely closed.\n");
                    return 0;

                default:
                    printf("Please choose a valid number.\n");
            }
        }
    }
}
