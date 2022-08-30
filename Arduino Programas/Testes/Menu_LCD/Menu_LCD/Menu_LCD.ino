#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>

#define TRIGGER_PIN  13
#define ECHO_PIN     12

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

int Botao_aumenta = 2; //Variável para selecção do pino digital (Botão 1).
int Botao_retrocede = 3;  //Variável para selecção do pino digital (Botão 3).
int Botao_confirma = 4;  //Variável para selecção do pino digital (Botão 3).
int Led_azul = 5;
int Led_verm = 6;
int chave = 7;

int Numero_Menu = 0;       //Variável para selecção da página.
int Numero_titulo = 1;     //Variável para selecção do titulo da página.

//Variável para os títulos das páginas.
char* Titulo_Menu[] = {"Tela - 0",
                       "Tela 1 - Chave",                   
                       "Tela 2 - L.Azul",
                       "Tela 3 - L.Verm",
                       "Tela 4 - Dist.", 
                       "2.1 - Ligar", "2.2 - Desligar",
                       "3.1 - Ligar", "3.2 - Desligar", "3.3 - Piscar"};

//Correr a função SETUP apenas uma vez após ser pressionado Reset:
void setup(){
  //Iniciar a Comunicação com LCD de 16x2:
  lcd.begin(2, 16);
  Serial.begin(9600);
  //Definição do tipo de pino (Saída ou entrada):
  pinMode(Botao_aumenta, INPUT_PULLUP);
  //Definição do tipo de pino (Saída ou entrada):
  pinMode(Botao_confirma, INPUT_PULLUP);
  //Definição do tipo de pino (Saída ou entrada):
  pinMode(Botao_retrocede, INPUT_PULLUP);
  pinMode(Led_azul, OUTPUT);
  pinMode(Led_verm, OUTPUT);
  pinMode(chave, INPUT_PULLUP);
}

//Correr a função LOOP repetidamente:
void loop(){
  //Correr a função:
  Pagina_Menu_0();
  //Correr a função:
  Pagina_1();
  //Correr a função:
  Pagina_Menu_2();
  //Correr a função:
  Pagina_2_1();
  //Correr a função:
  Pagina_2_2();
  //Correr a função:
  Pagina_Menu_3();
  //Correr a função:
  Pagina_3_1();
  //Correr a função:
  Pagina_3_2();
  //Correr a função:
  Pagina_3_3();
  //Correr a função:
  Pagina_4();
  
  //Atraso para o próximo passo:
  delay(200);
}

//Página do Menu - 0:
void Pagina_Menu_0(){
  //Condição para abrir página:
  if (Numero_Menu == 0){
    //Apaga a informação do LCD.
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(Titulo_Menu[0]);

 if (digitalRead(Botao_aumenta) == LOW){
      Numero_titulo = Numero_titulo+1;
      delay(100);
    }
 
    //Condição para escrever no LCD os nomes das páginas:
    if (Numero_titulo > 0 & Numero_titulo < 3){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[1]);
            
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 1);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[2]);
    }
    //Condição para escrever no LCD os nomes das páginas:
    else if (Numero_titulo > 2 & Numero_titulo < 5){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[3]);
      
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 1);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[4]);
    }
        
    //Condição para selecionar página 1 e 3:
    if (Numero_titulo == 1 || Numero_titulo == 3){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 0);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para selecionar página 2 e 4:
    else if (Numero_titulo == 2 || Numero_titulo == 4){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 1);
      //Escreve no LCD:
      lcd.print(">");
    }
  
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW){
      //Condição para selecionar página:
      if (Numero_titulo >= 1){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = Numero_titulo + 1;
      }
      //Condição para selecionar página:
      if (Numero_titulo > 4){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = 4;
      } 
    }  
      
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW){
      //Condição para selecionar página:
      if (Numero_titulo < 1){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = 1;
      }
      //Condição para selecionar página:
      if (Numero_titulo <= 4){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = Numero_titulo - 1;
      }
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW){
      //Condição para selecionar página:
      if (Numero_titulo == 1){
        //Altera o valor de selecção do menu.
        Numero_Menu = 1;
      }
      //Condição para selecionar página:
      else if (Numero_titulo == 2){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = 5;
        //Altera o valor de selecção do menu.
        Numero_Menu = 2;
      }
      //Condição para selecionar página:
      else if (Numero_titulo == 3){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = 7;
        //Altera o valor de selecção do menu.
        Numero_Menu = 3;
      }
      //Condição para selecionar página:
      else if (Numero_titulo == 4) {
        //Altera o valor de selecção do menu.
        Numero_Menu = 4;
      }
    }
  }
}

