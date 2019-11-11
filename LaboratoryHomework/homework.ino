const int speakerPin = A0;
const int pushButton = 2;
const int buzzerPin = 11;
int speakerValue = 0;
int buttonState = 0;
const int threshold = 355;
void setup() {
pinMode(speakerPin, INPUT);
Serial.begin(9600);
}
void loop() {
  speakerValue = analogRead(speakerPin);
  if (speakerValue > 345)
   Serial.println(speakerValue);
  if (speakerValue > threshold) {
     Serial.println("Knock");
     tone(11, 500);
     
  }
  buttonState = digitalRead(pushButton);
  if(buttonState == 1){
      noTone(11);
     }
  delay(10);

}
