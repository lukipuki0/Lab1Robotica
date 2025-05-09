# Lab1Robotica

Integrantes:
- Lucas Erazo
- José Lara
- Claudio Toledo
- Pablo Silva
- José Villamayor

## Preguntas I

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
      - Los acelerómetros de bajo costo suelen tener más ruido y el calculo de las señales imprecisas acumula errores muy rápidamente, haciendo que la estimación de velocidad sea poco fiable y además requeriría filtros avanzados y bastante calibracion para dar resultados decentes.

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

## Preguntas II

---

### 1. ¿Cómo se calcula la velocidad del robot sin encoders usando PWM?

La velocidad se estima mediante un proceso de calibración empírica:
1.  Se aplica un valor de PWM constante a los motores.
2.  Se mide la distancia que el robot recorre en un tiempo determinado.
3.  Se calcula la velocidad como: $Velocidad = \frac{Distancia}{Tiempo}$.
4.  Este proceso se repite para diferentes valores de PWM para crear una tabla que relacione PWM con una velocidad aproximada.
    * **Limitación:** Como se dijo antes, esta forma es muy sensible a variaciones (batería, superficie, carga) y no es precisa en tiempo real.

---

### 2. ¿Cómo factores afectan la trayectoria y velocidad del robot al cambiar los intervalos de tiempo?

Cambiar los intervalos de tiempo en los que se aplican comandos o se toman lecturas afecta principalmente la **reactividad y la suavidad del movimiento** y puede interactuar con otros factores:

* **Intervalos Cortos:** Mayor reactividad y control fino. Riesgo de sobrecarga/ruido.
* **Intervalos Largos:** Menor reactividad, posible movimiento a tirones, mayor acumulación de error.

---

### 3. ¿Cuáles son las ventajas y desventajas de usar un IMU para ajustar la dirección en lugar de encoders?

* **Ventajas de usar IMU:**
    * **Referencia Absoluta (parcial):** El IMU puede dar una idea del rumbo absoluto o mantener una dirección relativa al entorno, independientemente del deslizamiento de las ruedas.
    * **Detección de Perturbaciones Externas:** Detecta giros o inclinaciones causados por el terreno o colisiones leves que los encoders no registrarían como un cambio intencional de dirección basado en la rotación de las ruedas.
    * **Independiente del Deslizamiento:** La corrección de rumbo con IMU funciona incluso si las ruedas patinan, ya que mide la orientación real del chasis.

* **Desventajas de usar IMU:**
    * **Deriva (Drift):** Los giroscopios de los IMU sufren deriva con el tiempo, acumulando error en la estimación del ángulo.
    * **Ruido:** Las lecturas del IMU pueden ser ruidosas, necesitando filtrado.
    * **No mide rotación de ruedas:** Un IMU no informa sobre la distancia recorrida ni la velocidad de las ruedas, información que los encoders sí proporcionan y es crucial para giros precisos basados en el movimiento diferencial de las ruedas.
    * **Complejidad:** Implementar una fusión sensorial robusta para obtener un ángulo de Yaw estable puede ser más complejo que usar encoders para controlar giros por conteo de pulsos.
    * **Corrección reactiva, no predictiva:** El IMU corrige una desviación *después* de que ocurre. Los encoders pueden permitir un control más proactivo del ángulo de giro basado en el movimiento deseado de cada rueda.

---

### 4. ¿Qué efecto tiene la inclinación o el giro en el movimiento del robot, y cómo se corrige con el IMU?

* **Efecto de la Inclinación:**
    * **Cambio en la tracción:** Si el robot se inclina significativamente, la distribución del peso sobre las ruedas cambia. Esto puede afectar la tracción de cada rueda de manera desigual, haciendo que una patine más que la otra, lo que desvía al robot de su trayectoria o altera su velocidad.
    * **Afecta la estabilidad:** Una inclinación excesiva puede llevar al vuelco.
    * **Sensores:** Puede afectar las lecturas de otros sensores.

