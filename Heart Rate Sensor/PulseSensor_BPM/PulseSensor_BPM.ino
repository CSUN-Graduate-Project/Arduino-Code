
/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Arduino Code------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks LED on PIN 13 with user's Heartbeat.
--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM match
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library 

// Variables
const int Analog_Pin = 0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13; // The on-board Arduino LED, close to PIN 13.
int Threshold = 550; // use serial plotter to determine which signal to "count as a beat" based off your ECG signal
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup() {   

  Serial.begin(9600); // Set baud rate for Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(Analog_Pin); // Set the pin your Pulse Sensor is connected to
  pulseSensor.blinkOnPulse(LED13); // Set the pin that will blink to your pulse
  pulseSensor.setThreshold(Threshold); // Set a value that the Pulse Sensor signal has to cross when going up. Adjusting this can be useful to combat noise

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  // Returns the latest beats-per-minute as an int

if (pulseSensor.sawStartOfBeat()) {            // Constantly testing if new heartbeat occurred 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print following message
 Serial.print("BPM: ");                        
 Serial.println(myBPM);                       
}

  delay(20);            

}

  
