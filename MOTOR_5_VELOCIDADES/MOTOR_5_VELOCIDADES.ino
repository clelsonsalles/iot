const int FRENTE     = 1000;
const int ESQUERDA   = 1111;
const int DIREITA    = 2222;
const int PARADO     = 3333;
const int TRAS       = 4444;

int state;
int flag=0; //makes sure that the serial only prints once the state
//int recebidos[100];
int pos = 0;
//Configura os pínos de comunicação com o motor
int MotorRight1   = 5;
int MotorRight2   = 6;
int MotorLeft1    = 7;
int MotorLeft2    = 8; 
int ENA           = 9;
int ENB           = 10;
/*
int MotorRight1   = 2;
int MotorRight2   = 4;
int MotorLeft1    = 7;
int MotorLeft2    = 8; 
int ENA           = 5;
int ENB           = 6;
*/

//Controla a direção do carro
int direcaoAtual = PARADO;
//Controla a velocidade
int velocidade = 256 / 3;
//boolean aumenta = true;
int incrementoVelocidade = 256 / 3;
//int tempo = 60;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Bluetooth configurado...");
  pinMode (MotorRight1, OUTPUT); 
  pinMode (MotorRight2, OUTPUT); 
  pinMode (MotorLeft1, OUTPUT); 
  pinMode (MotorLeft2, OUTPUT); 
  pinMode (ENA, OUTPUT); 
  pinMode (ENB, OUTPUT); 

  digitalWrite (ENA, HIGH);     
  digitalWrite (ENB, HIGH);     
}

void loop() {
  //Aumenta a velocidade com o incremento, até 256
//  velocidade = 
//    ( (velocidade + incrementoVelocidade) > 256 ? 256 : (velocidade + incrementoVelocidade));

  if(Serial.available() > 0){

      state = (int)Serial.read();
      flag=0;

      Serial.println(state);
      if (state ==52){
        viraDireita();      
      }
      else if (state ==51){
        viraEsquerda();
      }
      else if (state ==49){
        emFrente();
      }
      else if (state ==50){
        praTras();
      }
      else if (state ==57){
//        Serial.println("\nSelect");
      }
      else if (state ==54){// Serial.println("\nX");
        parado();
      }
      else if (state ==56){
//        Serial.println("\nO");
        reduz();
      }
      else if (state ==53){
//        Serial.println("\nTri");
        acelera();
      }
      else if (state ==55){
        Serial.println("\nQuad");
      }
      else if (state ==48){
        Serial.println("\nStart");
      }
      else{
        Serial.print(state);
        Serial.print(", ");
        //Não recebeu comando de bluetooth
        //repeteComando(); 

      }
      delay(1);
  } else{
      repeteComando(); 
      delay(100);
  } 
 
}

  void acelera(){
    int novaVelocidade = (velocidade + incrementoVelocidade);
    for (int i = velocidade; i < novaVelocidade; i + 10){
      analogWrite(ENA, i);
      analogWrite(ENB, i);
      delay(100);
    }
    
    velocidade = 
      ( novaVelocidade > 256 ? 256 : novaVelocidade);

    analogWrite(ENA, velocidade);
    analogWrite(ENB, velocidade);
    
  }

  void reduz(){
    int novaVelocidade = (velocidade - incrementoVelocidade);
    for (int i = velocidade; i > novaVelocidade; i - 10){
      analogWrite(ENA, i);
      analogWrite(ENB, i);
      delay(100);
    }
    
    velocidade = 
      ( novaVelocidade < incrementoVelocidade ? incrementoVelocidade : novaVelocidade);

    analogWrite(ENA, velocidade);
    analogWrite(ENB, velocidade);
    
  }
  
  void repeteComando(){
  
        switch (direcaoAtual){
           case FRENTE:
              emFrente();
              break;
           case ESQUERDA: 
              viraEsquerda();
              break;
           case DIREITA: 
              viraDireita();      
              break;
           case PARADO: 
              parado();
              break;
           case TRAS:
              praTras();
              break;
        }
//      delay(200);
//        delay(tempo*3);
  }
  
  void viraDireita(){
    analogWrite(ENA, velocidade);
    analogWrite(ENB, velocidade/2);
    
    digitalWrite(MotorRight1, LOW) ;
    digitalWrite(MotorRight2, HIGH);
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);     

    direcaoAtual = DIREITA;
  }
  
  void viraEsquerda(){
    analogWrite(ENA, velocidade);
    analogWrite(ENB, velocidade/2);
    
    digitalWrite(MotorRight1, HIGH) ;
    digitalWrite(MotorRight2, LOW);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, HIGH);     

    direcaoAtual = ESQUERDA;
  }

  void emFrente(){
    if (direcaoAtual == TRAS){
      desacelera();
    }
    
    analogWrite(ENA, velocidade);
    analogWrite(ENB, velocidade);
    
    digitalWrite(MotorRight1, LOW) ;
    digitalWrite(MotorRight2, HIGH);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, HIGH);     

    direcaoAtual = FRENTE;
  }

   
 void desacelera(){
    //aumenta = false;
    while(velocidade > incrementoVelocidade){
      velocidade = 
        ( (velocidade - incrementoVelocidade) < incrementoVelocidade ? incrementoVelocidade : (velocidade - incrementoVelocidade));

      analogWrite(ENA, velocidade);
      analogWrite(ENB, velocidade);
      delay(500);
    }
    
    parado();
    delay(500);

    //aumenta = true;      
 }


  void praTras(){
    if (direcaoAtual == FRENTE){
      desacelera();
    }
 
    analogWrite(ENA, velocidade);
    analogWrite(ENB, velocidade);
    
    digitalWrite(MotorRight1, HIGH) ;
    digitalWrite(MotorRight2, LOW);
    digitalWrite(MotorLeft1, HIGH);
    digitalWrite(MotorLeft2, LOW);     

    direcaoAtual = TRAS;
  }

  void parado(){
    desacelera();
    //velocidade = 1;

    analogWrite(ENA, LOW);
    analogWrite(ENB, LOW);
    
    digitalWrite(MotorRight1, LOW) ;
    digitalWrite(MotorRight2, LOW);
    digitalWrite(MotorLeft1, LOW);
    digitalWrite(MotorLeft2, LOW);     

    direcaoAtual = PARADO;
  }


