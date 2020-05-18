/*************************************************************************
    File        : 2_StateFile.ino (opens in arduino IDE www.arduino.cc)
    Description : Example sketch using SerialEventParser Library
    Usage       : Using the Arduino serial monitor you can call the state
                  functions below by sending the state name ending in
                  "new line". In order to get a proper greeting, provide
                  your name as the first parameter.
    Example     : getTime\n
                  getGreeting::Larry\n
*************************************************************************/

#include <Arduino.h>
#include <StreamMessageHandler.h>

StreamMessageHandler handler;                                             // Defaults to using Serial "type" stream communication

#include "States.h"                                                       // State file includes all state definitions, placing them here makes main sketch more readable

void setup() {
  Serial.begin(9600);                                                     // Begin Serial communication at 9600 baud
  handler.registerState(getTime, "getTime");                              // Register the "getTime" state for callback
  handler.registerState(getGreeting, "getGreeting");                      // Register the "getGreeting" state for callback
}

void loop() {
  handler.run();                                                          // Run and monitor stream for messages, instantiate callbacks when received
}

/*************************************************************************
    End of File : 2_StateFile.ino
*************************************************************************/
