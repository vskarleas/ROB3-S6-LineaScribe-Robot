#include <Servo.h>
#include <math.h>

#define pinx A0 //Joystick
#define piny A1

#define pinbutton1 2 //Joystick button
#define pinbutton2 4
#define pinbutton3 7
#define pinbutton4 12
#define pinbutton5 13
#define pinbutton6 8 
#define pinbutton7 6 

#define ledPin 3 //LED pin declaration

int xtemp,ytemp,buttonval1,buttonval2; //values of the joystick's x and y axis, buttonval is the buttons values
int mode=-1; //choix de mode

#define DOWN_ 4 //With under score for dotted line
#define UP_ 3
#define UP 2
#define DOWN 1
#define SWITCH 0

#define dx 10  //decalage entre repere du robot et de la feuille
#define dy 0
Servo servo1;  
Servo servo2;
Servo servo3; //pen's motor

//Settings
float L1=10.0, L2=10.0;

//Inialisations
double pi = 3.141592653;

//Global x and y coordinate values used to control the robot's mouvement
double val;
double x=0.0;
double y=0.0;  

//Pen's configuration
double pen_down_ = 1650;
double pen_down = 1665;
double pen_up = 1590; //up max
double pen_up_ = 1620; //a little up for dot line
int penstate=0; //0 if down 1 if up

//Definition of teta1 and teta2 for pointers usage
double teta1=60;
double teta2=120;


double co2,teta2prec;

/* Takes a cartesien position (x,y) and updates the angles teta1 and teta2 that control the two motors (located on the same r) */
void get_angles(double x, double y, float L1, float L2, double* teta1, double* teta2){

  //Distance between the center of the robot and the starting point of the writing area
  x+=dx;
  y+=dy;

  //Geometric inveresed model available under teh section "Robot type SCARA"
  co2 = (x*x+y*y-L1*L1-L2*L2)/(2*L1*L2);
  teta2prec = atan2((-sqrt(1-co2*co2)),co2); //The root decides the orientation according to the configuration

  //Calculating the angle 1
  *teta1 = atan2(y,x) - atan2((L2*sin(teta2prec)),(L1+L2*cos(teta2prec)));

  teta2prec = teta2prec*180/pi; //rad to degrees 
  *teta1 = *teta1*180/pi;
  *teta2 = *teta2*180/pi;

  //teta2 is the final corrected angle according to "Specifications de notre modele" available on the Robot's documentation -> voir wiki 
  *teta2=-abs(teta2prec)+*teta1+180;

  *teta2 = 180-*teta2;
}

/* Controls the tool's position [choose between UP and DOWN] */
void pen_control(int control, int *penstate) //Down, up, swithc state
{
  if (control == DOWN) //write with pen [pen is down]
  {
    servo3.writeMicroseconds(pen_down); 
    *penstate=0;
  }
  if (control == DOWN_) //write with pen [pen is down]
  {
    servo3.writeMicroseconds(pen_down_); 
    *penstate=0;
  }
  else if (control == UP) //disable writing [pen is up]
  {
    *penstate=1;
    servo3.writeMicroseconds(pen_up);
  }
  else if (control == UP_) //disable writing [pen is up]
  {
    *penstate=1;
    servo3.writeMicroseconds(pen_up_);
  }
  else if (control == SWITCH) //disable writing [pen is up]
  {
    switch(*penstate){
      case 0:
        servo3.writeMicroseconds(pen_up);
        *penstate=1;
        break;
      case 1:
        servo3.writeMicroseconds(pen_down);
        *penstate=0;
        break;
    }
  }
  else
  {
    printf("An error occured on controling the pen\n");
  }
}

/* Draws a straight line in a specific length and to a given angle */
void straight_line(double *x_start, double *y_start, float length, double angle)
{  

  //Note: We divide the distance in multiple subpoints to be acquired. The greater the number, the most precision we can achieve of course with some limitations
  for (double i = 0; i < length*800; i++)
  {
    *x_start = *x_start + cos(angle)/800; //Current position + shift  
    *y_start = *y_start + sin(angle)/800;
    get_angles(*x_start,*y_start,L1,L2,&teta1, &teta2); //calculation of motors' angles
    servo1.write(teta1); //Sending data to the motors
    servo2.write(teta2);  
    delay(1);
  }
}

void straight_line_square(double *x_start, double *y_start, float length, double angle)
{  

  //Note: We divide the distance in multiple subpoints to be acquired. The greater the number, the most precision we can achieve of course with some limitations
  for (double i = 0; i < length*100; i++)
  {
    *x_start = *x_start + cos(angle)/100; //Current position + shift  
    *y_start = *y_start + sin(angle)/100;
    get_angles(*x_start,*y_start,L1,L2,&teta1, &teta2); //calculation of motors' angles
    servo1.write(teta1); //Sending data to the motors
    servo2.write(teta2);  
    delay(1);
  }
}

