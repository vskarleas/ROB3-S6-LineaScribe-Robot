#include <Servo.h>
#include <math.h>

#define pinx A0 //Joystick
#define piny A1
#define pinbutton1 2 //Joystick button
#define pinbutton2 4

const int buttonPin1 = 13;
const int buttonPin2 = 4;
const int buttonPin4 = 12;
const int buttonPin3 = 7;

int buttonState1;
int buttonState2;
int buttonState3;
int buttonState4;

const int ledPin = 3;

int xtemp,ytemp,buttonval1,buttonval2; //values of the joystick's x and y axis, buttonval is the buttons values
int mode=-1; //choix de mode

#define UP 2
#define DOWN 1
#define SWITCH 0

#define dx 5  //decalage entre repere du robot et de la feuille
#define dy 0
Servo servo1;  
Servo servo2;
Servo servo3; //pen's motor

//Settings
float L1=10.0, L2=10.0;

//Inialisations
double pi = 3.141592653;

double val;
double x=0.0;
double y=0.0;  

//Pen's configuration
int pen_down = 1750;
int pen_up = 1600;
int penstate=0; //0 if down 1 if up

//Definition of teta1 and teta2 for pointers usage
double teta1=60;
double teta2=120;


double co2,teta2prec;

//Takes a cartesien position (x,y) and returns the 
void get_angles(double x, double y, float L1, float L2, double* teta1, double* teta2){

  //decalage entre repere du robot et de la feuille
  x+=dx;
  y+=dy;


  co2 = (x*x+y*y-L1*L1-L2*L2)/(2*L1*L2);
  teta2prec = atan2((-sqrt(1-co2*co2)),co2); //La racine decide quelle orientation on veut. Selon la configuration 

  *teta1 = atan2(y,x) - atan2((L2*sin(teta2prec)),(L1+L2*cos(teta2prec)));

  teta2prec = teta2prec*180/pi; //rad to degrees
  *teta1 = *teta1*180/pi;
  *teta2 = *teta2*180/pi;

  //teta2 final c'est le  teta1 -teta2_de_base + pi -> voir wiki 
  *teta2=-abs(teta2prec)+*teta1+180;

  *teta2 = 180-*teta2;
}

void pen_control(int control) //Down, up, switch state
{
  if (control == DOWN) //write with pen [pen is down]
  {
    servo3.writeMicroseconds(pen_down); 
  }
  else if (control == UP) //disable writing [pen is up]
  {
    servo3.writeMicroseconds(pen_up);
  }
  else
  {
    printf("An error occured on controling the pen\n");
  }
}

void straight_line(double *x_start, double *y_start, int length, double angle)
{
  //repitive task for straight line of 5cm
  for (float i = 0; i < length*100; i++)
  {
    *x_start = *x_start + cos(angle)/100; //division of 100 for better precision
    *y_start = *y_start + sin(angle)/100;
    get_angles(*x_start,*y_start,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2);  
  }
}

void circle(double x_center, double y_center, double radius, double *x, double *y)
{
  for (double i = 0; i < 3600; i++)
  {
    *x = x_center + (radius * cos(radians(i/10)));
    *y = y_center + (radius * sin(radians(i/10)));
    get_angles(*x,*y,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2); 
  }
}

//I DON'T KNOW
void dotted_circle(double x_center, double y_center, double radius, double *x, double *y)
{
  pen_control(DOWN);
  for (int i = 0; i < 360; i++)
  {
    *x = x_center + (radius * cos(radians(i)));
    *y = y_center + (radius * sin(radians(i)));

    //THIS GOES HERE, ISN'T IT ?
    get_angles(*x,*y,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2);
  }
}


void square(double *x, double *y, int length, int angle)
{
 straight_line(x,y,length, radians(angle));
 delay(1000);
 straight_line(x,y,length, radians(angle+90));
 delay(1000);
 straight_line(x,y,length, radians(angle+180));
 delay(1000);
 straight_line(x,y,length, radians(angle+270));
 delay(1000);
}


