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

void appendHM(HashMap *, char[], char[]);

HashField *populateHF(char[], char[]);

void resizeHM(HashMap *);

void rehashHM(HashMap *, HashField *[], unsigned long);

void printHM(HashMap *);
