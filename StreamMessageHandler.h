/*************************************************************************
    File        : StreamMessageHandler.h (opens in arduino IDE www.arduino.cc)
    Description : Handles Stream Messages
    Date        : 26th April 2020
    Author      : Larry Colvin
*************************************************************************/

#define state void
 
#ifndef StreamMessageHandler_h

  #define StreamMessageHandler_h

  #define SMH_MAX_STATES 10
  #define SMH_MAX_PARAMETERS 10
  
  typedef state (*FUNCTION)(void);

  class StreamMessageHandler {
    public:
      StreamMessageHandler(Stream &streamObject = Serial);
      void registerState(FUNCTION FUNC, String NAME);
      void unregisterState(String NAME);
      String getRegisteredStates();
      void run();
      void runState(FUNCTION FUNC, String MESSAGEPARAMETERS[] = {}, int NUM_PARAMS = 0);
      String parameter(int INDEX);
      void sendMessage(String MESSAGESTATE, String MESSAGEPARAMETERS[] = {}, int NUM_PARAMS = 0);
      void write(char CHARACTER);
      void print(String MESSAGE);
      void println(String MESSAGE);
      void enable();
      void disable();
             
     private:
      Stream &_streamRef = Serial;
      static String EVENT_STRING;
      static bool EVENT_COMPLETE;
      static bool ENABLED;
      const String _DELIMITER = "::";
      const String _PARAMETER_DELIMITER = ",";
      const String _END_OF_LINE = "\n";
      FUNCTION STATES[SMH_MAX_STATES];
      String STATENAMES[SMH_MAX_STATES];
      String PARAMETER_ARRAY[SMH_MAX_PARAMETERS];
      
  };

#endif

/*************************************************************************
    End of File : StreamMessageHandler.h
*************************************************************************/
