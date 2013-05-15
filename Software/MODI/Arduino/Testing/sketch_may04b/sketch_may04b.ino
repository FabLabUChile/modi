//Version 2013

//Valparaiso

// RGB LED Common Cathode
int greenPin = 6;
int bluePin = 9;
int redPin = 10;


//motor A connected between A01 and A02
//motor B connected between B01 and B02

int STBY = 7; //standby

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 4; //Direction
int AIN2 = 2; //Direction

//Motor B
int PWMB = 11; //Speed control
int BIN1 = 8; //Direction
int BIN2 = 12; //Direction

char cmd;

int pulse = 1000;

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
  Serial.println(255);
  
  digitalWrite(greenPin, HIGH);
  
  
  //outputColour(0,100,200);
}

void loop(){
  
  if (Serial.available()){

    cmd=Serial.read();
   // Serial.print("state: ");
   // Serial.println(comando);
   switch(cmd){
     case '1': 
       go();
       Serial.print("state: ");
       Serial.println(cmd);
       break;
     case '2':
       back();
       Serial.print("state: ");
       Serial.println(cmd);
       break;
     case '3': 
       left();
       Serial.print("state: ");
       Serial.println(cmd);
       break;
     case '4': 
       right();
       Serial.print("state: ");
       Serial.println(cmd);
       break;
     default:
       Serial.print("state: ");
       Serial.println(cmd);
       stop();
       
   
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
  move(0, 0,0);
  stop();
}

void back(){
  //Serial.println("back");
  move(1, 100, 1); //motor 1, half speed, right
    move(0, 0,0);

  stop();
}

void left(){
  //Serial.println("left");
  move(0, 100, 0); //motor 2, half speed, right
    move(1, 0,0);
  stop();
}

void right(){
  //Serial.println("right");
  move(0, 100, 1); //motor 2, half speed, right
    move(1, 0,0);
  stop();  
}

void outputColour(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);    
}
