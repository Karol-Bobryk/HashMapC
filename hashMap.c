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
  if (hashMap == NULL) {
    free(hashMap);
    return NULL;
  }

  hashMap->fieldsSize = INIT_HASHMAP_SIZE;

  hashMap->fill = 0;
  hashMap->loadFactor = 0;

  hashMap->fields = calloc(INIT_HASHMAP_SIZE, sizeof(HashField *));
  if (hashMap->fields == NULL) {
    free(hashMap->fields);
    return NULL;
  }

  return hashMap;
}

int appendHM(HashMap *hashMap, char key[], char value[]) {
  if (hashMap == NULL)
    return -1;
  if (key == NULL)
    return -1;
  if (value == NULL)
    return -1;

  // TODO: add lower boundary
  if (hashMap->loadFactor >= MAX_LOAD_FACTOR) {
    if (resizeHM(hashMap) < 0)
      return -1;
  }

  HashField *newHF = populateHF(key, value);

  unsigned long hashAddress = dbj2Hash(key) % hashMap->fieldsSize;
  if (hashMap->fields[hashAddress] == NULL)
    hashMap->fields[hashAddress] = newHF;
  else if ((hashAddress = linearProbing(hashMap, hashAddress)) < 0)
    return -1;

  hashMap->fields[hashAddress] = newHF;
  hashMap->fill++;
  hashMap->loadFactor = hashMap->fill / (float)hashMap->fieldsSize;

  return 0;
  // TODO: handle collisions
}

HashField *populateHF(char key[], char value[]) {
  if (key == NULL)
    return NULL;
  if (value == NULL)
    return NULL;

  HashField *newHF = calloc(1, sizeof(HashField));
  if (newHF == NULL) {
    free(newHF);
    return NULL;
  }
  newHF->key = calloc(strlen(key) + 1, sizeof(key[0]));
  newHF->value = calloc(strlen(value) + 1, sizeof(value[0]));
  if (key == NULL || value == NULL) {
    free(newHF->key);
    free(newHF->value);
    return NULL;
  }
  memcpy(newHF->key, key, strlen(key) + 1);

  memcpy(newHF->value, value, strlen(value) + 1);
  return newHF;
}

int linearProbing(HashMap *hashMap, unsigned long hashAddress) {
  if (hashMap == NULL)
    return -1;
  if (hashAddress < 0)
    return -1;

  unsigned int i = hashAddress + 1;
  unsigned int probingAddress = i % hashMap->fieldsSize;

  while (probingAddress != hashAddress) {
    if (hashMap->fields[probingAddress] == NULL)
      return probingAddress;
    i++;
    probingAddress = i % hashMap->fieldsSize;
  }
  // TODO: Change error handling to enum style
  return -1;
};

int resizeHM(HashMap *hashMap) {

  if (hashMap == NULL)
    return -1;

  unsigned long prevSizeCache = hashMap->fieldsSize;
  hashMap->fieldsSize = hashMap->fieldsSize << 1;

  HashField **fieldsCache = calloc(hashMap->fieldsSize, sizeof(HashField *));
  memcpy(fieldsCache, hashMap->fields, prevSizeCache * sizeof(HashField *));
  if (fieldsCache == NULL) {
    free(fieldsCache);
    return -1;
  }

  free(hashMap->fields);
  hashMap->fields = calloc(hashMap->fieldsSize, sizeof(HashField *));
  if (hashMap->fields == NULL) {
    free(hashMap->fields);
    return -1;
  }

  if (rehashHM(hashMap, fieldsCache, prevSizeCache) < 0)
    return -1;

  hashMap->loadFactor = hashMap->fill / (float)hashMap->fieldsSize;

  free(fieldsCache);
  return 0;
}

int rehashHM(HashMap *hashMap, HashField *fields[],
             unsigned long prevSizeCache) {
  if (hashMap == NULL)
    return -1;
  if (fields == NULL)
    return -1;
  if (prevSizeCache < INIT_HASHMAP_SIZE)
    return -1;

  for (int i = 0; i < prevSizeCache; i++) {
    if (fields[i] != NULL) {
      unsigned long hashAddress =
          dbj2Hash(fields[i]->key) % hashMap->fieldsSize;

      if (hashMap->fields[hashAddress] != NULL)
        if ((hashAddress = linearProbing(hashMap, hashAddress)) < 0)
          return -1;
      hashMap->fields[hashAddress] = fields[i];
    }
  }
  return 0;
}

char *readHM(HashMap *hashMap, char key[]) {
  if (hashMap == NULL)
    return NULL;
  if (key == NULL)
    return NULL;

  unsigned long hashAddress = dbj2Hash(key) % hashMap->fieldsSize;

  if (strcmp(hashMap->fields[hashAddress]->key, key) == 0)
    return hashMap->fields[hashAddress]->value;

  unsigned int i = hashAddress + 1;
  unsigned int probingAddress = i % hashMap->fieldsSize;

  while (probingAddress != hashAddress) {
    if (strcmp(hashMap->fields[probingAddress]->key, key) == 0)
      return hashMap->fields[probingAddress]->value;
    i++;
    probingAddress = i % hashMap->fieldsSize;
  }

  return NULL;
}

int freeHM(HashMap *hashMap) {
  if (hashMap == NULL)
    return -1;
  for (int i = 0; i < hashMap->fieldsSize; i++) {
    if (hashMap->fields[i] != NULL) {
      free(hashMap->fields[i]->key);
      free(hashMap->fields[i]->value);
      free(hashMap->fields[i]);
    }
  }
  free(hashMap->fields);
  free(hashMap);
  return 0;
}
/*
 * {
 *  fieldssize - non allocd
 *  loadFactor - non allocd
 *  fields - allocd <- needs to be freed
 *  fill - non allocd
 * }
 *
 * {
 *  key - alloced <- needs to be freed
 *  value - alloced <- needs to be free
 * }
 *
 * */

int printHM(HashMap *hashMap) {
  if (hashMap == NULL)
    return -1;

  printf("\n");
  printf("fill: %d/%d\t", hashMap->fill, hashMap->fieldsSize);
  printf("fieldsSize: %d\t", hashMap->fieldsSize);
  printf("loadFactor: %f\t", hashMap->loadFactor);
  printf("\n{\n");

  for (int i = 0; i < hashMap->fieldsSize; i++) {
    if (hashMap->fields[i] != NULL)
      printf("\t%d %s:%s\n", i, hashMap->fields[i]->key,
             hashMap->fields[i]->value);
  }

  printf("}\n");

  return 0;
}
