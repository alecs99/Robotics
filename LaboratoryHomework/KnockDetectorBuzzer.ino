const int speakerPin = A0;
const int pushButton = 2;

int speakerValue = 0;
int buttonState = 0;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long interval = 5000;
unsigned triggered = 0;

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
     triggered = 1;
  }
  
  currentMillis = millis();
  
  if ((currentMillis - previousMillis >= interval) && triggered){
     tone(11,500);
     previousMillis = currentMillis;
  }
  
  buttonState = digitalRead(pushButton);
  if(buttonState == 1){
      noTone(11);
      triggered = 0;
     }
  delay(10);

}
