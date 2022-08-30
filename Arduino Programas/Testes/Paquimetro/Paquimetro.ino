#include <LiquidCrystal.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //PORTAS DO ARDUINO QUE SÃO UTILIZADAS PELO DISPLAY LCD

int analogPin = A0;
int val = 0;
int valor_mapeado;

void setup(){
 Serial.begin(9600);
 lcd.begin(16, 2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY. EM SUMA: UMA MATRIZ DE 16 COLUNAS E 2 LINHAS
}

void loop() {
 
 val = analogRead(analogPin);  // read the input pin

 if (val==14||val==15){valor_mapeado=0;}
 else if(val==62){valor_mapeado=1;}
 else if(val>62 && val<201){valor_mapeado = map(val,62,201,1,5);}
 else if(val==201){valor_mapeado=5;}
 else if(val>201 && val<396){valor_mapeado = map(val,201,396,5,10);}
 else if(val==396){valor_mapeado=10;}
 else if(val>396 && val<580){valor_mapeado = map(val,396,580,10,15);}
 else if(val==580){valor_mapeado=15;}
 else if(val>580 && val<798){valor_mapeado = map(val,580,798,15,20);}
 else if(val==798){valor_mapeado=20;}
 else if(val>798 && val<841){valor_mapeado = map(val,798,841,20,25);}
 else if(val==841){valor_mapeado=25;}
 else if(val>841 && val<875){valor_mapeado = map(val,841,875,25,30);}
 else if(val==875){valor_mapeado=30;}
 else if(val>875 && val<907){valor_mapeado = map(val,875,907,30,35);}
 else if(val==907){valor_mapeado=35;}
 else if(val>907 && val<936){valor_mapeado = map(val,907,936,35,40);}
 else if(val==936){valor_mapeado=40;}
 else if(val>936 && val<960){valor_mapeado = map(val,936,960,40,45);}
 else if(val==960){valor_mapeado=45;}
 else if(val>960 && val<1000){valor_mapeado = map(val,960,1000,45,50);}
 else if(val==1000){valor_mapeado=50;}
 else if(val>1000 && val<1023){valor_mapeado = map(val,1000,1023,50,55);}
 else if(val==1023){valor_mapeado=56;}

lcd.setCursor(0,0);
lcd.print("  SENAI--- ");
//lcd.setCursor(0,1); //SETAA POSIÇÃO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)
//lcd.print("Aprender Fazendo"); //ESCREVE A PALAVRA "DISPLAY LCD 16X2" NA SEGUNDA LINHA DISPLAY LCD

lcd.setCursor(0,1); //SETAA POSIÇÃO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)
lcd.print(valor_mapeado); //ESCREVE A PALAVRA "DISPLAY LCD 16X2" NA SEGUNDA LINHA DISPLAY LCD
lcd.setCursor(2,1); //SETAA POSIÇÃO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)
lcd.print("mm"); //ESCREVE A PALAVRA "DISPLAY LCD 16X2" NA SEGUNDA LINHA DISPLAY LCD


}
