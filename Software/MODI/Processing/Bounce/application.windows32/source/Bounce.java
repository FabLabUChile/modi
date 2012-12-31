import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class Bounce extends PApplet {

/**
 * Bounce. 
 * 
 * When the shape hits the edge of the window, it reverses its direction. 
 */
 



Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port

int rad = 90;        // Width of the shape
float xpos, ypos;    // Starting position of shape    

float xspeed = 2.8f;  // Speed of the shape
float yspeed = 4.5f;  // Speed of the shape

int xdirection = 1;  // Left or Right
int ydirection = 1;  // Top to Bottom


public void setup() 
{
  size(320, 240);
  noStroke();
  frameRate(10);
  ellipseMode(RADIUS);
  // Set the starting position of the shape
  xpos = width/2;
  ypos = height/2;
  
  
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 115200);
  
}

public void draw() 
{
  background(102);
   
  if (ydirection > 0) myPort.write('w'); 
  else myPort.write('s');
    
  if (xpos < (xpos + ( xspeed * xdirection ))) {
    myPort.write('d'); 

        }
    else {
     myPort.write('a');


    }
  // Update the position of the shape
  xpos = xpos + ( xspeed * xdirection );
  ypos = ypos + ( yspeed * ydirection );
  
 
  
  // Test to see if the shape exceeds the boundaries of the screen
  // If it does, reverse its direction by multiplying by -1
  if (xpos > width-rad || xpos < rad) {
    xdirection *= -1;

  }
  if (ypos > height-rad || ypos < rad) {
    ydirection *= -1;

  }


    

  // Draw the shape
  ellipse(xpos, ypos, rad, rad);
}
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "Bounce" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
