//const int BUZZER=3;
//const int GSR=A2;
//int threshold=0;
//int sensorValue;
//
//void setup(){
//  long sum=0;
//  Serial.begin(9600);
//  pinMode(BUZZER,OUTPUT);
//  digitalWrite(BUZZER,LOW);
//  delay(1000);
//  
//  for(int i=0;i<500;i++)
//  {
//  sensorValue=analogRead(GSR);
//  sum += sensorValue;
//  delay(5);
//  }
//  threshold = sum/500;
//   Serial.print("threshold =");
//   Serial.println(threshold);
//  }
//  
//
//void loop(){
//  int temp;
//  sensorValue=analogRead(GSR);
//  Serial.print("sensorValue=");
//  Serial.println(sensorValue);
//  temp = threshold - sensorValue;
//  if(abs(temp)>50)
//  {
//    sensorValue=analogRead(GSR);
//    temp = threshold - sensorValue;
//    if(abs(temp)>50){
//    digitalWrite(BUZZER,HIGH);
//    Serial.println("YES!");
//    delay(3000);
//    digitalWrite(BUZZER,LOW);
//    delay(1000);}
//  }
//  }

//const int LED=13;
//const int GSR=A0;
//int sensorValue;
//int ohm = 0;
//int gsr_val = 0;
//
//void setup()
//{
//Serial.begin(9600);
//pinMode(LED,OUTPUT);
//digitalWrite(LED,LOW);
//delay(1000);
//}
//
//void loop()
//{
//int temp;
//float conductivevoltage;
//sensorValue=analogRead(GSR);
//conductivevoltage = sensorValue*(5.0/1023.0); //10 bit resolution: 5 volts / 1024 units, 0.0049 volts (4.9 mV) per unit
//   ohm = ((1024+2*conductivevoltage)*10000)/(512-conductivevoltage);
//   ohm = ohm * (10^6);
//   gsr_val = 1/ohm;
//Serial.print("sensorValue=");
//Serial.println(gsr_val);
//delay(100);
//}

//typical GSR values are 1-20uS

const int GSR=A0;
int sensorValue=0;
int dig_volt=0;
int ohm = 0;
int GSR_val = 0;
int vout = 0;
int resistance = 0;
int range = 0;
 
void setup(){
  Serial.begin(9600);
}
 
void loop(){
  long sum=0;
  for(int i=0;i<10;i++)           //Average the 10 measurements to remove the glitch
      {
      sensorValue=analogRead(GSR);
      sum += sensorValue;
      delay(5);
      }
   dig_volt = sum/10;
   float ana_volt = dig_volt * (5.0 / 1023.0); //convert digital signal to analog voltage
  

   //calculate ohms using table
   float temp = ana_volt;
  // int temp_v = 0;
   float vout[] = {1.755, 1.677, 1.587, 1.434, 1.054, .923, .813, .357, .135};
   double rs [] = {10000, 49500, 100000, 200000, 560000, 760000, 1000000, 3300000, 9930000};
   float inc_rs[] = {0.1632, 0.1808, 0.2106, 0.3053, 0.4920, 0.7031, 1.6255, 9.6244};
   
   Serial.print("Digital Voltage : ");
   Serial.println(dig_volt);
   Serial.print("Analog Voltage (V): ");
   Serial.println(ana_volt);
   delay(1000);
 //double ana_volt = 1.7486;
  //determine range
  for(range;range < 9; range++){
  if(ana_volt < vout[range] && ana_volt > vout[range+1])
  break;
}
 float result = rs[range] + (abs(vout[range] - ana_volt)/.0032)*(10000.0*inc_rs[range]);
 float skin_cond = (1/result);
 skin_cond = skin_cond *10e6;

//float x = 10000*inc_rs[range];
//float y = vout[range];
//float z = rs[range];
//float a = abs(vout[range] - ana_volt);
//float b = abs(vout[range] - ana_volt)*(10000.0*inc_rs[range]);
//long sum = z + b;

  
  // Serial.println(temp, 4);
   Serial.print("Human Resistance : ");
   Serial.println(result);
   Serial.print("Skin Conductance : ");
   Serial.println(skin_cond, 8);
}
