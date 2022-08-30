#include "max6675.h" //INCLUSÃO DE BIBLIOTECA

int ktcSO = 52; //PINO DIGITAL (SO)
int ktcCS = 50; //PINO DIGITAL (CS)
int ktcCLK = 53; //PINO DIGITAL (CLK / SCK)

MAX6675 ktc(ktcCLK, ktcCS, ktcSO); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)

const int pinoReleCh1 = 7; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 1)
const int pinoReleCh2 = 6; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 2)

int incomingByte = 0;

int fimCurso1 = 22; //VARIÁVEL QUE CONTROLA O ESTADO DO MÓDULO RELÉ NO CANAL 1 (LIGADO / DESLIGADO)
int fimCurso2 = 24; //VARIÁVEL QUE CONTROLA O ESTADO DO MÓDULO RELÉ NO CANAL 2 (LIGADO / DESLIGADO)


void setup(){

  Serial.begin(9600);
  
  pinMode(pinoReleCh1, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoReleCh2, OUTPUT); //DEFINE O PINO COMO SAÍDA

  pinMode(fimCurso1, INPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(fimCurso2, INPUT); //DEFINE O PINO COMO SAÍDA
  
  digitalWrite(pinoReleCh1, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
  digitalWrite(pinoReleCh2, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
}    
void loop(){
 Serial.println(digitalRead(fimCurso1));
 Serial.println(digitalRead(fimCurso2));
  if(digitalRead(fimCurso1) == HIGH){
     Serial.println(digitalRead(fimCurso1));
     digitalWrite(pinoReleCh1, LOW); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
     digitalWrite(pinoReleCh2, LOW); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      
  }
  else if(digitalRead(fimCurso2) == HIGH){
     Serial.println(digitalRead(fimCurso2));
     digitalWrite(pinoReleCh1, HIGH); //DESLIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
     digitalWrite(pinoReleCh2, HIGH); //DESLIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
  }
 }
