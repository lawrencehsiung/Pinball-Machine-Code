#include <Servo.h>
#include "pitches.h"


Servo servo;
int servopos = 0;
int servotime = 0;


int SER = 2;  //SER
int RCLK = 3;
int SRCLK = 4;

int gameover = 13;

int irdetect1 = 0;
int irdetect2 = 2;

int knock1 = 8;
int knock2 = 9;

int digit1 = 12; //ones
int digit2 = 11; // tens
int digit3 = 10; //hunneds
int digit4 = 9; //thous

int score = 0;

byte numbers[10] {B00000011,B10011111, B00100101, B00001101, B10011001, B01001001, B01000001, B00011111,B00000001, B00001001};

//sounds //////////////////////////////////////////
int melody[] = {
  NOTE_E6, NOTE_D6, NOTE_FS5, NOTE_GS5, NOTE_CS6, NOTE_B5, NOTE_D5, NOTE_E5, NOTE_B5, NOTE_A5, NOTE_CS5, NOTE_E5, NOTE_A5
}; //NOKIA
int noteDurations[] = {
  8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4
};

void setup() {
  Serial.begin(9600);

  pinMode(SRCLK,OUTPUT);
  pinMode(SER,OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);



  pinMode(gameover, INPUT);
  pinMode(knock1, INPUT);
  pinMode(knock2, INPUT);
  //pinMode(irdetect, INPUT);

  servo.attach(5);
}

void loop() {
  //digitalWrite(gameover, LOW);
  Serial.print(analogRead(knock2));
  Serial.print('\n');
  //delay(1000);
  

if(analogRead(gameover)>900){
  score = 0;
  for (int thisNote = 0; thisNote < 13; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(8, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(13);
    }
  Serial.print("gameover");
  delay(1000);
}

  
if(servotime > 100){
  servopos = random(1,179);
  servo.write(servopos); 
  delay(15);
  servotime = 0;
}
  else{
    servotime++;
  }


  //Serial.print(analogRead(irdetect));
  //Serial.print('\n');



  if(score>9999){
    score = 0;
    
  }
  if(analogRead(irdetect1) >370){
    score++;
    displayup(score);
    tone(8, 1760, 50);
    tone(8,1976, 100);
    //Serial.print("score");
    //Serial.print('\n');
    //delay(50);
  }
    else if(analogRead(irdetect2) > 370){
    score = score + 5;
    tone(8, 1760, 50);
    tone(8,1568, 100);
    displayup(score);
  }
    else if(analogRead(knock1) >100){
      score = score + 10 ;
      tone(8, 1568, 50);
      displayup(score);
      //delay(500);
    }
       else if(analogRead(knock2) >100){
      score = score + 10 ;
       tone(8, 1568, 50);
      displayup(score);
      //delay(500);
    }
    
  else{
    displayup(score);
    //delay(50);
  }
 

      
}

void displayup(int score) {
  int score1000 = score / 1000;
  int score100 = (score - (score1000*1000)) / 100;
  int score10 = (score - (score1000*1000) - (score100*100)) / 10;
  int score1 = (score - (score1000*1000) - (score100*100) - (score10*10));
  

  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);

        //for(int t = 0; t < 3; t++){        // adjust t< whatever for time 10ms * t times = display time  // SENSITIVITY OF SENSOR

          
          digitalWrite(digit1, LOW);
          digitalWrite(digit2, HIGH);
          digitalWrite(digit3, HIGH);
          digitalWrite(digit4, HIGH);
          digitalWrite(RCLK, LOW);
          shiftOut(SER, SRCLK, LSBFIRST, numbers[score1]);   
          digitalWrite(RCLK, HIGH);
          delay(5);
          //Serial.print(score1);

          
          digitalWrite(digit1, HIGH);
          digitalWrite(digit2, LOW);
          digitalWrite(digit3, HIGH);
          digitalWrite(digit4, HIGH);
          digitalWrite(RCLK, LOW);
          //Serial.print(score10);
          shiftOut(SER, SRCLK, LSBFIRST, numbers[score10]);   
          digitalWrite(RCLK, HIGH);
          delay(5);
         
 
          digitalWrite(digit1, HIGH);
          digitalWrite(digit2, HIGH);
          digitalWrite(digit3, LOW);
          digitalWrite(digit4, HIGH);
          digitalWrite(RCLK, LOW);
          //Serial.print(score100);
          shiftOut(SER, SRCLK, LSBFIRST, numbers[score100]);   
          digitalWrite(RCLK, HIGH);
          delay(5);
         
          digitalWrite(digit1, HIGH);
          digitalWrite(digit2, HIGH);
          digitalWrite(digit3, HIGH);
          digitalWrite(digit4, LOW);
          digitalWrite(RCLK, LOW);
          //Serial.print(score1000);
          shiftOut(SER, SRCLK, LSBFIRST, numbers[score1000]);   
          digitalWrite(RCLK, HIGH);
          delay(5);       
     //}
        return;       
    
//  }
}

