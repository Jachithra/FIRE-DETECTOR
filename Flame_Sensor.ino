 #include <SoftwareSerial.h>
 
SoftwareSerial mySerial(9, 10);

 int a=100;
 int flame;
 
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);     // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(3, INPUT);      // Flame Sensor
  pinMode(5, OUTPUT);     // LED 1
  pinMode(7, OUTPUT);     // LED 2
  pinMode(4, OUTPUT);     // Buzzer
}

void loop()
{
 delay(1000);
 flame=digitalRead(3);
 Serial.println(flame);
 if(flame==0)
 {
  digitalWrite(7,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(4,HIGH);
  delay(1000);
  digitalWrite(4,LOW);
  SendMessage();
 }
 if(flame==1)
 {
  digitalWrite(5,HIGH);
  digitalWrite(7,LOW);
 }
 
 
      
 if (mySerial.available()>0)
 {
  Serial.write(mySerial.read());
 }
}

 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917558047334\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.print("Fire Detected!!! EMERGENCY");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