//Pagina do Menu - 1:
void Pagina_1(){
  //Condição para abrir página:
  if (Numero_Menu == 1){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[Numero_titulo]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 1);
    //Escreve no LCD:
    lcd.print("Chave: ");
    chave=digitalRead(7);
    if(chave==HIGH){lcd.print("ON");}
    if(chave==LOW){lcd.print("OFF");}
    
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW){
      //Altera o valor de selecção do menu.
      Numero_Menu = 0;
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW){
      //Não realiza nenhuma acção.
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW){
      //Não realiza nenhuma acção.
    }
  }
}

//Página do Menu - 2:
void Pagina_Menu_2(){
  //Condição para abrir página:
  if (Numero_Menu == 2){
    //Apaga a informação do LCD.
    lcd.clear();     
    //Condição para escrever no LCD os nomes das páginas:
    if (Numero_titulo == 5 || Numero_titulo == 6){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[5]);
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 1);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[6]);
    }
    //Condição para selecionar página 2.1:
    if (Numero_titulo == 5){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 0);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para selecionar página 2.2:
    else if (Numero_titulo == 6){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 1);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW){      
      //Condição para selecionar página:
      if (Numero_titulo == 5){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = Numero_titulo + 1;
      }
      //Condição para selecionar página:
      else if (Numero_titulo == 6){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = Numero_titulo - 1;
      } 
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW){
      //Altera o valor de selecção do título do menu.
      Numero_titulo = 2;
      //Altera o valor de selecção do menu.
      Numero_Menu = 0;
    }
        
    //Atraso para o próximo passo:
    delay(100);
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW){
      //Condição para selecionar página:
      if (Numero_titulo == 5){
        //Altera o valor de selecção do menu.
        Numero_Menu = 5;
      }
      //Condição para selecionar página:
      else if (Numero_titulo == 6){
        //Altera o valor de selecção do menu.
        Numero_Menu = 6;  
      }
    }
  }
}

//Página do Menu - 2.1:
void Pagina_2_1(){
  //Condição para abrir página:
  if (Numero_Menu == 5){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[5]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
     lcd.print("Led Azul ON...");
     digitalWrite(Led_azul, HIGH);
        
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW) {
      //Altera o valor de selecção do menu.
      Numero_Menu = 2;
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW) {
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW) {
      //Não realiza nenhuma acção.
    }
  }
}

//Página do Menu - 2.2:
void Pagina_2_2() {
  //Condição para abrir página:
  if (Numero_Menu == 6){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[6]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Led Azul OFF...");
    digitalWrite(Led_azul, LOW);
    delay(500);
 
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW) {
      //Altera o valor de selecção do menu
      Numero_Menu = 2;
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW) {
      //Não realiza nenhuma acção.
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW) {
      //Não realiza nenhuma acção.
    }
  }
}

