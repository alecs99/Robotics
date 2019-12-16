#include "LedControl.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>
const int brightness = 2;
const int dinPin = 12;
const int clkPin = 11;
const int loadPin = 10;
const int noOfDrivers = 1;
const int pinY1 = A1;
const int pinY2 = A3;
const int RS = 13;
const int enable = 8;
const int backLight = 7;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int pinY = A1;
const int pinSW = A2;
const int pinX = A4;

bool buttonPressed = false;
bool buttonMore = false;
bool buttonOnOff = false;
bool exitSettings = false;
bool isOn = true;
bool exitHS = false;
bool exitMore = false;
bool exitPlay = false;
bool joyMovedY = false;
bool joyMovedYMore = false;
bool joyMovedYSettings = false;
bool joyMovedX = false;
bool joyMovedXContrast = false;
bool joyMovedXLight = false;
bool lvlUp = false;
int contrast = 110;
int dispState = 1;
int highScore = 0;
int scoreP1 = 0;
int scoreP2 = 0;
int startingLevel = 1;
int lvlVal = 1;
int player1Lives = 3;
int player2Lives = 3;
int level = 1;
int score = 0;
int newGame = 0;

unsigned long previousTime = 0;
unsigned long currentTime = 0;

bool finish = false;
bool inOther = false;

int movedValue = 0;
int movedValueMore = 0;
int movedValueSettings = 0;

int yValue = 0;
int yValueMore = 0;
int yValueSettings = 0;
int xValue = 0;
int xValueContrast = 110;
int xValueLight = 0;

int buttonValue = 1;
int lcdCol = 0;
int lcdRow = 1;
int lcdColMore = 0;
int lcdRowMore = 1;
int lcdColSettings = 0;
int lcdRowSettings = 1;
int lastButtonState = 1;
int buttonState = 1;

int arrowPosMenu[3][2] = {  // Position of menu selections on LCD 
   {0, 1},
   {6, 1},
   {10, 1}
};

int eeAddress = 0;
void saveHS(){   //save a new highScore value on EEPROM
  eeAddress = 0;
  EEPROM.put(eeAddress, highScore);
  eeAddress += sizeof(int);
}

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

void myMenu(){  // Main menu
  lcd.setCursor(5, 0);
  lcd.print("PONG");
  lcd.setCursor(1, 1);
  lcd.print("Play");
  lcd.setCursor(7,1);
  lcd.print("HS");
  lcd.setCursor(11,1);
  lcd.print("More");
}
void more(){   //More menu
  lcd.setCursor(5, 0);
  lcd.print("More");
  lcd.setCursor(1, 1);
  lcd.print("Settings");
  lcd.setCursor(11,1);
  lcd.print("Info");
}
void inGame(int livesP1, int livesP2, int timer, int scoreP1, int scoreP2, int level){  // Tab for in-game info
  lcd.setCursor(0, 0);
  lcd.print("P1 ");
  lcd.setCursor(3, 0);
  lcd.print("L:");
  lcd.print(livesP1);
  lcd.setCursor(7,0);
  lcd.print("S:");
  lcd.print(scoreP1);
  
  lcd.setCursor(0, 1);
  lcd.print("P2 ");
  lcd.setCursor(3, 1);
  lcd.print("L:");
  lcd.print(livesP2);
  lcd.setCursor(7,1);
  lcd.print("S:");
  lcd.print(scoreP2);
  
  lcd.setCursor(13, 0);
  lcd.print("LV");
  lcd.print(level);
  lcd.setCursor(14,1);
  lcd.print(timer);
   
}
void highMenu(int highScore){  //Tab for showing info about HighScore
  lcd.setCursor(0, 0);
  lcd.print("HighScore:");
  lcd.print(highScore);
  lcd.setCursor(0,1);
  lcd.print("Player");
}
void settingsMenu(int lvlVal, int dispState, int contrast){  //Tab for Menu
  lcd.setCursor(5, 0);
  lcd.print("Settings");
  lcd.setCursor(1, 1);
  lcd.print("Lvl:");
  lcd.print(lvlVal);
  lcd.setCursor(7,1);
  lcd.print("D:");
  lcd.print(dispState);
  lcd.setCursor(11, 1);
  lcd.print("C:");
  lcd.print(contrast);
}
void infoMenu(){  //Tab for Info about game/developer
  lcd.setCursor(0,0);
  lcd.print("Creator:Alecs");
  lcd.setCursor(0,1);
  lcd.print("PONG GAME");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("github.com/alecs");
  lcd.setCursor(0,1);
  lcd.print("99");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("@UnibucRobotics");
  delay(3000);
  lcd.clear();
}
int yValue1 = 0;
int yValue2 = 0;
bool player1Win = false;
bool player2Win = false;
bool joyMovedY1 = false;
bool joyMovedY2 = false;
bool movedPosL1 = false;
bool movedPosR1 = false;
bool movedPosL2 = false;
bool movedPosR2 = false;
int movePos1 = -1;
int movePos2 = -1;
int minThreshold = 300;
int maxThreshold = 700;

