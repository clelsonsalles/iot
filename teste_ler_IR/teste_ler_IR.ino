int ir_pin = 9;    //Sensor pin 3, the data pin
int data[12];
  
void setup() {
  //pinMode(pwr_high, OUTPUT);    
  //pinMode(pwr_low, OUTPUT);
  pinMode(ir_pin, INPUT);
  //digitalWrite(pwr_high, HIGH);    //Sensor pin 1 always high
  //digitalWrite(pwr_low, LOW);      //Sensor pin 2 always low
  Serial.begin(9600);
}

void loop() {
  data[0] = pulseIn(ir_pin, LOW);    //Start measuring bits --the sensor defaults high, goes low on infrared 
  data[1] = pulseIn(ir_pin, LOW);
  data[2] = pulseIn(ir_pin, LOW);
  data[3] = pulseIn(ir_pin, LOW);
  data[4] = pulseIn(ir_pin, LOW);
  data[5] = pulseIn(ir_pin, LOW);
  data[6] = pulseIn(ir_pin, LOW);
  data[7] = pulseIn(ir_pin, LOW);
  data[8] = pulseIn(ir_pin, LOW);
  data[9] = pulseIn(ir_pin, LOW);
  data[10] = pulseIn(ir_pin, LOW);
  data[11] = pulseIn(ir_pin, LOW);
  
  Serial.println("-----");    //Send them all
  Serial.print(data[0]);
  Serial.print(data[1]);
  Serial.print(data[2]);
  Serial.print(data[3]);
  Serial.print(data[4]);
  Serial.print(data[5]);
  Serial.print(data[6]);
  Serial.print(data[7]);
  Serial.print(data[8]);
  Serial.print(data[9]);
  Serial.print(data[10]);
  Serial.println(data[11]);
  Serial.println("-----");    //Send them all
}
