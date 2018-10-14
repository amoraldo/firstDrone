/*
UVIDrone: Julio 2018

Configuracion del Drone:

cw    ccw
(3)   (1)
  \   /
   \ /
   ( )
   / \
  /   \
(2)   (4)
ccw    cw
*/

// receptor

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
//Declaremos los pines CE y el CSN
#define CE_PIN 8
#define CSN_PIN 10
 
#define Motor1 2
#define Motor2 3
#define Motor3 4
#define Motor4 5

//Definimos los centros de los sticks
int o_Stick1 = 522;
int o_Stick2 = 468;
int o_Stick3 = 563;
int o_Stick4 = 539;


//Variable con la dirección del canal que se va a leer
byte direccion[5] ={'c','a','n','a','l'}; 

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector para los datos recibidos
int datos[4];
int val_min=20;   // Defino el valor minimo de funcionamiento de los motores
// Definimos las ganancias de cada stick
float w1 = 1;
float w2 = 0.2;
float w3 = 0.2;
float w4 = 0.2;

int mot1,mot2,mot3,mot4;

void setup()
{
 //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
  
  //Abrimos el canal de Lectura
  radio.openReadingPipe(1, direccion);
  
  //empezamos a escuchar por el canal
  radio.startListening();

  //Defino los pines de los motores como Salidas
  pinMode(Motor1,OUTPUT);
  pinMode(Motor2,OUTPUT);
  pinMode(Motor3,OUTPUT);
  pinMode(Motor4,OUTPUT);

}
 
void loop() {
 uint8_t numero_canal;
 //if ( radio.available(&numero_canal) )
 if ( radio.available() )
 {    
     //Leemos los datos y los guardamos en la variable datos[]
     radio.read(datos,sizeof(datos));
     
     //reportamos por el puerto serial los datos recibidos
     Serial.print("Stick1 = " );
     Serial.print(datos[0]);
     Serial.print(", Stick2 = " );
     Serial.print(datos[1]);
     Serial.print(", Stick3 = ");
     Serial.print(datos[2]);
     Serial.print(", Stick4 = ");
     Serial.print(datos[3]);


     // Stick1
     mot1 = (datos[0] / 4) * w1;
     mot2 = (datos[0] / 4) * w1;
     mot3 = (datos[0] / 4) * w1;
     mot4 = (datos[0] / 4) * w1;

     // Stick2
//     mot1 = mot1 - w2 * ((datos[1] - o_Stick2) / 4);
//     mot2 = mot2 - w2 * ((datos[1] - o_Stick2) / 4);
//     mot3 = mot3 + w2 * ((datos[1] - o_Stick2) / 4);
//     mot4 = mot4 + w2 * ((datos[1] - o_Stick2) / 4);

     // Stick3
     mot1 = mot1 - w3 * ((datos[2] - o_Stick3) / 4);
     mot2 = mot2 + w3 * ((datos[2] - o_Stick3) / 4);
     mot3 = mot3 - w3 * ((datos[2] - o_Stick3) / 4);
     mot4 = mot4 + w3 * ((datos[2] - o_Stick3) / 4);

     // Stick4
     mot1 = mot1 - w4 * ((datos[3] - o_Stick4) / 4);
     mot2 = mot2 + w4 * ((datos[3] - o_Stick4) / 4);
     mot3 = mot3 + w4 * ((datos[3] - o_Stick4) / 4);
     mot4 = mot4 - w4 * ((datos[3] - o_Stick4) / 4);
  

     if (datos[0]<=val_min){mot1=0;mot2=0;mot3=0;mot4=0;} 

     Serial.print(", Motor1 = " );
     Serial.print(mot1);
     Serial.print(", Motor2 = " );
     Serial.print(mot2);
     Serial.print(", Motor3 = " );
     Serial.print(mot3);
     Serial.print(", Motor4 = " );
     Serial.println(mot4);
 
 }
 else
 {
     Serial.println("No hay datos de radio disponibles");
 }

 analogWrite(Motor1,mot1);
 analogWrite(Motor2,mot2);
 analogWrite(Motor3,mot3);
 analogWrite(Motor4,mot4);

 delay(200);
}
