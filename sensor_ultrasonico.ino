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
