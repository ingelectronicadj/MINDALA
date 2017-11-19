/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
 int tiempo = 1000;  //milisegundos
 int transicion = 20;  //milisegundos
 int brillo; //Variable auxiliar para condicionales

/****Pines Lectura RGBW****/
int pinR = 23;
int pinG = 24;
int pinB = 25;

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup() {
  Serial.begin(9600);
  configurarSalidasPWM();
}


void configurarSalidasPWM() {
  pinMode(pinR, OUTPUT); // rojo
  pinMode(pinG, OUTPUT); // verde
  pinMode(pinB, OUTPUT); // azul
}


/**********************************************************/

void leeSerialRGBW2PC(int canales, int veces){
  for (int i=0; i<veces; i++){
    for (int j=0; j<canales; j++){
      leerBandaRGBW();
    }
  }
}

void leerBandaRGBW() {
  switch(leerPuerto()){
   case 'R':
    analogWrite(pinR, leerPuerto());
    break;
   case 'G':
    analogWrite(pinG, leerPuerto());
    break;
   case 'B':
    analogWrite(pinB, leerPuerto());
    break;
   }
}
// lee el puerto serial
int leerPuerto() {
  while (Serial.available()<=0) {}
  return Serial.read();
}


/*********************************************************/

void blink(){
    titileoRGB(pinR); //Rojo
    titileoRGB(pinG); //Verde
    titileoRGB(pinB); //Azul
    titileoCMY(pinG,pinB); // Cian
    titileoCMY(pinR,pinB); // Magenta
    titileoCMY(pinR,pinG); // Amarillo
}

void titileoRGB(const byte ledPin) {
    digitalWrite(ledPin, HIGH);
    delay(tiempo);
    digitalWrite(ledPin, LOW);
    delay(transicion);
}

void titileoCMY(const byte ledPin,const byte ledPin2) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin2, HIGH);
    delay(tiempo);
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
    delay(transicion);
}

void rutinaBrillos(){
  intensidadBrilloRGB(pinR);
  intensidadBrilloRGB(pinG);
  intensidadBrilloRGB(pinB);
  intensidadBrilloCMY(pinG,pinB); // Cian
  intensidadBrilloCMY(pinR,pinB); // Magenta
  intensidadBrilloCMY(pinR,pinG); // Amarillo
}

void intensidadBrilloRGB(const byte ledPin){
  for(brillo=0; brillo<=255; brillo++){
      analogWrite(ledPin, brillo);
      delay(transicion); // tiempo de transicion
     }
     analogWrite(ledPin, 0);
     //delay(1000); // Sostiene el color 1s
}

void intensidadBrilloCMY(const byte ledPin,const byte ledPin2){
  for(brillo=0; brillo<=255; brillo++){
      analogWrite(ledPin, brillo);
      analogWrite(ledPin2, brillo);
      delay(transicion); // tiempo de transicion
     }
     analogWrite(ledPin, 0);
     analogWrite(ledPin2, 0);
     //delay(1000); // Sostiene el color 1s
}

/*
 ***********************************************************************
 *              LOOP BUCLE PRINCIPAL
 ***********************************************************************
 */
void loop() {
  leeSerialRGBW2PC(4,10);//# Canales, # veces que se repite
  //blink();
  //rutinaBrillos();
}
