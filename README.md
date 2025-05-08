# Lab1Robotica

Integrantes:
- Lucas Erazo
- José Lara
- Claudio Toledo
- Pablo Silva
- José Villamayor

## Preguntas

### 1. ¿Qué función cumple los sensores, actuadores y controladores en el robot?

* **Sensores:** Los sensores son los "sentidos" del robot y lo que capta informacion del entorno.
  - Sensor ultrasonico (HC-SR04): Mide distancias a objetos, permitiendo al robot detectar obstáculos.
  - IMU (MPU6050/MPU9250): Mide la orientación, inclinacion y el movimiento del robot. Son los "sentidos" del robot. Recopilan información del entorno o del estado interno del robot.
    

* **Actuadores:** Son los "músculos" del robot. Su finalidad es hacer acciones físicas, interactuar con el entorno o cambiando el estado del robot.
  - Motores DC : Son los principales actuadores, encargados de mover las ruedas para que el robot se desplace.

* **Controladores:** Son el "cerebro" del robot. Su función es procesar la información de los sensores y tomar decisiones para enviar instrucciones a los actuadores, con la finalidad de cumplir una tarea específica.
   - Arduino UNO: Es el microcontrolador principal. Ejecuta el programa que lee los datos de los sensores y basándose en la lógica programada, envía señales al driver para controlar la velocidad y dirección de los motores.

---

### 2. ¿Cómo se puede estimar la velocidad sin encoders?

Es un proceso menos directo y que conlleva otros pasos y analitica

* **Estimación basada en PWM:**
    * **Método:** Se establece una relación entre el valor del PWM enviado a los motores y la velocidad lineal resultante del robot.  Se mide la distancia recorrida en un tiempo fijo y calcular la velocidad para ese PWM. Repitiendo esto para varios valores de PWM, se puede generar una curva de calibración.
  * **Desventajas:**
    - Hace que sea muy sensible la medicion, ya sea por la carga de la bateria, la superficie donde se mueve o el peso del robot.

* **Estimación basada en IMU:**
    * **Método:** Integrar la aceleración lineal medida por el acelerómetro del IMU a lo largo del tiempo para obtener la velocidad.
    * **Desventajas**
        * Los acelerómetros de bajo costo suelen tener un **ruido** considerable.
        * La integración de estas señales imprecisas acumula errores muy rápidamente, haciendo que la estimación de velocidad sea poco fiable incluso a corto plazo.
        * Requeriría filtros avanzados y bastante calibracion para dar resultados decentes.

---

### 3. ¿Cómo afecta la falta de encoders a la precisión del movimiento?

Los encoders son la principal y más precisa forma de obtener informacion sobre el movimiento del robot, sin estos los datos se degradan y/o se vuelve más complicado de trabajar. Sin estos pueden haber problemas como:
* **Distancia y Giros:** No se pueden recorrer distancias o ejecutar giros con exactitud, ya que no hay medición real del movimiento de las ruedas.
* **Trayectoria Recta:** Dificulta mantener una línea recta debido a diferencias entre motores o superficies.
* **Odometría:** La estimación de la posición del robot (odometría) se vuelve muy poco fiable.
* **Detección de Problemas:** Imposibilita detectar si una rueda patina o se atasca.

---

### 4. ¿Qué es PWM y cómo ayuda a controlar la velocidad de los motores?

* **PWM (Pulse Width Modulation):**
    Es una técnica que permite obtener un comportamiento analógico utilizando una señal digital. Consiste en enviar una serie de pulsos digitales a una frecuencia fija.

* **Control de Velocidad:** Al cambiar el ancho del pulso (ciclo de trabajo), se modifica el voltaje promedio efectivo que recibe el motor. Un pulso más ancho significa mayor voltaje promedio y por lo tanto, mayor velocidad.

---

### 5. ¿Cómo afecta el control de velocidad a la precisión de la navegación sin encoders?

El control de velocidad sin encoders **no mejora fundamentalmente la precisión de la navegación en términos de distancia o ángulos exactos.**
* La principal limitación sigue siendo la **falta de realimentación (feedback)** sobre la velocidad o distancia real recorrida.
* Permite movimientos más suaves o variados, pero la exactitud sigue dependiendo de una calibración que puede no mantenerse constante.
* Es útil para permitir correcciones de rumbo si se usa un IMU, pero esto no resuelve la imprecisión en la medición de la distancia.

---


### Videos
1) [Test de desplazamiento](https://drive.google.com/file/d/1nokwZUeq9rRg8nBmv52C5dTU3TDMIuL5/view?usp=drive_link)
2) [Prueba de giroscopio y acelerometro](https://drive.google.com/file/d/1nlhAjYXBzJLkUY0hQxEpVfxsgM_zUrdT/view?usp=drive_link)
3) [Medicio con sensor ultrasonico](https://drive.google.com/file/d/15SWQwM49HeAbmrr0XVFq3G-2YpeKKy19/view?usp=drive_link)
