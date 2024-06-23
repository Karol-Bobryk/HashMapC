typedef struct {
  unsigned int valuesSize;
  unsigned int keysSize;
  float loadFactor;
  char **values;
  char **keys;
  unsigned int fill;
} HashMap;

unsigned long dbj2Hash(char *);

HashMap *initHM();

void appendHM(HashMap *, char[], char[]);

void printHM(HashMap *);
