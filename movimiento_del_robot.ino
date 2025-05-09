
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