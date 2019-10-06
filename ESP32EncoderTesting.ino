enum {
  switchPin = 5,
  encoderDtPin = 18,
  encoderClkPin = 19,
  ledRedPin = 21,
  ledGreenPin = 22,
  ledBluePin = 23,
  ledBuiltinPin = LED_BUILTIN,

  switchToggleDebounceMillis = 20,
  encoderDebounceMillis = 1,
};

const short int EncoderArray[4][4] =
  {{ 0, 1,-1, 0 },
   {-1, 0, 0, 1 },
   { 1, 0, 0,-1 },
   { 0,-1, 1, 0 }};

volatile bool changeFlag = false;
volatile byte encoderPreviousValue = 0;
byte encoderCount = 0;
volatile unsigned int encoderOldMillis = 0;
volatile bool switchToggleValue = false;
volatile unsigned int switchToggleOldMillis = 0;

//typedef struct {
//  byte value;
//  byte count;
//} bufferItem;
volatile byte circularQueue[100] = {0};
volatile byte head = 0; // Index of next empty byte in circular queue
volatile byte tail = 0; // Index of oldest item in circular queue
volatile bool error = false;

volatile bool dtState;
volatile bool clkState;

void IRAM_ATTR SwitchChangeIsr() {
  if (digitalRead(switchPin) == LOW
      && millis() - switchToggleOldMillis > switchToggleDebounceMillis)
  {
    switchToggleValue = !switchToggleValue;
    switchToggleOldMillis = millis();
  }
}

//void IRAM_ATTR dtRaiseIsr() {
//  dtState = 0b10;
//  circularQueue[head] = (dtState + clkState);
//  head++;
//  if(head == 100) { head = 0; }
//}
//
//void IRAM_ATTR dtFallIsr() {
//  dtState = 0b00;
//  circularQueue[head] = (dtState + clkState);
//  head++;
//  if(head == 100) { head = 0; }
//}
//
//void IRAM_ATTR clkRaiseIsr() {
//  clkState = 0b01;
//  circularQueue[head] = (dtState + clkState);
//  head++;
//  if(head == 100) { head = 0; }
//}
//
//void IRAM_ATTR clkFallIsr() {
//  clkState = 0b00;
//  circularQueue[head] = (dtState + clkState);
//  head++;
//  if(head == 100) { head = 0; }
//}

void IRAM_ATTR EncoderChangeIsr() {
//  if (millis() - encoderOldMillis < encoderDebounceMillis) {
//    return;
//  }

//  if(head + 1 == tail) {
//    error = true;
//  }
//  

  byte encoderValue = (digitalRead(encoderDtPin) << 1) + digitalRead(encoderClkPin);
//  if (encoderValue == encoderPreviousValue) {
//    return;
//  }
  
  circularQueue[head] = encoderValue;
  head++;
  if(head == 100) { head = 0; }
//
//  encoderPreviousValue = encoderValue;
  
//  byte encoderValue = digitalRead(encoderDtPin) << 1 + digitalRead(encoderClkPin);
//  if (encoderValue == 0b00) {
//    if (encoderPreviousValue == 0b01) {
//      encoderCount++;
//    } else {
//      encoderCount--;
//    }
//  } else if (encoderValue == 0b11) {
//    if (encoderPreviousValue == 0b10) {
//      encoderCount++;
//    } else {
//      encoderCount--;
//    }
//  }
//  circularQueue[head].count = encoderCount;
//
//  encoderPreviousValue = encoderValue;
//  encoderOldMillis = millis();
}

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(encoderDtPin, INPUT);
  pinMode(encoderClkPin, INPUT);

  dtState = digitalRead(encoderDtPin);
  clkState = digitalRead(encoderClkPin);
  
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(ledBuiltinPin, OUTPUT);

  switchToggleOldMillis = millis();
  encoderOldMillis = millis();
  encoderPreviousValue = digitalRead(encoderDtPin) << 1 + digitalRead(encoderClkPin);

  attachInterrupt(switchPin, SwitchChangeIsr, CHANGE);
  attachInterrupt(encoderDtPin, EncoderChangeIsr, CHANGE);
  attachInterrupt(encoderClkPin, EncoderChangeIsr, CHANGE);

//  attachInterrupt(encoderDtPin, dtRaiseIsr, RISING);
//  attachInterrupt(encoderDtPin, dtFallIsr, FALLING);
//  attachInterrupt(encoderClkPin, clkRaiseIsr, RISING);
//  attachInterrupt(encoderClkPin, clkFallIsr, FALLING);

  Serial.begin(115200);
}

void loop() {
  if(error) {
    Serial.println("error");
  }

  while(tail != head) {
//    Serial.print(circularQueue[tail].count);
//    Serial.print("   ");
//    Serial.print(circularQueue[tail].value & 0b10 >> 1);
//    Serial.print(circularQueue[tail].value & 0b01);
//    Serial.println();
//    Serial.println(circularQueue[tail], BIN);

    short unsigned int encoderValue = circularQueue[tail];
    encoderCount += EncoderArray[encoderPreviousValue][encoderValue];
    encoderPreviousValue = encoderValue;
    tail++;
    if(tail == 100) { tail = 0; }
  }

  Serial.println(encoderCount);
  delay(50);
//  Serial.print(encoderCount);
//  Serial.print("    ");
//  Serial.println(switchToggleValue);
//
//  digitalWrite(ledBuiltinPin, switchToggleValue);
//
//  switch(encoderCount % 3) {
//    case 0:
//      digitalWrite(ledRedPin, HIGH);
//      digitalWrite(ledGreenPin, LOW);
//      digitalWrite(ledBluePin, LOW);
//      break;
//    case 1:
//      digitalWrite(ledRedPin, LOW);
//      digitalWrite(ledGreenPin, HIGH);
//      digitalWrite(ledBluePin, LOW);
//      break;
//    case 2:
//      digitalWrite(ledRedPin, LOW);
//      digitalWrite(ledGreenPin, LOW);
//      digitalWrite(ledBluePin, HIGH);
//      break;
//  }

  delay(10);
}
