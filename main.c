#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(){
    char **dictionary; //to store array of dynamically allocated strings for breeds types (e.g., {"Ragdoll","Siamese", "Maincoone"})
    int breedCount; //number of breed types
    dictionary = readBreeds(&breedCount);



    return 0;
}

char ** readBreeds(int *count){
    char **breeds = (char*)malloc((*count) * sizeof(char));
    scanf("%d", count);
    for(int i = 0; i < *count; i++){
        scanf("%s", breeds[i]);
    }
    return breeds;
}

char* getCharPtrByBreed(char **dictionary, char *breedName, int breedCount){
    for(int i = 0; i < breedCount; i++){
        if(strcmp(breedName, *dictionary[i]) == 0){
            return *dictionary[i];
        }
    }
    return NULL;
}

CatStore *createStore(int kennelCount, int breedCount, char ** dictionary){
    CatStore *store = (CatStore*)malloc(sizeof(CatStore));
    
}

Kennel* createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary){

}

Cat **createCats(char **dictionary, int breedCount, int count){

}

Cat* createSingleCat(char **dictionary, int breedCount){

}

int canMoveTo(CatStore *s, char *location, char *breed, char **dictionary, int breedCount){

}

Kennel *getKennelByCat(CatStore *s, Cat *cat){

}

int getCatPosi(Kennel *home, Cat *cat){

}

Cat *getCatByName(CatStore *s, char *catName){

}

void removeCatFromKennel(Kennel *k, Cat *cat){

}

void runQueries(CatStore *s, char **dictionary, int breedCount, int numQueries){

}

void freeBreeds(char **dictionary, int breedCount){

}

void freeStore(int count, CatStore *store){

}