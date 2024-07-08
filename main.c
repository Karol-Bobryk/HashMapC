#include "hashMap.h"
#include <stdio.h>
int main() {
  HashMap *hm = HMInit();
  HMAppend(hm, "key1", "value1");
  HMAppend(hm, "key5", "value5");
  HMAppend(hm, "key2", "value2");
  HMAppend(hm, "key3", "value3");
  HMAppend(hm, "key3", "value69");
  HMAppend(hm, "key4", "value4");
  printf("\n%s\n", HMRead(hm, "key4"));
  HMPrint(hm);
  HMFree(hm);
  return 0;
}
