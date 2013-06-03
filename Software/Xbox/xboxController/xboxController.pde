import procontroll.*;
import processing.serial.*;

Serial port;
ControllIO controllIO;
ControllDevice joypad;
ControllStick stick;
ControllStick trigger;

void setup(){
  println(Serial.list());
  port = new Serial(this, "COM4", 115200);
  controllIO = ControllIO.getInstance(this);
  joypad = controllIO.getDevice("Controller (XBOX 360 For Windows)");
  ControllSlider sliderX = joypad.getSlider("Eixo X");
  ControllSlider sliderY = joypad.getSlider("Eixo Y");
  ControllSlider sliderZ = joypad.getSlider("Eixo Z");
  stick = new ControllStick(sliderX,sliderY);  
  stick.setTolerance(0.25f);
  trigger = new ControllStick(sliderZ,sliderZ);
  trigger.setTolerance(0.05f);
}

void draw(){
  float stk = stick.getX();
  float tgr = trigger.getX();
  int StickValue = int(map(stk,-1,1,1,9));
  int TriggerValue = int(map(tgr,-1,1,1,10));
  int output = 10 * StickValue + TriggerValue;
  port.write(output);
  while (port.available() > 0) {
    int input = (port.read());
    println(input);
  }
}
