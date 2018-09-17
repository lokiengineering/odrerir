#include <Arduino.h>

#define TEST_VARIABLE   "FOOBAR"

extern String getTestVariable() {
  return TEST_VARIABLE;
}
