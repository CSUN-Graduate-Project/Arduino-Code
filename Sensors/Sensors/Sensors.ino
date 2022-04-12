#define USE_ARDUINO_INTERRUPTS true // Set-up low-level interrupts for most acurate BPM match
#include <PulseSensorPlayground.h> // Includes the PulseSensorPlayground Library 

// Variables
const int Analog_Pin = 0; // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13; // The on-board Arduino LED, close to PIN 13.
int Threshold = 550; // use serial plotter to determine which signal to "count as a beat" based off your ECG signal
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

//typical GSR values are 1-20uS

const int GSR=A1;
int sensorValue=0;
int gsr_avg=0;
int ohm = 0;

void setup()
{

//Heart rate
  Serial.begin(9600); // Set baud rate for Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(Analog_Pin); // Set the pin your Pulse Sensor is connected to
  pulseSensor.blinkOnPulse(LED13); // Set the pin that will blink to your pulse
  pulseSensor.setThreshold(Threshold); // Set a value that the Pulse Sensor signal has to cross when going up. Adjusting this can be useful to combat noise

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }

//GSR  
//Serial.begin(9600);
////pinMode(LED,OUTPUT);
//digitalWrite(LED,LOW);
//delay(1000);
}

void loop()
{
//Heart rate
int myBPM = pulseSensor.getBeatsPerMinute();  // Returns the latest beats-per-minute as an int

if (pulseSensor.sawStartOfBeat()) {            // Constantly testing if new heartbeat occurred 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print following message
 Serial.print("BPM: ");                        
 Serial.println(myBPM);  
//after each heartbeat, read GSR values next

//GSR  
long sum=0;
  for(int i=0;i<10;i++)           //Average the 10 measurements to remove the glitch
      {
      sensorValue=analogRead(GSR);
      sum += sensorValue;
      delay(5);
      }
   gsr_avg = sum/10;
   ohm = ((1024+2*gsr_avg)*10000)/(512-gsr_avg);
   //ohm = ohm * (10^-6);
   //GSR_val = 1/ohm;
   
   Serial.print("GSR average : ");
   Serial.println(gsr_avg);
   Serial.print("Human Resistance : ");
   Serial.println(ohm);

//Temperature
   
}

  delay(20); 
////GSR  
//long sum=0;
//  for(int i=0;i<10;i++)           //Average the 10 measurements to remove the glitch
//      {
//      sensorValue=analogRead(GSR);
//      sum += sensorValue;
//      delay(5);
//      }
//   gsr_avg = (sum/10)*(10^6);
//   ohm = ((1024+2*gsr_avg)*10000)/(512-gsr_avg);
//   //ohm = ohm * (10^-6);
//   //GSR_val = 1/ohm;
//   
//   Serial.print("GSR average : ");
//   Serial.println(gsr_avg);
//   Serial.print("Human Resistance : ");
//   Serial.println(ohm);
}


  
