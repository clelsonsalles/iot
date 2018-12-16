// This program uses an Arduino Uno and a L298N motor driver board. It will make both motors go forward.

 

int fPinA = 2;    // Forward for motor A (left)
int rPinA = 3;    // Reverse for motor A (Left)
int toggleA = 5;  // Turns motor A on/off

int fPinB = 4;    // Forward for motor B (Right)
int rPinB = 7;    // Reverse for motor B (Right)
int toggleB = 6; // Turns motor B on/off

const int buttonPin = 8; 
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
const int ledAzul =  13;      // the number of the LED pin
const int ledVerde =  12;      // the number of the LED pin
const int ledVermelho =  11;      // the number of the LED pin


const int FRENTE = 0;
const int ESQUERDA = 1;
const int DIREITA = 2;
const int PARADO = 3;
const int TRAS = 4;
 

void setup()
{
  // initialize the LED pin as an output:
  pinMode(ledAzul, OUTPUT);     
  pinMode(ledVerde, OUTPUT);      
  pinMode(ledVermelho, OUTPUT);      
  // initialize the pushbutton pin as an input:
   pinMode(buttonPin, INPUT);    

   pinMode( fPinA, OUTPUT );   
   pinMode( rPinA, OUTPUT );
   pinMode( toggleA, OUTPUT );

   pinMode( fPinB, OUTPUT );   
   pinMode( rPinB, OUTPUT );  
   pinMode( toggleB, OUTPUT );
}

void comandoDirecao(int direcao, int tempo){
 
   switch (direcao){
   case FRENTE:
     digitalWrite( fPinA, HIGH );    // Makes motor A go forward
     digitalWrite( rPinA, LOW );     // Reverse not used
     digitalWrite( fPinB, HIGH );    // Makes motor B go forward
     digitalWrite( rPinB, LOW );     // Reverse not used
     break;
   case ESQUERDA: 
     digitalWrite( fPinA, LOW );    // Makes motor A go forward
     digitalWrite( rPinA, HIGH );     // Reverse not used
     digitalWrite( fPinB, LOW );    // Makes motor B go forward
     digitalWrite( rPinB, LOW );     // Reverse not used
     break;
   case DIREITA: 
     digitalWrite( fPinA, LOW );    // Makes motor A go forward
     digitalWrite( rPinA, LOW );     // Reverse not used
     digitalWrite( fPinB, LOW );    // Makes motor B go forward
     digitalWrite( rPinB, HIGH );     // Reverse not used
     break;
   case PARADO: 
     digitalWrite( fPinA, LOW );    // Makes motor A go forward
     digitalWrite( rPinA, LOW );     // Reverse not used
     digitalWrite( fPinB, LOW );    // Makes motor B go forward
     digitalWrite( rPinB, LOW );     // Reverse not used
     break;
   case TRAS:
     digitalWrite( fPinA, LOW );    // Makes motor A go forward
     digitalWrite( rPinA, HIGH );     // Reverse not used
     digitalWrite( fPinB, LOW );    // Makes motor B go forward
     digitalWrite( rPinB, HIGH );     // Reverse not used
     break;
    
   }
   
   delay(tempo);
   digitalWrite( fPinA, LOW );    // Makes motor A go forward
   digitalWrite( rPinA, LOW );     // Reverse not used
   digitalWrite( fPinB, LOW );    // Makes motor B go forward
   digitalWrite( rPinB, LOW );     // Reverse not used
}
 
 
void acender(int led){
   digitalWrite(ledAzul, LOW);
   digitalWrite(ledVerde, LOW);
   digitalWrite(ledVermelho, LOW);  
   
   switch (led){
    case ledAzul:
     digitalWrite(ledAzul, HIGH);
     break;
    case ledVerde:
     digitalWrite(ledVerde, HIGH);
     break;
    case ledVermelho:
     digitalWrite(ledVermelho, HIGH);
     break;
   }
  
  
}

void loop()
{
    // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println("Button: " + digitalRead(buttonPin));

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {    
    // turn LED off:
    acender(ledAzul);
    digitalWrite( toggleA, HIGH );  // Turns motor A on
    digitalWrite( toggleB, HIGH );  // Turns motor B on

    comandoDirecao(FRENTE, 2000);
    comandoDirecao(PARADO, 1000);

    acender(ledVerde);
    comandoDirecao(TRAS, 2000);
    comandoDirecao(PARADO, 1000);

    acender(ledVermelho);
    comandoDirecao(ESQUERDA, 1000);
    comandoDirecao(DIREITA, 400);
    comandoDirecao(ESQUERDA, 1000);
    comandoDirecao(DIREITA, 400);
    comandoDirecao(ESQUERDA, 1000);
    comandoDirecao(DIREITA, 400);
    comandoDirecao(ESQUERDA, 2000);
    comandoDirecao(DIREITA, 1000);
    
    acender(LOW);
   digitalWrite( fPinA, LOW );    // Makes motor A go forward
   digitalWrite( rPinA, LOW );     // Reverse not used
   digitalWrite( fPinB, LOW );    // Makes motor B go forward
   digitalWrite( rPinB, LOW );     // Reverse not used
   delay(4000);
  }
  else {
    // turn LED on:    
    acender(ledVermelho);
    delay(400);
    acender(LOW);
    delay(400);
  }

}
