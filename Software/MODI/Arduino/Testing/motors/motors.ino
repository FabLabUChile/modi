//For Testing propose of motors in Robot MODI
//Santiago

//Motor A connected between A01 and A02
//Motor B connected between B01 and B02

int STBY = 7; //standby

//Motor A
int PWMA = 3; //Speed control
int AIN1 = 4; //Direction
int AIN2 = 2; //Direction

//Motor B
int PWMB = 11; //Speed control
int BIN1 = 48; //Direction
int BIN2 = 12; //Direction

int pulse = 100;


int motor;
int speedM;
int dir;

void setup()
{
  //Motors pin set
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  //For XBee
  Serial.begin(115200);

}

void loop()
{
  
  Serial.println("Hi!! This is testing for MODI Motors");
  delay(500);
  Serial.println("Please tell me which motor u <3 to move?");
  delay(500);
  Serial.println("1 or 2?");
  delay(500);
  while(Serial.available() == 0)
    motor=Serial.read();
    Serial.flush();
  
  Serial.println("speed?: 0-255");
   while(Serial.available() == 0)
    speedM=Serial.read();
    Serial.flush();

  
  Serial.println("Direction?  o d?");
   while(Serial.available() == 0)
    dir=Serial.read();
    Serial.flush();

    
  move(motor, speedM, dir); //motor 1, half speed, right
     
           
}

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  delay(pulse);
  digitalWrite(STBY, LOW);
  //Serial.println("stop");
}


