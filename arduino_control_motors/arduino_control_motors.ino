/*
 * Author: Kevin Lutzer
 * Date: Jan 28 2017
 * Description:
 *  - B000XXXX sets fwd dir
 *  - B001XXXX sets bwd dir
 *  - B010XXXX sets lft dir
 *  - B011XXXX sets rgt dir
 *  - B100XXXX sets stop moving dir
 */

#include <Servo.h>

#define MOTORR_PLUS 9
#define MOTORL_PLUS 11
#define MOTORL_NEG  6
#define MOTORR_NEG  10

#define PAN_SERVO   5
#define TILT_SERVO  3

#define PAN_TOP     130
#define PAN_BOTTOM  30
#define TILT_TOP    90
#define TILT_BOTTOM 30

/* enumerated type for direction */
enum Direction { fwd, bwd, lft, rgt, stp };

/* global vars and objects */
Servo tiltServo, panServo;
int newInstr = 0;

/* init the gpio */
void init_gpio(void){
  
  /*setup motor pins*/
  pinMode(MOTORL_PLUS, OUTPUT);
  pinMode(MOTORL_NEG, OUTPUT);
  pinMode(MOTORR_PLUS, OUTPUT);
  pinMode(MOTORR_NEG, OUTPUT);
  
  /*setup servo motors */
  panServo.attach(PAN_SERVO);
  tiltServo.attach(TILT_SERVO);
  
  return;
}

/* set direction and speed */
void set_dir( Direction dir, byte vel ){
  switch(dir){
    case fwd:{
      analogWrite(MOTORL_PLUS, vel);
      analogWrite(MOTORL_NEG, 0);
      analogWrite(MOTORR_PLUS, vel);
      analogWrite(MOTORR_NEG, 0);
      break;
    }
    case bwd:{
      analogWrite(MOTORL_PLUS, 0);
      analogWrite(MOTORL_NEG, vel);
      analogWrite(MOTORR_PLUS, 0);
      analogWrite(MOTORR_NEG, vel);
      break;
    }
    case lft:{
      analogWrite(MOTORL_PLUS, vel);
      analogWrite(MOTORL_NEG, 0);
      analogWrite(MOTORR_PLUS, 0);
      analogWrite(MOTORR_NEG, vel);
      break;
    }
    case rgt:{
      analogWrite(MOTORL_PLUS, 0);
      analogWrite(MOTORL_NEG, vel);
      analogWrite(MOTORR_PLUS, vel);
      analogWrite(MOTORR_NEG, 0);
      break;
    }
    case stp:{
      analogWrite(MOTORL_PLUS, 0);
      analogWrite(MOTORL_NEG, 0);
      analogWrite(MOTORR_PLUS, 0);
      analogWrite(MOTORR_NEG, 0);
      break;
    }
  }
  return;
}

/* sets the angular position of the gimble */
void set_servo_pos(byte pan, byte tilt){

  /* set pan angle */
  if( pan >= PAN_TOP ){
    panServo.write(PAN_TOP);
  }
  else if( pan <= PAN_BOTTOM ){
    panServo.write(PAN_BOTTOM);
  }
  else{
    panServo.write(pan);
  }

  /* set tilt angle */
  if( tilt >= TILT_TOP ){
    tiltServo.write(TILT_BOTTOM);
  }
  else if( tilt <= TILT_BOTTOM ){
    tiltServo.write(TILT_BOTTOM);
  }
  else{
    tiltServo.write(tilt);    
  }
  return;
}

/* setup function */
void setup() {
  init_gpio();  
  Serial.begin(9600);
}


/* decode instruction */
void decode_instr(byte instr){

  /* get first three bits of instructions */
  byte firstFewBits = (instr >> 5) & B111;
  byte lastFewBits = (instr) & B00011111;
  
  Serial.write(firstFewBits);

  /* B000XXXXX sets fwd */
  if( firstFewBits == 1 ){
    set_dir(fwd, map(lastFewBits, 0, 31, 0, 255));
    Serial.println("Go Forward"); 
  }
  /* B001XXXXX sets bwd*/
  else if( firstFewBits == 2 ){
    set_dir(bwd, map(lastFewBits, 0, 31, 0, 255));
    Serial.println("Go Backward");
  }
  /* B010XXXXX sets lft*/
  else if( firstFewBits == 3 ){
    set_dir(lft, map(lastFewBits, 0, 31, 0, 255));
    Serial.println("Go left");
  }
  /* B011XXXXX sets rgt*/
  else if( firstFewBits == 4 ){
    set_dir(rgt, map(lastFewBits, 0, 31, 0, 255));
    Serial.println("Go right");
  }
  /* B100XXXXX sets stp*/
  else if( firstFewBits == 5 ){
    set_dir(stp, 0);
    Serial.println("Stop");
  }
  /* if it doesn't match any of the above */
  else{
    Serial.println("Stop");
  }
  
  return;
  
}

/* loop indefinitely */
void loop() {
  /*
  set_servo_pos(30,30);
  delay(2000);
  set_dir(fwd, 255);
  delay(2000);
  set_dir(bwd, 255);
  delay(2000);
  set_dir(lft, 255);
  delay(2000);
  set_dir(rgt, 255);
  delay(2000);
  set_dir(stp, 0);
  */
  /* get new data when it is avaliable from buffer */
  if( Serial.available() > 0 ){
    
    /* get new byte */
    newInstr = Serial.read();  

    /* print value of instruction */
    Serial.write(newInstr);
    Serial.println("\n");

    /* decode instruction */
    decode_instr(newInstr);
    
    
  }
}



