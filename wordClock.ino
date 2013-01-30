#include <Wire.h> // necessary, or the application won't build properly
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

int correct_address = 0;
PCF8583 rtc (0xA0);
Matrice10x11 horloge;

	
void setup(void){
  Serial.begin(9600);
  Serial.print("booting...");
  Serial.println(" done");

}



void loop(void){
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


  rtc.get_time();
  gestionHeureMot(rtc.hour,rtc.minute,rtc.second);
 /* char time[50];
  sprintf(time, "%02d/%02d/%02d %02d:%02d:%02d",
	  rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);
  Serial.println(time);*/
  delay(1000);
 
/*for(int i =0;i<24;i++){
   for(int j=0;j<60;j++){
    Serial.print(i);
    Serial.print(':');
    Serial.println(j);
    gestionHeureMot(i,j,0);
    delay(100);  
 } */
 
}  


 



void gestionHeureMot(byte heure,byte minute,byte seconde){
 String textOut;
  Serial.print("IL EST ");
  textOut = "IL EST ";
 //cas des heures
 if (minute >= 35){heure++;} //cas des heure du genre 8 h mois ving cinq moins le quart etc
 byte heure12 = heure%12; //conversion 24h en 12h
 if (heure12==1){Serial.print("UNE ");textOut += "UNE ";}
 if (heure12==2){Serial.print("DEUX ");textOut += "DEUX ";}
 if (heure12==3){Serial.print("TROIS ");textOut += "TROIS ";}
 if (heure12==4){Serial.print("QUATRE ");textOut += "QUATRE ";}
 if (heure12==5){Serial.print("CINQ ");textOut += "CINQ ";}
 if (heure12==6){Serial.print("SIX ");textOut += "SIX ";}
 if (heure12==7){Serial.print("SEPT ");textOut += "SEPT ";}
 if (heure12==8){Serial.print("HUIT ");textOut += "HUIT ";}
 if (heure12==9){Serial.print("NEUF ");textOut += "NEUF";}
 if (heure12==10){Serial.print("DIX ");textOut += "DIX ";}
 if (heure12==11){Serial.print("ONZE ");textOut += "ONZE ";}
 
 if (heure==12){Serial.print("MIDI ");textOut += "MIDI ";}
 if (heure==0 || heure==24){Serial.print("MINUIT ");textOut += "MINUIT ";}
 
 if ( heure!=0 && heure != 12 && heure !=24 && heure12 !=1){Serial.print("HEURES ");textOut += "HEURES ";}

 if (heure12==1){Serial.print("HEURE ");textOut += "HEURE ";}
 //cas des minutes
 
 if (minute < 5){Serial.println("");textOut += "";}
 if (minute >= 5 && minute < 10){Serial.println("CINQ");textOut += "CINQ";}
 if (minute >= 10 && minute < 15){Serial.println("DIX");textOut += "DIX";}
 if (minute >= 15 && minute < 20){Serial.println("ET QUART");textOut += "ET QUART";}
 if (minute >= 20 && minute < 25){Serial.println("VINGT");textOut += "VINGT";}
 if (minute >= 25 && minute < 30){Serial.println("VINGT-CINQ");textOut += "VINGT CINQ";}
 if (minute >= 30 && minute < 35){Serial.println("ET DEMI");textOut += "ET DEMI";}
 if (minute >= 35 && minute < 40){Serial.println("MOINS VINGT CINQ");textOut += "MOINS VINGT CINQ";}
 if (minute >= 40 && minute < 45){Serial.println("MOINS VINGT");textOut += "MOINS VINGT";}
 if (minute >= 45 && minute < 50){Serial.println("MOINS LE QUART");textOut += "MOINS LE QUART";}
 if (minute >= 50 && minute < 55){Serial.println("MOINS DIX");textOut += "MOINS DIX";}
 if (minute >= 55 && minute < 60){Serial.println("MOINS CINQ");textOut += "MOINS CINQ";}
 
 horloge.affChaineMatrixScroll("IL EST CINQ HEURES VINGT",30,COULBLANCHE);
}


