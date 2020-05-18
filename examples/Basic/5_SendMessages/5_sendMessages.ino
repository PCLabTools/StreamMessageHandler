/*************************************************************************
    File        : 5_sendMessages.ino (opens in arduino IDE www.arduino.cc)
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

void setup() {
  Serial.begin(9600);                                                     // Begin Serial communication at 9600 baud
}

void loop() {
  handler.run();                                                          // Run and monitor stream for messages, instantiate callbacks when received
  String messageState = "Test";
  String messageParameters[] = {"send", "Message", String(millis())};     // Create array of parameters to send
  handler.sendMessage(messageState, messageParameters, (sizeof(messageParameters)/sizeof(messageParameters[0])));
  delay(1000);
}

/*************************************************************************
    End of File : 5_sendMessages.ino
*************************************************************************/