* **Efecto del Giro:**
    * **Desvío de la trayectoria:** El robot no sigue la línea recta o la curva deseada. Esto puede ser causado por diferencias en la velocidad de los motores, superficies irregulares, o perturbaciones externas.

* **Cómo se corrige con el IMU:**
    * **Corrección de Inclinación:**
        * El IMU detecta los ángulos de Pitch y Roll.
        * Esta información es crítica para mantener el equilibrio ajustando activamente los actuadores.
        * Adaptar la velocidad o la potencia de los motores para intentar compensar la pendiente.

    * **Corrección de Giro (Yaw):**
        * El IMU detecta el ángulo de Yaw actual.
        * Se compara este ángulo con un ángulo de Yaw deseado.
        * Si hay una diferencia, un algoritmo de control ajusta diferencialmente la velocidad de los motores:
            * Si el robot giró a la derecha sin querer, se aumenta la velocidad del motor derecho y/o se disminuye la del izquierdo para corregir hacia la izquierda.
            * Si giró a la izquierda, se hace lo opuesto.

---

## Codificacíon

### Parte 1

* **Prueba de movimiento inicial**
  const int IN1 = 9;  
  const int IN2 = 10;  
  const int ENA = 11;  
  
  const int IN3 = 4;
  const int IN4 = 5; 
  const int ENB = 6;  
  
  void setup() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    
    detener();
    
    delay(2000);
    
    ejecutarSecuenciaPrueba();
  }
  
  void loop() {
    ejecutarSecuenciaPrueba();
    delay(3000); 
  
  void avanzar() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  
  void retroceder() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  
  void girarDerecha() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  
  void girarIzquierda() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  
  void detener() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  
  void ejecutarSecuenciaPrueba() {
    avanzar();
    delay(500);
    
    detener();
    delay(1000);
    
    retroceder();
    delay(500);
    
    detener();
    delay(1000);
    
    girarDerecha();
    delay(500);
    
    detener();
    delay(1000);
    
    girarIzquierda();
    delay(500);
    
    detener();
    delay(1000);
  }

* **Prueba de sensor ultrasónico**
  const int TRIG = 2;
  const int ECHO = 3;
  
  size_t duracion;
  float distancia;
  float distanciaEnCm;
  
  void setup() {
    Serial.begin(9600);
    Serial.println("Iniciando el ultrasónico");
  
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
  
    digitalWrite(TRIG, LOW);
  
    Serial.println("Sensor ultrasónico iniciado.");
    Serial.println("Mostrando mediciones de distancia cada 500ms:");
  
  }
  
  void loop() {
  
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
  
    duracion = pulseIn(ECHO, HIGH);
    distanciaEnCm = (duracion * 0.0343) / 2; 
  
    Serial.print("Distancia: ");
    Serial.print(distanciaEnCm);
    Serial.println(" cm");
  
    delay(1000);
  }

* **Prueba de MPU**
  #include <Wire.h>
  #include <MPU9250_asukiaaa.h>
  
  MPU9250_asukiaaa mpu;
  
  float gyroBiasX = 0, accelBiasX = 0;
  const int N = 500;
  
  void setup() {
    Serial.begin(115200);
    Wire.begin();
    mpu.setWire(&Wire);
    mpu.beginAccel();
    mpu.beginGyro();
    delay(1000);
  
    Serial.println("Calibrando...");
  
    for (int i = 0; i < N; i++) {
      mpu.accelUpdate();
      mpu.gyroUpdate();
      gyroBiasX += mpu.gyroX();
      accelBiasX += mpu.accelX();
      delay(5);
    }
  
    gyroBiasX /= N;
    accelBiasX /= N;
  
    Serial.print("Bias del giroscopio X: ");
    Serial.println(gyroBiasX);
    Serial.print("Bias del acelerómetro X: ");
    Serial.println(accelBiasX);
  }
  
  void loop() {
    mpu.accelUpdate();
    mpu.gyroUpdate();
  
    float gyroX_corr = mpu.gyroX() - gyroBiasX;
    float accelX_corr = mpu.accelX() - accelBiasX;
  
    Serial.print("Giro corregido X: ");
    Serial.print(gyroX_corr);
    Serial.print(" | Aceleración corregida X: ");
    Serial.println(accelX_corr);
  
    delay(100);
  }

### parte 2

* **Prueba de movimiento con las ecuaciones**

  #include <math.h>
  
  // Motor A 
  const int IN1 = 9;  
  const int IN2 = 10; 
  const int ENA = 11; 
  
  // Motor B 
  const int IN3 = 4; 
  const int IN4 = 5;
  const int ENB = 6; 
  
  const float WHEEL_RADIUS = 0.033;     
  const float WHEEL_BASE_WIDTH = 0.15;
  
  const float MOTOR_LINEAR_SPEED = 0.15;   
  
  float robot_x = 0.0;     
  float robot_y = 0.0;    
  float robot_theta = 0.0; 
  
  void setup() {
    Serial.begin(9600); 
  
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
  
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
  
    detener();
  
    Serial.println("Robot listo. Iniciando secuencia de prueba en 2 segundos...");
    Serial.println("Pose inicial: X=0.00, Y=0.00, Theta=0.00 deg");
  
    delay(2000);
  
    ejecutarSecuenciaPrueba();
  }
  
  void loop() {
    ejecutarSecuenciaPrueba();
    Serial.println("--- Secuencia completada, esperando 3 segundos ---");
    delay(3000); 
  }
  
  void avanzar() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  }
  
  void retroceder() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);  
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);  
  }
  
  void girarDerecha() {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); 
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); 
  }
  
  void girarIzquierda() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); 
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); 
  
  void detener() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); 
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); 
  
  /**
   * @param vL 
   * @param vR
   * @param dt 
   */
  
  void updatePosition(float vL, float vR, float dt) {
    if (dt == 0) return; 
  
    float v_robot = (vR + vL) / 2.0;
    float omega_robot = (vR - vL) / WHEEL_BASE_WIDTH;
  
    float dx = v_robot * cos(robot_theta) * dt;
    float dy = v_robot * sin(robot_theta) * dt;
    float d_theta = omega_robot * dt;
  
    robot_x += dx;
    robot_y += dy;
    robot_theta += d_theta;
  
    while (robot_theta > M_PI) {
      robot_theta -= 2.0 * M_PI;
    }
    while (robot_theta < -M_PI) {
      robot_theta += 2.0 * M_PI;
    }
  
    Serial.print("Pose estimada -> ");
    Serial.print("X: "); Serial.print(robot_x, 3);
    Serial.print(" m, Y: "); Serial.print(robot_y, 3);
    Serial.print(" m, Theta: "); Serial.print(robot_theta * 180.0 / M_PI, 2);
    Serial.println(" deg");
  }
  
  void ejecutarSecuenciaPrueba() {
    float duration;
  
    Serial.println("Iniciando secuencia de prueba...");
  
    duration = 0.5; 
    Serial.print("Avanzando por "); Serial.print(duration); Serial.println("s");
    avanzar();
    delay((unsigned long)(duration * 1000));
    updatePosition(MOTOR_LINEAR_SPEED, MOTOR_LINEAR_SPEED, duration);
  
    duration = 1.0;
    Serial.print("Deteniendo por "); Serial.print(duration); Serial.println("s");
    detener();
    delay((unsigned long)(duration * 1000));
    updatePosition(0.0, 0.0, duration);
  
    duration = 0.5; 
    Serial.print("Retrocediendo por "); Serial.print(duration); Serial.println("s");
    retroceder();
    delay((unsigned long)(duration * 1000));
    updatePosition(-MOTOR_LINEAR_SPEED, -MOTOR_LINEAR_SPEED, duration);
  
    duration = 1.0;
    Serial.print("Deteniendo por "); Serial.print(duration); Serial.println("s");
    detener();
    delay((unsigned long)(duration * 1000));
    updatePosition(0.0, 0.0, duration);
  
    duration = 0.5;
    Serial.print("Girando a la derecha por "); Serial.print(duration); Serial.println("s");
    girarDerecha(); 
    delay((unsigned long)(duration * 1000));
    updatePosition(MOTOR_LINEAR_SPEED, -MOTOR_LINEAR_SPEED, duration);
  
    duration = 1.0; 
    Serial.print("Deteniendo por "); Serial.print(duration); Serial.println("s");
    detener();
    delay((unsigned long)(duration * 1000));
    updatePosition(0.0, 0.0, duration);
  
    duration = 0.5;
    Serial.print("Girando a la izquierda por "); Serial.print(duration); Serial.println("s");
    girarIzquierda(); 
    delay((unsigned long)(duration * 1000));
    updatePosition(-MOTOR_LINEAR_SPEED, MOTOR_LINEAR_SPEED, duration);
  
    duration = 1.0; 
    Serial.print("Deteniendo por "); Serial.print(duration); Serial.println("s");
    detener();
    delay((unsigned long)(duration * 1000));
    updatePosition(0.0, 0.0, duration);
  
    Serial.println("Fin de la secuencia de prueba.");
    Serial.print("Pose final estimada: ");
    Serial.print("X: "); Serial.print(robot_x, 3);
    Serial.print(" m, Y: "); Serial.print(robot_y, 3);
    Serial.print(" m, Theta: "); Serial.print(robot_theta * 180.0 / M_PI, 2);
    Serial.println(" deg");
    Serial.println("------------------------------------");
  }

