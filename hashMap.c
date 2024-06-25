#include "hashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_HASHMAP_SIZE 4
#define MAX_LOAD_FACTOR 0.7f

unsigned long dbj2Hash(char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

HashMap *initHM() {
  HashMap *hashMap = (HashMap *)malloc(sizeof(HashMap));

  hashMap->keysSize = INIT_HASHMAP_SIZE;
  hashMap->valuesSize = INIT_HASHMAP_SIZE;

  hashMap->fill = 0;
  hashMap->loadFactor = 0;

  hashMap->keys = calloc(INIT_HASHMAP_SIZE, sizeof(char *));
  hashMap->values = calloc(INIT_HASHMAP_SIZE, sizeof(char *));

  return hashMap;
}

void appendHM(HashMap *hashMap, char key[], char value[]) {

  // TODO: add lower boundary
  if (hashMap->loadFactor > MAX_LOAD_FACTOR)
    resizeHM(hashMap);

  hashMap->keys[hashMap->fill] = calloc(strlen(key) + 1, sizeof(char));
  strncpy(hashMap->keys[hashMap->fill], key, strlen(key));

  // TODO: handle collisions
  unsigned long hashAddress = dbj2Hash(key) % hashMap->valuesSize;
  printf("\n%lu\n", hashAddress);
  hashMap->values[hashAddress] = calloc(strlen(value) + 1, sizeof(char));
  strncpy(hashMap->values[hashAddress], value, strlen(value));

  hashMap->fill++;
  hashMap->loadFactor = hashMap->fill / (float)hashMap->keysSize;
  printHM(hashMap);
}

void resizeHM(HashMap *hashMap) {
  char **keysCache = malloc(hashMap->keysSize * sizeof(hashMap->keys[0]));
  char **valuesCache = malloc(hashMap->valuesSize * sizeof(hashMap->values[0]));

  memcpy(keysCache, hashMap->keys,
         hashMap->keysSize * sizeof(hashMap->keys[0]));

  memcpy(valuesCache, hashMap->values,
         hashMap->valuesSize * sizeof(hashMap->values[0]));

  hashMap->keys = reallocarray(hashMap->keys, hashMap->keysSize << 1,
                               sizeof(hashMap->keys[0]));
  hashMap->values = reallocarray(hashMap->values, hashMap->valuesSize << 1,
                                 sizeof(hashMap->values[0]));
  hashMap->valuesSize = hashMap->valuesSize << 1;

  hashMap->keysSize = hashMap->keysSize << 1;
  rehashHM(hashMap, keysCache, valuesCache);

  hashMap->loadFactor = hashMap->fill / (float)hashMap->keysSize;

  free(keysCache);
  free(valuesCache);
}
// fix this shit below
void rehashHM(HashMap *hashMap, char **keys, char **values) {
  for (int i = 0; i < hashMap->fill; i++) {
    char *key = keys[i];
    unsigned long hashAddressCache =
        dbj2Hash(keys[i]) % hashMap->valuesSize / 2;
    char *value = values[hashAddressCache];

    hashMap->keys[i] = calloc(strlen(key) + 1, sizeof(char));
    strcpy(hashMap->keys[i], key);

    unsigned long hashAddress = dbj2Hash(key) % hashMap->valuesSize;
    hashMap->values[hashAddress] = calloc(strlen(value) + 1, sizeof(char));
    strcpy(hashMap->values[hashAddress], value);
  }
}

void printHM(HashMap *hashMap) {
  printf("\n");
  printf("fill: %d/%d\t", hashMap->fill, hashMap->keysSize);
  printf("keysSize: %d\t", hashMap->keysSize);
  printf("valuesSize: %d\t", hashMap->valuesSize);
  printf("loadFactor: %f\t", hashMap->loadFactor);
  printf("\n{\n");
  for (int i = 0; i < hashMap->fill; i++) {
    printf("\t%s:%s\n", hashMap->keys[i],
           hashMap->values[dbj2Hash(hashMap->keys[i]) % hashMap->valuesSize]);
  }
  printf("}\n");
}
