/*
 ***********************************************************************
 *              LIBRERIAS y CONSTANTES
 ***********************************************************************
 */
 
import controlP5.*;//Graficos interactivos
import processing.serial.*;//Lectura y escritura serial
import java.util.Map;//para crear diccionarios

/*Variables previstas para graficos interactivos*/
sliderV sliderV1, sliderV2, sliderV3, sliderV4;

/*Definicion de variables para escribir datos PWM al TIVA*/
Serial puertoSerial;
int LINE_FEED = 10;// <LF> constant
int R,G,B = 0; //Tono rojo


/* Tipo de datos para almacenar imágenes .gif, .jpg, .tga, .png */
PImage img, img2, img3;

/*
 ***********************************************************************
 *              SETUP CONFIGURACIÓN INICIAL
 ***********************************************************************
 */
void setup() {
  size(1400, 800); //Define un tamaño para la interfaz
  img = loadImage("../imagenes/tux.png");
  img2 = loadImage("../imagenes/rgb.png");
  img3 = loadImage("../imagenes/logo.png");

  // Comprueba disponibilidad de puerto serial en la maquina  
  println("Puerto Serial disponible.");
  println("Dispositivo: "+Serial.list()[0]);
  puertoSerial = new Serial(this, Serial.list()[0], 9600);//9600 es el baudrate o tasa de baudios
  // Setup the serialEvent to be called when we receive complete response
  // packets from the HRMI device
  puertoSerial.bufferUntil(LINE_FEED);//caracter en ascii breakline o salto de linea
 
 
  // Creamos Sliders
  // sliderVx = new sliderV(ubicacion x, ubicacion y, ancho, largo, color);
  sliderV1 = new sliderV(925, 50, 90, 255, #FF0000); //125
  sliderV2 = new sliderV(1025, 50, 90, 255, #03FF00); //225
  sliderV3 = new sliderV(1125, 50, 90, 255, #009BFF); //325
}

/****** INICIO FUNCIONES ADICIONALES SETUP******/
/* Funcion para incrustar imagenes y dibujar sliders*/
/* Esta función es un bucle que dibuja en el lienzo, por eso se llama draw.*/
/* Se ejecuta el numero de veces de la tasa de refresco frame rate*/
void draw() {
  dibujarImagenes();
  renderizarSliders();  
  rxtxSerial();
  textos();
}

/* Clase Slider */
class sliderV {
  //atributos del objeto
  int x, y, w, h, p;//h=alto,p=rango de 0 a 255 (altura)
  color col;
  boolean slide;
  String texto;
  //constructor del objeto
  public sliderV (int _x, int _y, int _w, int _h, color _col) {
    x = _x;//Posicion X
    y = _y;//Posicion y
    w = _w;//Ancho
    h = _h;//Alto
    p = 60;//Valor (0-255) del PWM inicial (porcentaje)
    col = _col;//Color
    slide = true;
    texto = "";
  }
  //Función que renderiza el objeto
  private void render() {
    noStroke();//Sin contorno, linea de afuera del rectángulo
    fill(col);//color de relleno
    rect(x-1, y-4, w, h+10);
    fill(100,100,100,100);//Rojo,Verde,Azul,Alfa
    rect(x, h-p+y-5, w-2, 13);
    this.escribirEtiquetas();
    this.mouseOver();
  }
  
  private void escribirEtiquetas() {
    fill(255);
    textSize(11);
    int porcentaje = p * 100 / 255;//Porcentaje
    texto = str(porcentaje) + " %";//Texto porcentaje barras color(sliders)
    text(texto, x+2, h-p+y+6);
  }
  
  private void mouseOver() {
    if (slide==true && mousePressed==true && mouseX < x+w && mouseX > x) {
      if ((mouseY<=y+h+150) && (mouseY>=y-150)) {
        p = h-(mouseY-y);
        if (p<0) {
          p=0;
        } else if (p>h) {
          p=h;
        }
      }
    }
  }
}

void dibujarImagenes() {
  background(0); //Color de fondo 0=negro
  image(img, 730, 200);// img ,posicion x, posicion y TUX
  image(img2, 900, 350); // croma
  image(img3, 0, 10); //logo
}

void renderizarSliders() {
  sliderV1.render();//Renderiza slider
  sliderV2.render();
  sliderV3.render();
}

void textos() {
  textSize(20);
  String creditos = "Explora las combinaciones del color antes de entrar al juego, observa el circulo cromático y saca tus conclusiones...";
  fill(255);
  text(creditos, 650, 340, 300, 400);
}

float tiempoRefrescoDato = 41.667;//mS
int FPS = 24;//tiempoFPS=1/fps;
int bucles = (int)Math.ceil(tiempoRefrescoDato/1000*FPS);//redondeo hacia arriba
int contadorBucles = 1;//Se inicia el contador en 1 vez
void rxtxSerial(){
  //Se envian y reciben los datos a cierta velocidad
  if(contadorBucles>=bucles){
    escribePWMSerial();
    contadorBucles = 0;
  } else {
    contadorBucles++;
  }
}

void escribePWMSerial() {
  // Escribe por puerto Serial caracteres ascci (0-255)
  puertoSerial.write('R');
  puertoSerial.write((sliderV1.p)*55/100); //Se acondiciona para operacion al 55%
  puertoSerial.write('G');
  puertoSerial.write(sliderV2.p);
  puertoSerial.write('B');
  puertoSerial.write(sliderV3.p);
  //puertoSerial.clear();
  
}

void trazoAngular(int x, int y, float anguloRadian, float magnitud){
  strokeWeight(4); // Añade un grosor al trazo
  line(x, y, x+cos(anguloRadian)*magnitud, y-sin(anguloRadian)*magnitud); //line(x1, y1, x2, y2)
}

void keyPressed() {//Cuando se pulse una tecla
  if (key=='s' || key=='S' || key=='q' || key=='Q') {
    exit();//Salimos del programa
  }
}