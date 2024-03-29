//  Biblioteca para acesso ao sensor IR
#include <IRremote.h>

#define pinoIR    2 // Pino digital para receber sinal do sensor IR

IRrecv receptor(pinoIR);   //  Cria um receptor que decodifica o sinal do sensor IR - codigos do controle remoto
decode_results resultados; //  Variavel que aramzenara os resultados recebidos



long int codTecla1 =   16753245; //CÓDIGO DA TECLA 1 (ALTERE PARA O CÓDIGO DECIMAL QUE VOCÊ CAPTUROU)
long int codTecla2 = 16736925; //CÓDIGO DA TECLA 2 (ALTERE PARA O CÓDIGO DECIMAL QUE VOCÊ CAPTUROU)
long int codTecla3 = 16769565; //CÓDIGO DA TECLA 3 (ALTERE PARA O CÓDIGO DECIMAL QUE VOCÊ CAPTUROU)
long int codTecla4 = 16720605; //CÓDIGO DA TECLA 4 (ALTERE PARA O CÓDIGO DECIMAL QUE VOCÊ CAPTUROU)
long int codTecla5 = 16712445; //CÓDIGO DA TECLA 5 (ALTERE PARA O CÓDIGO DECIMAL QUE VOCÊ CAPTUROU)

const int pinoReleCh1 = 3; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 1)
const int pinoReleCh2 = 4; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 2)

int incomingByte = 0;

int statusLampCh1 = 0; //VARIÁVEL QUE CONTROLA O ESTADO DO MÓDULO RELÉ NO CANAL 1 (LIGADO / DESLIGADO)
int statusLampCh2 = 0; //VARIÁVEL QUE CONTROLA O ESTADO DO MÓDULO RELÉ NO CANAL 2 (LIGADO / DESLIGADO)



void setup(){

  Serial.begin(9600);
  
  receptor.enableIRIn();    //  Habilita o receptor para inicio de processamento dos codigos recebidos do emissor IR
  
  pinMode(pinoReleCh1, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoReleCh2, OUTPUT); //DEFINE O PINO COMO SAÍDA
  
  digitalWrite(pinoReleCh1, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
  digitalWrite(pinoReleCh2, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
}    
void loop(){

 //if (Serial.available() > 0)
 if(receptor.decode(&resultados)) {
    // lê do buffer o dado recebido:
    //incomingByte = Serial.read();

    // responde com o dado recebido:
    Serial.print("I received: ");
    Serial.println(resultados.value);
    delay(100); //INTERVALO DE 100 MILISSEGUNDOS

    if(resultados.value == codTecla1 && statusLampCh1 == 0){
      digitalWrite(pinoReleCh1, LOW); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      statusLampCh1 = 1; //VARIÁVEL RECEBE O VALOR 1
      digitalWrite(pinoReleCh2, LOW); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      statusLampCh2 = 1; //VARIÁVEL RECEBE O VALOR 1
      delay(200); //INTERVALO DE 200 MILISSEGUNDOS
    }
    else if(resultados.value == codTecla1 && statusLampCh1 == 1){
      digitalWrite(pinoReleCh1, HIGH); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      statusLampCh1 = 0; //VARIÁVEL RECEBE O VALOR 1
      digitalWrite(pinoReleCh2, HIGH); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
      statusLampCh2 = 0; //VARIÁVEL RECEBE O VALOR 1
      delay(200); //INTERVALO DE 200 MILISSEGUNDOS
    }
    receptor.resume(); //AGUARDA O RECEBIMENTO DE UM NOVO SINAL IR
  }
  delay(10); //INTERVALO DE 10 MILISSEGUNDOS
}
