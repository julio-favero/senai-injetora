
int PulsoDoDriver2= 2;
int DirecaoDoDriver2 = 3;       

int pd = 800; //Aqui você define a velocidade dos motores, quanto maior mais lento fica, não diminuir mais que 750 

boolean setdir = HIGH; //(HIGH sentido horario injeta material ,LOW sentido anti retorna material horario)


void setup() {
  Serial.begin(9600);
  pinMode (PulsoDoDriver2, OUTPUT);
  pinMode (DirecaoDoDriver2, OUTPUT);
  
}

void loop(){

        digitalWrite(DirecaoDoDriver2,setdir);
        digitalWrite(PulsoDoDriver2,HIGH);
        delayMicroseconds(pd);
        digitalWrite(PulsoDoDriver2,LOW);
        delayMicroseconds(pd);

}
