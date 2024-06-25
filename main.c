#include "hashMap.h"
int main() {
  HashMap *hm = initHM();
  appendHM(hm, "key1", "value1");
  appendHM(hm, "key2", "value2");
  appendHM(hm, "key3", "value3");
  appendHM(hm, "key4", "value4");
  appendHM(hm, "key1231231", "value5");
  return 0;
}
