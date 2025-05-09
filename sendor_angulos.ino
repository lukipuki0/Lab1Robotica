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
