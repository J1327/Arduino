#include <Adafruit_NeoPixel.h> //svarbus elementas ,pagrindas

//NURODYMAI
#define PIN 3 // D? - LED DATA Laidelis ijungtas i arduino nano siuo atveju D3
#define MIC_PIN A3 // A? -Mikrofono DATA Laidelis ijungtas i arduino nano siuo atveju A0
#define lightCount 144 //nurodyti kiek lempuciu bus aktyvios
#define STRENGHT 18   // galima padidinti arba sumazinti rodoma garsuma , iprastai "1" , Didesnis Skaicius PRAILGINA UZKROVIMA [2020.11.26] , "0" ISJUNGIA LEMPPUTES
#define THRESHOLD 18 // Sulaiko Pasalinius Garsus [2020.11.26] , iprastai "18" , SENSORIAUS JAUTRUMO NESUMAZINA
#define POWER 10 // Ryskumas [2020.11.23/2020.11.26] , Didesnis Skaicius PRAILGINA GALUTINI UZKROVIMA?
#define DURATION 3 // Trukme kiek laiko pasiliks ties tuo paciu garsu  , iprastai leciausias "1" - greiciausias "3" , "0" lemputes tiesiog sviecia , SUMAZINUS MIKROFONUI DAUGIAU GARSO
// didesnis garsumas maziau  "tikroviskumo" , mazesnis garsumas didesnis "tikroviskumas"..

//VCC - 3V3
//GND - GND
//OUT - A0

//

Adafruit_NeoPixel strip = Adafruit_NeoPixel(lightCount, PIN,NEO_GRB + NEO_KHZ800);//LED TIPAS GRB = RGB , naudoti google ar kita RGB spalvu "paemeja"

//KINTAMIEJI
int vol = 0;
float total = 0;
int fadeCol = 0;
int val[25];
int volLast = 0;
int fadeAmt = 0;
int counter = 0;



// PASILEIS TIK KARTA ARBA TIK PRADZIOJE
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
//Serial.begin(9600); //debug.FUTURE
strip.setBrightness(POWER); //2020.11.23  nustato bendra sviesumo ryskuma
}


// NESIBAIGIANCIAI KARTOSIS (TIKRINIMO GARSUMO BEI ATVAIZDAVIMAS LED..)
void loop() {
fadeCol = 0;
total = 0;

  for (int i = 0; i < lightCount; i++){
      counter = 0;
       do{
      vol = analogRead(A1)*STRENGHT;
 
      counter = counter + 1;
      if (counter > 500){

       // tuscias kodas , nereikalingas kodas , neaisku del ko cia reikia jo ..
      }
    }while (vol == 0);
   
    total = total + vol - THRESHOLD;
 
  }
 
  vol = total / 80;

 
  vol = map(vol,20,255,0,20);  // BE SITO NEPASILEIDZIA "KLAUSIMASI" , lemputes tiesiog visos blikcioja
 
 
  if (volLast > vol) {
    vol = volLast-DURATION; // turi visada buti matematinis sprendinys kitaip neveiks lemputes.
  }
 
  volLast = vol;
  fadeAmt = 0;

  for (int i = 0; i<strip.numPixels();i++){
   
   
 
    if (i < vol){
   
         
         
         strip.setPixelColor((i+strip.numPixels()/2), strip.Color( 0, 255, 0 )); //VIDURYS ZALIAS
         strip.setPixelColor((strip.numPixels()/2-i), strip.Color( 0, 255, 0 )); //VIDURYS ZALIAS
    }
   else if (i < (vol + vol)) { // vol + 8 default
     
         strip.setPixelColor((i+strip.numPixels()/2), strip.Color( 255, 255, 0 )); // GALAS 
         strip.setPixelColor((strip.numPixels()/2-i), strip.Color( 255, 0, 0 )); // GALAS
     
    }
   else
   {
       
     
        strip.setPixelColor((i+strip.numPixels()/2), strip.Color( 0, 0, 0 )); // GALAS
        strip.setPixelColor((strip.numPixels()/2-i), strip.Color( 0, 0, 0 )); // GALAS
     
    }
  }
//Serial.println(vol); //debug 
strip.show();
//strip.clear();
}
