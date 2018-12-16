#include <SPI.h>
#include <MFRC522.h>


//Configura os pinos de comunicação coma placa RFID
#define RST_PIN		9		// 
#define SS_PIN		10		//
/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12       de ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance

const String uid_tag_azul       = "4294940404";
const String uid_nfc_azul       = "4294935114";
const String uid_nfc_vermelho   = "20042";
const String uid_nfc_laranja    = "4294935122";
const String uid_nfc_verde      = "4294937938";
const String uid_cartao_branco  = "4294941365";

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
int ENA           = 2;
int ENB           = 4;


/*
const int ledAzul =  13;      // the number of the LED pin
const int ledVerde =  12;      // the number of the LED pin
const int ledVermelho =  11;      // the number of the LED pin
*/

//Controla a direção do carro
int direcaoAtual = PARADO;
//Controla a velocidade
int velocidade = 256/6;
boolean aumenta = true;
int incrementoVelocidade = velocidade;
int tempo = 60;

/*
int buttonpin = 2; // define the Reed sensor interfaces
int val ;// define numeric variables val
boolean parar = false;
*/


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();			// Init SPI bus
  mfrc522.PCD_Init();		// Init MFRC522
  ShowReaderDetails();	// Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));

  Serial.println("Bluetooth configurado...");
  pinMode (MotorRight1, OUTPUT); // Pin 5 (PWM)
  pinMode (MotorRight2, OUTPUT); // Pin 6 (PWM)
  pinMode (MotorLeft1, OUTPUT); // Pin 9 (PWM)
  pinMode (MotorLeft2, OUTPUT); // Pin 10 (PWM) 
  pinMode (ENA, OUTPUT); // Pin 7  
  pinMode (ENB, OUTPUT); // Pin 8  

/*
  // initialize the LED pin as an output:
  pinMode(ledAzul, OUTPUT);     
  pinMode(ledVerde, OUTPUT);      
  pinMode(ledVermelho, OUTPUT);      

//  pinMode (buttonpin, INPUT) ;// output interface as defined Reed sensor
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);  

*/
  digitalWrite (ENA, HIGH);     
  digitalWrite (ENB, HIGH);     


}

void loop() {
/*  
  if (parar){
    acender(ledVermelho);
    delay(tempo * 15);
    return;
  
  }

  val = digitalRead(buttonpin) ;// digital interface will be assigned a value of 3 to read val
  if (val < HIGH) // When the Reed sensor detects a signal, LED flashes
  {
    parar = true;

    acender(ledVerde);
    delay(tempo * 15);
    acender(ledVermelho);
    delay(tempo * 15);
    acender(ledAzul);
    delay(tempo * 15);

    return;
  }
*/

  //Aumenta a velocidade com o incremento, até 256
  /*
  velocidade = 
    ( (velocidade + incrementoVelocidade) > 256 ? 256 : (velocidade + incrementoVelocidade));
  */
    // Look for new cards
    if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
       String idRFID = getID_mfrc522();
       Serial.println("UID String :" + idRFID);
       if (idRFID.equals(uid_tag_azul )){
         Serial.println("Este é a tag AZUL");
       }
       if (idRFID.equals(uid_nfc_azul )){
         Serial.println("Este é a tag NFC AZUL");
       }
       if (idRFID.equals(uid_nfc_vermelho )){
         Serial.println("Este é a tag NFC VERMELHA");
       }
       if (idRFID.equals(uid_nfc_laranja )){
         Serial.println("Este é a tag NFC LARANJA");
       }
       if (idRFID.equals(uid_nfc_verde )){
         Serial.println("Este é a tag NFC VERDE");
       }
       if (idRFID.equals(uid_cartao_branco )){
         Serial.println("Este é a tag CARTAO BRANCO");
       }
       
      parado();
      delay(tempo * 15);
      return;

    }

  
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
      ( ( (velocidade > 256) || (velocidade + incrementoVelocidade) > 256) ? 256 : (velocidade + incrementoVelocidade));
      
    //acender(ledVerde);
    delay(tempo);
  }
  
  void diminuiVelocidade(){
    velocidade = 
      ( (velocidade - incrementoVelocidade) < 0 ? 0 : (velocidade - incrementoVelocidade));
    
    //acender(ledAzul);

    delay(tempo);
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
        delay(tempo);
  }
  
  void viraEsquerda(){
    int veloz1 = incrementoVelocidade * 2;
    int veloz2= incrementoVelocidade;

    analogWrite(MotorRight1, LOW) ;
    analogWrite(MotorRight2, veloz1);
    analogWrite(MotorLeft1, veloz2);
    analogWrite(MotorLeft2, LOW);     

//    direcaoAtual = DIREITA;
  }
  
  void viraDireita(){
    int veloz1 = incrementoVelocidade * 2;
    int veloz2= incrementoVelocidade;
    
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
      
      if (velocidade >= incrementoVelocidade)
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
/*
  digitalWrite(ledAzul, LOW);
   digitalWrite(ledVerde, LOW);
   digitalWrite(ledVermelho, LOW);  
   
   digitalWrite(led, HIGH);
*/  
}


String getID_mfrc522(){
  
  unsigned long UID_unsigned;
  UID_unsigned =  mfrc522.uid.uidByte[0] << 24;
  UID_unsigned += mfrc522.uid.uidByte[1] << 16;
  UID_unsigned += mfrc522.uid.uidByte[2] <<  8;
  UID_unsigned += mfrc522.uid.uidByte[3];

//  Serial.println("recuperando o ID...");
//  Serial.println("UID Unsigned int"); 
//  Serial.println(UID_unsigned);

  String UID_string =  (String)UID_unsigned;
  long UID_LONG=(long)UID_unsigned;

/*
  Serial.println("UID Long :");
  Serial.println(UID_LONG);

  Serial.println("UID String :");
  Serial.println(UID_string);
*/

  return UID_string;
}

void ShowReaderDetails() {
	// Get the MFRC522 software version
	byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
	Serial.print(F("MFRC522 Software Version: 0x"));
	Serial.print(v, HEX);
	if (v == 0x91)
		Serial.print(F(" = v1.0"));
	else if (v == 0x92)
		Serial.print(F(" = v2.0"));
	else
		Serial.print(F(" (unknown)"));
	Serial.println("");
	// When 0x00 or 0xFF is returned, communication probably failed
	if ((v == 0x00) || (v == 0xFF)) {
		Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
	}
}