bool player1Turn = false;
bool player2Turn = false;
bool startMatch = true;
bool matchOver = false;
bool newRound = false;
bool nextRound = false;
bool roundOver = false;
bool wallHit = false;
bool point = false;


int paddleHit = 1;

LedControl lc = LedControl(dinPin, clkPin, loadPin, noOfDrivers);
 bool matrix[8][8] = {
{0, 0, 1, 1, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 1, 1, 0, 0, 0}
};
 bool animationMatrix[8][8] = {
{0, 1, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 0, 0, 0, 1},
{1, 1, 0, 1, 0, 0, 1, 1},
{0, 0, 0, 1, 0, 1, 0, 1},
{0, 0, 0, 1, 0, 1, 0, 1},
{0, 1, 1, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 0, 0, 0}
};
void idleAnimation(){   //Function to show the P G on the matrix during menu scrolling
  for( int row = 0; row < 8; row++){
    for ( int col = 0; col < 8; col++){
      lc.setLed(0, row, col, false);
      lc.setLed(0, row, col, animationMatrix[row][col]);
    }
  }
}
int paddlePos1[2] = { 2, 4};  //Saving ends of the paddles in order to move it on matrix
int paddlePos2[2] = { 2, 4};  //Saving ends of the paddles in order to move it on matrix
int ballPos [2] = { 1, 3};

