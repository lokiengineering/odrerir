// This file is loaded into main.cpp
// Order: 2

#include <Arduino.h>

// serial logging helpers
extern void log(String message) {
  Serial.println(message);
}
extern void logInline(String message) {
  Serial.print(message);
}
extern void logHex(int message, int type) {
  Serial.println(message, type);
}
// Generic helpers
extern void error(String err) {
  log(err);
  while (1);
}

extern char* convertStringToChar(String str) {
  int str_len = str.length() + 1; // Length (with one extra character for the null terminator)
  char char_array[str_len]; // Prepare the character array (the buffer)
  str.toCharArray(char_array, str_len); // copy it over
  return char_array; // return the character array
}

// Serial Input Helpers
extern bool getUserInput(char buffer[], uint8_t maxSize) {
  // timeout in 100 milliseconds
  TimeoutTimer timeout(100);
  memset(buffer, 0, maxSize);
  while((!Serial.available()) && !timeout.expired()) {
    delay(1);
  }
  if (timeout.expired()) return false;
  delay(2);
  uint8_t count=0;
  do {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while ((count < maxSize) && (Serial.available()));
  return true;
}
