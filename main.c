#include "hashMap.h"
#include <stdio.h>
int main() {
  HashMap *hm = initHM();
  appendHM(hm, "key1", "value1");
  appendHM(hm, "key5", "value5");
  appendHM(hm, "key2", "value2");
  appendHM(hm, "key3", "value3");
  appendHM(hm, "key4", "value4");
  printf("\n%s\n", readHM(hm, "key4"));
  return 0;
}