* **Codigo de ajuste de posición**
  #include <Wire.h>
#include <MPU9250_asukiaaa.h> 
#include <math.h>           


const float WHEEL_DISTANCE = 0.13;      
const unsigned long INITIAL_DELAY_MS = 8000; 
const unsigned long MOVEMENT_DURATION_MS = 10000; 
const int BASE_SPEED_PWM = 150;           


const int ENA = 11; 
const int IN1 = 9;  
const int IN2 = 10; 
const int ENB = 6;  
const int IN3 = 4;  
const int IN4 = 5;  
const float WHEEL_BASE = 0.15;      
const float MAX_MOTOR_SPEED_MPS = 0.5; 

float robotX = 0.0;     
float robotY = 0.0;     
int currentPwmLeft = 0;
int currentPwmRight = 0;
int dirLeft = 0;
int dirRight = 0;
unsigned long lastTimeKinematics = 0;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
  Serial.println("Estimacion de Posicion con Cinematica Diferencial");
  Serial.println("Robot inicia en (0,0) Theta=0");

  lastTimeKinematics = millis();
}

void moverAdelante(int velocidadIzquierda, int velocidadDerecha) {
  velocidadIzquierda = constrain(velocidadIzquierda, 0, 255);
  velocidadDerecha = constrain(velocidadDerecha, 0, 255);

  Serial.print("Moviendo Adelante - PWM Izq: "); Serial.print(velocidadIzquierda);
  Serial.print(" PWM Der: "); Serial.println(velocidadDerecha);

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidadIzquierda);

  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  analogWrite(ENB, velocidadDerecha);

  currentPwmLeft = velocidadIzquierda;
  currentPwmRight = velocidadDerecha;
  dirLeft = 1;
  dirRight = 1;
}

