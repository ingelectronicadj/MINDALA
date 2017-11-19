/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
 int tiempo = 50;  //milisegundos
 int transicion = 20;  //milisegundos
 int brillo; //Variable auxiliar para condicionales
 //tapete
 int pulsador[6] = {33,34,35,36,37,38};
 int bit0,bit1,bit2,bit3 = LOW;
 int bit4,bit5,bit6,bit7 = LOW;


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
  configPulsadores();
  configurarSalidasPWM();
}

void configPulsadores() {
  for (int i=0; i<6;i++){
    pinMode(pulsador[i], INPUT);
  }
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

void titileoWhite(const byte ledPin,const byte ledPin2,const byte ledPin3) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    delay(tiempo);
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
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


void bloqueGenerador() {
   bit0 = digitalRead(pulsador[0]);
   bit1 = digitalRead(pulsador[1]);
   bit2 = digitalRead(pulsador[2]);
   bit3 = digitalRead(pulsador[3]);
   bit4 = digitalRead(pulsador[4]);
   bit5 = digitalRead(pulsador[5]);

   unsigned int vari=(bit0<<5) | (bit1<<4) | (bit2<<3) | (bit3<<2) | (bit4<<1) | bit5;
   Serial.println(vari);
   delay(250);

   switch (vari) {
         // SERIE 1 titileoRGB / intensidadBrilloRGB
       case 0b010000: titileoRGB(pinB); break;
       case 0b100000: titileoRGB(pinR); break;
       case 0b001000: titileoRGB(pinG); break;
       case 0b000100: titileoCMY(pinG,pinB); break;
       case 0b000010: titileoCMY(pinR,pinB); break;
       case 0b000001: titileoCMY(pinR,pinG); break;
       case 0b000011: titileoWhite(pinR,pinG,pinB); break;
       case 0b000110: titileoWhite(pinR,pinG,pinB); break;
       case 0b001100: titileoWhite(pinR,pinG,pinB); break;
       case 0b011000: titileoWhite(pinR,pinG,pinB); break;
       case 0b110000: titileoWhite(pinR,pinG,pinB); break;
       case 0b100001: titileoWhite(pinR,pinG,pinB); break;
       case 0b100010: titileoWhite(pinR,pinG,pinB); break;
       case 0b100100: titileoWhite(pinR,pinG,pinB); break;
       case 0b101000: titileoWhite(pinR,pinG,pinB); break;
       case 0b010100: titileoWhite(pinR,pinG,pinB); break;
       case 0b010010: titileoWhite(pinR,pinG,pinB); break;
       case 0b010001: titileoWhite(pinR,pinG,pinB); break;
       case 0b001010: titileoWhite(pinR,pinG,pinB); break;
       case 0b001001: titileoWhite(pinR,pinG,pinB); break;
       case 0b000101: titileoWhite(pinR,pinG,pinB); break;
       default:
     // if nothing else matches, do the default
     // default is optional
   break;
 }
}

/*
 ***********************************************************************
 *              LOOP BUCLE PRINCIPAL
 ***********************************************************************
 */
void loop() {
  //leeSerialRGBW2PC(4,10);//# Canales, # veces que se repite
  //blink();
  //rutinaBrillos();
  bloqueGenerador();
}
