#include <SoftwareSerial.h>
#include <String.h>

#define proxout 3
#define trigPin 5
#define echoPin 6
#define binid 5098
#define maxbinlevel 25

float duration, distance=50;
String str;
String tempstr;
SoftwareSerial SIM900(9,10); //rx,tx

void setup(){
  Serial.begin(9600);
  SIM900.begin(9600);  /* Define baud rate for software serial communication */
  pinMode(proxout,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  str="AT+HTTPPARA=\"URL\",\"sajeevkrishna10.pythonanywhere.com/statupdate?binid="+String(binid)+"&binstatus=";
  initgsm();
}

void loop(){
  if (digitalRead(proxout)== LOW){
    //switch on the ultrasonic sensor to scare them away
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10000);
    digitalWrite(trigPin, LOW);
  }
  else if (digitalRead(proxout)== HIGH){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Measure the response from the HC-SR04 Echo Pin
   
    duration = pulseIn(echoPin, HIGH);
    
    // Determine distance from duration
    // Use 343 metres per second as speed of sound
    
    distance = (duration/2)*0.0343;

    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    
    distance=(distance/maxbinlevel)*100;
    //calculate percentage
       
    Serial.print("level = ");
    Serial.print(distance);
    Serial.println(" %");

    delay(500);  
    }

  tempstr=str+String(distance)+"\"";
  Serial.println(tempstr);
  Serial.println(tempstr);
  SIM900.println(tempstr); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPACTION=0");
  SIM900.println("AT+HTTPACTION=0"); 
  delay(10000);
  ShowSerialData();
  delay(10000);
  Serial.println("AT+HTTPREAD");
  SIM900.println("AT+HTTPREAD"); 
  delay(8000);
  ShowSerialData();
  delay(8000);
  Serial.println("AT+HTTPTERM");  
  SIM900.println("AT+HTTPTERM");  
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=0,1");
  SIM900.println("AT+SAPBR=0,1"); 
  delay(5000);
  ShowSerialData();
  delay(5000);

}
void initgsm(){
  Serial.println("AT");
  SIM900.println("AT");
  delay(5000);
  ShowSerialData();
  delay(5000);
  
  Serial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");    
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=3,1,\"APN\",\"www\"");  
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"www\""); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=1,1");
  SIM900.println("AT+SAPBR=1,1"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+SAPBR=2,1");
  SIM900.println("AT+SAPBR=2,1"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPINIT");
  SIM900.println("AT+HTTPINIT"); 
  delay(5000); 
  ShowSerialData();
  delay(5000);
  Serial.println("AT+HTTPPARA=\"CID\",1");
  SIM900.println("AT+HTTPPARA=\"CID\",1"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
}
void ShowSerialData()
{
  while(SIM900.available()!=0)  /* If data is available on serial port */
  Serial.write(char (SIM900.read())); /* Print character received on to the serial monitor */
}
