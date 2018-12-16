int irPin = 1; //Sensor pin 1 wired to Arduino's pin 2

int start_bit = 2200; //Start bit threshold (Microseconds)
int bin_1 = 1000; //Binary 1 threshold (Microseconds)
int bin_0 = 400; //Binary 0 threshold (Microseconds)


void setup() {
  // put your setup code here, to run once:
  // initialize serial communication at 9600 bits per second:
  pinMode(irPin, INPUT);
  
  Serial.begin(9600);
  Serial.println("Waiting: ");

}

void loop() {
  // put your main code here, to run repeatedly:
 // print out the state of the button:
  int key = getIRKey(); //Fetch the key
  
  if(key != 0) //Ignore keys that are zero
    Serial.print("Key Recieved: " + key);
  
    delay(100);

}


int getIRKey() {
    int data[12];
    int i;
    
    while(pulseIn(irPin, LOW) < start_bit); //Wait for a start bit
    
    for(i = 0 ; i < 11 ; i++)
      data[i] = pulseIn(irPin, LOW); //Start measuring bits, I only want low pulses
    
    for(i = 0 ; i < 11 ; i++) //Parse them
    {
      if(data[i] > bin_1) //is it a 1?
        data[i] = 1;
      else if(data[i] > bin_0) //is it a 0?
        data[i] = 0;
      else

      return -1; //Flag the data as invalid; I don't know what it is! Return -1 on invalid data
    }
    
    int result = 0;
    for(i = 0 ; i < 11 ; i++) //Convert data bits to integer
      if(data[i] == 1) result |= (1, i);
    
    return result; //Return key number
}