void clearTable(){  // clear table from the ball
     for( int row = 0; row < 8; row++){
      for ( int col = 0; col < 8; col++){
      lc.setLed(0, row, col, false);
      }
    }
    lc.setLed(0, 0, 2, true);
    lc.setLed(0, 0, 3, true);
    lc.setLed(0, 0, 4, true);
    lc.setLed(0, 7, 2, true);
    lc.setLed(0, 7, 3, true);
    lc.setLed(0, 7, 4, true);
}
void movePaddle1(){ //Function to move paddle for player 1
   yValue1 = analogRead(pinY1);

    if( yValue1 > maxThreshold && joyMovedY1 == false){
      if(paddlePos1[0] == 0){
          movePos1 = -1;
       }
        else{
         movedPosR1 = true;
         movePos1 = paddlePos1[0]-1;
         
        }
        joyMovedY1 = true;
     }
  
      if ( yValue1 < minThreshold && joyMovedY1 == false){
          if(paddlePos1[1] == 7){
              movePos1 = -1;
          }
          else{
            movedPosL1 = true;
           movePos1 = paddlePos1[1] + 1;
          }
          joyMovedY1 = true;
       }
      if( yValue1 >= minThreshold && yValue1 <= maxThreshold){
          joyMovedY1 = false;
       }
       if(movePos1 != -1){
           if(movedPosL1 == true){
               lc.setLed(0, 0, movePos1-3, false);
               lc.setLed(0, 0, movePos1, true);
               matrix[0][movePos1] = 1;
               matrix[0][movePos1-3] = 0;
               paddlePos1[0] = movePos1-2;
               paddlePos1[1] = movePos1;
               movedPosL1 = false;
           }
           if(movedPosR1 == true){
               lc.setLed(0, 0, movePos1+3, false);
               lc.setLed(0, 0, movePos1, true);
               paddlePos1[0] = movePos1;
               paddlePos1[1] = movePos1+2;
               movedPosR1 = false;
           }
             
        }
}
void movePaddle2(){
  yValue2 = analogRead(pinY2);

    if( yValue2 > maxThreshold && joyMovedY2 == false){
      if(paddlePos2[1] == 7){
          movePos2 = -1;
       }
        else{
         movedPosR2 = true;
         movePos2 = paddlePos2[1] + 1;
        }
        joyMovedY2 = true;
     }
  
      if ( yValue2 < minThreshold && joyMovedY2 == false){
          if(paddlePos2[0] == 0){
              movePos2 = -1;
          }
          else{
            movedPosL2 = true;
            movePos2 = paddlePos2[0]-1;
          }
          joyMovedY2 = true;
       }
      if( yValue2 >= minThreshold && yValue2 <= maxThreshold){
          joyMovedY2 = false;
       }
       if(movePos2 != -1){
           if(movedPosL2 == true){
               lc.setLed(0, 7, movePos2+3, false);
               lc.setLed(0, 7, movePos2, true);
               paddlePos2[0] = movePos2;
               paddlePos2[1] = movePos2+2;
               movedPosL2 = false;
           }
           if(movedPosR2 == true){
               lc.setLed(0, 7, movePos2 - 3, false);
               lc.setLed(0, 7, movePos2, true);
               matrix[0][movePos2] = 1;
               matrix[0][movePos2 - 3] = 0;
               paddlePos2[0] = movePos2 - 2;
               paddlePos2[1] = movePos2;
               movedPosR2 = false;
           }
             
        }
  
}
void resetTable(){  // reset table
   for( int row = 0; row < 8; row++){
      for ( int col = 0; col < 8; col++){
      lc.setLed(0, row, col, false);
      }
    }
    lc.setLed(0, 0, 2, true);
    lc.setLed(0, 0, 3, true);
    lc.setLed(0, 0, 4, true);
    lc.setLed(0, 7, 2, true);
    lc.setLed(0, 7, 3, true);
    lc.setLed(0, 7, 4, true);
  nextRound = false;
  roundOver = false;
  wallHit = false;
  
}
void moveBallP1(){  //function to move the ball from player 1 to player 2
    if(paddleHit == 1 && !nextRound && !roundOver){
      lc.setLed(0, ballPos[0], ballPos[1], true);
      delay(100);
      lc.setLed(0, ballPos[0], ballPos[1], false);
      lc.setLed(0, ballPos[0]+1, ballPos[1], true);
      ballPos[0] = ballPos[0]+1;
      delay(100);
      if ( ballPos[0] + 1 == 7){
        if(ballPos[1]  == paddlePos2[0]){
          nextRound = true;
          paddleHit = 0;
        }
        else if(ballPos[1]  == paddlePos2[0]+1){
          nextRound = true;
          paddleHit = 1;
        }else if(ballPos[1]  == paddlePos2[0]+2){
          nextRound = true;
          paddleHit = 2;
          
        }
        else{
          point = true;
          lc.setLed(0, ballPos[0], ballPos[1], false);
          roundOver = true;
        }
        lc.setLed(0, ballPos[0], ballPos[1], false);
      }
    }

    if(paddleHit == 0 && !nextRound && !roundOver){
      lc.setLed(0, ballPos[0], ballPos[1], true);
      delay(100);
      if( ballPos[1] == 0){
           wallHit = true;
      }
      if(wallHit == false){
     
        lc.setLed(0, ballPos[0], ballPos[1], false);
        lc.setLed(0, ballPos[0] + 1, ballPos[1]-1, true);
        ballPos[0] = ballPos[0] + 1;
        ballPos[1] = ballPos[1] - 1;
        
        delay(100);
      }
      if(wallHit == true){
        lc.setLed(0, ballPos[0], ballPos[1], false);
        lc.setLed(0, ballPos[0] + 1, ballPos[1]+1, true);
        ballPos[0] = ballPos[0] + 1;
        ballPos[1] = ballPos[1] + 1;
        delay(100);
      }
      
      if ( ballPos[0] + 1 == 7){
        if(ballPos[1] + 1 == paddlePos2[0]){
          wallHit = false;
          nextRound = true;
          paddleHit = 0;
        }
        else if(ballPos[1] + 1 == paddlePos2[0]+1){
          wallHit = false;
          nextRound = true;
          paddleHit = 1;
        }else if(ballPos[1] + 1 == paddlePos2[0]+2){
          wallHit = false;
          nextRound = true;
          paddleHit = 2;
          
        }
        else{
          wallHit = false;
          point = true;
          lc.setLed(0, ballPos[0], ballPos[1], false);
          roundOver = true;
        }
      }
      
    }
    if( paddleHit == 2 && !nextRound && !roundOver){
       lc.setLed(0, ballPos[0], ballPos[1], true);
       delay(100);
       if( ballPos[1] == 7){
           wallHit = true;
      }
      if(wallHit == false){
        
        lc.setLed(0, ballPos[0], ballPos[1], false);
        lc.setLed(0, ballPos[0] + 1, ballPos[1]+1, true);
        ballPos[0] = ballPos[0] + 1;
        ballPos[1] = ballPos[1] + 1;
        delay(100);
      }
      if(wallHit == true){
        lc.setLed(0, ballPos[0], ballPos[1], false);
        lc.setLed(0, ballPos[0] + 1, ballPos[1]-1, true);
        ballPos[0] = ballPos[0] + 1;
        ballPos[1] = ballPos[1] - 1;
        delay(100);
      }
      
      if ( ballPos[0] + 1 == 7){
        if(ballPos[1] - 1 == paddlePos2[0]){
          wallHit = false;
          nextRound = true;
          paddleHit = 0;
        }
        else if(ballPos[1] - 1 == paddlePos2[0]+1){
          wallHit = false;
          nextRound = true;
          paddleHit = 1;
        }else if(ballPos[1] - 1 == paddlePos2[0]+2){
          wallHit = false;
          nextRound = true;
          paddleHit = 2;
          
        }
        else{
          wallHit = false;
          point = true;
          lc.setLed(0, ballPos[0], ballPos[1], false);
          roundOver = true;
        }
      }
      
    }
}
void moveBallP2(){ //function to move ball from player 2 to player 1
   if(paddleHit == 1 && !nextRound && !roundOver){
      lc.setLed(0, ballPos[0], ballPos[1], true);
      delay(100);
      lc.setLed(0, ballPos[0], ballPos[1], false);
      lc.setLed(0, ballPos[0]-1, ballPos[1], true);
      ballPos[0] = ballPos[0]-1;
      delay(100);
      if ( ballPos[0] - 1 == 0){
        Serial.println("In");
        if(ballPos[1]  == paddlePos1[0]){
             Serial.println("In 0");
          nextRound = true;
          paddleHit = 0;
        }
        else if(ballPos[1]  == paddlePos1[0]+1){
             Serial.println("In 1");
          nextRound = true;
          paddleHit = 1;
        }else if(ballPos[1]  == paddlePos1[0]+2){
          Serial.println("In 2");
          nextRound = true;
          paddleHit = 2;
          
        }
        else{
          point = true;
          lc.setLed(0, ballPos[0], ballPos[1], false);
          roundOver = true;
        }
        lc.setLed(0, ballPos[0], ballPos[1], false);
      }
    }

    if(paddleHit == 0 && !nextRound && !roundOver){
      lc.setLed(0, ballPos[0], ballPos[1], true);
      delay(100);
      if( ballPos[1] == 0){
           wallHit = true;
      }
      if(wallHit == false){
     
        lc.setLed(0, ballPos[0], ballPos[1], false);
        lc.setLed(0, ballPos[0] - 1, ballPos[1]-1, true);
        ballPos[0] = ballPos[0] - 1;
        ballPos[1] = ballPos[1] - 1;
        
        delay(100);
      }
      if(wallHit == true){
        lc.setLed(0, ballPos[0], ballPos[1], false);
        lc.setLed(0, ballPos[0] - 1, ballPos[1]+1, true);
        ballPos[0] = ballPos[0] - 1;
        ballPos[1] = ballPos[1] + 1;
        delay(100);
      }
      
      if ( ballPos[0] - 1 == 0){
        if(ballPos[1] + 1 == paddlePos1[0]){
          wallHit = false;
          nextRound = true;
          paddleHit = 0;
        }
        else if(ballPos[1] + 1 == paddlePos1[0]+1){
          wallHit = false;
          nextRound = true;
          paddleHit = 1;
        }else if(ballPos[1] + 1 == paddlePos1[0]+2){
          wallHit = false;
          nextRound = true;
          paddleHit = 2;
          
        }
        else{
          wallHit = false;
          point = true;
          lc.setLed(0, ballPos[0], ballPos[1], false);
          roundOver = true;
        }
      }
      
    }
    if( paddleHit == 2 && !nextRound && !roundOver){
       lc.setLed(0, ballPos[0], ballPos[1], true);
       delay(100);
       if( ballPos[1] == 7){
           wallHit = true;
      }
      if(wallHit == false){
        
        lc.setLed(0, ballPos[0], ballPos[1], false);
        lc.setLed(0, ballPos[0] - 1, ballPos[1]+1, true);
        ballPos[0] = ballPos[0] - 1;
        ballPos[1] = ballPos[1] + 1;
        delay(100);
      }
      if(wallHit == true){
        lc.setLed(0, ballPos[0], ballPos[1], false);
        lc.setLed(0, ballPos[0] - 1, ballPos[1]-1, true);
        ballPos[0] = ballPos[0] - 1;
        ballPos[1] = ballPos[1] - 1;
        delay(100);
      }
      
      if ( ballPos[0] - 1 == 0){
        if(ballPos[1] - 1 == paddlePos1[0]){
          wallHit = false;
          nextRound = true;
          paddleHit = 0;
        }
        else if(ballPos[1] - 1 == paddlePos1[0]+1){
          wallHit = false;
          nextRound = true;
          paddleHit = 1;
        }else if(ballPos[1] - 1 == paddlePos1[0]+2){
          wallHit = false;
          nextRound = true;
          paddleHit = 2;
          
        }
        else{
          wallHit = false;
          point = true;
          lc.setLed(0, ballPos[0], ballPos[1], false);
          roundOver = true;
        }
      }
      
    }
  
}

