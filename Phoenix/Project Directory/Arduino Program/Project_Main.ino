#include <TinyGPS.h>
#include <SoftwareSerial.h>


#define echoPin1 5 
#define trigPin1 6 
#define echoPin2 7 
#define trigPin2 8 
#define echoPin3 9 
#define trigPin3 10 
#define echoPin4 11 
#define trigPin4 12 

long duration; // variable for the duration of sound wave travel
int dis;
int light=0;
int j=0;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
int temp=0,i;
SoftwareSerial ss(RXPin, TXPin);
String stringVal = "";

void setup() {
  pinMode(4,INPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT); 
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT); 
  pinMode(echoPin4, INPUT);
  Serial.begin(9600); 
  ss.begin(GPSBaud);
  temp=0;
}

void loop() {
  int temp=digitalRead(4);     
  delay(300);
  if(temp<light)               
  {
    digitalWrite(12,HIGH); 
    delay(200);
  }
  if(temp>light)
  {
    digitalWrite(12,HIGH);
    delay(150);
    digitalWrite(12,LOW);
    delay(150);
    digitalWrite(12,HIGH);
    delay(150);
  }  
  light=temp;
  digitalWrite(12,LOW);        
  
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  dis = duration * 0.034 / 2;
  check(dis);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  dis = duration * 0.034 / 2;
  check(dis);
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH);
  dis = duration * 0.034 / 2;
  check(dis);
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration = pulseIn(echoPin4, HIGH);
  dis = duration * 0.034 / 2;
  check(dis);
  
  serialEvent();
      while(temp)
      {
        while (ss.available() > 0)
        {
          gps.encode(ss.read());
                if (gps.location.isUpdated())
                {
                 temp=0;
                 tracking();
                } 
          if(!temp)
          break;  
        }
      }

}

void serialEvent()
{
  while(Serial.available()>0)
  { 
    if(Serial.find("Track Vehicle"))
    {
      temp=1;
      break;
    }
    else
    {
    temp=0;
    }
  }
}
void gsm_init()
{

  boolean at_flag=1;
  while(at_flag)
  {
    Serial.println("AT");
    delay(1);
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      at_flag=0;
    }
    
    delay(1000);
  }
  boolean echo_flag=1;
  while(echo_flag)
  {
    Serial.println("ATE0");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      echo_flag=0;
    }
    delay(1000);
  }
  boolean net_flag=1;
  while(net_flag)
  {
    Serial.println("AT+CPIN?");
    while(Serial.available()>0)
    {
      if(Serial.find("+CPIN: READY"))
      net_flag=0;
    }
    delay(1000);
  }
}

void init_sms()
{
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"8825737586\"");   // use your 10 digit cell no. here
  delay(400);
}
void send_data(String message)
{
  Serial.print(message);
 delay(200);
}
void send_sms()
{
  Serial.write(26);
}
void tracking()
{
    init_sms();
    send_data("Vehicle Tracking Alert:");
    Serial.println(" "); 
    send_data("Your Vehicle Current Location is:");
    Serial.println(" "); 
    Serial.print("Latitude: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print("\n Longitude: ");
    Serial.println(gps.location.lng(), 6);

   // https://www.google.com/maps/@8.2630696,77.3022699,14z
   Serial.print("https://www.google.com/maps/@");
   Serial.print(gps.location.lat(), 6);
   Serial.print(',');
   Serial.print(gps.location.lng(), 6);
   Serial.print(",14z");
    send_sms();
}
void check(int distance)
{
  if(distance<150)
  {
    digitalWrite(11,HIGH);
    delay(100);
    digitalWrite(11,LOW);
  }
  if(distance<100)
  {
    digitalWrite(11,HIGH);
    delay(150);
    digitalWrite(11,LOW);
  }
  if(distance<50)
  {
    digitalWrite(11,HIGH);
    delay(200);
    digitalWrite(11,LOW);
  }
  if(distance<30)
  {
    digitalWrite(11,HIGH);
    delay(300);
    digitalWrite(11,LOW);
  }
  if(distance<10)
  {
    for(j=0;j<10-distance;j++)
    {digitalWrite(11,HIGH);
    delay(100);
    digitalWrite(11,LOW);}
  }
  }
  
