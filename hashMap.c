#include "hashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_HASHMAP_SIZE 4

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
  // TODO: handle overloads
  hashMap->keys[hashMap->fill] = calloc(strlen(key) + 1, sizeof(char));
  strncpy(hashMap->keys[hashMap->fill], key, strlen(key));

  // TODO: handle collisions
  unsigned long hashAddress = dbj2Hash(key) % hashMap->valuesSize;

  hashMap->values[hashAddress] = calloc(strlen(value) + 1, sizeof(char));
  strncpy(hashMap->values[hashAddress], value, strlen(value));

  hashMap->fill++;
  hashMap->loadFactor = hashMap->fill / (float)hashMap->keysSize;
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
