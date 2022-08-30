/* 
 * Mini-Inhjetora Elétrica
 * 
 * 
 * References
 * 
 * 
 */

//***********Bibliotecas***********
#include <Keypad.h> // Biblioteca Teclado
#include <Wire.h> // Biblioteca I2C
#include <LiquidCrystal_I2C.h> // Biblioteca módulo I2C Display
#include "max6675.h" //Biblioteca Sensor Temperatura

//***********Configuração Display***********
LiquidCrystal_I2C lcd(0x27,16,2);

//***********Configuração Teclado***********
const byte LINHAS = 4; // Linhas do teclado
const byte COLUNAS = 4; // Colunas do teclado

const char TECLAS_MATRIZ[LINHAS][COLUNAS] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte PINOS_LINHAS[COLUNAS] = {45, 43, 41, 39}; // Pinos de conexao com as linhas do teclado
const byte PINOS_COLUNAS[LINHAS] = {37, 35, 33, 31}; // Pinos de conexao com as colunas do teclado

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado

//***********Configuração Módulo Sensor Temp.***********
int ktcSO = 52; //Pino Digital (SO)
int ktcCS = 50; //Pino Digital (CS)
int ktcCLK = 53; //Pino Digital (CLK / SCK)

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

//***********Configuração Pinos Relés***********
const int pinoRele1Ch1 = 7; //Pino digital módulo relé 1
const int pinoRele1Ch2 = 6; //Pino digital módulo relé 1

//***********Configuração Pinos Drives Motores***********
int driver1PUL = 13 ; // Pino digital PUL driver 1
int driver1DIR = 12 ; // Pino digital DIR driver 1

int driver2PUL = 11 ; // Pino digital PUL driver 2
int driver2DIR = 10 ; // Pino digital DIR driver 2

//***********Variáveis de Controle***********
int i = 0; // Controle giro fuso infinito**

long giro1 = 0; // Controle giro 1
long giro2 = 0; // Controle giro 2
long giro3 = 0; // Controle giro 3
long giro4 = 0; // Controle giro 4

int pd = 1000;//Controle velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750    
int pd2 = 700;//Controle velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750  

float incomingByte = 0; // Recebe Valor temperatura

int fimCurso1 = 24; //Pino Digital Fim de curso 1
int fimCurso2 = 22; //Pino Digital Fim de curso 2

boolean StatusFimCurso1 = LOW; // Status Fim de Curso 1
boolean StatusFimCurso2 = LOW; // Status Fim de Curso 2

//***********Setup***********
void setup() {
  Serial.begin(9600); // Inicia porta serial
  
  lcd.init(); //Inicia função display LCD
  lcd.setBacklight(HIGH); //Liga o backlight do display LCD

  pinMode (driver1PUL, OUTPUT); //Define pino relé sáida
  pinMode (driver1DIR, OUTPUT); //Define pino relé sáida

  pinMode (driver2PUL, OUTPUT); //Define pino relé sáida
  pinMode (driver2DIR, OUTPUT); //Define pino relé sáida

  pinMode(pinoRele1Ch1, OUTPUT); //Define pino relé sáida
  pinMode(pinoRele1Ch2, OUTPUT); //Define pino relé sáida
  
  pinMode(fimCurso1, INPUT); //Define pino como entrada
  pinMode(fimCurso2, INPUT); //Define pino como entrada
  
  digitalWrite(pinoRele1Ch1, HIGH); //Módulo relé 1 incia desligado
  digitalWrite(pinoRele1Ch2, HIGH); //Módulo relé 2 inicia desligado
  
}
//***********Função Liga Módulos***********
void acionaRele(){
   digitalWrite(pinoRele1Ch1, LOW); //Liga módulo relé 1
   digitalWrite(pinoRele1Ch2, LOW); //Liga módulo relé 2
}
//***********Função Desliga Módulos***********
void desligaRele(){
   digitalWrite(pinoRele1Ch1, HIGH); //Desliga módulo relé 2
   digitalWrite(pinoRele1Ch2, HIGH); //Desliga módulo relé 2
}
//***********Função Fuso Infinito***********
void fusoInfinito(){
       digitalWrite(driver2DIR,HIGH);
 
       for (i; i<=4000; i++)
       {
          digitalWrite(driver2PUL,HIGH);
          delayMicroseconds(800);
          digitalWrite(driver2PUL,LOW);
          delayMicroseconds(800);
       }
       i = 0;
}

