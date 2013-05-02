//Version 2013

//Valparaiso

// RGB LED Common Cathode
int greenPin = 6;
int bluePin = 9;
int redPin = 10;


//motor A connected between A01 and A02
//motor B connected between B01 and B02

int STBY = 7; //standby
int robotID = 1; 

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 4; //Direction
int AIN2 = 2; //Direction

//Motor B
int PWMB = 11; //Speed control
int BIN1 = 8; //Direction
int BIN2 = 12; //Direction

char comando;

int pulse = 100;

void setup(){
  pinMode(redPin,   OUTPUT);   // sets the pins as output
  pinMode(greenPin, OUTPUT);   
  pinMode(bluePin,  OUTPUT);
  
  //Motor pin set
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  // For XBee
  Serial.begin(115200);
  
  digitalWrite(greenPin, HIGH);
  
  
  //outputColour(0,100,200);
}

void loop(){
  
  if (Serial.available()){

    comando=Serial.read();
   // Serial.print("state: ");
   // Serial.println(comando);
   if(robotID==1){
     
    if(comando=='p')go();
    else if(comando=='q')back();
    else if(comando=='r')left();
    else if(comando=='s')right();
    else if(comando=='t')stop();
    
   }
   else if (robotID==2){
     
    if(comando=='i')go();
    else if(comando=='k')back();
    else if(comando=='j')left();
    else if(comando=='l')right();
    else if(comando=='u')stop();
   }
  }

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

void go(){
  //Serial.println("go");
  move(1, 100, 0); //motor 1, half speed, right
  move(2, 100, 0); //motor 2, half speed, right
  stop();
}

void back(){
  //Serial.println("back");
  move(1, 100, 1); //motor 1, half speed, right
  move(2, 100, 1); //motor 2, half speed, right
  stop();
}

void left(){
  //Serial.println("left");
  move(1, 100, 1); //motor 1, half speed, right
  move(2, 100, 0); //motor 2, half speed, right
  stop();
}

void right(){
  //Serial.println("right");
  move(1, 100, 0); //motor 1, half speed, right
  move(2, 100, 1); //motor 2, half speed, right
  stop();  
}

void outputColour(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);    
}
