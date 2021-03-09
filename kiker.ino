
#include <Arduino.h>
#include <TM1637Display.h>


const int RED_CLK = 12;
const int RED_DIO = 11;
const int RED_DISP_POWER = 10;
const int RED_LASER_POWER = 9;
const int RED_GOAL_PIN = 8;

const int GREEN_CLK = 7;
const int GREEN_DIO = 6;
const int GREEN_DISP_POWER = 5;
const int GREEN_LASER_POWER = 4;
const int GREEN_GOAL_PIN = 3;   

const int BUZ_PIN = 2;

TM1637Display red_display(RED_CLK, RED_DIO);
TM1637Display green_display(GREEN_CLK, GREEN_DIO);

int red_score = 0;
int green_score =0;
int cur_red_state =0;
int prev_red_state = 0;
int cur_green_state = 0;
int prev_green_state = 0;

void setup() {
  //Serial.begin(9600);
  pinMode(RED_LASER_POWER, OUTPUT);
  digitalWrite(RED_LASER_POWER, HIGH);
  pinMode(RED_DISP_POWER, OUTPUT);
  digitalWrite(RED_DISP_POWER, HIGH);
  pinMode(GREEN_LASER_POWER, OUTPUT);
  digitalWrite(GREEN_LASER_POWER, HIGH);
  pinMode(GREEN_DISP_POWER, OUTPUT);
  digitalWrite(GREEN_DISP_POWER, HIGH);
  pinMode(RED_GOAL_PIN, INPUT);
  pinMode(GREEN_GOAL_PIN, INPUT);
  red_display.setBrightness(4);
  red_display.clear();
  green_display.setBrightness(7);
  green_display.clear();
}

void loop() {
  cur_red_state = digitalRead(RED_GOAL_PIN);
  //Serial.println(String("cur= ") + cur_red_state);
  if (cur_red_state == LOW) {
    if (cur_red_state != prev_red_state) {
      green_score++;
      goal();
      prev_red_state = cur_red_state;
    }
  } else {
    prev_red_state = cur_red_state;
  }
 cur_green_state = digitalRead(GREEN_GOAL_PIN);
  if (cur_green_state == LOW) {
    if (cur_green_state != prev_green_state) {
      red_score++; 
      goal();
      prev_green_state = cur_green_state;
    }
  } else {
    prev_green_state = cur_green_state;
  }
}

void goal(){
  if (red_score < 10 && green_score < 10){
    tone(BUZ_PIN, 1000, 600 );  
    red_display.showNumberDecEx(red_score*10+green_score, 0b11100000, true, 2,1);
    green_display.showNumberDecEx(green_score*10+red_score, 0b10000000, true, 2,1);
    } 
    else {
      match_end();
    }
  delay(4000);
}

void match_end(){
  if (red_score > green_score){
      red_display.showNumberDecEx(red_score*10+green_score, 0b11100000, true, 3,0);
      green_display.showNumberDecEx(green_score*100+red_score, 0b10000000, true, 3,1);
  } else {
      red_display.showNumberDecEx(red_score*100+green_score, 0b11100000, true, 3,1);
      green_display.showNumberDecEx(green_score*10+red_score, 0b10000000, true, 3,0);
  }
  
  tone(BUZ_PIN, 1000, 600 );  
  delay(1000);
  tone(BUZ_PIN, 1000, 600 );
  delay(1000);
  tone(BUZ_PIN, 1000, 1200 );
  red_score = 0;
  green_score = 0;
  delay(5000);
  red_display.clear();
  green_display.clear();
  red_display.showNumberDecEx(red_score*10+green_score, 0b11100000, true, 2,1);
  green_display.showNumberDecEx(green_score*10+red_score, 0b10000000, true, 2,1);
}