//***********Função Processo Injetora***********
void processoInjetora(){
           
            //Fecha Molde------------------------------------------------------------------------------------
           
              long giro1 = 0; // Controle giro 1
              long giro2 = 0; // Controle giro 2
              long giro3 = 0; // Controle giro 3
              long giro4 = 0; // Controle giro 4

              boolean StatusFimCurso1 = LOW; // Status Fim de Curso 1
              boolean StatusFimCurso2 = LOW; // Status Fim de Curso 2

              /*
              incomingByte = ktc.readCelsius();
              Serial.println(incomingByte);
              if(incomingByte <=100)
              {
                acionaRele();
                }
              else if(incomingByte >= 105)
              {
                desligaRele();
               }
              */
      
              digitalWrite(driver1DIR,HIGH); //Aqui é primeiro giro do projeto, fechamento do molde
    
              for (giro1= 0; giro1<=5560; giro1++){ //Aqui você faz o preset de quanto ele vai andar, quando for fazer o preset, zere o valor dos outros giros. 
                digitalWrite(driver1PUL,HIGH);
                delayMicroseconds(700);
                digitalWrite(driver1PUL,LOW);
                delayMicroseconds(700);
                /*
                StatusFimCurso2 = digitalRead(fimCurso2);
                if(StatusFimCurso2 == HIGH)
                {
                  Serial.println(giro1);
                  Serial.println(StatusFimCurso2);
                  giro1 = 700000;
                }
                */
              }

              delay (250); // Este é um pequeno delay após o fechamento do molde para encher
          
          //Injeção de Material----------------------------------------------------------------------------
              digitalWrite(driver2DIR,HIGH); // Aqui é a injeção do material
        
              for (giro2= 0; giro2<=4000; giro2++){ // Aqui você define o tanto que o fuso vai rodar, recomendo 11000
                digitalWrite(driver2PUL,HIGH);
                delayMicroseconds(pd);
                digitalWrite(driver2PUL,LOW);
                delayMicroseconds(pd);
              }
        
              delay (7000); // Este é o tempo que o material esfria dentro do molde
              
          //Retira Pressão----------------------------------------------------------------------------      
              digitalWrite(driver2DIR,LOW); // Aqui é a volta do fuso para tirar a pressão
        
              for (giro3= 0; giro3<=4000; giro3++){ //Recomendo colocar 2000 aqui
                digitalWrite(driver2PUL,HIGH);
                delayMicroseconds(pd);
                digitalWrite(driver2PUL,LOW);
                delayMicroseconds(pd);
              }

              delay (3000); // Este é o tempo de espera para o molde abrir
         
          //Abre Molde----------------------------------------------------------------------------      
              digitalWrite(driver1DIR,LOW); // Está ultima operação abre o molde
        
              for (giro4= 0; giro4<=5560; giro4++){ //Aqui o valor deve ser igual ao do fechamento do molde, pois abre a mesma quantidade.
                digitalWrite(driver1PUL,HIGH);
                delayMicroseconds(700);
                digitalWrite(driver1PUL,LOW);
                delayMicroseconds(700);
               /*
                StatusFimCurso1 = digitalRead(fimCurso1);
                if(StatusFimCurso1 == HIGH){
                  Serial.println(giro4);
                   Serial.println(StatusFimCurso1);
                  giro4 = 700000;
                }
                */
              }
             
           Serial.println(giro1);
           Serial.println(giro2);
           Serial.println(giro3);
           Serial.println(giro4);
          //-----------------------------------------------------------------------------------------------
}

//***********Loop***********
void loop() {
  
  lcd.setCursor(0,0);
  lcd.print(ktc.readCelsius());

  incomingByte = ktc.readCelsius();
  Serial.println(incomingByte);

  /*
  Serial.println(incomingByte);
  if(incomingByte <=100.0)
  {
     acionaRele();
  }
  else if(incomingByte >= 105.0)
  {
     desligaRele();
  }
  */
  char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variavel a leitura do teclado
  
  if (leitura_teclas) { // Se alguma tecla foi pressionada
     
     
     switch(leitura_teclas)
     {
        case 'A': acionaRele();  break;
        case 'B': desligaRele(); break;
        case 'C': fusoInfinito(); break;
        case 'D': processoInjetora(); break;
     }
  }
  delay(500);
  lcd.clear();
}
