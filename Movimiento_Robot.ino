const int Ain1= 1;
const int AIN2 = 2;

const int BIN1 = 3;
const int BIN2 = 4;


const int PMWA=1;
const int PMWB=2;
const int Velocidad = 20;

const int pos_value= 0; //posición con respecto a la linea
const int incline_value=0; //Inclinación del Robot

void RobotFoward(){ //Función para que el robot siga la línea
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  ledcWrite(PMWA, Velocidad + pos_value);
  ledcWrite(PMWB, Velocidad - pos_value);
}

void MotorsFoward(){ //Función para que el robot se balancee
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  
  ledcWrite(PMWA, incline_value);
  ledcWrite(PMWB, incline_value);
}


void MotorsBackward(){ //Función para que el robot se balancee
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  
  ledcWrite(PMWA, incline_value);
  ledcWrite(PMWB, incline_value);
}


void GiroIzquierda(){//Giro sobre el eje 
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  
  ledcWrite(PMWA, Velocidad);
  ledcWrite(PMWB, Velocidad);
}

void GiroDerecha(){//Giro sobre el eje 
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  
  ledcWrite(PMWA, Velocidad);
  ledcWrite(PMWB, Velocidad);
}