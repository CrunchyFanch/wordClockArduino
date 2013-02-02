#include <Wire.h> 
#include <stdio.h>
#include <PCF8583.h>
#include <HL1606strip.h>
#include <String.h>
#include "Matrice10x11RubanLed.h"
/*****************************************************************************

 *
 *  Arduino analog input 5 - I2C SCL (PCF8583 pin 6)
 *  Arduino analog input 4 - I2C SDA (PCF8583 pin 5)
 *
 *  Changement de l'heure par port serie en respectant YYMMddhhmmss;
 *
 ******************************************************************************/
/*MATRICE 

ILNESTODEUX
QUATRETROIS
NEUFUNESEPT
HUITSIXCINQ
MIDIXMINUIT
ONZERHEURES
MOINSOLEDIX
ETRQUARTPMD
VINGT-CINQU
ETSDEMIEPAM */

#define COULEURMOT COULTURQUOISE

prog_char string_0[] PROGMEM = "Bon anniversaire DENIS !!!! as tu pensé a arreter de fumer?";  
prog_char string_1[] PROGMEM = "Bon anniversaire BENE";
prog_char string_2[] PROGMEM = "Bon anniversaire OSCAR!!";
prog_char string_3[] PROGMEM = "Bon anniversaire ANDREEA!!";
prog_char string_4[] PROGMEM = "Bon anniversaire FRANCOIS!!";
prog_char string_5[] PROGMEM = "Joyeux Noel!!";

PROGMEM const char *string_table[] = 	   
{   
  string_0,
  string_1,
  string_2,
  string_3,
  string_4,
  string_5 };


const int datesSpeciales[] = {            
    // Jour, Mois 
    13,6,      
    11,9,      
    23,1,      
    27,4,      
    27,12,      
    25,12,
    0,0,  //pour arreter le parsing du tableau de date    
};

char buffer[200];

int correct_address = 0;
PCF8583 rtc (0xA0);
Matrice10x11 horloge;
String bufString; 

	
void setup(void){
  Serial.begin(9600);
  Serial.print("booting...");
  Serial.println(" done");


}



void loop(void){



  rtc.get_time();
  miseALHeure();
  affHeureSerial();
  boolean changement = gestionHeureMot(rtc.hour,rtc.minute,rtc.second);
  if (changement){   
    testDatesSpeciales(rtc.day, rtc.month);
  }
 
  delay(1000);

}

 /*for(int i =0;i<24;i++){ //test de tout les affichages possible (emulation de l'heure tout les 500ms
   for(int j=0;j<60;j++){
    Serial.print(i);
    Serial.print(':');
    Serial.println(j);
    gestionHeureMot(i,j,0);
    delay(500);  */
 

/*MATRICE
01234567890
ILNESTODEUX0
QUATRETROIS1
NEUFUNESEPT2
01234567890
HUITSIXCINQ3
MIDIXMINUIT4
ONZERHEURES5
01234567890
MOINSOLEDIX6
ETRQUARTPMD7
VINGT-CINQU8
ETSDEMIEPAM9 */


void affHeureSerial(){
  char time[50];
  sprintf(time, "%02d/%02d/%02d %02d:%02d:%02d",
	  rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);
  Serial.println(time);

}
void miseALHeure(void){ ///fonction de mise a l'heure par la fonction read port serie
  if(Serial.available() > 0){
       rtc.year= (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48)) + 2000;
       rtc.month = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
       rtc.day = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
       rtc.hour  = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
       rtc.minute = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
       rtc.second = (byte) ((Serial.read() - 48) * 10 + (Serial.read() - 48)); // Use of (byte) type casting and ascii math to achieve result.  

       if(Serial.read() == ';'){
         Serial.println("setting date");
	 rtc.set_time();
       }
  }
}