void roundManager(int startMatch, bool &p1Win, bool &p2Win){  //manages every round if a player gets/loose a point or the ball hit the paddle and move on
   p1Win = false;
   p2Win = false;
   movePaddle1();
   movePaddle2();
  if(startMatch){
    startMatch = false;
    resetTable();
    lc.setLed(0, ballPos[0], ballPos[1], false);
    ballPos[0] = 1;
    ballPos[1] = 3;
    paddleHit = 1;
    player1Win = false;
    player2Win = false;
  }
  if(ballPos[0] == 0 || ballPos[0] == 1){
    player1Turn = true;
  }
  movePaddle1();
  movePaddle2();
  if(player1Turn){
     moveBallP1();
     if(nextRound){
      nextRound = false;
      player1Turn = false;
      player2Turn = true;
    }
  }
  movePaddle1();
  movePaddle2();
  if(ballPos[0] == 6 || ballPos[0] == 7){
    player2Turn = true;
  }
  movePaddle1();
  movePaddle2();
  if(player2Turn){
    moveBallP2();
     if(nextRound){
      nextRound = false;
      player1Turn = true;
      player2Turn = false;
    }
  }
  movePaddle1();
  movePaddle2();
  if(roundOver){
    roundOver = false;
    newRound = true;
    lc.setLed(0, ballPos[0], ballPos[1], false);
    
    if(ballPos[0] == 6){
       player1Win = true;
    }
    else{
      player2Win = true;
    }
     
  }
  movePaddle1();
  movePaddle2();
  if(player2Win == true){
    p2Win = true;
    lc.setLed(0, ballPos[0], ballPos[1], false);
    player2Win = false;
    ballPos[0] = 1;
    ballPos[1] = 3;
  }
  else if(player1Win == true){
      p1Win = true;
      lc.setLed(0, ballPos[0], ballPos[1], false);
      player1Win = false;
      ballPos[0] = 6;
      ballPos[1] = 3;
  }
  movePaddle1();
  movePaddle2();
  if(newRound){
    clearTable();
    roundOver = false;
    newRound = false;
    nextRound = false;
    player1Turn = false;
    player2Turn = false;
    lc.setLed(0, ballPos[0], ballPos[1], true);
    paddleHit = 1;
    paddlePos1[0] = 2;
    paddlePos1[1] = 4;
    paddlePos2[0] = 2;
    paddlePos2[1] = 4;
  }
  movePaddle1();
  movePaddle2();
}
void buttonRead(bool &buttonPressed){
   buttonValue = digitalRead(pinSW);
  if(buttonValue == LOW && buttonPressed == false) {
     buttonPressed = true;
  }
  else 
    if (buttonValue == LOW) {
      buttonPressed = false;
    }
  }