void moverAtras(int velocidadIzquierda, int velocidadDerecha) {
  velocidadIzquierda = constrain(velocidadIzquierda, 0, 255);
  velocidadDerecha = constrain(velocidadDerecha, 0, 255);

  Serial.print("Moviendo Atras - PWM Izq: "); Serial.print(velocidadIzquierda);
  Serial.print(" PWM Der: "); Serial.println(velocidadDerecha);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidadIzquierda);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, velocidadDerecha);

  currentPwmLeft = velocidadIzquierda;
  currentPwmRight = velocidadDerecha;
  dirLeft = -1;
  dirRight = -1;
}

void girarIzquierda(int velocidad) { 
  velocidad = constrain(velocidad, 0, 255);
  Serial.print("Girando Izquierda - Velocidad: "); Serial.println(velocidad);

  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidad);

  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  analogWrite(ENB, velocidad);

  currentPwmLeft = velocidad;
  currentPwmRight = velocidad;
  dirLeft = -1; 
  dirRight = 1; 
}

void girarDerecha(int velocidad) { 
  velocidad = constrain(velocidad, 0, 255);
  Serial.print("Girando Derecha - Velocidad: "); Serial.println(velocidad);

  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidad);

  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, velocidad);

  currentPwmLeft = velocidad;
  currentPwmRight = velocidad;
  dirLeft = 1;  
  dirRight = -1; 
}

