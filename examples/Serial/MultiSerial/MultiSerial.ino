/*************************************************************************
    File        : MultiSerial.ino (opens in arduino IDE www.arduino.cc)
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

StreamMessageHandler handler1(Serial);                                    // Use "Serial" stream object as handler1 stream
StreamMessageHandler handler2(Serial1);                                   // Use "Serial1" stream object as handler2 stream

state getTime() {
  handler1.println(millis());
}

state getGreeting() {
  handler2.println("Hello " + handler.parameter(0) + ", have a nice day!");
}

void setup() {
  Serial.begin(9600);                                                     // Begin Serial communication at 9600 baud
  Serial1.begin(9600);                                                    // Begin Serial1 communication at 9600 baud
  handler1.registerState(getTime, "getTime");                             // Register the "getTime" state for callback
  handler2.registerState(getGreeting, "getGreeting");                     // Register the "getGreeting" state for callback
}

void loop() {
  handler1.run();                                                         // Run and monitor stream for messages, instantiate callbacks when received
  handler2.run();                                                         // Run and monitor stream for messages, instantiate callbacks when received
}

/*************************************************************************
    End of File : MultiSerial.ino
*************************************************************************/