/* Designing a circle in a specific radius and a specific starting point */
void circle(double x_center, double y_center, double angle_start, double angle, double radius, double *x, double *y, int init, int res)
{

  //Placement in a specific starting point
  if(init==0){
    *x = x_center + (radius * cos(radians(angle_start)));
    *y = y_center + (radius * sin(radians(angle_start)));
    get_angles(*x,*y,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2); 
    delay(1000);

    //Get into writing position
    pen_control(DOWN,&penstate);
    delay(500);
  }
  
  //Repetead calculation different points between a starting angle and a final angle
  for (double i = (angle_start*res); i < (angle*res); i++)
  {
    *x = x_center + (radius * cos(radians(i/res))); //Formula of finding the position of a point is based on the tan function decomposed in x and y axis
    *y = y_center + (radius * sin(radians(i/res)));
    get_angles(*x,*y,L1,L2,&teta1, &teta2); //Calculation of angles for the motors
    servo1.write(teta1); //Sending data to the motors
    servo2.write(teta2);
    delay(1);  
  }
}

/* Designs a dotted circle in a specific radius and a specific starting point */
void dotted_circle(double x_center, double y_center, double angle_space, double angle_dot, double radius, double *x, double *y)
{
  
  *x = x_center + (radius * cos(radians(0)));
  *y = y_center + (radius * sin(radians(0)));
  get_angles(*x,*y,L1,L2,&teta1, &teta2);
  servo1.write(teta1); 
  servo2.write(teta2); 
  delay(1000);

  //It's a recursive loop leading to a 360 degrees circle that calls circle function with a starting and final point
  double i=0.0;
  while(i < 360) {
    
    pen_control(DOWN_, &penstate);
    delay(200);
    circle(x_center, y_center,i, angle_dot+i, radius, x, y, 1, 4);
    delay(200);

    i = i + angle_dot; //update of the current position - required to verify of a circle of 360 degress has been designed

    if(i>=360) break;

    //Between delays we chage writing mode in order to create a dotted effect
    pen_control(UP, &penstate);
    delay(200);
    circle(x_center, y_center,i, (angle_space+i), radius, x, y, 1, 4);
    i = i + angle_space;
    delay(200);

  }
}

/* Designs a square of a given length and in a given angle */
void square(double *x, double *y, int length, int angle)
{

  //Square is composed of four straight lines of a given length and they are vertical between them
 straight_line_square(x,y,length, radians(angle));
 delay(1000);
 straight_line_square(x,y,length, radians(angle+90));
 delay(1000);
 straight_line_square(x,y,length, radians(angle+180));
 delay(1000);
 straight_line_square(x,y,length, radians(angle+270));
 delay(1000);
}

