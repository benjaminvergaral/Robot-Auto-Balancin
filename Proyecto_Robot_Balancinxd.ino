///////////Librerias//////////
#include <Wire.h>

//////////////////// CONTROL Y VARIABLES MOTORES)////////////
const int L_IN1=1;
const int L_IN2 = 2;
const int L_PMW = 3;
const int R_IN1 = 4; 
const int R_IN2 = 5; 
const int R_PMW = 6; 
int valor = 1;

const int velocidad = 180; 

const int limite_velocidad = 255; 

void MotorIzquierdo(int velocidad, bool adelante){//Funcion para controlar Motor Izquierdo
  if (adelante) { 
    digitalWrite(L_IN1,HIGH);
    digitalWrite(L_IN2, LOW);
    analogWrite(L_PMW,velocidad);
  }
  else{
    digitalWrite(L_IN1,LOW);
    digitalWrite(L_IN2,HIGH);
    analogWrite(L_PMW,velocidad);
  }
}

void MotorDerecho(int velocidad, bool adelante){//Funcion para controlar Motor Derecho
  if (adelante){
    digitalWrite(R_IN1,HIGH);
    digitalWrite(R_IN2,LOW);
    analogWrite(R_PMW, velocidad);
  }
  else{
    digitalWrite(R_IN1,LOW);
    digitalWrite(R_IN2,HIGH);
    analogWrite(R_PMW, velocidad);
  }
}

void Motores(int velocidad, bool adelante){//Funcion para controlar ambos motores
  if (adelante){
    digitalWrite(R_IN1,HIGH);
    digitalWrite(R_IN2,LOW);
    
    digitalWrite(L_IN1,HIGH);
    digitalWrite(L_IN2, LOW);

    analogWrite(R_PMW, velocidad);
    analogWrite(L_PMW,velocidad);
  }
  else{
    digitalWrite(L_IN1,LOW);
    digitalWrite(L_IN2,HIGH);

    digitalWrite(R_IN1,LOW);
    digitalWrite(R_IN2,HIGH);

    analogWrite(R_PMW, velocidad);
    analogWrite(L_PMW,velocidad);

  }
}

void Detener(){//Funcion para detener los motores
  analogWrite(L_PMW,0);
  analogWrite(R_PMW,0);
}

void pruebaMotores(){//Probamos las funciones
  //Prueba Motor Izquierdo adelante
  MotorIzquierdo(velocidad,true);
  delay(1000);
  Detener();
  delay(100);
  
  MotorIzquierdo(velocidad,false);
  delay(1000);
  Detener();
  delay(100);
  
  MotorDerecho(velocidad,true);
  delay(1000);
  Detener();
  delay(100);

  MotorDerecho(velocidad,false);
  delay(1000);
  Detener();
  delay(100);

  Motores(velocidad,true);
  delay(1000);
  Detener();
  delay(100);

  Motores(velocidad,false);
  delay(1000);
  Detener();
  delay(100);

}

/////FIN FUNCIONES MOTORES///////
/////Sección Módulo MPU6050//////
const int MPU_ADDR = 0x68;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int16_t gx_offset = 0, gy_offset = 0, gz_offset = 0;

float roll = 0, pitch = 0, yaw = 0;
unsigned long lastTime;
float dt;



void readMPU6050() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read(); // Skip temperature
  gx = Wire.read() << 8 | Wire.read();
  gy = Wire.read() << 8 | Wire.read();
  gz = Wire.read() << 8 | Wire.read();
}

void calibrateGyro() {
  long sumX = 0, sumY = 0, sumZ = 0;
  const int samples = 100;

  for (int i = 0; i < samples; i++) {
    readMPU6050();
    sumX += gx;
    sumY += gy;
    sumZ += gz;
    delay(5);
  }

  gx_offset = sumX / samples;
  gy_offset = sumY / samples;
  gz_offset = sumZ / samples;
}



void setup() {
  //Configuración de Pines
  pinMode(L_IN1,OUTPUT);
  pinMode(L_IN2,OUTPUT);
  pinMode(L_PMW, OUTPUT);

  pinMode(R_IN1,OUTPUT);
  pinMode(R_IN2,OUTPUT);
  pinMode(R_PMW,OUTPUT);

  //Probamos los Motores
  pruebaMotores();
  delay(100);
  Detener();
  delay(2000);

  Wire.begin();

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Power management
  Wire.write(0);
  Wire.endTransmission(true);
  
  calibrateGyro();
  delay(2000);

  Motores(velocidad,true);
  delay(100);
  Detener();

  lastTime = millis();

}


void loop() {
  readMPU6050();

  unsigned long now = millis();
  dt = (now - lastTime) / 1000.0;
  lastTime = now;

  // Calcular yaw usando el giroscopio
  float gyroZ = (gz - gz_offset) / 131.0;
  yaw += gyroZ * dt;

  // Convertir aceleraciones a float
  float ax_f = (float)ax;
  float ay_f = (float)ay;
  float az_f = (float)az;

  // Calcular roll y pitch
  float denominator = sqrt(ay_f * ay_f + az_f * az_f);

  roll = atan2(ay_f, az_f) * 180.0 / PI;
  pitch = atan2(-ax_f, denominator) * 180.0 / PI;


  // Control básico del motor izquierdo
  if (roll > 3 && roll<60) {
  valor = 10*int(roll);  
    if (8*int(roll)>255){
      valor = 255;
    }

  Motores(valor, true);
}
else if (roll < -3 && roll>-30) {
  valor = 10*int(abs(roll));  
    if (8*int(abs(roll))>255){
      valor = 255;
    }

  Motores(valor, false);

}
else {

  Detener();
}

  delay(100);
}

