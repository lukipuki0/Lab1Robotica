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