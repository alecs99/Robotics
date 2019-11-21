const int pinSW = A2; 
const int pinX = A0; 
const int pinY = A1;

const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;
const int segSize = 8;
const int noOfDisplays = 4;
const int noOfDigits = 10;

int xValue = 0;
int yValue = 0;

bool buttonPressed = false;
bool joyMovedY = false;
bool joyMovedX = false;
bool chosen = false;
int digit = 0;
int buttonValue = 0;
int selectedSegment = 0;
int previousSegment = 0;
int minThreshold= 400;
int maxThreshold= 600;

byte digitMatrix[noOfDigits][segSize-1] = {
//a b  c  d  e  f  g
{1, 1, 1, 1, 1, 1, 0}, // 0
{0, 1, 1, 0, 0, 0, 0}, // 1
{1, 1, 0, 1, 1, 0, 1}, // 2
{1, 1, 1, 1, 0, 0, 1}, // 3
{0, 1, 1, 0, 0, 1, 1}, // 4
{1, 0, 1, 1, 0, 1, 1}, // 5
{1, 0, 1, 1, 1, 1, 1}, // 6
{1, 1, 1, 0, 0, 0, 0}, // 7
{1, 1, 1, 1, 1, 1, 1}, // 8
{1, 1, 1, 1, 0, 1, 1} // 9
};

int values[noOfDisplays] = {
  0, 0, 0, 0
};
int segments[segSize] = {
 pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

int digits[noOfDisplays] = {
pinD1, pinD2, pinD3, pinD4
};

void displayNumber(byte digit) {
  for (int i = 0; i < segSize - 1; i++) {
      digitalWrite(segments[i], digitMatrix[digit][i]);
  }
}

void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num],LOW);
}

void displayDP(byte decimalPoint){
  digitalWrite(segments[segSize-1], decimalPoint);
}

void clearSeg(){
   for (int i = 0; i < segSize; i++) {
      digitalWrite(segments[i], 0);
  }
}

void setup() {
  pinMode(pinSW, INPUT_PULLUP);
  for (int i = 0; i < segSize; i++){
      pinMode(segments[i], OUTPUT);
  }
  
  for (int i = 0; i < noOfDisplays; i++){
      pinMode(digits[i], OUTPUT);
  }
  
  Serial.begin(9600);

}

void loop() {
   buttonValue = digitalRead(pinSW);
   if(buttonValue == 0 && buttonPressed == false){
         buttonPressed = true;
         showDigit(selectedSegment);
         displayDP(LOW);
      }else if(buttonValue == 0){
             buttonPressed = false;
             showDigit(selectedSegment);
             clearSeg();
             displayDP(HIGH);
        }
    if (buttonPressed == false){
      xValue = analogRead(pinX);
      if( xValue < minThreshold && joyMovedX == false){       
        if(selectedSegment > 0){
           selectedSegment--;
         }
         else{
          selectedSegment = 3;
         }
         joyMovedX = true;
      }
      if ( xValue > maxThreshold && joyMovedX == false){
        if(selectedSegment < 3){
           selectedSegment++;
         }
         else{
          selectedSegment = 0;
         }
         joyMovedX = true;
      }
      if( xValue >= minThreshold && xValue <= maxThreshold){
        joyMovedX = false;
      }
      digit = values[selectedSegment];  
      showDigit(selectedSegment);
      displayDP(HIGH);
    }else{
      yValue = analogRead(pinY);
      if( yValue > maxThreshold && joyMovedY == false){
        if(digit > 0){
          digit--;
        }
        else{
         digit = 9;
        }
        joyMovedY = true;
     }
  
     if ( yValue < minThreshold && joyMovedY == false){
       if(digit < 9){
         digit++;
        }
        else{
         digit = 0;
        }
       joyMovedY = true;
     }
     if( yValue >= minThreshold && yValue <= maxThreshold){
      joyMovedY = false;
     }
     values[selectedSegment] = digit;
     showDigit(selectedSegment);
     displayNumber(values[selectedSegment]);
    }
}
