/*Incluír las librerías a usar*/
#include <Servo.h>
#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>
#define SD_ChipSelectPin 10

TMRpcm tmrpcm;
Servo B_Izquierdo;
Servo B_Derecho;
int velocidad1 = 6, dirPin1 = 7, dirPin2 = 4,velocidad2 = 5, dirPin3 = 3,dirPin4 = 2,velocidadM = 0, valor;
char c;
String state;
String listaWalle[] = {"Wall-edice1.wav", "Wall-edice2.wav", "Wall-edice3.wav"};      	                                                                                                              
String listaadivinanzas[] = {"Adivinanza1.wav", "Adivinanza2.wav", "Adivinanza3.wav"};
void setup() {
  /*definir pines como salida*/
int pins[] = {velocidad1, dirPin1, dirPin2, dirPin3, dirPin4,velocidad2};
  for(int i = 0; i < 10; i++)
  pinMode(pins[i], OUTPUT);

  /*Inizializar motores en 0 (apagados)*/
  digitalWrite(dirPin1,0);
  digitalWrite(dirPin2,0);
  digitalWrite(dirPin3,0);
  digitalWrite(dirPin4,0);
  /*Configurar pines de los servomotores e inizializarlos en 0*/
  B_Izquierdo.attach(0);
  B_Derecho.attach(8);
  B_Izquierdo.write(0);
  B_Derecho.write(0);
  Serial.begin(9600);
  /*Configuración del Lector MicroSD*/
  tmrpcm.speakerPin = 9;
  if(!SD.begin(SD_ChipSelectPin)){
    Serial.println("SD fail");
    return;
  }
  //define volumen y calidad de audio
  tmrpcm.setVolume(5);
}

void loop() {
  /*verificar si existen datos enviados desde la aplicación*/
  while(Serial.available()){
    delay(5);
    c = Serial.read();
    /*Obtener valores de los sliders enviados desde la aplicación y usarlos
    para el control de los servomotores*/
    if(c >= 0 && c <= 9){
      valor = map(c,0,9,0,180);
      B_Izquierdo.write(valor);
     
    }
    else if(c >= 10 && c <= 19){
      valor = map(c,10,19,0,180);
      B_Derecho.write(valor);
    }
    /*Obtener los valores del tercer slider y usarlo para el control de la velocidad*/
    else if(c >= 20 && c <= 29){
      valor = map(c,20,29,150,255);
      velocidadM = valor;
    }
    /*Usar el comando switch para realizar acciones dependiendo de cada caso específico*/
    switch (c) {
      case 50:
        digitalWrite(dirPin1,1);
        digitalWrite(dirPin2,0);
        analogWrite(velocidad1,velocidadM);
        digitalWrite(dirPin3,1);
        digitalWrite(dirPin4,0);
        analogWrite(velocidad2,velocidadM);
        delay(1);
        //adelante
        break;
      case 51:
        digitalWrite(dirPin1,0);
        digitalWrite(dirPin2,1);
        analogWrite(velocidad1,velocidadM);
        digitalWrite(dirPin3,0);
        digitalWrite(dirPin4,1);
        analogWrite(velocidad2,velocidadM);
        delay(1);
        // atras
        break;
      case 52:
        digitalWrite(dirPin1,0);
        digitalWrite(dirPin2,1);
        analogWrite(velocidad1,velocidadM);
        digitalWrite(dirPin3,1);
        digitalWrite(dirPin4,0);
        analogWrite(velocidad2,velocidadM);
        delay(1);
        //Izquierda
        break;
      case 53:
        digitalWrite(dirPin1,1);
        digitalWrite(dirPin2,0);
        analogWrite(velocidad1,velocidadM);
        digitalWrite(dirPin3,0);
        digitalWrite(dirPin4,1);
        analogWrite(velocidad2,velocidadM);
        delay(1);
        //Derecha
        break;
      case 54:
        digitalWrite(dirPin1,0);
        digitalWrite(dirPin2,0);
        digitalWrite(dirPin3,0);
        digitalWrite(dirPin4,0);
      break;
      default:
       state += c;
       Serial.println(state);
      break;
    }
  }
  /*En el caso de obtener cadenas de caracteres se les aplica sentencias
  condicionales para realizar diferentes acciones*/
  if (state.length() > 0) {
    if (state == "baila") {
      tmrpcm.play("bailar.wav");
      for (int x=0; x<5; x++) {
        digitalWrite(dirPin1, 1);
        digitalWrite(dirPin2, 0);
        analogWrite(velocidad1, velocidadM);
        digitalWrite(dirPin3, 0);
        digitalWrite(dirPin4, 1);
        analogWrite(velocidad2, velocidadM);
        delay(1000);
        digitalWrite(dirPin1, 0);
        digitalWrite(dirPin2, 1);
        analogWrite(velocidad1, velocidadM);
        digitalWrite(dirPin3, 1);
        digitalWrite(dirPin4, 0);
        analogWrite(velocidad2, velocidadM);
        delay(1000);
        digitalWrite(dirPin1, 1);
        digitalWrite(dirPin2, 0);
        analogWrite(velocidad1, velocidadM);
        digitalWrite(dirPin3, 1);
        digitalWrite(dirPin4, 0);
        analogWrite(velocidad2, velocidadM);
        delay(1000);
        digitalWrite(dirPin1, 0);
        digitalWrite(dirPin2, 1);
        analogWrite(velocidad1, velocidadM);
        digitalWrite(dirPin3, 0);
        digitalWrite(dirPin4, 1);
        Serial.println(velocidadM);
        analogWrite(velocidad2, velocidadM);
        delay(1000);
      }
      tmrpcm.pause();
    }
    else if (state == "saluda") {
      tmrpcm.play("Saludo.wav");
      Serial.println("si funciona XD");
      digitalWrite(dirPin1,0);
      digitalWrite(dirPin2,1);
      analogWrite(velocidad1,velocidadM);
      digitalWrite(dirPin3,0);
      digitalWrite(dirPin4,1);
      analogWrite(velocidad2,velocidadM);
      delay(2000);
      tmrpcm.pause();
    }
    else if(state == "canta"){
      tmrpcm.play("cantar.wav");
      delay(20000);
      tmrpcm.pause();  
    }
    else if (state == "celebra"){
      tmrpcm.play("celebrar.wav");
      for(int x=0;x<5;x++){
        B_Derecho.write(180);
        B_Izquierdo.write(0);
        B_Derecho.write(0);
        B_Izquierdo.write(180);
      }
      tmrpcm.pause();    
    }
    else if (state == "cuenta un cuento"){
      tmrpcm.play("cuento.wav");
      B_Derecho.write(180);
      B_Izquierdo.write(0);
      delay(10000);
      B_Derecho.write(0);
      B_Izquierdo.write(180);
      delay(10000);
      B_Derecho.write(180);
      B_Izquierdo.write(0);
      delay(2000);
      tmrpcm.pause();  
    }
    else if (state == "silva"){
      tmrpcm.play("silvar.wav");
      B_Derecho.write(180);
      B_Izquierdo.write(180);
      delay(2000);
      tmrpcm.pause();  
    }
    digitalWrite(dirPin1, 0);
    digitalWrite(dirPin2, 0);
    digitalWrite(dirPin3, 0);
    digitalWrite(dirPin4, 0);
    state ="";
  }
}