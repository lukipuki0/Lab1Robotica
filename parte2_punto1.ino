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
