int PulsoDoDriver = 12 ; //Azul    
int DirecaoDoDriver = 11; //Azul

int PulsoDoDriver2= 2; //Preto
int DirecaoDoDriver2 = 3;//Preto  
     
int giro1 = 0;
int giro2 = 0;
int giro3 = 0;
int giro4 = 0;

int pd = 1000;//Aqui você define a velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750    
int pd2 = 700;//Aqui você define a velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750  

boolean setdir = HIGH; 
boolean setdir2 = HIGH; 


void setup() {
  pinMode (PulsoDoDriver, OUTPUT);
  pinMode (DirecaoDoDriver, OUTPUT);
  pinMode (PulsoDoDriver2, OUTPUT);
  pinMode (DirecaoDoDriver2, OUTPUT);
  
}

void loop(){

{
  //Fecha Molde------------------------------------------------------------------------------------
  
      digitalWrite(DirecaoDoDriver,LOW); //Aqui é primeiro giro do projeto, fechamento do molde

      for (giro1= 0; giro1<=0; giro1++){ //Aqui você faz o preset de quanto ele vai andar, quando for fazer o preset, zere o valor dos outros giros. 
        digitalWrite(PulsoDoDriver,HIGH);
        delayMicroseconds(pd);
        digitalWrite(PulsoDoDriver,LOW);
        delayMicroseconds(pd);
      }
      
  //-----------------------------------------------------------------------------------------------
      
      delay (250); // Este é um pequeno delay após o fechamento do molde para encher
  
  //Injeção de Material----------------------------------------------------------------------------
      digitalWrite(DirecaoDoDriver2,HIGH); // Aqui é a injeção do material

      for (giro2= 0; giro2<=1900000; giro2++){ // Aqui você define o tanto que o fuso vai rodar, recomendo 11000
        digitalWrite(PulsoDoDriver2,HIGH);
        delayMicroseconds(pd);
        digitalWrite(PulsoDoDriver2,LOW);
        delayMicroseconds(pd);
      }
  //-----------------------------------------------------------------------------------------------

      delay (7000); // Este é o tempo que o material esfria dentro do molde
      
  //Retira Pressão----------------------------------------------------------------------------      
      digitalWrite(DirecaoDoDriver2,LOW); // Aqui é a volta do fuso para tirar a pressão

      for (giro3= 0; giro3<=0; giro3++){ //Recomendo colocar 2000 aqui
        digitalWrite(PulsoDoDriver2,HIGH);
        delayMicroseconds(pd);
        digitalWrite(PulsoDoDriver2,LOW);
        delayMicroseconds(pd);
      }
  //-----------------------------------------------------------------------------------------------
      delay (3000); // Este é o tempo de espera para o molde abrir
 
  //Abre Molde----------------------------------------------------------------------------      
      digitalWrite(DirecaoDoDriver,HIGH); // Está ultima operação abre o molde

      for (giro4= 0; giro4<=0; giro4++){ //Aqui o valor deve ser igual ao do fechamento do molde, pois abre a mesma quantidade.
        digitalWrite(PulsoDoDriver,HIGH);
        delayMicroseconds(pd);
        digitalWrite(PulsoDoDriver,LOW);
        delayMicroseconds(pd);
      }
  //-----------------------------------------------------------------------------------------------
  }
}
