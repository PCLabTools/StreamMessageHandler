/*************************************************************************
    File        : 4_runStates.ino (opens in arduino IDE www.arduino.cc)
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

state getTime() {
  handler.println(millis());
}

state getGreeting1() {
  handler.println("Hello " + handler.parameter(0) + ", have a nice day!");
}

state getGreeting2() {
  handler.println("This greeting had a statically set number of parameters of: " + handler.parameter(0));
}

void setup() {
  Serial.begin(9600);                                                     // Begin Serial communication at 9600 baud
}

void loop() {
  handler.run();                                                          // Run and monitor stream for messages, instantiate callbacks when received
  handler.runState(getTime);                                              // "getTime" has no parameters so no need to specify any
  String functionParameters[] = {"Arduino User"};                         // Create array of parameters to pass to "getGreeting" function
  handler.runState(getGreeting1, functionParameters, (sizeof(functionParameters)/sizeof(functionParameters[0])));
  functionParameters[0] = {"1"};                                    // Create array of parameters to pass to "getGreeting" function
  handler.runState(getGreeting2, functionParameters, 1);
  delay(1000);
}

/*************************************************************************
    End of File : 4_runStates.ino
*************************************************************************/
