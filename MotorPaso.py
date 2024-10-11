import serial
import time
import matplotlib.pyplot as plt

# Configura el puerto y la velocidad del Serial
ser = serial.Serial('/dev/ttyUSB0', 115200)  # Ajusta el puerto según tu sistema
time.sleep(2)  # Espera a que el puerto Serial esté listo

# Envía el comando de inicio para el barrido
ser.write(b's70\n')  # Comienza con un barrido de 70 grados, puedes ajustar este valor

# Variables para la gráfica en tiempo real
angulos = []
intensidades = []

# Configura la gráfica en tiempo real
plt.ion()
fig, ax = plt.subplots()
line, = ax.plot([], [], 'b-o')
ax.set_xlim(0, 70)  # Límite inicial del eje X
ax.set_ylim(0, 3.3)  # Límite del eje Y para el voltaje máximo de 3.3V
ax.set_xlabel("Ángulo (grados)")
ax.set_ylabel("Intensidad (Voltaje)")

# Inicia la lectura y la gráfica en tiempo real
try:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode().strip()
            angle, intensity = map(float, data.split())
            
            # Agrega los datos a las listas
            angulos.append(angle)
            intensidades.append(intensity)
            
            # Actualiza los datos de la gráfica
            line.set_xdata(angulos)
            line.set_ydata(intensidades)
            
            # Ajusta los límites si se supera el rango de ángulos
            ax.set_xlim(0, max(angulos) + 5)
            fig.canvas.draw()
            fig.canvas.flush_events()

except KeyboardInterrupt:
    print("Deteniendo la adquisición de datos.")
finally:
    ser.close()
