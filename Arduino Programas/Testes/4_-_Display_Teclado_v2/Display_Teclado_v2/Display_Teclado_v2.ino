
/*******************************************************************************
* Teclado Matricial 16 Teclas : Primeiros Passos (v1.0)
*
* Codigo base para exibir as teclas pressionadas no monitor serial da IDE.
*
* Copyright 2020 RoboCore.
* Escrito por Matheus Cassioli (30/07/2019).
* Atualizado por Giovanni de Castro (22/01/2020).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version (<https://www.gnu.org/licenses/>).
*******************************************************************************/

#include <Keypad.h> // Biblioteca do codigo
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,16,2);

const byte LINHAS = 4; // Linhas do teclado
const byte COLUNAS = 4; // Colunas do teclado

const char TECLAS_MATRIZ[LINHAS][COLUNAS] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//const byte PINOS_COLUNAS[COLUNAS] = {31, 33, 35, 37}; // Pinos de conexao com as linhas do teclado
//const byte PINOS_LINHAS[LINHAS] = {39, 41, 43, 45}; // Pinos de conexao com as colunas do teclado
//const byte PINOS_LINHAS[LINHAS] = {31, 33, 35, 37}; // Pinos de conexao com as linhas do teclado
//const byte PINOS_COLUNAS[COLUNAS] = {39, 41, 43, 45}; // Pinos de conexao com as colunas do teclado


const byte PINOS_LINHAS[COLUNAS] = {45, 43, 41, 39}; // Pinos de conexao com as linhas do teclado
const byte PINOS_COLUNAS[LINHAS] = {37, 35, 33, 31}; // Pinos de conexao com as colunas do teclado

Keypad teclado_personalizado = Keypad(makeKeymap(TECLAS_MATRIZ), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado


const int pinoRele1Ch1 = 7; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 1)
const int pinoRele1Ch2 = 6; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ (CANAL 2)

void setup() {
  Serial.begin(9600); // Inicia porta serial
  
  pinMode(pinoRele1Ch1, OUTPUT); //DEFINE O PINO COMO SAÍDA
  pinMode(pinoRele1Ch2, OUTPUT); //DEFINE O PINO COMO SAÍDA
  
  digitalWrite(pinoRele1Ch1, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
  digitalWrite(pinoRele1Ch2, HIGH); //MÓDULO RELÉ INICIA DESLIGADO

  lcd.init();
  lcd.setBacklight(LOW);
}

void loop() {

  char leitura_teclas = teclado_personalizado.getKey(); // Atribui a variavel a leitura do teclado

  if (leitura_teclas) { // Se alguma tecla foi pressionada
     Serial.println(leitura_teclas); // Imprime a tecla pressionada na porta serial
     lcd.setBacklight(HIGH);
     lcd.setCursor(0,0);
     lcd.print("Injetora !!");
     lcd.setCursor(0,1);
     //lcd.print(leitura_teclas);
     if(leitura_teclas == 'A')
     {
     // lcd.print("FUNCIONOU !!");
      digitalWrite(pinoRele1Ch1, LOW); //MÓDULO RELÉ INICIA DESLIGADO
      digitalWrite(pinoRele1Ch2, LOW); //MÓDULO RELÉ INICIA DESLIGADO
     }
       if(leitura_teclas == 'C')
     {
      //lcd.print("FUNCIONOU !!");
      digitalWrite(pinoRele1Ch1, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
      digitalWrite(pinoRele1Ch2, HIGH); //MÓDULO RELÉ INICIA DESLIGADO
     }
  }
}
