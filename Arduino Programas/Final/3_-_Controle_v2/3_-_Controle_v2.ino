
#include <Keypad.h> // Biblioteca do codigo
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "max6675.h" //INCLUSÃO DE BIBLIOTECA


LiquidCrystal_I2C lcd(0x27,16,2);

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

int ktcSO = 52; //PINO DIGITAL (SO)
int ktcCS = 50; //PINO DIGITAL (CS)
int ktcCLK = 53; //PINO DIGITAL (CLK / SCK)


const int pinoRele1Ch1 = 7; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 1)
const int pinoRele1Ch2 = 6; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 2)

int driver1PUL = 13 ;    // PUL- pin
int driver1DIR = 12 ;    // DIR- pin

int driver2PUL = 11 ;    // PUL- pin
int driver2DIR = 10 ;    // DIR- pin

long int giro1 = 0;
long int giro2 = 0;
long int giro3 = 0;
long int giro4 = 0;

int pd = 1000;//Aqui você define a velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750    
int pd2 = 700;//Aqui você define a velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750  

int i = 0;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado
int fimCurso1 = 24; //Pino Digital Fim de curso 1
int fimCurso2 = 22; //Pino Digital Fim de curso 2

boolean StatusFimCurso1 = LOW; // Status Fim de Curso 1
boolean StatusFimCurso2 = LOW; // Status Fim de Curso 2

void setup() {
  Serial.begin(9600); // Inicia porta serial
  
  pinMode(pinoRele1Ch1, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoRele1Ch2, OUTPUT); //DEFINE O PINO COMO SAÍDA

  pinMode (driver1PUL, OUTPUT);
  pinMode (driver2DIR, OUTPUT);

  pinMode (driver2PUL, OUTPUT);
  pinMode (driver2DIR, OUTPUT);
  
  digitalWrite(pinoRele1Ch1, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
  digitalWrite(pinoRele1Ch2, HIGH); //MÓDULO RELÉ INICIA DESLIGADO

  pinMode(fimCurso1, INPUT); //Define pino como entrada
  pinMode(fimCurso2, INPUT); //Define pino como entrada

  lcd.init();
  lcd.setBacklight(HIGH);
}

void loop() {
  
  lcd.setCursor(0,0);
  lcd.print(ktc.readCelsius());

  char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variavel a leitura do teclado
  
  if (leitura_teclas) { // Se alguma tecla foi pressionada
     
     lcd.setCursor(0,1);
     
     if(leitura_teclas == 'A')
     {
      digitalWrite(pinoRele1Ch1, LOW); //MÓDULO RELÉ INICIA DESLIGADO
      digitalWrite(pinoRele1Ch2, LOW); //MÓDULO RELÉ INICIA DESLIGADO
      lcd.clear();
     }
     if(leitura_teclas == 'C')
     {
       digitalWrite(driver2DIR,HIGH);
 
       for (i; i<=4000; i++)
       {
          digitalWrite(driver2PUL,HIGH);
          delayMicroseconds(850);
          digitalWrite(driver2PUL,LOW);
          delayMicroseconds(850);
       }
       i = 0;
     }
     if(leitura_teclas == 'D')
     {
              long int giro1 = 0; // Controle giro 1
              long int giro2 = 0; // Controle giro 2
              long int giro3 = 0; // Controle giro 3
              long int giro4 = 0; // Controle giro 4   
              
              digitalWrite(driver1DIR,LOW); //Aqui é primeiro giro do projeto, fechamento do molde
    
              for (giro1= 0; giro1<=700000; giro1++){ //Aqui você faz o preset de quanto ele vai andar, quando for fazer o preset, zere o valor dos outros giros. 
                digitalWrite(driver1PUL,HIGH);
                delayMicroseconds(pd);
                digitalWrite(driver1PUL,LOW);
                delayMicroseconds(pd);

                StatusFimCurso2 = digitalRead(fimCurso2);
                if(StatusFimCurso2 == HIGH)
                {
                  Serial.println(StatusFimCurso2);
                  giro1 = 700000;
                }
              }
              
          //-----------------------------------------------------------------------------------------------
              
              delay (250); // Este é um pequeno delay após o fechamento do molde para encher
          
          //Injeção de Material----------------------------------------------------------------------------
              digitalWrite(driver2DIR,HIGH); // Aqui é a injeção do material
        
              for (giro2= 0; giro2<=4000; giro2++){ // Aqui você define o tanto que o fuso vai rodar, recomendo 11000
                digitalWrite(driver2PUL,HIGH);
                delayMicroseconds(pd);
                digitalWrite(driver2PUL,LOW);
                delayMicroseconds(pd);
              }
          //-----------------------------------------------------------------------------------------------
        
              delay (7000); // Este é o tempo que o material esfria dentro do molde
              
          //Retira Pressão----------------------------------------------------------------------------      
              digitalWrite(driver2DIR,LOW); // Aqui é a volta do fuso para tirar a pressão
        
              for (giro3= 0; giro3<=4000; giro3++){ //Recomendo colocar 2000 aqui
                digitalWrite(driver2PUL,HIGH);
                delayMicroseconds(pd);
                digitalWrite(driver2PUL,LOW);
                delayMicroseconds(pd);
              }
          //-----------------------------------------------------------------------------------------------
              delay (3000); // Este é o tempo de espera para o molde abrir
         
          //Abre Molde----------------------------------------------------------------------------      
              digitalWrite(driver1DIR,HIGH); // Está ultima operação abre o molde
        
              for (giro4= 0; giro4<=700000; giro4++){ //Aqui o valor deve ser igual ao do fechamento do molde, pois abre a mesma quantidade.
                digitalWrite(driver1PUL,HIGH);
                delayMicroseconds(pd);
                digitalWrite(driver1PUL,LOW);
                delayMicroseconds(pd);
               
                StatusFimCurso1 = digitalRead(fimCurso1);
                if(StatusFimCurso1 == HIGH){
                  giro4 = 700000;
                }
              }
     }
       if(leitura_teclas == 'B')
     {
      digitalWrite(pinoRele1Ch1, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
      digitalWrite(pinoRele1Ch2, HIGH); //MÓDULO RELÉ INICIA DESLIGADO 
      lcd.clear();
     }
  }
  delay(500);
 
  lcd.clear();
}
