int PulsoDoDriver = 12 ; //Azul    
int DirecaoDoDriver = 13; //Azul

int PulsoDoDriver2= 2; //Preto
int DirecaoDoDriver2 = 3;//Preto  

int FimDeCurso = 7;//
int FimDeCurso2 = 8;//
     
int giro1 = 0;
int giro2 = 0;
int giro3 = 0;
int giro4 = 0;

int pd = 900;//Aqui você define a velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750    
int pd2 = 900;//Aqui você define a velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750  

boolean setdir = HIGH; 
boolean setdir2 = HIGH; 

boolean StatusFimDeCurso = LOW;
boolean StatusFimDeCurso2 = LOW;

int serialDado = 0;
int var;


void setup() {

  Serial.begin(9600);
  pinMode (PulsoDoDriver, OUTPUT);
  pinMode (DirecaoDoDriver, OUTPUT);
  pinMode (PulsoDoDriver2, OUTPUT);
  pinMode (DirecaoDoDriver2, OUTPUT);
  pinMode (FimDeCurso, OUTPUT);
  
}

void loop(){
  
  if(Serial.available()>0){
    
    serialDado = Serial.read();
    var = 1;
    Serial.println(var);
    Serial.println(StatusFimDeCurso);
    
      while(var<=20){
        var++; 
        int giro1 = 0;
        int giro2 = 0;
        int giro3 = 0;
        int giro4 = 0;
        Serial.println(var);

        delay (3000); // Este é o tempo de espera para o molde abrir
     
        digitalWrite(DirecaoDoDriver,LOW); //Aqui é primeiro giro do projeto, fechamento do molde
        for (giro1; giro1<=6400; giro1++){ //Aqui você faz o preset de quanto ele vai andar, quando for fazer o preset, zere o valor dos outros giros. 
          digitalWrite(PulsoDoDriver,HIGH);
          delayMicroseconds(pd);
          digitalWrite(PulsoDoDriver,LOW);
          delayMicroseconds(pd);
          StatusFimDeCurso2 = digitalRead(FimDeCurso2);
          if(StatusFimDeCurso2 == HIGH)
          {
            Serial.println(StatusFimDeCurso2);
            giro1 = 10000;
          }
        }
       
        delay (250); // Este é um pequeno delay após o fechamento do molde para encher
   
        digitalWrite(DirecaoDoDriver2,HIGH); // Aqui é a injeção do material
        for (giro2; giro2<=25000; giro2++){ // Aqui você define o tanto que o fuso vai rodar, recomendo 11000
          digitalWrite(PulsoDoDriver2,HIGH);
          delayMicroseconds(750);
          digitalWrite(PulsoDoDriver2,LOW);
          delayMicroseconds(750);
        }
  
        delay (10000); // Este é o tempo que o material esfria dentro do molde
        
        digitalWrite(DirecaoDoDriver2,LOW); // Aqui é a volta do fuso para tirar a pressão
        for (giro3; giro3<=1000; giro3++){ //Recomendo colocar 2000 aqui
          digitalWrite(PulsoDoDriver2,HIGH);
          delayMicroseconds(pd);
          digitalWrite(PulsoDoDriver2,LOW);
          delayMicroseconds(pd);
        }
        
        delay (3000); // Este é o tempo de espera para o molde abrir
        
        digitalWrite(DirecaoDoDriver,HIGH); // Está ultima operação abre o molde
        for (giro4; giro4<=6400; giro4++){ //Aqui o valor deve ser igual ao do fechamento do molde, pois abre a mesma quantidade.
           digitalWrite(PulsoDoDriver,HIGH);
           delayMicroseconds(pd);
           digitalWrite(PulsoDoDriver,LOW);
           delayMicroseconds(pd);
           StatusFimDeCurso = digitalRead(FimDeCurso);
           if(StatusFimDeCurso == HIGH)
           {
            Serial.println(StatusFimDeCurso);
            giro4 = 10000;
           }
        }
        delay (2000); // Este é o tempo de espera para o molde abrir
    }
  }
}
     