void Joystick(double *x, double *y)
{
  //Sending mode on, sending joystick data to processing
  int out=0;
  while(out==0){

    //On verifie si on Lit les valeurs du Joystick ou l'utilisateur a decide d'arrete
    if (Serial.available() > 0) {
      String response = Serial.readStringUntil('\n'); 
      response.trim();  // Remove any leading or trailing whitespace
      
      if (response.equals("Done")) {
        //digitalWrite(13,LOW);
        break;  // Stop sending data to processing
      }
    }
    //Reading Joysticks values
    xtemp = analogRead(pinx);
    ytemp = analogRead(piny);

    buttonval1 = 1-digitalRead(pinbutton1);
    buttonval2 = digitalRead(pinbutton2);

    //Sending Joysticks values to processing
    Serial.print(xtemp);
    Serial.print("\t");
    Serial.print(ytemp);
    Serial.print("\t");
    Serial.print(buttonval1); 
    Serial.print("\t");
    Serial.println(buttonval2);
    
    //Cette boucle empeche le chevauchement de plusieur valeur etant donne que la frequence d';envoi de donne de l'arduino est plus eleve que la frequence de recoit de processing
    //On attend donc jusqu'a ce que la donnee est bien lu par processing avant d'envoyer une autre donne
    
    while (true) {
      if (Serial.available() > 0) {
        String response = Serial.readStringUntil('\n'); 
        response.trim();  // Remove any leading or trailing whitespace
        
        if (response.equals("Received")) break;  // Exit the while loop
        else if (response.equals("Done")) out=1; //get out of the loop
      }
    }
  }
  
  //Receiving mode on, the arduino is ready to draw
  while (true) {
    if (Serial.available() > 0) {
      String receivedString = Serial.readStringUntil('\t');
      
      if (receivedString.startsWith("end")) {
        // Termination signal "end" received, stop processing data
        digitalWrite(13,LOW);
        break;  // Exit the while loop
      }
      
      *x = receivedString.toDouble();

      receivedString = Serial.readStringUntil('\t');
      
      if (receivedString.startsWith("end")) break;  // Exit the while loop
      *y = receivedString.toDouble();
      
      //draw here with *x,*y

    
      // Serial.print(*x);
      // Serial.print("\t");
      // Serial.println(*y); 
    }
  }
}

void control_mode(int mode, double x, double y)
{
  if (mode == 3)
  {
    pen_control(DOWN);
    delay(100);
    get_angles(x,y,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2);
  }

  if (mode == 2)
  {
    pen_control(UP);
    servo1.write(0); 
    servo2.write(90);
  }
  else
  {
    pen_control(UP);
    get_angles(x,y,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2);
  }
  
}

void dotted_line(double *x_start, double *y_start, int length, double angle, double dot_length, double space_length, int delay_time) {
  for (int i = 0; i < length; i += dot_length + space_length) {
    // Move to the starting point of the dot
    *x_start += cos(angle) * dot_length / 100;
    *y_start += sin(angle) * dot_length / 100;

    // Update arm positions for the dot
    get_angles(*x_start, *y_start, L1, L2, &teta1, &teta2);
    servo1.write(teta1);
    servo2.write(teta2);

    // Pen down to draw the dot
    pen_control(DOWN);
    delay(delay_time); // Adjust delay for desired dot duration

    // Pen up for the space
    pen_control(UP);
    delay(delay_time); // Adjust delay for desired space duration

    // Move to the starting point of the next dot (considering space length)
    *x_start += cos(angle) * (space_length + dot_length) / 100;
    *y_start += sin(angle) * (space_length + dot_length) / 100;
  }
}

/* Not tested yet  */
void dotted_line_v2(double *x_start, double *y_start, int length, double angle, int dot_length, int gap_length)
{
    int total_length = length * 100; 
    int dot_steps = dot_length * 10;  // Convert dot length to steps
    int gap_steps = gap_length * 10;  // Convert gap length to steps
    int step_count = 0;
    
    for (int i = 0; i < total_length; i++)
    {
        if (step_count < dot_steps) {
            pen_control(DOWN);
        } else {
            pen_control(UP);
        }

        // Move to the next point
        *x_start = *x_start + cos(angle) / 100;
        *y_start = *y_start + sin(angle) / 100;
        get_angles(*x_start, *y_start, L1, L2, &teta1, &teta2);
        servo1.write(teta1); 
        servo2.write(teta2);

        // Increment the step count and reset if necessary
        step_count++;
        if (step_count >= (dot_steps + gap_steps)) {
            step_count = 0;
        }
    }

    //servo3.write(0);  // Pen up position
}



