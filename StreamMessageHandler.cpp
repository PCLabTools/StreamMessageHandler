/*************************************************************************
    File        : StreamMessageHandler.cpp (opens in arduino IDE www.arduino.cc)
    Description : Handles Stream Messages
    Date        : 26th April 2020
    Author      : Larry Colvin
*************************************************************************/

#include <Arduino.h>
#include "StreamMessageHandler.h"

bool StreamMessageHandler::EVENT_COMPLETE;
String StreamMessageHandler::EVENT_STRING;
bool StreamMessageHandler::ENABLED = true;

StreamMessageHandler::StreamMessageHandler(Stream &streamObject) {
  _streamRef=streamObject;
}

void StreamMessageHandler::registerState(FUNCTION FUNC, String NAME) {
  for(byte i=0; i<SMH_MAX_STATES; i++){
    if (STATENAMES[i] == "") {
      STATENAMES[i] = NAME;
      STATES[i] = FUNC;
      break;
    }
  }
}

void StreamMessageHandler::unregisterState(String NAME) {
  for(byte i=0; i<SMH_MAX_STATES; i++){
    if (NAME == STATENAMES[i]) {
      STATENAMES[i] = "";
      break;
    }
  }
}

String StreamMessageHandler::getRegisteredStates() {
  String returnString;
  for (byte i=0 ; i < SMH_MAX_STATES ; i++) {
    if (STATENAMES[i] == ""){
      //break;
    } else {
      returnString += STATENAMES[i] + "\n";
    }
  }
  return returnString;
}

void StreamMessageHandler::run() {
  // READ STREAM FOR MESSAGES
  if (ENABLED) {
    if (!EVENT_COMPLETE) {
      while (_streamRef.available()> 0) {
        char thisChar = (char)_streamRef.read();
        if (thisChar == '\n') {
          if (EVENT_STRING != "") {
            EVENT_COMPLETE = true;
          }
        } else {
          EVENT_STRING += thisChar; 
        }
      }
    }
  }
  String eventState = "";
  String eventData = "";
  bool stateActioned = false;
  // WHEN MESSAGE RECEIVED, SPLIT MESSAGE INTO STATE/DATA
  if (EVENT_COMPLETE) {
    if (EVENT_STRING.indexOf(_DELIMITER) > 0) {
      if (EVENT_STRING.substring(EVENT_STRING.indexOf(_DELIMITER) + _DELIMITER.length()) != "") {
        eventState = EVENT_STRING.substring(0, EVENT_STRING.indexOf(_DELIMITER));
        eventData = EVENT_STRING.substring(EVENT_STRING.indexOf(_DELIMITER) + _DELIMITER.length());
        for (byte i=0 ; i<SMH_MAX_PARAMETERS ; i++) {
          if (eventData.indexOf(_PARAMETER_DELIMITER) == -1) {
            PARAMETER_ARRAY[i] = eventData;
            break;
          }
          PARAMETER_ARRAY[i] = eventData.substring(0,eventData.indexOf(_PARAMETER_DELIMITER));
          eventData = eventData.substring(eventData.indexOf(_PARAMETER_DELIMITER) + _PARAMETER_DELIMITER.length());
        }
      }
    } else {
      eventState = EVENT_STRING;
    }
    // ACTION THE STATE IF STATE NAME IS PRESENT IN STATENAMES[]:
    for(byte i=0; i<SMH_MAX_STATES; i++){
      if (eventState == STATENAMES[i]) {
        stateActioned = true;
        (*STATES[i])();
        break;
      }
    }
    if (stateActioned == true) { 
      // STATE ACTIONED NO OTHER ACTIONS NECESSARY
    } else if (eventState == "getStates") {
      String stateList = getRegisteredStates() + "getStates";
      println(stateList);
    } else {
      // STATE DOES NOT EXIST, PRODUCE ERROR
      String errorMessage = "";
      if (PARAMETER_ARRAY[0] != "") {
        errorMessage += "ERROR - Unrecognised Event = " + eventState + " [Parameters: ";
        for (byte i=0; i<((sizeof(PARAMETER_ARRAY)/(sizeof(PARAMETER_ARRAY[0])))); i++) {
          if (PARAMETER_ARRAY[i] != "") {
            if (i==0) {
              errorMessage += PARAMETER_ARRAY[i];
            } else {
              errorMessage += "," + PARAMETER_ARRAY[i];
            }
          }
        }
        errorMessage += "]";
        println(errorMessage);
      } else {
        errorMessage += "ERROR - Unrecognised Event = " + eventState;
        println(errorMessage);
      }
    }
    // RE-INITIALISE FLAGS TO READY FOR NEXT MESSAGE
    EVENT_COMPLETE = false;
    EVENT_STRING = "";
    for (int i=0 ; i<SMH_MAX_PARAMETERS ; i++) {
      PARAMETER_ARRAY[i] = "";
    }
  }
}

void StreamMessageHandler::runState(FUNCTION FUNC, String MESSAGEPARAMETERS[], int NUM_PARAMS) {
  if (ENABLED) {
    for (int i=0 ; i<NUM_PARAMS ; i++) {
      PARAMETER_ARRAY[i] = MESSAGEPARAMETERS[i];
    }
    FUNC();
    for (int i=0 ; i<SMH_MAX_PARAMETERS ; i++) {
      PARAMETER_ARRAY[i] = "";
    }
  }
}

String StreamMessageHandler::parameter(int INDEX) {
  return PARAMETER_ARRAY[INDEX];
}

void StreamMessageHandler::sendMessage(String MESSAGESTATE, String MESSAGEPARAMETERS[], int NUM_PARAMS) {
  String messageToSend = "";
  messageToSend += MESSAGESTATE;
  messageToSend += _DELIMITER;
  for (byte i=0 ; i < NUM_PARAMS ; i++) {
    messageToSend += MESSAGEPARAMETERS[i];
    if (i+1 < NUM_PARAMS) {
      messageToSend += _PARAMETER_DELIMITER;
    }
  }
  messageToSend += "\n";
  print(messageToSend);
}

void StreamMessageHandler::write(char CHARACTER) {
  _streamRef.write(CHARACTER);
}

void StreamMessageHandler::print(String MESSAGE) {
  for (byte i=0; i<(MESSAGE.length()); i++){
    write(MESSAGE[i]);
  }
}

void StreamMessageHandler::println(String MESSAGE) {
  for (byte i=0; i<(MESSAGE.length()); i++){
    write(MESSAGE[i]);
  }
  for (byte i=0; i<(_END_OF_LINE.length()); i++) {
    write(_END_OF_LINE[i]);
  }
}

void StreamMessageHandler::enable() {
  ENABLED = true;
}

void StreamMessageHandler::disable() {
  ENABLED = false;
}

/*************************************************************************
    End of File : StreamMessageHandler.cpp
*************************************************************************/
