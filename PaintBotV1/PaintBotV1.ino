/*
______________________________________________________________________________________ 
PaintBot v.1   10-04-2019            |      Saneet Fulsunder
                                     |      http://fulsunder.co
_____________________________________|________________________________________________
*/
int sprayPin = 12;

int vMotPin1 = 8;
int vMotPin2 = 9;
int hMotPin1 = 10;
int hMotPin2 = 11;

int vMin = 4,vMax = 5;
int interruptPin = 3;

void setup() {
pinMode(sprayPin,OUTPUT);

pinMode( vMotPin1 ,OUTPUT);
pinMode( vMotPin2,OUTPUT);
pinMode( hMotPin1,OUTPUT);
pinMode( hMotPin2,OUTPUT);

pinMode( vMin,INPUT);
pinMode(vMax,INPUT);
pinMode( interruptPin,INPUT);
}

void loop() 
{                                           
  if( lookAhead() == 0 && digitalRead(interruptPin) == LOW)  
                                            // If safe to complete next move, then                   
    moveNext();                             // Perform next Move
  else
    delay(100);                             // wait
}
  
void moveV(int mode = 0)                    // Vertical Motion Control. Modes -- 0: full cycle, 1: up, 2: down
{
  switch(mode)
  {
    case 0:
      while(digitalRead(vMax) != HIGH)
      {
         digitalWrite(vMotPin1, HIGH);  
         digitalWrite(vMotPin2, LOW);
         delay(200);
      }
      while(digitalRead(vMin) != HIGH)
      {
         digitalWrite(vMotPin1, LOW);  
         digitalWrite(vMotPin2, HIGH);
         delay(200);     
      }
    break;
    case 1:
      while(digitalRead(vMax) != HIGH)
      {
         digitalWrite(vMotPin1, HIGH);  
         digitalWrite(vMotPin2, LOW);
         delay(200);
      }
    break;
    case 2: 
      while(digitalRead(vMin) != HIGH)
      {
         digitalWrite(vMotPin1, LOW);  
         digitalWrite(vMotPin2, HIGH);
         delay(200);     
      }
    break;
    };
}

void moveH()                                // Forward Motion Control
{
    if(lookHSafe() > 10)
    {
         digitalWrite(hMotPin1, LOW);  
         digitalWrite(hMotPin2, HIGH);
         delay(2000);     
    }
}

int lookAhead()                             // Scan for obstacles, move spray to bottom
{
  if(lookHSafe() < 10 || digitalRead(vMin) == LOW )
  {
    moveV(2);
    return 1;
  }
  else
    return 0;
}

void setSpray( bool val = false)            // Sprayer Control Block
{
  if(val == true)
    digitalWrite(sprayPin,HIGH);
  else
    digitalWrite(sprayPin,LOW);
}

void  moveNext()                            /// Main Movement Routine Control Block
{
  setSpray(true);
  moveV();
  setSpray(false);
  moveH();
}

const int pingPin = 7;                      // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6;                      // Echo Pin of Ultrasonic Sensor

int lookHSafe()
{
   long duration, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   return duration / 29 / 2;
}



