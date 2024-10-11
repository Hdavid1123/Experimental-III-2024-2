#include <Stepper.h>      // setSpeed(1) libreria stepper
 
int Pin1 = 12;
int Pin2 = 13;
int Pin3 = 5;
int Pin4 = 23;

int pinFoto= 2;
// 1 step es aproximadmente 0.1757º,  según los 2048 steps

float pasos_por_grado = 5.058844111;

Stepper motor(2048,Pin1,Pin2,Pin3,Pin4);   /* Una vuelta completa (360º)según las especificaciones
es de 2048, pero según los calculo que hicimos en la clase pasada es de 1800 pasos */


 
void setup() {
  Serial.begin(115200);
  motor.setSpeed(1);/* la velocidad "setSpeed()" se mide en RPM #devueltas/minuto 
  pero como queremos saber el tiempo sería 60/2048 = 0.02929 s y en mms es 29,29 mms, como el 
  tiempo mínimo que soporta el motor es de (1/100)s (se obtuvo del data sheet del motro ), es decir 
  10mms */

  
}
 
void loop() {
  int adc = analogRead(pinFoto);
  float V = (adc*3.3)/4095;
  motor.step(1024);         // cantidad de pasos, le otorgué 1024 porque sería 180º
  delay(1000);        // demora de 1 sg
  motor.step(-1024); // el menos es paraque cuando llegué a esa posición se devuelva otra vez
  delay(1000);        // demora de 1 sg