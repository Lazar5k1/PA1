#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char STATUS_CAT[3][20] = {"ADOPTED", "PENDING", "AVAILABLE"};

typedef struct Cat{
 char *name; // dynamically allocated space for the name without wasting space
 int age; // specifies the age of the cat
 float weight; // stores the decimal value in weight for this specific cat
 char *breed; //points to an already allocated breed string (Ragdoll, Siamese, Maincoone, etc..). No malloc/calloc for this property
 int status; //specifies if a cat is adopted, pending, or available, ranges from 0 to 2, initially set to available for newly added cats
} Cat;

typedef struct Kennel {
 char *location; // dynamically allocated space for the location without wasting space
int occupancy; // stores the current number of cats in the kennel
 Cat **cats; // dynamically allocated array of pointers to Cats that reside in the kennel
 int maxCapacity; // specifies the max cap to
} Kennel;

typedef struct CatStore {
 int **capacities; //dynamically allocated double int array stores the breeds constraints for all kennels
 int numKenels; //specifies the total number of kennels this store owns
 Kennel *kennels; // dynamically allocated array of kennels
} CatStore;


char ** readBreeds(int *count);
char* getCharPtrByBreed(char **dictionary, char *breedName, int breedCount);

CatStore *createStore(int kennelCount, int breedCount, char ** dictionary);
Kennel* createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary);
Cat **createCats(char **dictionary, int breedCount, int count);
Cat* createSingleCat(char **dictionary, int breedCount);
int canMoveTo(CatStore *s, char *location, char *breed, char **dictionary, int breedCount);
Kennel *getKennelByCat(CatStore *s, Cat *cat);
int getCatPosi(Kennel *home, Cat *cat);
Cat *getCatByName(CatStore *s, char *catName);
void removeCatFromKennel(Kennel *k, Cat *cat);
void runQueries(CatStore *s, char **dictionary, int breedCount, int numQueries);
void freeBreeds(char **dictionary, int breedCount);
void freeStore(int count, CatStore *store);

//custom functions
void printCatStore(CatStore *catStore, int breedCount, char **dictionary); //old function for testing if input was valid
void printByBreed(CatStore *s, char *breed);
void updateStatus(CatStore *s, int status, char *name);
void moveCat(CatStore *s, char *name, char *location, char **dictionary, int breedCount);