/* Logig for joystick manipulation */
void Joystick(double *x, double *y)
{
  int dimx=0;
  int t=0;

  //Sending mode on, sending joystick data to processing
  int out=0;
  int out1=0;
  while(out==0){

    //We check if we read the values ​​of the Joystick where the user decided to stop (On verifie si on Lit les valeurs du Joystick ou l'utilisateur a decide d'arrete)
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
    
    //This loop prevents the overlap of several values ​​given that the frequency of sending data from the Arduino is higher than the frequency of receiving processing (Cette boucle empeche le chevauchement de plusieur valeur etant donne que la frequence d';envoi de donne de l'arduino est plus eleve que la frequence de recoit de processing)
    //We therefore wait until the data is read by processing before sending another data (On attend donc jusqu'a ce que la donnee est bien lu par processing avant d'envoyer une autre donne)
    out1=0;
    while (out1 == 0) {
      //digitalWrite(13,LOW);
      if (Serial.available() > 0) {
        String response = Serial.readStringUntil('\n'); 
        response.trim();  // Remove any leading or trailing whitespace
        
        if (response.equals("Done")) {
          out=1; //get out of the loop  //checck  andif we really get out of the loop check if it doesnt give another line of data after i wanted to start
          out1=1;
        }
        else if (response.equals("Received")) out1=1;  // Exit while loop
      }
    }
  }
  
  //tab data
  double*** tab;

  //Receive tab dimensions
  while (true) {
    if (Serial.available() > 0) {
      String receivedString = Serial.readStringUntil('\n'); // Read until newline character
      //decode data
      int rowIndex = 0;
      int colIndex = 0;
      int depthIndex = 0;

      String buffer = ""; // Buffer to hold the float string
      
      //premier element
      int i = 0;
      while(1){
        char c = receivedString.charAt(i);
        if (c == ',') {
          dimx = buffer.toInt();
          buffer = ""; // Reset buffer
        }
        else if (c == ';') {
          t = buffer.toInt();
          buffer = ""; // Reset buffer
          i++;
          break;
        }
        else {
          buffer += c; // Add character to buffer
        }
        i++;
      }

      if(t==1) digitalWrite(ledPin, LOW);

      tab = (double ***)malloc(t * sizeof(double **));
      for (int l = 0; l < t; l++) {
        tab[l] = malloc(2 * sizeof(double*)); //tableau de donne
        for (int j = 0; j < 2; j++) {
          tab[l][j] = malloc(dimx * sizeof(double));
        }
      }

      for (i; i < receivedString.length(); i++) {
        char c = receivedString.charAt(i);
        if (c == ',') {
          tab[depthIndex][rowIndex][colIndex] = buffer.toDouble();
          colIndex++;
          buffer = ""; // Reset buffer
        } else if (c == ';') {
          tab[depthIndex][rowIndex][colIndex] = buffer.toDouble();
          rowIndex++;
          colIndex = 0;
          buffer = ""; // Reset buffer
        } else if (c == '|') {
        tab[depthIndex][rowIndex][colIndex] = buffer.toDouble();
        depthIndex++;
        rowIndex = 0;
        colIndex = 0;
        buffer = ""; // Reset buffer
        } else {
          buffer += c; // Add character to buffer
        }
      }
      // Capture the last float value
      tab[depthIndex][rowIndex][colIndex] = buffer.toDouble();

      break;
    }

  }



  for (int j = 0; j < t; j++) {

      get_angles(tab[j][0][0],tab[j][1][0],L1,L2,&teta1, &teta2); //Position initiale
      servo1.write(teta1); 
      servo2.write(teta2);
      delay(1000);

      pen_control(DOWN,&penstate);
      delay(500);

    for (int i = 0; i < dimx; i++) {

      double xt = tab[j][0][i];
      double yt = tab[j][1][i];

      if(xt!=-1 && yt!=-1){
        get_angles(xt,yt,L1,L2,&teta1, &teta2);
        servo1.write(teta1); 
        servo2.write(teta2);
        delay(100);
      }
    }
    pen_control(UP,&penstate);
    delay(500);
  }

}

/* Designs a dotted line in a specific length */
void dotted_line(double *x_start, double *y_start, int length, double angle, float dot_length, float space_length) {
  float i=0;

  //control for the desired length
  while(i < length) {
    
    //get into writing position
    pen_control(DOWN_, &penstate);
    delay(100);
    straight_line(x_start,y_start,dot_length, angle);


    i=i+dot_length; //The length that should write a line
    if(i>=length) break;

    //Pen is on UP_ state
    pen_control(UP_, &penstate);
    delay(100);
    straight_line(x_start,y_start,space_length, angle);
    i = i + space_length; //adding the space that shouldn't write anything on the paper

  }
}

void setup() {
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object
  servo2.attach(10); 
  servo3.attach(11);
  
  //declarations of different button as input ports to detect actions
  pinMode(pinx,INPUT);
  pinMode(piny,INPUT);
  pinMode(pinbutton1,INPUT_PULLUP);
  pinMode(pinbutton2,INPUT);
  pinMode(pinbutton3,INPUT);
  pinMode(pinbutton4,INPUT);
  pinMode(pinbutton5,INPUT);

  //declaration of LED pin as an output port to send commands (control if it's switched on or off)
  pinMode(ledPin,OUTPUT);

  //Get into a default starting point
  get_angles(0.0,0.0,L1,L2,&teta1, &teta2);
  servo1.write(teta1); 
  servo2.write(teta2);  

  delay(1000);
  //straight_line(&x,&y,15, radians(45));

  //Put the effector in UP position and stand by
  pen_control(UP,&penstate);

  //Start serial communication
  Serial.begin(9600);
}