void lcdLight(bool &buttonPressed){
   buttonValue = digitalRead(pinSW);
  if(buttonValue == LOW && buttonPressed == false) {
     buttonPressed = true;
  }
  else 
    if (buttonValue == LOW) {
      buttonPressed = false;
    }
  }

void gameManager(int noOfLives, int multiplier, int &scoreP1, int &scoreP2, int bonus, int level, int &newGame){  //sets the score and decide if the game is over
    bool p1Win = false;
    bool p2Win = false;
    int start = true;
    player1Lives = noOfLives; //sets lives for the players
    player2Lives = noOfLives;
    previousTime = currentTime;
    inGame(player1Lives, player2Lives, currentTime, scoreP1, scoreP2, level);   //prints on the LCD info 
    roundManager(true, p1Win, p2Win);  //starts the game for the first time
    while((player1Lives >= 0) && (player2Lives >= 0) && (currentTime - previousTime < 60)){   // while there are lives and time
      inGame(player1Lives, player2Lives, currentTime-previousTime, scoreP1, scoreP2, level);  //refresh the info on the LCD
      currentTime = millis()/1000;  //get time
      roundManager(false, p1Win, p2Win);
      if(p1Win){
        player2Lives--;
        scoreP1 = scoreP1 + multiplier;
      }
      
      else if(p2Win){
           player1Lives--;
           scoreP2 = scoreP2 + multiplier;
      }
    }
    if(player1Lives < 0){
      scoreP2 = scoreP2 + player2Lives * bonus;
    }
    else if(player2Lives < 0){
         scoreP1 = scoreP1 +player1Lives * bonus;
    }
    previousTime = currentTime;
    newGame = 0;
      
    
  }
  
   
  