//Página do Menu - 3:
void Pagina_Menu_3(){
  //Condição para abrir página:
  if (Numero_Menu == 3){
    //Apaga a informação do LCD.
    lcd.clear();
    //Condição para escrever no LCD os nomes das páginas:
    if (Numero_titulo > 6 & Numero_titulo < 9){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[7]);
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 1);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[8]);
    }
    //Condição para escrever no LCD os nomes das páginas:
    else if (Numero_titulo == 9){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(1, 0);
      //Escreve no LCD:
      lcd.print(Titulo_Menu[9]);
    }
    //Condição para selecionar pagina 3.1:
    if (Numero_titulo == 7 || Numero_titulo == 9){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 0);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para selecionar pagina 3.2:
    else if (Numero_titulo == 8){
      //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
      lcd.setCursor(0, 1);
      //Escreve no LCD:
      lcd.print(">");
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW){
      //Condição para selecionar página:
      if (Numero_titulo >= 7){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = Numero_titulo + 1;
      }
      //Condição para selecionar página:
      if (Numero_titulo > 9){
        //Altera o valor de selecção do título do menu.
        Numero_titulo = 7;
      } 
    }  
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW){
      //Altera o valor de selecção do titulo do menu.
      Numero_titulo = 3;
      //Altera o valor de selecção do menu.
      Numero_Menu = 0;
    }
    
    //Atraso para o próximo passo:
    delay(100);
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW){
      //Condição para selecionar página:
      if (Numero_titulo == 7){
        //Altera o valor de selecção do menu.
        Numero_Menu = 7;
      }
      //Condição para selecionar página:
      else if (Numero_titulo == 8){
        //Altera o valor de selecção do menu.
        Numero_Menu = 8;
      }
      //Condição para selecionar pagina:
      else if (Numero_titulo == 9){
        //Altera o valor de selecção do menu.
        Numero_Menu = 9;
      }
    }
  }
}

//Página do Menu - 3.1:
void Pagina_3_1() {
  //Condição para abrir página:
  if (Numero_Menu == 7){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[7]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Led Verm. ON");
    digitalWrite(Led_verm,HIGH);
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW) {
      //Altera o valor de selecção do menu.
      Numero_Menu = 3;
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW) {
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW) {
      //Não realiza nenhuma acção.
    }
  }
}
//Página do Menu - 3.2:
void Pagina_3_2() {
  //Condição para abrir página:
  if (Numero_Menu == 8){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[8]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Led verm. OFF");
    digitalWrite(Led_verm,LOW);
       
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW) {
      //Altera o valor de selecção do menu.
      Numero_Menu = 3;
    }
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW) {
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW) {
      //Não realiza nenhuma acção.
    }
  }
}

//Página do menu - 3.3:
void Pagina_3_3() {
  //Condição para abrir página:
  if (Numero_Menu == 9){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[9]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
    lcd.print("Piscando...");
    digitalWrite(Led_verm,HIGH);
    delay(500);
    digitalWrite(Led_verm,LOW);
    delay(500);
    
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW) {
      //Altera o valor de selecção do menu.
      Numero_Menu = 3;
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW) {
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW) {
      //Não realiza nenhuma acção.
    }
  }
}

//Página do Menu - 4:
void Pagina_4() {


  
  //Condição para abrir página:
  if (Numero_Menu == 4){
    //Apaga a informação do LCD.
    lcd.clear();
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(0, 0);
    //Escreve no LCD:
    lcd.print(Titulo_Menu[Numero_titulo]);
    lcd.print(":");
    //Define a coluna (em 16) e a linha (em 2) do LCD onde escrever:
    lcd.setCursor(1, 1);
    //Escreve no LCD:
   

  lcd.print("dist: ");
  lcd.print(ultrasonic.Ranging(CM)); // CM or INC
  lcd.print(" cm");
  delay(500);

    //Condição para acção dos botões na página:
    if (digitalRead(Botao_retrocede) == LOW){
      //Altera o valor de selecção do menu.
      Numero_Menu = 0;
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_confirma) == LOW){
      //Não realiza nenhuma acção.
    }
    //Condição para acção dos botões na página:
    if (digitalRead(Botao_aumenta) == LOW){
      //Não realiza nenhuma acção.
    }
  }
}
