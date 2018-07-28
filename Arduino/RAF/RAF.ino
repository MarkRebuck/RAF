#include <Servo.h>
#define MOSFET 2
#define BUTTON 12
#define JOYX A0
#define JOYY A1
#define SERV1 3
#define SERV2 5
#define SERV3 6
#define LIGHT A2
#define TEMP A3
#define RED 11
#define GREEN 10
#define BLUE 9

Servo xServo,yServo;
void setup() {
  Serial.begin(115200);
  Serial.println("Ready Aim Fire!");
  xServo.attach(SERV1);
  yServo.attach(SERV2);
  yServo.write(90);
  pinMode(MOSFET,OUTPUT);
  digitalWrite(MOSFET,LOW);

 pinMode(RED,OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE,OUTPUT);
 pinMode(BUTTON,INPUT_PULLUP);

 for (int i = 9; i < 12; i++)
 {
  digitalWrite(i,HIGH);
  delay(200);
  digitalWrite(i,LOW);
 }
 
}

int lastx;
int lasty;

void loop() {


  if (digitalRead(BUTTON) == LOW)
  {
    Serial.println("fire!");
    digitalWrite(RED,HIGH);
    digitalWrite(MOSFET,HIGH);
    delay(250);
    digitalWrite(MOSFET,LOW);
    digitalWrite(RED,LOW);
    delay(100);
  }
  int light = analogRead(LIGHT);
  int temp = analogRead(TEMP);
  Serial.print("LIGHT: ");Serial.print(light);Serial.print(" TEMP: ");Serial.println(temp);
  int x = analogRead(JOYX);
  int y = analogRead(JOYY);

  if(abs(lastx-x)>2)
  {
    //Serial.print("X: ");Serial.println(x);
    xServo.write(x/4);
    lastx =x;
  }
  if(abs(lasty-y)>2)
  {

    // Y is also around 450-500 but y axis is at 90 essentially at rest,  so map forward and back;
    //Serial.print("Y: ");Serial.println(y);
    if (y < 523)
    {
      yServo.write(map(y,0,523,1,80));
    }else
      yServo.write(map(y,524,1023,81,110));
    lasty = y;
  }

}
