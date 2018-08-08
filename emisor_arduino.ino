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
// Transmisor

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN 9
#define CSN_PIN 10
 
byte direccion[5] ={'c','a','n','a','l'};

RF24 radio(CE_PIN, CSN_PIN);

int datos[4];

void setup()
{
  
  radio.begin();
  
  Serial.begin(9600); 
 
 radio.openWritingPipe(direccion);
 
 }

 void loop()
{ 

// datos[0]=analogRead(0)* (5.0 / 1023.0);;
//datos[1]=millis();
//datos[2]=3.14;
// Serial.println("leyendo datos");
 datos[0]=analogRead(0);
 datos[1]=analogRead(1);
 datos[2]=analogRead(2);
 datos[3]=analogRead(3);
 
// Serial.println("Datos leidos");
 
 //enviamos los datos
 bool ok = radio.write(datos, sizeof(datos));
  if(ok)
  {
     Serial.print(datos[0]); 
     Serial.print(" , "); 
     Serial.print(datos[1]); 
     Serial.print(" , "); 
     Serial.print(datos[2]); 
     Serial.print(" , "); 
     Serial.println(datos[3]); 
  }
  else
  {
     Serial.println("no se ha podido enviar"); 
  }
  delay(200);
}
