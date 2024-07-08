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

unsigned long HashDbj2(char *);

HashMap *HMInit();

int HMAppend(HashMap *, char[], char[]);

HashField *HFPopulate(char[], char[]);

int linearProbing(HashMap *, unsigned long, char[]);

int HMResize(HashMap *);

int HMRehash(HashMap *, HashField *[], unsigned long);

char *HMRead(HashMap *, char[]);

int HMFree(HashMap *);

int HMPrint(HashMap *);