boolean gestionHeureMot(byte heure,byte minute,byte seconde){
 String textOut = "";
    
  Serial.print("IL EST ");horloge.setSegmentMatrix(0,0,2,COULEURMOT);horloge.setSegmentMatrix(3,0,3,COULEURMOT);
  textOut = "IL EST ";
 //cas des heures
 if (minute >= 35){heure++;} //cas des heure du genre 8 h mois ving cinq moins le quart etc
 byte heure12 = heure%12; //conversion 24h en 12h
 if (heure12==1){Serial.print("UNE ");textOut += "UNE ";horloge.setSegmentMatrix(4,2,3,COULEURMOT);}
 if (heure12==2){Serial.print("DEUX ");textOut += "DEUX ";horloge.setSegmentMatrix(7,0,4,COULEURMOT);}
 if (heure12==3){Serial.print("TROIS ");textOut += "TROIS ";horloge.setSegmentMatrix(6,1,5,COULEURMOT);}
 if (heure12==4){Serial.print("QUATRE ");textOut += "QUATRE ";horloge.setSegmentMatrix(0,1,6,COULEURMOT);}
 if (heure12==5){Serial.print("CINQ ");textOut += "CINQ ";horloge.setSegmentMatrix(7,3,4,COULEURMOT);}
 if (heure12==6){Serial.print("SIX ");textOut += "SIX ";horloge.setSegmentMatrix(4,3,3,COULEURMOT);}
 if (heure12==7){Serial.print("SEPT ");textOut += "SEPT ";horloge.setSegmentMatrix(7,2,4,COULEURMOT);}
 if (heure12==8){Serial.print("HUIT ");textOut += "HUIT ";horloge.setSegmentMatrix(0,3,4,COULEURMOT);}
 if (heure12==9){Serial.print("NEUF ");textOut += "NEUF";horloge.setSegmentMatrix(0,2,4,COULEURMOT);}
 if (heure12==10){Serial.print("DIX ");textOut += "DIX ";horloge.setSegmentMatrix(2,4,3,COULEURMOT);}
 if (heure12==11){Serial.print("ONZE ");textOut += "ONZE ";horloge.setSegmentMatrix(0,5,4,COULEURMOT);}
 
 if (heure==12){Serial.print("MIDI ");textOut += "MIDI ";horloge.setSegmentMatrix(0,4,4,COULEURMOT);}
 if (heure==0 || heure==24){Serial.print("MINUIT ");textOut += "MINUIT ";horloge.setSegmentMatrix(5,4,6,COULEURMOT);}
 
 if ( heure!=0 && heure != 12 && heure !=24 && heure12 !=1){Serial.print("HEURES ");textOut += "HEURES ";horloge.setSegmentMatrix(5,5,6,COULEURMOT);}

 if (heure12==1){Serial.print("HEURE ");textOut += "HEURE ";horloge.setSegmentMatrix(5,5,5,COULEURMOT);}
 //cas des minutes
 
 if (minute < 5){Serial.println("");textOut += "";}
 if (minute >= 5 && minute < 10){Serial.println("CINQ");textOut += "CINQ";horloge.setSegmentMatrix(6,8,4,COULEURMOT);}
 if (minute >= 10 && minute < 15){Serial.println("DIX");textOut += "DIX";horloge.setSegmentMatrix(8,6,3,COULEURMOT);}
 if (minute >= 15 && minute < 20){Serial.println("ET QUART");textOut += "ET QUART";horloge.setSegmentMatrix(0,7,2,COULEURMOT);horloge.setSegmentMatrix(3,7,5,COULEURMOT);}
 if (minute >= 20 && minute < 25){Serial.println("VINGT");textOut += "VINGT";horloge.setSegmentMatrix(0,8,5,COULEURMOT);}
 if (minute >= 25 && minute < 30){Serial.println("VINGT-CINQ");textOut += "VINGT-CINQ";horloge.setSegmentMatrix(0,8,10,COULEURMOT);}
 if (minute >= 30 && minute < 35){Serial.println("ET DEMI");textOut += "ET DEMI";horloge.setSegmentMatrix(0,9,2,COULEURMOT);horloge.setSegmentMatrix(3,9,4,COULEURMOT);}
 if (minute >= 35 && minute < 40){Serial.println("MOINS VINGT-CINQ");textOut += "MOINS VINGT-CINQ";horloge.setSegmentMatrix(0,6,5,COULEURMOT);horloge.setSegmentMatrix(0,8,10,COULEURMOT);}
 if (minute >= 40 && minute < 45){Serial.println("MOINS VINGT");textOut += "MOINS VINGT";horloge.setSegmentMatrix(0,6,5,COULEURMOT);horloge.setSegmentMatrix(0,8,5,COULEURMOT);}
 if (minute >= 45 && minute < 50){Serial.println("MOINS LE QUART");textOut += "MOINS LE QUART";horloge.setSegmentMatrix(0,6,5,COULEURMOT);horloge.setSegmentMatrix(6,6,2,COULEURMOT);horloge.setSegmentMatrix(3,7,5,COULEURMOT);}
 if (minute >= 50 && minute < 55){Serial.println("MOINS DIX");textOut += "MOINS DIX";horloge.setSegmentMatrix(0,6,5,COULEURMOT);horloge.setSegmentMatrix(8,6,3,COULEURMOT);}
 if (minute >= 55 && minute < 60){Serial.println("MOINS CINQ");textOut += "MOINS CINQ";horloge.setSegmentMatrix(0,6,5,COULEURMOT);horloge.setSegmentMatrix(6,8,4,COULEURMOT);}
 
// horloge.affChaineMatrixScroll(textOut,30,COULBLEUE);
  if (textOut != bufString) {//detecte si il y a eu un changement d'heure (evite l'effacement de la matrice toute les secondes)
   bufString = textOut; 
   return 1;
  }
  horloge.affMatrice();
  return 0;
}

void testDatesSpeciales(int jour, int mois){
  for (int i=0; datesSpeciales[i] > 0; i+=2){ 
    if (datesSpeciales[i] == jour && datesSpeciales[i+1] == mois){ // test si aujourdhui est un jour particulier
              
         horloge.stripOff();
         horloge.rainbowParty(80);
         horloge.stripOff();
         strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i/2]))); // Necessary casts and dereferencing, just copy.  
         horloge.affChaineMatrixScroll(String(buffer) ,30,COULROUGE);
         horloge.affMatrice(); 
         horloge.rainbowParty(80);
         horloge.stripOff();
    }
  }
    

}
