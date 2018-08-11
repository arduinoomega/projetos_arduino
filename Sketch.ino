#define tmpMaxPalma  100 //Tempo se encontra em milisegundos
#define tmpMaxPalmas 500 //Tempo se encontra em milisegundos
#define pinMic 7
#define pinRelay 8

unsigned long tmpEspera = 0;
unsigned long tmpPalmas = 0;
int contPalmas = 0;
void Action();

void setup() {
  pinMode(pinMic, INPUT);
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, HIGH); //Ligar arduino com Relay desligado
}

void loop() {
  //verifica o estado do sensor de som (ele fica normalmente com a porta ligada. Quando ouver uma palma, ele desliga momentaneamente a porta)
  int sensorMic = digitalRead(pinMic);

  //se o sensor detectou palmas
  if (sensorMic == LOW) {

     //espera um tempo para nao detectar a mesma palma mais de uma vez 
     if (tmpEspera == 0) {
        tmpEspera = tmpPalmas = millis(); 
        contPalmas++;
     } else if ((millis() - tmpEspera) >= tmpMaxPalma) {
        tmpEspera = 0;
     }
  }

  //caso exceda o tempo maximo entre palmas, zera o contador de palmas
  if ( (contPalmas != 0) && ((millis() - tmpPalmas) > 500) ) {
     Action();
     contPalmas = 0;
     tmpPalmas = millis();
  }
  
}


void Action() 
{
  
  switch (contPalmas) {
    case 2: 
       digitalWrite(pinRelay, !digitalRead(pinRelay));
       break;
  }
}
