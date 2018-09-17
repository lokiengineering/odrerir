// This file is loaded into main.cpp
// Order: 5

#include <Arduino.h>

#define TEST_COMMAND                "TEST"

// Main Application Methods

extern bool runCommandTest(String incomingMessage) {
  if (incomingMessage.equals(TEST_COMMAND)) { // test command was sent
    log("[Recieved] TEST COMMAND"); // print to serial terminl
    sendUARTmessage("Response Message");
    return true;
  }
  return false;
}

extern void CommandsLoop() {
  // Check for incoming UART commands from Bluefruit
  String incomingMessage = getUARTmessage();
  if (!incomingMessage.equals("NULL")) { // string comparison
    if (runCommandTest(incomingMessage)) { return; }
    return;
  }
}
