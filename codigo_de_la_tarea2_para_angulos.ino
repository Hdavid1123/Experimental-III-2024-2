// Importante: hay que hallar la relación de paso con cuántos grados


#include<Servo.h>
Servo myservo;
int pinServo = 14;//Pin dónde vamos a conectar el servo motor.
float angulo;



void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
myservo.attach(pinServo);
}

void loop() {
  // put your main code here, to run repeatedly:

myservo.write(angulo);//Aquí es el ángulo en grados
delay(1000);

}
