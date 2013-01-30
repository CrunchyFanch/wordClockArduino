#include <Arduino.h>
#include "matrice10x11RubanLed.cpp"

//**************librairy Matrix10x11
//constructeur Matrice

Matrice10x11::Matrice10x11(void){
stripOff();
}
void Matrice10x11::setLedXYMatrix(int col, int row, int couleur){

    //cas des lignes impaires 
    int n = row*10+col;
    if ((row%2) != 0){
      n = ((row+1)*10-col-1);
    }
    strip.setLEDcolor(n,couleur);

}

void Matrice10x11::setSegmentMatrix(int coldeb, int rowdeb,int longeur, int couleur){
    for (int i=0;i<longeur;i++){
        if (coldeb > 10){coldeb=0;rowdeb++;}
        setLedXYMatrix(coldeb,rowdeb,couleur);
        coldeb++;
    }
}

void Matrice10x11::setLigneBitMatrix(const byte col, const byte data,int couleur){
     byte mask = B10000000;
     for (int i=8;i>0;i--){
        
        if (data & mask){
          setLedXYMatrix(col+1,i,couleur);
        }else{
          setLedXYMatrix(col+1,i,COULNOIRE);
        }
       mask=mask>>1;
    }
  

}

void Matrice10x11::affLettreMatrix (const byte c,int couleur){
  for (byte col = 0; col < 8; col++)
    setLigneBitMatrix(col + 1, pgm_read_byte (&cp437_font [c] [col]),couleur);
 }  // end of letter
 
 void Matrice10x11::affChaineMatrix(const char * s, const unsigned long time,int couleur){
  char c;
  while (c = *s++)
    {
    affLettreMatrix(c,couleur);
   strip.writeStrip(); 
    delay (time);
    affLettreMatrix(' ',couleur);  // brief gap between letters
    delay (10);      
    }
}  

 void Matrice10x11::affChaineMatrixScroll(const char * s, const unsigned long time,int couleur){
 char c;
 int i,j;
 int cpt = 0;
 int cpt2 = 0;
 char temp[300];
 
 while(c = *s++){
   
   for (byte col = 0; col < 8; col++){
     temp[cpt]=pgm_read_byte (&cp437_font [c] [col]);
    cpt++;   
   }
   cpt2++;
 }
 
 for(i=0;i<(cpt-7);i++){
 
     for (j=0;j<10;j++){
      
       setLigneBitMatrix(j,temp[i+j],couleur);
       
     }
   strip.writeStrip(); 
    delay (time);
   // affLettreMatrix(' ',couleur);  // brief gap between letters
    //delay (10);
   //stripOff();   
 }
 }

void Matrice10x11::rainbowParty(uint8_t wait) {
  uint8_t i, j;

  for (i=0; i< strip.numLEDs(); i+=6) {
    // initialize strip with 'rainbow' of colors
    strip.setLEDcolor(i, RED);
    strip.setLEDcolor(i+1, YELLOW);
    strip.setLEDcolor(i+2, GREEN);
    strip.setLEDcolor(i+3, TEAL);
    strip.setLEDcolor(i+4, BLUE);
    strip.setLEDcolor(i+5, VIOLET);
 
  }
  strip.writeStrip();   
  
  for (j=0; j < strip.numLEDs(); j++) {

    // now set every LED to the *next* LED color (cycling)
    uint8_t savedcolor = strip.getLEDcolor(0);
    for (i=1; i < strip.numLEDs(); i++) {
      strip.setLEDcolor(i-1, strip.getLEDcolor(i));  // move the color back one.
    }
    // cycle the first LED back to the last one
    strip.setLEDcolor(strip.numLEDs()-1, savedcolor);
    strip.writeStrip();
    delay(wait);
  }
}

void Matrice10x11::stripOff(void) {
  // turn all LEDs off!
  for (uint8_t i=0; i < strip.numLEDs(); i++) {
      strip.setLEDcolor(i, BLACK);
  }
  strip.writeStrip();   
}

void Matrice10x11::chaseSingle(uint8_t color, uint8_t wait) {
  uint8_t i;
  
  // turn everything off
  for (i=0; i< strip.numLEDs(); i++) {
    strip.setLEDcolor(i, BLACK);
  }

  for (i=0; i < strip.numLEDs(); i++) {
    strip.setLEDcolor(i, color);
    if (i != 0) {
      // make the LED right before this one OFF
      strip.setLEDcolor(i-1, BLACK);
    }
    strip.writeStrip();
    delay(wait);  
  }
  // turn off the last LED before leaving
  strip.setLEDcolor(strip.numLEDs() - 1, BLACK);
}

void Matrice10x11::colorWipe(uint8_t color, uint8_t wait) {
  uint8_t i;
  
  for (i=0; i < strip.numLEDs(); i++) {
      strip.setLEDcolor(i, color);
      strip.writeStrip();   
      delay(wait);
  }
}


