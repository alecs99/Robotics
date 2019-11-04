const int redPin = 11; 
const int bluePin = 10; 
const int greenPin = 9; 

const int redIn = A0; 
const int greenIn =A1; 
const int blueIn = A2; 

int redVal; 
int greenVal; 
int blueVal; 

void setup() { 

} 
void loop() { 
redVal = analogRead(redIn); 
greenVal = analogRead(greenIn); 
blueVal = analogRead(blueIn); 
redVal = map(redVal, 0, 1023, 0, 255); 
greenVal = map(greenVal, 0, 1023, 0, 255); 
blueVal = map(blueVal, 0, 1023, 0, 255); 
colorControl(redVal, greenVal, blueVal);
}

int colorControl(int redVal, int greenVal, int blueVal){
  analogWrite(redPin, redVal); 
  analogWrite(greenPin, greenVal); 
  analogWrite(bluePin, blueVal);
}
