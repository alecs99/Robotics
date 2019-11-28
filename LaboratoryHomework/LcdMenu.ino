#include <LiquidCrystal.h>
int highScore = 0;

const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int pinY = A0;
const int pinSW = A1;
const int pinX = A2;

bool buttonPressed = false;
bool joyMovedY = false;
bool joyMovedX = false;
bool lvlUp = false;
int startingLevel = 1;
int lvlVal = 1;
int lives = 3;
int level = 1;
int score = 0;
int newGame = 0;

unsigned long previousTime = 0;
unsigned long currentTime = 0;

bool finish = false;
bool inOther = false;

int movedValue = 0;
int minThreshold = 400;
int maxThreshold = 600;

int yValue = 0;
int xValue = 0;

int buttonValue = 1;
int lcdCol = 0;
int lcdRow = 0;
int lastButtonState = 1;
int buttonState = 1;

int arrowPosMenu[3][2] = {
   {0, 0},
   {0, 1},
   {6, 0}
};

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);
void setup() {
lcd.begin(16, 2);
pinMode(pinSW, INPUT_PULLUP);
Serial.begin(9600);
}
void loop() {
 buttonValue = digitalRead(pinSW);
 if(buttonValue == 0 && buttonPressed == false){
  delay(50);
  buttonValue = digitalRead(pinSW);
  if(buttonValue == 1){
     buttonPressed = true;
  }
 }else if(buttonValue == 0){
         delay(50);
         buttonValue = digitalRead(pinSW);
         if(buttonValue == 1){
            buttonPressed = false;
            lcd.clear();
            previousTime = currentTime;
            newGame = 0;
         }     
 }
 if(buttonPressed == false){
  myMenu();
  delay(100);
  lcd.clear();
  lcd.setCursor(lcdCol,lcdRow);
  lcd.print(">");
  yValue = analogRead(pinY);
  yValue = analogRead(pinY);
  if( yValue > maxThreshold && joyMovedY == false){
      if(movedValue > 0){
          movedValue--;
       }
        else{
         movedValue = 2;
        }
        joyMovedY = true;
     }
  
   if ( yValue < minThreshold && joyMovedY == false){
       if(movedValue < 2){
         movedValue++;
        }
        else{
         movedValue = 0;
        }
       joyMovedY = true;
     }
     if( yValue >= minThreshold && yValue <= maxThreshold){
      joyMovedY = false;
     }

  lcdCol = arrowPosMenu[movedValue][0];
  lcdRow = arrowPosMenu[movedValue][1];
 }
 else if(buttonPressed == true){
      if(movedValue == 0 && newGame == 0){
        if(currentTime - previousTime == 0){
          level = startingLevel;
          score = 0;
          previousTime = currentTime;
        }
        inGame(lives, level, score);
        delay(1000);
        currentTime = millis()/1000;
        if(currentTime - previousTime == 5){
            level = level+1;
            score = score + level * 3;
        }
        if(currentTime - previousTime == 10){
          lcd.clear();
          lcd.print("Congrats you win Press to exit");
          if(score > highScore){
            highScore = score;
          }
          previousTime = currentTime;
          newGame = 1;
        } 
      }
       if(movedValue == 2){
           highMenu(highScore);
       }
       if(movedValue == 1){
          settingsMenu(startingLevel);
           xValue = analogRead(pinX);
           if( xValue < minThreshold && joyMovedX == false){       
              if(lvlVal > 1){
                 lvlVal--;
               }
               else{
                lvlVal = 4;
               }
               joyMovedX = true;
            }
            if ( xValue > maxThreshold && joyMovedX == false){
              if(lvlVal < 4){
                 lvlVal++;
               }
               else{
                lvlVal = 1;
               }
               joyMovedX = true;
            }
            if( xValue >= minThreshold && xValue <= maxThreshold){
              joyMovedX = false;
            }
            startingLevel = lvlVal;
       }
 }
}
void myMenu(){
  lcd.setCursor(1, 0);
  lcd.print("Play");
  lcd.setCursor(7, 0);
  lcd.print("HighScore");
  lcd.setCursor(1,1);
  lcd.print("Settings");
}

void inGame(int lives, int level, int score){
  lcd.setCursor(0, 0);
  lcd.print("Lives:");
  lcd.print(lives);
  lcd.setCursor(9, 0);
  lcd.print("Level:");
  lcd.print(level);
  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.print(score);
   
}
void highMenu(int highScore){
  lcd.setCursor(0, 0);
  lcd.print("HighScore:");
  lcd.print(highScore);
  lcd.setCursor(0,1);
  lcd.print("Player");
}
void settingsMenu(int value){
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.print(value);
  lcd.setCursor(0,1);
  lcd.print("Push to exit!");
}