int main(){
    char **dictionary; //to store array of dynamically allocated strings for breeds types (e.g., {"Ragdoll","Siamese", "Maincoone"})
    int breedCount; //number of breed types
    int kennelCount; //number of kennels
    CatStore* store; //store of cats

    dictionary = readBreeds(&breedCount); //array of breeds
    scanf("%d", &kennelCount); //inputs num of kennels
    store = createStore(kennelCount, breedCount, dictionary); //calls a bunch of functions and makes a store
    // printCatStore(store, breedCount, dictionary); //debug function for checking input

    int numQueries;
    scanf("%d", &numQueries);
    runQueries(store, dictionary, breedCount, numQueries);

    freeBreeds(dictionary, breedCount); //frees all memory associated with dictionary
    freeStore(kennelCount, store); //frees all memory associated with store

    return 0;
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

char* getCharPtrByBreed(char **dictionary, char *breedName, int breedCount){ //returns breed index from dictionary
    for(int i = 0; i < breedCount; i++){
        if(strcmp(breedName, dictionary[i]) == 0){
            return dictionary[i];
        }
    }
    return NULL;
}

CatStore *createStore(int kennelCount, int breedCount, char ** dictionary){ //master function that branches off into other mini functions in a chain reaction. Creates a CatStore and takes input for all of its values and allocates memory accordingly
    CatStore *store = (CatStore*)malloc(sizeof(CatStore)); //allocates memory for store

    store->capacities = (int**)malloc(kennelCount * sizeof(int*)); //allocates and reads input into store->capacities
    for(int i = 0; i < kennelCount; i++){
        store->capacities[i] = (int*)malloc(breedCount * sizeof(int));
        for(int j = 0; j < breedCount; j++){

            scanf("%d", &store->capacities[i][j]);
        }
    }
    store->numKenels = kennelCount; //inputs kennel count into numkennels
    store->kennels = createKennels(store->capacities, kennelCount, breedCount, dictionary); //creates, allocates, and reads input into an array of kennels. Then stores them in store.

    return store;
}

Kennel* createKennels(int **constraints, int kennelCount, int breedCount, char **dictionary){ //creates the kennels within the store. calls upon createCats() to make cats
    Kennel *kennel = (Kennel*)malloc(kennelCount * sizeof(Kennel));
    char tempLocation[26];

    for(int i = 0; i < kennelCount; i++){
        scanf("%s", tempLocation);
        kennel[i].location = (char*)malloc((strlen(tempLocation)+ 1) * sizeof(char));
        strcpy(kennel[i].location, tempLocation);
        scanf("%d", &kennel[i].occupancy);
        kennel[i].maxCapacity = 0;
        for(int j = 0; j < breedCount; j++){
            kennel[i].maxCapacity += constraints[i][j];
        }
        if(kennel[i].occupancy == 0){
            kennel[i].cats = NULL;
        }
        else{
            kennel[i].cats = createCats(dictionary, breedCount, kennel[i].occupancy); //creates, allocates, and reads input into an array of cats. Then stores them in kennel.
        }
    }

    return kennel;
}

Cat **createCats(char **dictionary, int breedCount, int count){ //makes cats. calls createSingleCat to make a cat.
    Cat **catArr;
    
    if(count == 0){
        catArr = NULL;
    }
    else{
        catArr = (Cat**)malloc(count * sizeof(Cat*));
        for(int i = 0; i < count; i++){
            catArr[i] = createSingleCat(dictionary, breedCount);
        }
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

int canMoveTo(CatStore *s, char *location, char *breed, char **dictionary, int breedCount){ //returns 1 if chosen breed can be moved into chosen location, 0 if not.
    for(int i = 0; i < s->numKenels; i++){
        if(strcmp(location, s->kennels[i].location) == 0){
            if(s->kennels[i].occupancy >= s->kennels[i].maxCapacity){ //return if kennel is full
                return 0;
            }

            int totalBreed = 0;
            for(int j = 0; j < s->kennels[i].occupancy; j++){ //checks how many of each cat is the same as breed
                if(strcmp(breed, s->kennels[i].cats[j]->breed) == 0){
                    totalBreed++;
                }
            }
            
            int breedIndex = -1;
            for(int j = 0; j < breedCount; j++){ //finds breed index in capacities
                if(strcmp(breed, dictionary[j]) == 0){
                    breedIndex = j;
                    break;
                }
            }
            if(totalBreed < s->capacities[i][breedIndex]){ //can fit or not
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    return 0; //default can't find location
}

Kennel *getKennelByCat(CatStore *s, Cat *cat){
    for(int i =0; i < s->numKenels; i++){
        for(int j = 0; j < s->kennels[i].occupancy; j++){
            if(cat == s->kennels[i].cats[j]){
                return &s->kennels[i];
            }
        }
    }
    return NULL;
}

int getCatPosi(Kennel *home, Cat *cat){
    for(int i =0; i < home->occupancy; i++){
        if(cat == home->cats[i]){
            return i;
        }
    }
    return -1;
}

Cat *getCatByName(CatStore *s, char *catName){
    for(int i = 0; i < s->numKenels; i++){
        for(int j = 0; j < s->kennels[i].occupancy; j++){
            if(strcmp(catName, s->kennels[i].cats[j]->name) == 0){
                return s->kennels[i].cats[j];
            }
        }
    }
    return NULL;
}

void removeCatFromKennel(Kennel *k, Cat *cat){
    int catPos = getCatPosi(k, cat);

    if(catPos == -1){
        return;
    }
    for(int i = catPos; i < k->occupancy - 1; i++){
        k->cats[i] = k->cats[i + 1];
    }
    k->occupancy--;
}

void runQueries(CatStore *s, char **dictionary, int breedCount, int numQueries){
    int type;
    char breed[26];
    int status;
    char name[26];
    char location[26];

    for(int i = 0; i < numQueries; i++){
        scanf("%d", &type);
        if(type == 1){
            scanf("%s", breed);
            printByBreed(s, breed);
        }
        else if(type == 2){
            scanf("%d %s", &status, name);
            updateStatus(s, status, name);
        }
        else if(type == 3){
            scanf("%s %s", name, location);
            moveCat(s, name, location, dictionary, breedCount);
        }
    }
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

void printCatStore(CatStore *store, int breedCount, char **dictionary){ //prints out all input before query section
    printf("%d\n", breedCount);
    for(int i = 0; i < breedCount; i++){
        printf("%s\n", dictionary[i]);
    }
    printf("%d\n", store->numKenels);
    for(int i = 0; i < store->numKenels; i++){
        for(int j = 0; j < breedCount; j++){
            printf("%d ", store->capacities[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < store->numKenels; i++){
        printf("%s %d\n", store->kennels[i].location, store->kennels[i].occupancy);
        for(int j = 0; j < store->kennels[i].occupancy; j++){
            printf("%s %d %.2f %s\n", store->kennels[i].cats[j]->name, store->kennels[i].cats[j]->age, store->kennels[i].cats[j]->weight, store->kennels[i].cats[j]->breed);
        }
    }
}

void printByBreed(CatStore *s, char *breed){ //moves through every cat, asks if it is selected breed, if so then print out its content
    int exists = 0;
    
    for(int i =0; i < s->numKenels; i++){
        for(int j = 0; j < s->kennels[i].occupancy; j++){
            if(strcmp(breed, s->kennels[i].cats[j]->breed) == 0){
                printf("%s %.2f %d %s %s\n", s->kennels[i].cats[j]->name, s->kennels[i].cats[j]->weight, s->kennels[i].cats[j]->age, s->kennels[i].location, STATUS_CAT[s->kennels[i].cats[j]->status]);
                exists = 1;
            }
        }
    }
    if(!exists){
        printf("No cat with breed %s\n", breed);
    }
}

void updateStatus(CatStore *s, int status, char *name){
    Cat *cat = getCatByName(s, name);
    Kennel *k = getKennelByCat(s, cat);
    if(status == 0){
        removeCatFromKennel(k, cat);
        free(cat->name);
        free(cat);
        cat = NULL;
    }
    else{
        cat->status = status;
    }
    printf("%s is now %s!\n", name, STATUS_CAT[status]);
}

void moveCat(CatStore *s, char *name, char *location, char **dictionary, int breedCount){
    Cat *cat = getCatByName(s, name);
    Kennel *kennel = getKennelByCat(s, cat);

    if(canMoveTo(s, location, cat->breed, dictionary, breedCount)){
        removeCatFromKennel(kennel, cat);
        for(int i =0; i < s->numKenels; i++){
            if(strcmp(location, s->kennels[i].location) == 0){
                Cat **temp = malloc((s->kennels[i].occupancy + 1) * sizeof(Cat*));
                for(int j = 0; j < s->kennels[i].occupancy; j++){
                    temp[j] = s->kennels[i].cats[j];
                }
                temp[s->kennels[i].occupancy] = cat;
                free(s->kennels[i].cats);
                s->kennels[i].cats = temp;
                s->kennels[i].occupancy++;
                printf("%s moved successfully to %s\n", name, location);
                break;
            }
        }
    }
    else{
        printf("%s cannot take a %s cat!\n", location, cat->breed);
    }
}