void setup() {
  servo1.attach(9);
  servo2.attach(10); 
  servo3.attach(11);

  pinMode(pinx,INPUT);
  pinMode(piny,INPUT);
  pinMode(pinbutton1,INPUT_PULLUP);
  pinMode(pinbutton2,INPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);

  pinMode(ledPin, OUTPUT);

  pinMode(13,OUTPUT);

  get_angles(0.0,0.0,L1,L2,&teta1, &teta2);
  servo1.write(0); 
  servo2.write(90);
  servo3.writeMicroseconds(1100);
  delay(2000);
  straight_line(&x,&y,5, radians(90));
  delay(10000);


  
  //delay(1000);
  //straight_line(&x,&y,15, radians(45));

  Serial.begin(9600);
  
}


//void loop() {
  //dotted_line(&x, &y, 5, 0.0, 0.2, 0.2, 300);
  //dotted_circle(2.5, 2.5, 2.5, &x, &y, 1, 0.3);
  

//   /* Simple implementations of existing functions for testing purposes.
//   We have only one active every time. All the others has to be commented in order to observe the robot's mouvements */
//   //square(&x,&y,5, 0);  

//   dotted_line(&x, &y, 100, radians(45), 5, 10); // Draw a dotted line at 45 degrees, 100 units long with 5 unit dots and 10 unit spaces

//   // straight_line(&x,&y,5, radians(45)); //straight line in x'x axes
//   // delay(1000);
//   // straight_line(&x,&y,5, radians(180+45));    

//   //===========================================

//   /* Joystick test */
//   // Joystick(&x,&y); 

//   // digitalWrite(13,HIGH);  
                    
//}


void blinkLED(int ledPin) {
    digitalWrite(ledPin, HIGH);
    delay(350);
    digitalWrite(ledPin, LOW);
    delay(350);
    
}


void loop() {
  buttonState1 = digitalRead(buttonPin1); // Read button 1 state
  buttonState2 = digitalRead(buttonPin2); // Read button 2 state
  buttonState3 = digitalRead(buttonPin3); // Read button 3 state
  buttonState4 = digitalRead(buttonPin4); // Read button 4 state

  // Check if any button is pressed (active low)
 
  
  //blinkLED(ledPin);
  
  // Check which button was pressed
  if (buttonState1 == HIGH) {
    buttonState1 = LOW;
    // Button 1 pressed, perform straight line

    Serial.print("Line\n");
    //control_mode(2,0.0, 0.0); //put into writing position
    delay(100);
    digitalWrite(ledPin, HIGH);
    delay(700);
    straight_line(&x,&y,5, radians(90));
    //square(&x, &y, 5, radians(0)); 
    digitalWrite(ledPin, LOW);
    delay(400);
    control_mode(2, 0.0, 0.0); 
  } 
  // else if (buttonState2 == HIGH) {
  //   buttonState2 = LOW;
  //   // Button 2 pressed, perform circle
  //   double x_center = 0.0, y_center = 0.0, radius = 5.0; 
  //   Serial.print("Circle\n");
  //   delay(100);
  //   control_mode(3, 2.5, 2.5); //put into writing position
  //   digitalWrite(ledPin, HIGH);
  //   circle(x_center, y_center, radius, &x, &y); // Update x and y for circle
  //   digitalWrite(ledPin, LOW);
  //   control_mode(0, 0.0, 0.0); 
  // } else if (buttonState3 == HIGH) {
  //   buttonState3 = LOW;
  //   // Button 3 pressed, perform dotted line
  //   Serial.print("Dotted line\n");
  //   control_mode(3, 0.0, 0.0); //put into writing position
  //   digitalWrite(ledPin, HIGH);
  //   dotted_line(&x, &y, 5, 0.0, 0.2, 0.2, 300);
  //   digitalWrite(ledPin, LOW);
  //   control_mode(0, 0.0, 0.0); 
  // } else if (buttonState4 == HIGH) {
  //   buttonState4 = LOW;
  //   // Button 4 pressed, perform dotted circle
  //   Serial.print("Dotted circle\n");
  //   control_mode(3, 0.0, 0.0); //put into writing position
  //   digitalWrite(ledPin, HIGH);
  //   square(&x,&y,5, 0);  
  //   digitalWrite(ledPin, LOW);
  //   control_mode(0, 0.0, 0.0); 
  // }
}



