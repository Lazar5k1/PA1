#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(){
    char **dictionary; //to store array of dynamically allocated strings for breeds types (e.g., {"Ragdoll","Siamese", "Maincoone"})
    int breedCount; //number of breed types
    int kennelCount; //number of kennels
    CatStore* catStore; //store of cats

    dictionary = readBreeds(&breedCount); //array of breeds
    scanf("%d", &kennelCount); //inputs num of kennels
    catStore = createStore(kennelCount, breedCount, dictionary); //calls a bunch of functions and makes a store
    // printCatStore(catStore, breedCount, dictionary); //debug function for checking input

    freeBreeds(dictionary, breedCount); //frees all memory associated with dictionary
    freeStore(kennelCount, catStore); //frees all memory associated with catStore

    return 0;
}

void printCatStore(CatStore *catStore, int breedCount, char **dictionary){ //prints out all input before query section
    printf("%d\n", breedCount);
    for(int i = 0; i < breedCount; i++){
        printf("%s\n", dictionary[i]);
    }
    printf("%d\n", catStore->numKenels);
    for(int i = 0; i < catStore->numKenels; i++){
        for(int j = 0; j < breedCount; j++){
            printf("%d ", catStore->capacities[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < catStore->numKenels; i++){
        printf("%s %d\n", catStore->kennels[i].location, catStore->kennels[i].occupancy);
        for(int j = 0; j < catStore->kennels[i].occupancy; j++){
            printf("%s %d %.2f %s\n", catStore->kennels[i].cats[j]->name, catStore->kennels[i].cats[j]->age, catStore->kennels[i].cats[j]->weight, catStore->kennels[i].cats[j]->breed);
        }
    }
}

char ** readBreeds(int *count){ //takes input from first couple of lines, creates dictionary of breeds and allocates its memory
    scanf("%d", count);
    char **breeds = (char**)malloc((*count) * sizeof(char*));
    char tempBreed[26];
    
    for(int i = 0; i < *count; i++){
        scanf("%s", tempBreed);
        breeds[i] = (char*)malloc((strlen(tempBreed) + 1) * sizeof(char));
        strcpy(breeds[i], tempBreed);
    }
    return breeds;
}

char* getCharPtrByBreed(char **dictionary, char *breedName, int breedCount){ //returns breed index from dictionary (used in create cat function as to not anger ahmed our beloved by not allocating memory)
    for(int i = 0; i < breedCount; i++){
        if(strcmp(breedName, dictionary[i]) == 0){
            return dictionary[i];
        }
    }
    return NULL;
}

CatStore *createStore(int kennelCount, int breedCount, char ** dictionary){ //master function that branches off into other mini functions in a chain reaction. Creates a CatStore and takes input for all of its values and allocates memory accordingly
    CatStore *catStore = (CatStore*)malloc(sizeof(CatStore)); //allocates memory for catStore

    catStore->capacities = (int**)malloc(kennelCount * sizeof(int*)); //allocates and reads input into catStore->capacities
    for(int i = 0; i < kennelCount; i++){
        catStore->capacities[i] = (int*)malloc(breedCount * sizeof(int));
        for(int j = 0; j < breedCount; j++){

            scanf("%d", &catStore->capacities[i][j]);
        }
    }
    catStore->numKenels = kennelCount; //inputs kennel count into numkennels
    catStore->kennels = createKennels(catStore->capacities, kennelCount, breedCount, dictionary); //creates, allocates, and reads input into an array of kennels. Then stores them in catStore.

    return catStore;
}

Kennel* createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary){ //creates the kennels within the store. calls upon createCats() to make cats
    Kennel *kennel = (Kennel*)malloc(kennelCount * sizeof(Kennel));
    char tempLocation[26];

    for(int i = 0; i < kennelCount; i++){
        scanf("%s", tempLocation);
        kennel[i].location = (char*)malloc((strlen(tempLocation)+ 1) * sizeof(char));
        strcpy(kennel[i].location, tempLocation);
        scanf("%d", &kennel[i].occupancy);
        kennel[i].cats = createCats(dictionary, breedCount, kennel[i].occupancy); //creates, allocates, and reads input into an array of cats. Then stores them in kennel.
        kennel[i].maxCapacity = 0;
        for(int j = 0; j < breedCount; j++){
            kennel[i].maxCapacity += constraints[i][j];
        }
    }

    return kennel;
}

Cat **createCats(char **dictionary, int breedCount, int count){ //makes cats. calls createSingleCat to make a cat.
    Cat **catArr = (Cat**)malloc(count * sizeof(Cat*));
    
    for(int i = 0; i < count; i++){
        catArr[i] = createSingleCat(dictionary, breedCount);
    }

    return catArr;
}

Cat* createSingleCat(char **dictionary, int breedCount){ //makes a cat.
    Cat *cat = (Cat*)malloc(sizeof(Cat));
    char tempName[26];
    char tempBreed[26];

    scanf("%s", tempName);
    cat->name = (char*)malloc((strlen(tempName) + 1)* sizeof(char));
    strcpy(cat->name, tempName);
    scanf("%d", &cat->age);
    scanf("%f", &cat->weight);
    scanf("%s", tempBreed);
    cat->breed = getCharPtrByBreed(dictionary, tempBreed, breedCount); //bypasses allocating memory by using dictionary
    cat->status = 2;

    return cat;
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

void freeBreeds(char **dictionary, int breedCount){ //frees dictionary and breed memory
    for(int i = 0; i < breedCount; i++){
        free(dictionary[i]);
    }
    free(dictionary);
}

void freeStore(int count, CatStore *store){ //frees all memory used in store
    for(int i = 0; i < count; i++){
        for(int j = 0; j < store->kennels[i].occupancy; j++){
            free(store->kennels[i].cats[j]->name);
            free(store->kennels[i].cats[j]);
        }
        free(store->kennels[i].cats);
        free(store->kennels[i].location);
    }
    free(store->kennels);
    for(int i = 0; i < count; i++){
        free(store->capacities[i]);
    }
    free(store->capacities);
    free(store);
}