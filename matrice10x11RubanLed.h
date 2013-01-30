
#ifndef Matrice10x11RubanLed_h
#define Matrice10x11RubanLed_h

#include <Arduino.h>
#include <HL1606strip.h>

#include <avr/pgmspace.h>

// use -any- 3 pins!
#define STRIP_D 4
#define STRIP_C 3
#define STRIP_L 2

#define COULNOIRE 0
#define COULVERTE 1
#define COULROUGE 2
#define COULJAUNE 3
#define COULBLEUE 4
#define COULTURQUOISE 5
#define COULVIOLETTE 6
#define COULBLANCHE 7




//**************librairy Matrix10x11
 class Matrice10x11
    {
      public:

          Matrice10x11();
        void setLedXYMatrix(int col, int row, int couleur);
		void setSegmentMatrix(int coldeb, int rowdeb,int longeur, int couleur);
		void setLigneBitMatrix(const byte col, const byte data,int couleur);
		void affLettreMatrix (const byte c,int couleur);
		void affChaineMatrix(const char * s, const unsigned long time,int couleur);
		void affChaineMatrixScroll(const char * s, const unsigned long time,int couleur);
		void rainbowParty(uint8_t wait);
		void stripOff(void);
		void chaseSingle(uint8_t color, uint8_t wait);
		void colorWipe(uint8_t color, uint8_t wait);
      private:


    };
       


 #endif