void lcdMenu(){
 buttonRead(buttonPressed);
 Serial.println(buttonPressed);
 if(buttonPressed == false){
  idleAnimation();
  newGame = 1;
  myMenu();
  delay(100);
  lcd.clear();
  lcd.setCursor(lcdCol,lcdRow);
  lcd.print(">");
  yValue = analogRead(pinY);
  if( yValue > maxThreshold && joyMovedY == false){
      if(movedValue < 2){
          movedValue++;
       }
        else{
         movedValue = 0;
        }
        joyMovedY = true;
     }
  
   if ( yValue < minThreshold && joyMovedY == false){
       if(movedValue > 0){
         movedValue--;
        }
        else{
         movedValue = 2;
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
      if(movedValue == 0){
        if(newGame == 1){
          if(lvlVal == 1){
            gameManager(3, 1, scoreP1, scoreP2, 1, 1, newGame);
          }
          if(lvlVal == 2){
            gameManager(2, 2, scoreP1, scoreP2, 3, 2, newGame);
          }
          if(lvlVal == 3){
            gameManager(1, 5, scoreP1, scoreP2, 4, 3, newGame);
          }
        }
        if (newGame == 0){
          
         if(scoreP1 > scoreP2){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Player 1 win!");
          lcd.setCursor(0,1);
          lcd.print("Score P1");
          lcd.setCursor(9,1);
          lcd.print(scoreP1);
          lcd.setCursor(11,1);
          lcd.print("P2");
          lcd.setCursor(14,1);
          lcd.print(scoreP2);
          buttonPressed = false;
          delay(5000);
          eeAddress = 0;
          EEPROM.get(eeAddress, highScore);
          if(scoreP1 > highScore){
            highScore = scoreP1;
            saveHS();
           }
           scoreP1 = 0;
           scoreP2 = 0;
         }
       
        else if (scoreP2 > scoreP1){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Player 2 win!");
              lcd.setCursor(0,1);
              lcd.print("Score P1");
              lcd.setCursor(9,1);
              lcd.print(scoreP1);
              lcd.setCursor(11,1);
              lcd.print("P2");
              lcd.setCursor(14,1);
              lcd.print(scoreP2);
              buttonPressed = false;
              delay(5000);
              eeAddress = 0;
              EEPROM.get(eeAddress, highScore);
              if(scoreP2 > highScore){
                highScore = scoreP2;
                saveHS();
              }
             scoreP1 = 0;
             scoreP2 = 0;
        }
      }
      }
       if(movedValue == 1){
           eeAddress = 0;
           EEPROM.get(eeAddress, highScore);
           lcd.clear();
           highMenu(highScore);
           delay(100);
       }
       if(movedValue == 2){
          more();
          delay(100);
          lcd.clear();
          lcd.setCursor(lcdColMore,lcdRowMore);
          lcd.print(">");
          yValueMore = analogRead(pinY);
          if( yValueMore > maxThreshold && joyMovedYMore == false){
              if(movedValueMore > 0){
                  movedValueMore-2;
               }
                else{
                 movedValueMore = 2;
                }
                joyMovedYMore = true;
             }
          
           if ( yValueMore < minThreshold && joyMovedYMore == false){
               if(movedValueMore < 1){
                 movedValueMore+2;
                }
                else{
                 movedValueMore = 0;
                }
               joyMovedYMore = true;
             }
             if( yValueMore >= minThreshold && yValueMore <= maxThreshold){
              joyMovedYMore = false;
             }
            lcdColMore = arrowPosMenu[movedValueMore][0];
            lcdRowMore = arrowPosMenu[movedValueMore][1];
            buttonRead(buttonMore);
            
            while(buttonMore){
              if(movedValueMore == 0){
                settingsMenu(lvlVal, isOn, contrast);
                delay(150);
                lcd.clear();
                lcd.setCursor(lcdColSettings,lcdRowSettings);
                lcd.print(">");
                yValueSettings = analogRead(pinY);
                if( yValueSettings > maxThreshold && joyMovedYSettings == false){
                      if(movedValueSettings > 0){
                          movedValueSettings--;
                       }
                        else{
                         movedValueSettings = 2;
                        }
                        joyMovedYSettings = true;
                     }
                  
                 if ( yValueSettings < minThreshold && joyMovedYSettings == false){
                       if(movedValueSettings < 2){
                         movedValueSettings++;
                        }
                        else{
                         movedValueSettings = 0;
                        }
                       joyMovedYSettings = true;
                     }
                     if( yValueSettings >= minThreshold && yValueSettings <= maxThreshold){
                      joyMovedYSettings = false;
                     }
                    lcdColSettings = arrowPosMenu[movedValueSettings][0];
                    lcdRowSettings = arrowPosMenu[movedValueSettings][1];
                    if(movedValueSettings == 0){
                       xValue = analogRead(pinX);
                       if( xValue < minThreshold && joyMovedX == false){       
                          if(lvlVal > 1){
                                   lvlVal--;
                                 }
                                 else{
                                  lvlVal = 3;
                                 }
                                 joyMovedX = true;
                              }
                              if ( xValue > maxThreshold && joyMovedX == false){
                                if(lvlVal < 3){
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
                         else if(movedValueSettings == 1){
                               xValueLight = analogRead(pinX);
                               if( xValueLight < minThreshold && joyMovedXLight == false){       
                                  if(dispState == 1)
                                      dispState = 0;
                                         joyMovedXLight = true;
                                   }
                                      if ( xValueLight > maxThreshold && joyMovedXLight == false){
                                        if(dispState == 0)
                                           dispState = 1;
                                         joyMovedX = true;
                                      }
                                      if( xValueLight >= minThreshold && xValueLight <= maxThreshold){
                                        joyMovedXLight = false;
                                      }
                                      if(dispState == 1){
                                        digitalWrite(backLight, LOW);
                                      } else{
                                        digitalWrite(backLight, HIGH);
                                      }
                                      
                         }
                                                 
                         
                         else if(movedValueSettings == 2){
                              xValueContrast = analogRead(pinX);
                               if( xValueContrast < minThreshold && joyMovedXContrast == false){       
                                  if(lvlVal > 1){
                                           contrast--;
                                         }
                                         else{
                                          contrast = 150;
                                         }
                                         joyMovedXContrast = true;
                                      }
                                      if ( xValueContrast > maxThreshold && joyMovedXContrast == false){
                                        if(contrast < 150){
                                           contrast++;
                                         }
                                         else{
                                          contrast = 1;
                                         }
                                         joyMovedXContrast = true;
                                      }
                                      if( xValueContrast >= minThreshold && xValueContrast <= maxThreshold){
                                        joyMovedXContrast = false;
                                      }
                                      analogWrite(6, contrast);
                                      
                       }
              } else if(movedValueMore == 2){
                    lcd.clear();
                    infoMenu();
                    buttonPressed = false;
              }
             
              buttonRead(exitSettings);
              if(exitSettings){
                buttonMore = false;
              }
            }
       }   
     } 
}
           

void setup() {

  lc.shutdown(0,false); 
  lc.setIntensity(0, brightness); 
  lc.clearDisplay(0); 
  for( int row = 0; row < 8; row++){
    for ( int col = 0; col < 8; col++){
      lc.setLed(0, row, col, matrix[row][col]);
    }
  }
  lcd.begin(16, 2);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, LOW);
  pinMode(pinSW, INPUT_PULLUP);
  analogWrite(6, contrast);
  Serial.begin(9600);
}

void loop() {
    lcdMenu();  
}
