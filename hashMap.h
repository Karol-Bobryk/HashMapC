typedef struct {
  char *key;
  char *value;

} HashField;

typedef struct {
  unsigned int fieldsSize;
  float loadFactor;
  HashField **fields;
  unsigned int fill;
} HashMap;

unsigned long dbj2Hash(char *);

HashMap *initHM();

int appendHM(HashMap *, char[], char[]);

HashField *populateHF(char[], char[]);

int linearProbing(HashMap *, unsigned long);

int resizeHM(HashMap *);

int rehashHM(HashMap *, HashField *[], unsigned long);

char *readHM(HashMap *, char[]);

int printHM(HashMap *);
