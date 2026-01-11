int redLED = 2;
int yellowLED = 3;
int greenLED = 4;
int buttonPin = 5;
int segmentPins[7] = {6, 7, 8, 9, 10, 11, 12}; // A-G
bool p = false;

byte numbers[10][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}  //9
};

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buttonPin, INPUT);
  for (int i = 0; i < 7; i++) pinMode(segmentPins[i], OUTPUT);
  showDigit(0);
}

void loop() {
  // RED
  digitalWrite(redLED, HIGH);
  unsigned long start = millis();
  while (millis() - start < 3000) {
    if (digitalRead(buttonPin) == HIGH) {
      p = true;  
    }
  }
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, HIGH);
  start = millis();
  while (millis() - start < 1000) {
    if (digitalRead(buttonPin) == HIGH) {
      p = true;
    }
  }
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, HIGH);
  if (p) {
    countdown();  
    p = false; 
  } else {
    start = millis();
    showDigit(0);
    while (millis() - start < 3000) {
      if (digitalRead(buttonPin) == HIGH) {
        countdown();
      }
    }
  }
  digitalWrite(greenLED, LOW);
  showDigit(0); 
}

void countdown() {
  int i = 9;
  unsigned long s = millis();
  while (i >= 0) {
    if (millis() - s >= 1000) {
      showDigit(i);
      i--;
      s = millis(); 
    }
    if (digitalRead(buttonPin) == HIGH) {
      p = true; 
    }
  }
}
void showDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[num][i] ? HIGH : LOW);
  }
}
