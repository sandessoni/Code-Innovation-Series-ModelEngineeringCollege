#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 

long duration; // variable for the duration of sound wave travel
int distance;
int old=0;
int light=0;
int i=0;

void setup() {
  pinMode(4,INPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); //initialise serial monitor

}

void loop() {
  int temp=digitalRead(4);      //assign value of LDR sensor to a temporary variable
  Serial.println("Intensity="); //print on serial monitor using ""
  Serial.println(temp);         //display output on serial monitor
  delay(300);
  if(temp<light)               //HIGH means,light got blocked
  {
    digitalWrite(12,HIGH);        //if light is not present,LED on
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
  digitalWrite(12,LOW);         //if light is present,LED off
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(distance<(0.9*old))
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
    for(i=0;i<10-distance;i++)
    {digitalWrite(11,HIGH);
    delay(100);
    digitalWrite(11,LOW);}
  }
  }
  old=distance;
    
}
