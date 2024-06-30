#include "hashMap.h"
int main() {
  HashMap *hm = initHM();
  appendHM(hm, "key1", "value1");
  appendHM(hm, "key2", "value2");
  appendHM(hm, "key3", "value3");
  appendHM(hm, "key4", "value1");
  printHM(hm);
  return 0;
}
