#include "hashMap.h"
int main() {
  HashMap *hm = initHM();
  appendHM(hm, "key1", "value1");
  appendHM(hm, "key2", "value2");
  appendHM(hm, "key3", "value3");
  printHM(hm);
  return 0;
}
