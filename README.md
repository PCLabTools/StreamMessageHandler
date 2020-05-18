# StreamMessageHandler
Library abstracting stream based communications to allow sending Messages containing state and data information. Uses a system of callbacks to facilitate the state actions, simplifying code readability.


## Navitagation
* [Information](#information)
   * [Description](#description)
   * [Installation](#installation)
   * [Usage](#usage)
   * [Theory](#theory)
   * [Links](#links)
* [Functions](#functions)
* [License](#license)


## Information

### Description
The StreamMessageHandler library is designed to abstract and simplify communication between devices. This can be used to provide a "state machine" type framework to the device allowing creation of multi-instrument systems that use a unified communication method.

### Installation
To install the library clone the repository or download and unzip the source into the following folder:
```
<Arduino Libraries Folder>/StreamMessageHandler
Windows: C:/Users/<User>/Documents/Arduino/libraries/StreamMessageHandler
```
For more information on how to install libraries please visit [Installing Additional Arduino Libraries](https://www.arduino.cc/en/guide/libraries "arduino.cc").

### Usage

### Theory

### Links


## Functions

### StreamMessageHandler()
The constructor. You usually need only one StreamMessageHandler object in a sketch. The input parameter for the StreamMessageHandler is the "Stream" class that you want to use for communication.
```c++
StreamMessageHandler handler;            //Defaults to using "Serial" Object
StreamMessageHandler handler(Serial2);   //Uses "Serial2" Object
```

### void registerState(FUNCTION FUNC, String NAME)
Call function *FUNC* when state *NAME* is called. The callback function must be declared as `void f()`
```c++
state getTime() {
	Serial.println(millis());
}

handler.registerState(getTime, "getTime");
```

### void unregisterState(String NAME)
Remove registry of state *NAME*.
```c++
state getTime() {
	Serial.println(millis());
}

handler.unregisterState("getTime");
```

### String getRegisteredStates()
Return the list of registered states seperated by `\n`
>Return Type: String
```c++
handler.getRegisteredStates();
```

### void run()
Run the stream message handler and handle any messages that have been received. This function must be called within the sketch's main loop to scan and handle messages. Any messages received that match a registered state will create a callback to that state.
```c++
void loop() {
   handler.run();
}
```

### void runState(FUNCTION STATE, String PARAMETERS[], int NUM_PARAMS)
Runs the specified *STATE* with the defined *PARAMETERS[]* of length *NUM_PARAMS*. This can run states without the need for the stream to call it. States do not need to be registered to be called through this method.
```c++
void loop() {
   String messageParameters[] = {"Arduino User"};
   handler.runState(getGreeting, messageParameters, (sizeof(messageParameters)/sizeof(messageParameters[0])));
}
```

### String parameter(int INDEX)
Return the message parameter specified by *INDEX*. Use this function within a state so that during callback the state can access the message parameters.
>Return Type: String
```c++
state getGreeting() {
   Serial.println("Hello " + handler.parameter(0) + ", I hope you have a nice day!");
}
```

### void sendMessage(String STATE, String PARAMETERS[], int NUM_PARAMS)
This function will send a message using the chosen stream type and format the message as defined by the library settings. The message state will be *STATE* and the parameters will be *PARAMETERS[]* of length *NUM_PARAMS*.
```c++
handler.sendMessage("getGreeting",{"Friend"});
```

### void write()
Performs a write command on the chosen stream and sends a character.
```c++
handler.write('A');
```

### void print()
Performs a print command on the chosen stream and sends the string.
```c++
handler.print("Print this message");
```

### void println()
Performs a print line command on the chosen stream and sends the string appended with a carriage return.
```c++
handler.println("Print this message and append carriage return");
```

### void enable()
Enables handling messages. This is the default state of the StreamMessageHandler when created.
```c++
handler.enable();
```

### void disable()
Disables handling messages. When disabled all messages that are received will be lost.
```c++
handler.disable();
```


## License

MIT License

Copyright (c) 2020 PCLabTools

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.