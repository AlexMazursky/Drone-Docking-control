//////////// SERVO_CONTROL_MASTER
// Written by Alex J. Mazursky
// July, 2018
// This script takes a push-button input to switch 
// between OFF (open) and ON (closed) states.
////////////

#include <Servo.h> 
class Sweeper
{
  Servo servo;              // the servo
  int pos = 65;              // current servo position 
  int increment;        // increment to move for each interval
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position

public: 
  Sweeper(int interval)
  {
    updateInterval = interval;
    increment = 1;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
      if ((pos >= 155) || (pos <= 65)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }
  }
};

Sweeper sweeper1(7);

/////////// BUTTON GLOBAL
int inPin = 2;         // the number of the input pin (push button)
int reading;           // the current reading from the input pin

void setup() 
{ 
  Serial.begin(9600);
  pinMode(inPin, INPUT);
  sweeper1.Attach(9);
} 
 
void loop() 
{ 
  reading = digitalRead(inPin);
  if(reading == HIGH)
  {
     sweeper1.Update();
  }
} 
