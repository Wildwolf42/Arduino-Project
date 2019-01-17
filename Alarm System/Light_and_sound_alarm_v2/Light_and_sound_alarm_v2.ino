/*
Prototype code for an alarm system that detects
how far away something is, then if it is below a certain
distance, flashes a light and plays a soundr
*/


const int trigPin = 2;
const int echoPin = 4;
int inPin = 8; 
int val = 0;
bool running = true;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(inPin, INPUT); //Set the pushbutton pin as input
  
}

// the loop function runs over and over again forever
void loop() {
  if (! running) {
    return;
  }
  // Detects distance, then flashes light if it meets if statement
  distance(); 
  if (distance() < 100) 
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
    noTone(6);
  // play a note on pin 6 for 100 ms:
  tone(6, 440, 200);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                // wait for a half second
    noTone(6);
  // play a note on pin 6 for 100 ms:
  tone(6, 440, 200);
  delay(100);
  noTone(6);
 val = digitalRead(inPin);
  if (val == 1) 
    running = false;
}

  
  long distance() 
  {
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  return inches;
}

long microsecondsToInches(long microseconds) 
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
