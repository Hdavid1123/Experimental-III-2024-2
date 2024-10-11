#include <Stepper.h>

const float pasosPorGrado = 5.058844111;  // Pasos por grado
Stepper myStepper(2048, 23, 13, 5, 12);   // Configuración del motor

int angulo_barrido = 70;    // Ángulo de barrido por defecto
int comenzar = 0;           // Bandera para activar el barrido
#define puerto_fotoresistencia A0 // Foto-resistencia conectada al pin A0

void setup() {
  myStepper.setSpeed(10); // Velocidad en RPM del motor de paso
  Serial.begin(115200);
}

void loop() {
  // Revisa si hay datos disponibles en el puerto Serial
  if (Serial.available() > 0) {
    char caracter = Serial.read();
    if (caracter == 'p') {
      // Comando 'p#' para avanzar 'pasos' específicos
      int pasos = Serial.parseInt();
      myStepper.step(pasos);
    } else if (caracter == 'f') {
      // Comando 'f' para leer el voltaje de la fotoresistencia
      float voltage = analogRead(puerto_fotoresistencia) * 3.3 / 1023.0;
      Serial.println(voltage);
    } else if (caracter == 's') {
      // Comando 's#' para definir el ángulo de barrido
      angulo_barrido = Serial.parseInt();
      comenzar = 1;  // Activa el barrido
    }
  }

  if (comenzar == 1) {
    // Si se activa el barrido
    comenzar = 0;  // Resetea la bandera de activación
    int Npasos = angulo_barrido * pasosPorGrado; // Calcula el número de pasos según el ángulo de barrido
    for (int i = 0; i < Npasos; i++) {
      // Lee el voltaje de la fotoresistencia
      float voltaje_fotoresistencia = analogRead(puerto_fotoresistencia) * 3.3 / 1023.0;
      
      // Imprime el ángulo y voltaje en Serial
      Serial.print(i / pasosPorGrado); // Ángulo actual basado en pasos
      Serial.print(" ");
      Serial.println(voltaje_fotoresistencia); // Voltaje de la fotoresistencia
      
      delay(100);  // Tiempo entre pasos para que la medición se estabilice
      myStepper.step(1);  // Avanza un paso
    }
  }
}
