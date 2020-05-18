/*************************************************************************
    File        : States.h (opens in arduino IDE www.arduino.cc)
    Description : State definition file containing state functions for callback
*************************************************************************/

state getTime() {
  handler.println(millis());
}

state getGreeting() {
  handler.println("Hello " + handler.parameter(0) + ", have a nice day!");
}

/*************************************************************************
    End of File : States.h
*************************************************************************/