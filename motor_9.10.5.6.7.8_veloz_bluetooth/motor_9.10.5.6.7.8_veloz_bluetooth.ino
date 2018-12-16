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
int MotorLeft1    = 9;
int MotorLeft2    = 10; 
int ENA           = 7;
int ENB           = 8;

const int ledAzul =  13;      // the number of the LED pin
const int ledVerde =  12;      // the number of the LED pin
const int ledVermelho =  11;      // the number of the LED pin


//Controla a direção do carro
int direcaoAtual = PARADO;
//Controla a velocidade
int velocidade = 256/8;
boolean aumenta = true;
int incrementoVelocidade = velocidade;
int tempo = 60;

int buttonpin = 2; // define the Reed sensor interfaces
int val ;// define numeric variables val
boolean parar = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Bluetooth configurado...");
  pinMode (MotorRight1, OUTPUT); // Pin 5 (PWM)
  pinMode (MotorRight2, OUTPUT); // Pin 6 (PWM)
  pinMode (MotorLeft1, OUTPUT); // Pin 9 (PWM)
  pinMode (MotorLeft2, OUTPUT); // Pin 10 (PWM) 
  pinMode (ENA, OUTPUT); // Pin 7  
  pinMode (ENB, OUTPUT); // Pin 8  

  // initialize the LED pin as an output:
  pinMode(ledAzul, OUTPUT);     
  pinMode(ledVerde, OUTPUT);      
  pinMode(ledVermelho, OUTPUT);      

  digitalWrite (ENA, HIGH);     
  digitalWrite (ENB, HIGH);     

  pinMode (buttonpin, INPUT) ;// output interface as defined Reed sensor
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);  

}

void loop() {
  if (parar){
    acender(ledVermelho);
    delay(tempo * 15);
    return;
  
  }
  
  val = digitalRead(buttonpin) ;// digital interface will be assigned a value of 3 to read val
  if (val < HIGH) // When the Reed sensor detects a signal, LED flashes
  {
    parar = true;
    parado();

    acender(ledVerde);
    delay(tempo * 15);
    acender(ledVermelho);
    delay(tempo * 15);
    acender(ledAzul);
    delay(tempo * 15);

    return;
  }
  //Aumenta a velocidade com o incremento, até 256
  /*
  velocidade = 
    ( (velocidade + incrementoVelocidade) > 256 ? 256 : (velocidade + incrementoVelocidade));
  */
  
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
        Serial.println("\nO");
      }
      else if (state ==53){
        aumentaVelocidade();
//        Serial.println("\nTri");
      }
      else if (state ==55){
        diminuiVelocidade();
//        Serial.println("\nQuad");
      }
      else if (state ==48){
        Serial.println("\nStart");
      }
      else{
        Serial.print(state);
        Serial.print(", ");
        //Não recebeu comando de bluetooth
        repeteComando(); 

      }
      delay(tempo);
  } else{
      repeteComando(); 
  } 
 
}

  void aumentaVelocidade(){
    velocidade = 
      ( (velocidade + incrementoVelocidade) > 256 ? 256 : (velocidade + incrementoVelocidade));
      
    //acender(ledVerde);
    delay(tempo * 4);
  }
  
  void diminuiVelocidade(){
    velocidade = 
      ( (velocidade - incrementoVelocidade) < 0 ? 0 : (velocidade - incrementoVelocidade));
    
    //acender(ledAzul);

    delay(tempo * 4);
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
        delay(tempo*3);
  }
  
  void viraDireita(){
    int veloz1 = (velocidade*2 >= 256) ? 200 : velocidade*2;
    int veloz2= veloz1 >= 200 ? velocidade/2 : velocidade;

    analogWrite(MotorRight1, LOW) ;
    analogWrite(MotorRight2, veloz1);
    analogWrite(MotorLeft1, veloz2);
    analogWrite(MotorLeft2, LOW);     

//    direcaoAtual = DIREITA;
  }
  
  void viraEsquerda(){
    int veloz1 = (velocidade*2 >= 256) ? 200 : velocidade*2;
    int veloz2= veloz1 >= 200 ? velocidade/2 : velocidade;
    
    analogWrite(MotorRight1, veloz1) ;
    analogWrite(MotorRight2, LOW);
    analogWrite(MotorLeft1, LOW);
    analogWrite(MotorLeft2, veloz2);     

//    direcaoAtual = ESQUERDA;
  }

  void emFrente(){
    if (direcaoAtual == TRAS)
      desacelera();

    //Configura a velocidade inicial
    velocidade = velocidade < incrementoVelocidade ? incrementoVelocidade : velocidade;

    analogWrite(MotorRight1, LOW) ;
    analogWrite(MotorRight2, velocidade);
    analogWrite(MotorLeft1, LOW);
    analogWrite(MotorLeft2, velocidade);     

    direcaoAtual = FRENTE;
  }

   
 void desacelera(){
    aumenta = false;
    while(velocidade != 1){
      velocidade = 
        ( (velocidade - incrementoVelocidade) < 1 ? 1 : (velocidade - incrementoVelocidade));
      if (direcaoAtual == FRENTE){
        //Andar pra frente até parar
        //emFrente();
        analogWrite(MotorRight1, LOW) ;
        analogWrite(MotorRight2, velocidade);
        analogWrite(MotorLeft1, LOW);
        analogWrite(MotorLeft2, velocidade);     
        
      }
      else if (direcaoAtual == TRAS){
        //Andar pra tras até parar
        //praTras();
        analogWrite(MotorRight1, velocidade) ;
        analogWrite(MotorRight2, LOW);
        analogWrite(MotorLeft1, velocidade);
        analogWrite(MotorLeft2, LOW);     
      }
      delay(tempo);
    }


    aumenta = true;      
 }


  void praTras(){
    if (direcaoAtual == FRENTE)
      desacelera();
 
    //Configura a velocidade inicial
    velocidade = velocidade < incrementoVelocidade ? incrementoVelocidade : velocidade;

    analogWrite(MotorRight1, velocidade) ;
    analogWrite(MotorRight2, LOW);
    analogWrite(MotorLeft1, velocidade);
    analogWrite(MotorLeft2, LOW);     

    direcaoAtual = TRAS;
  }

  void parado(){
    desacelera();
    velocidade = 1;

    analogWrite(MotorRight1, LOW) ;
    analogWrite(MotorRight2, LOW);
    analogWrite(MotorLeft1, LOW);
    analogWrite(MotorLeft2, LOW);     

    //acender(ledVermelho);

    direcaoAtual = PARADO;
  }


void acender(int led){
   digitalWrite(ledAzul, LOW);
   digitalWrite(ledVerde, LOW);
   digitalWrite(ledVermelho, LOW);  
   
   digitalWrite(led, HIGH);
  
}

