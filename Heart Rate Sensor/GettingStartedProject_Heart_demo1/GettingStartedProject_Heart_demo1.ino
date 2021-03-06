
/*  PulseSensor Starter Project and Signal Tester
 *  The Best Way to Get Started  With, or See the Raw Signal of, your PulseSensor.com™ & Arduino.
 *
 *  Here is a link to the tutorial
 *  https://pulsesensor.com/pages/code-and-guide
 *
 *  WATCH ME (Tutorial Video):
 *  https://www.youtube.com/watch?v=RbB8NSRa5X4
 *
 *
-------------------------------------------------------------
1) This shows a live human Heartbeat Pulse.
2) Live visualization in Arduino's Cool "Serial Plotter".
3) Blink an LED on each Heartbeat.
4) This is the direct Pulse Sensor's Signal.
5) A great first-step in troubleshooting your circuit and connections.
6) "Human-readable" code that is newbie friendly."

*/


//  Variables
int PulseSensorPurplePin = 0; // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED_pin13 = 13; // The on-board Arduion LED


int heart_signal; // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;  // use serial plotter to determine which signal to "count as a beat" based off your ECG signa;


// The SetUp Function:
void setup() {
  pinMode(LED_pin13,OUTPUT); // pin that will blink to your heartbeat!
   Serial.begin(9600); // Set's up Serial Communication at certain speed.

}

// The Main Loop Function
void loop() {

  heart_signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value and store in heart_signal
   Serial.println(heart_signal); // Send the Signal value to Serial Plotter.

//Flash led using heart rate signal
   if(heart_signal > Threshold){ // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED_pin13,HIGH);
   } else {
     digitalWrite(LED_pin13,LOW); //  Else, the sigal must be below "550", so "turn-off" this LED.
   }


delay(10);


}
