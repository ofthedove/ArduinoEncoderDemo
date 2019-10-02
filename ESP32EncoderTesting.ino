enum {
  switchPin = 5,
  encoderDtPin = 18,
  encoderClkPin = 19,
  ledRedPin = 21,
  ledGreenPin = 22,
  ledBluePin = 23,
  ledBuiltinPin = LED_BUILTIN,

  switchToggleDebounceMillis = 20,
  encoderDebounceMillis = 10,
};

volatile bool changeFlag = false;
volatile byte encoderPreviousValue = 0;
volatile byte encoderCount = 0;
volatile unsigned int encoderOldMillis = 0;
volatile bool switchToggleValue = false;
volatile unsigned int switchToggleOldMillis = 0;

volatile byte circularQueue[100] = {0};
volatile byte head = 0; // Index of next empty byte in circular queue
volatile byte tail = 0; // Index of oldest item in circular queue
volatile bool error = false;

void IRAM_ATTR SwitchChangeIsr() {
  if (digitalRead(switchPin) == LOW
      && millis() - switchToggleOldMillis > switchToggleDebounceMillis)
  {
    switchToggleValue = !switchToggleValue;
    switchToggleOldMillis = millis();
  }
}

void IRAM_ATTR EncoderChangeIsr() {
//  if (millis() - encoderOldMillis < encoderDebounceMillis) {
//    return;
//  }

  if(head + 1 == tail) {
    error = true;
  }
  
  circularQueue[head] = digitalRead(encoderDtPin) << 1 + digitalRead(encoderClkPin);
  head++;
  
//  byte encoderValue = digitalRead(encoderDtPin) << 1 + digitalRead(encoderClkPin);
//  if (encoderValue == 0b00) {
//    if (encoderPreviousValue == 0b01) {
//      encoderCount++;
//    } else {
//      encoderCount--;
//    }
//  } else if (encoderValue == 0b11) {
//    if (encoderPreviousValue == 0b01) {
//      encoderCount++;
//    } else {
//      encoderCount--;
//    }
//  }
//
//  encoderPreviousValue = encoderValue;
  encoderOldMillis = millis();
}

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(encoderDtPin, INPUT);
  pinMode(encoderClkPin, INPUT);
  
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

  Serial.begin(115200);
}

void loop() {
  if(error) {
    Serial.println("error");
  }

  while(tail < head) {
    Serial.println(circularQueue[tail], BIN);
    tail++;
  }
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