void loop() {  
  /* Simple implementations of existing functions for testing purposes.
  We have only one active every time. All the others has to be commented in order to observe the robot's mouvements */
  int buttonState1 = digitalRead(pinbutton5); // Read button 1 state
  int buttonState2 = digitalRead(pinbutton2); // Read button 2 state
  int buttonState3 = digitalRead(pinbutton3); // Read button 3 state
  int buttonState4 = digitalRead(pinbutton4); // Read button 4 state
  int buttonState5 = digitalRead(pinbutton1); // Joystick
  int buttonState6 = digitalRead(pinbutton6); // Read button 5 state
  int buttonState7 = digitalRead(pinbutton7); // Read button 5 state
  //square(&x,&y,5, 0);

  if (buttonState1 == 1) {
    while (digitalRead(pinbutton5)==1){}
    // Button 1 pressed, perform straight line

    //start
    digitalWrite(ledPin, HIGH);

    pen_control(UP,&penstate);
    x=0.0;
    y=0.0;
    delay(500);
    get_angles(x,y,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2);  
    delay(1000);

    pen_control(DOWN,&penstate);
    delay(500);

    //function
    straight_line(&x,&y,4, radians(90));

    //end
    pen_control(UP,&penstate);
    delay(500);
    digitalWrite(ledPin, LOW);
  } 

  if (buttonState2 == 1) {
    while (digitalRead(pinbutton2)==1){}
    // Button 1 pressed, perform straight line

    //start
    digitalWrite(ledPin, HIGH);

    pen_control(UP,&penstate);
    x=0.0;
    y=0.0;
    delay(500);
    get_angles(x,y,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2);  
    delay(1000);

    pen_control(DOWN,&penstate);
    delay(500);

    //function
    dotted_line(&x, &y, 4, radians(90), 0.5, 0.5);
    //straight_line(&x,&y,5, radians(90));

    //end
    pen_control(UP,&penstate);
    delay(500);
    digitalWrite(ledPin, LOW);
  } 

  //circle
  if (buttonState3 == 1) {
    while (digitalRead(pinbutton3)==1){}
    // Button 1 pressed, perform straight line

    //start
    digitalWrite(ledPin, HIGH);

    pen_control(UP,&penstate);
    x=1.0;
    y=1.0;

    //function
    circle(1, 1, 0, 360, 2.5, &x, &y, 0, 9);
    //straight_line(&x,&y,5, radians(90));

    //end
    pen_control(UP,&penstate);
    delay(500);
    digitalWrite(ledPin, LOW);
  } 

  //dotted circle
  if (buttonState4 == 1) {
    while (digitalRead(pinbutton4)==1){}
    // Button 1 pressed, perform straight line

    //start
    digitalWrite(ledPin, HIGH);

    pen_control(UP,&penstate);
    x=1.0;
    y=1.0;

    //function
    dotted_circle(1, 1, 10, 10, 2.5, &x, &y);

    //end
    pen_control(UP,&penstate);
    delay(500);
    digitalWrite(ledPin, LOW);
  } 

  //Joystick in processing
  if (buttonState6 == 1) {
    while (digitalRead(pinbutton6)==1){}
    digitalWrite(ledPin, HIGH);
    Joystick(&x,&y); 
    digitalWrite(ledPin, LOW);
  }

  if (buttonState7 == 1) {
    while (digitalRead(pinbutton7)==1){}
    // Button 1 pressed, perform straight line

    //start
    digitalWrite(ledPin, HIGH);

    pen_control(UP,&penstate);
    x=1.0;
    y=1.0;

    //function
    square(&x,&y,4, 0);
    //straight_line(&x,&y,5, radians(90));

    //end
    pen_control(UP,&penstate);
    delay(500);
    digitalWrite(ledPin, LOW);
  } 

  //Manual control of the robot using joystic
  if (buttonState5 == 0) {
    //Allows a smooth operation when a button is pushed (detect one time the tap)
    while (digitalRead(pinbutton1)==0){}

    digitalWrite(ledPin, HIGH);
    pen_control(UP,&penstate);
    x=0.0;
    y=0.0;
    delay(500);
    get_angles(x,y,L1,L2,&teta1, &teta2);
    servo1.write(teta1); 
    servo2.write(teta2);  
    delay(1000);

    pen_control(DOWN,&penstate);
    delay(500);

    double coef= 0.0003;
    
    while(digitalRead(pinbutton1)==1){
      //If the button is pressed then the effector is swithcing mode. For instance, if it was in writing position it goes UP and if it was UP then it gets into writing position.
      if (digitalRead(pinbutton5) == 1) {
        while (digitalRead(pinbutton5)==1){}
        pen_control(SWITCH,&penstate);
      }

      // Read analog values
      xtemp = int(512.0 - analogRead(pinx));
      ytemp = int(512.0 - analogRead(piny));

      // Apply dead zone for small movements
      if (abs(xtemp) <= 100) xtemp = 0;
      if (abs(ytemp) <= 100) ytemp = 0;

      // Update x and y coordinates
      x += xtemp * coef;
      y += ytemp * coef;

      Serial.print(x);
      Serial.print("\t");
      Serial.println(y);

      get_angles(x,y,L1,L2,&teta1, &teta2); //calculate motors' angles
      servo1.write(teta1);  //send data to the motors
      servo2.write(teta2);
      delay(10);

    }
    while (digitalRead(pinbutton1)==0){}
    digitalWrite(ledPin, LOW);
    pen_control(UP,&penstate);
    delay(500);
  }

}


