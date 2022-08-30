#include "max6675.h" //INCLUSÃO DE BIBLIOTECA

int ktcSO = 11; //PINO DIGITAL (SO)
int ktcCS = 12; //PINO DIGITAL (CS)
int ktcCLK = 13; //PINO DIGITAL (CLK / SCK)

MAX6675 ktc(ktcCLK, ktcCS, ktcSO); //CRIA UMA INSTÂNCIA UTILIZANDO OS PINOS (CLK, CS, SO)

const int pinoReleCh1 = 10; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 1)
const int pinoReleCh2 = 9; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 2)

float incomingByte = 0;

int statusLampCh1 = 0; //VARIÁVEL QUE CONTROLA O ESTADO DO MÓDULO RELÉ NO CANAL 1 (LIGADO / DESLIGADO)
int statusLampCh2 = 0; //VARIÁVEL QUE CONTROLA O ESTADO DO MÓDULO RELÉ NO CANAL 2 (LIGADO / DESLIGADO)



void setup(){

  Serial.begin(9600);
  
  pinMode(pinoReleCh1, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoReleCh2, OUTPUT); //DEFINE O PINO COMO SAÍDA
  
  digitalWrite(pinoReleCh1, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
  digitalWrite(pinoReleCh2, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
}    
void loop(){
  
 //Serial.println(ktc.readCelsius()); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
 delay(200);
 
    incomingByte = ktc.readCelsius();
    Serial.print("I received: ");
    Serial.println(incomingByte);
     
    delay(200);
    
    if(incomingByte <= 250.0){
      digitalWrite(pinoReleCh1, LOW); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      digitalWrite(pinoReleCh2, LOW); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      delay(200); //INTERVALO DE 200 MILISSEGUNDOS
      Serial.print("I received: ");
      Serial.println(incomingByte);
    }
    else if(incomingByte >= 255.0){
      digitalWrite(pinoReleCh1, HIGH); //DESLIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      digitalWrite(pinoReleCh2, HIGH); //DESLIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      delay(200); //INTERVALO DE 200 MILISSEGUNDOS
      Serial.print("I received: ");
      Serial.println(incomingByte);
     }
      
  delay(10); //INTERVALO DE 10 MILISSEGUNDOS
  }
