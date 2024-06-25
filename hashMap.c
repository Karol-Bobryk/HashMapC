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

  hashMap->fieldsSize = INIT_HASHMAP_SIZE;

  hashMap->fill = 0;
  hashMap->loadFactor = 0;

  hashMap->fields = calloc(INIT_HASHMAP_SIZE, sizeof(HashField *));

  return hashMap;
}

void appendHM(HashMap *hashMap, char key[], char value[]) {

  // TODO: add lower boundary
  if (hashMap->loadFactor > MAX_LOAD_FACTOR)
    resizeHM(hashMap);

  HashField *newHF = populateHF(key, value);

  unsigned long hashAddress = dbj2Hash(key) % hashMap->fieldsSize;
  printf("\n%lu\n", hashAddress);
  hashMap->fields[hashAddress] = newHF;
  hashMap->fill++;
  hashMap->loadFactor = hashMap->fill / (float)hashMap->fieldsSize;
  // TODO: handle collisions
}

HashField *populateHF(char key[], char value[]) {
  HashField *newHF = calloc(1, sizeof(HashField));

  newHF->key = calloc(strlen(key) + 1, sizeof(key[0]));
  newHF->value = calloc(strlen(value) + 1, sizeof(value[0]));

  memcpy(newHF->key, key, strlen(key) + 1);

  memcpy(newHF->value, value, strlen(value) + 1);
  return newHF;
}

void resizeHM(HashMap *hashMap) {}
// fix this shit below
void rehashHM(HashMap *hashMap, char **keys, char **values) {}
// check print function for errors
void printHM(HashMap *hashMap) {
  printf("\n");
  printf("fill: %d/%d\t", hashMap->fill, hashMap->fieldsSize);
  printf("fieldsSize: %d\t", hashMap->fieldsSize);
  printf("loadFactor: %f\t", hashMap->loadFactor);
  printf("\n{\n");
  for (int i = 0; i < hashMap->fill; i++) {
    if (hashMap->fields[i] != 0)
      printf("\t%s:%s\n", hashMap->fields[i]->key, hashMap->fields[i]->value);
  }
  printf("}\n");
}