void detenerMotores() {
  Serial.println("Deteniendo Motores");
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  currentPwmLeft = 0;
  currentPwmRight = 0;
  dirLeft = 0;
  dirRight = 0;
}

void actualizarCinematica() {
  unsigned long currentTime = millis();
  float deltaTime = (currentTime - lastTimeKinematics) / 1000.0; // Delta t en segundos
  lastTimeKinematics = currentTime;

  if (deltaTime == 0) return; 

  float vL_mps = dirLeft  * (currentPwmLeft / 255.0) * MAX_MOTOR_SPEED_MPS;
  float vR_mps = dirRight * (currentPwmRight / 255.0) * MAX_MOTOR_SPEED_MPS;

  float v_robot_mps = (vR_mps + vL_mps) / 2.0;
  float omega_robot_radps = (vR_mps - vL_mps) / WHEEL_BASE; // Radianes por segundo

  float deltaTheta = omega_robot_radps * deltaTime;
  float avgTheta = robotTheta + deltaTheta / 2.0;

  float deltaX = v_robot_mps * cos(avgTheta) * deltaTime;
  float deltaY = v_robot_mps * sin(avgTheta) * deltaTime;

  robotX += deltaX;
  robotY += deltaY;
  robotTheta += deltaTheta;

  while (robotTheta > PI) robotTheta -= 2 * PI;
  while (robotTheta < -PI) robotTheta += 2 * PI;
}

void loop() {
  actualizarCinematica();

  moverAdelante(180, 180); 
  delay(2000);             
  actualizarCinematica();  
  imprimirPose();

  detenerMotores();
  delay(1000);
  actualizarCinematica();
  imprimirPose();

  girarDerecha(150);      
  delay(1000);             
  actualizarCinematica();
  imprimirPose();

  detenerMotores();
  delay(1000);
  actualizarCinematica();
  imprimirPose();

  moverAdelante(180,180); 
  delay(1500);
  actualizarCinematica();
  imprimirPose();

  detenerMotores();
  delay(1000);
  actualizarCinematica();
  imprimirPose();


  Serial.println("--- Fin de Secuencia --- Esperando 10s ---");
  delay(10000); 
}

void imprimirPose() {
  Serial.print("Pose Estimada: X=");
  Serial.print(robotX, 4); 
  Serial.print(" m, Y=");
  Serial.print(robotY, 4);
  Serial.print(" m, Theta=");
  Serial.print(robotTheta * 180.0 / PI, 2); 
  Serial.println(" deg");
}



### Aspectos adicionales

Tuvimos problemas con el motor derecho de nuestro robot rotande de manera mas lenta que su contraparte restringiendo el ajuste de su posicion.

### Videos
1) [Test de desplazamiento](https://drive.google.com/file/d/1nokwZUeq9rRg8nBmv52C5dTU3TDMIuL5/view?usp=drive_link)
2) [Prueba de giroscopio y acelerometro](https://drive.google.com/file/d/1nlhAjYXBzJLkUY0hQxEpVfxsgM_zUrdT/view?usp=drive_link)
3) [Medicio con sensor ultrasonico](https://drive.google.com/file/d/15SWQwM49HeAbmrr0XVFq3G-2YpeKKy19/view?usp=drive_link)
4) [Video ejercicio 2.2 parte 1](https://drive.google.com/file/d/1oN8sdKT6e6eRqnFSMuFRyw29IkOSf3lg/view?usp=drive_link)
5) [Video ejercicio 2.2 parte 2](https://drive.google.com/file/d/1o7HBVTGWAaULxNEcVYtREUhBlEsQpCmD/view?usp=drive_link)
