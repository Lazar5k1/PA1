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