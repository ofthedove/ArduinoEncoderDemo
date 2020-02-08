// ----- Global Constants
enum {
  buttonPin = 5,
  encoderDtPin = 18,
  encoderClkPin = 19,
  ledRedPin = 21,
  ledGreenPin = 22,
  ledBluePin = 23,
  ledBuiltinPin = LED_BUILTIN,

  buttonToggleDebounceMillis = 20,
  encoderQueueSize = 100,
};

const short int EncoderArray[4][4] =
  {{ 0, 1,-1, 0 },
   {-1, 0, 0, 1 },
   { 1, 0, 0,-1 },
   { 0,-1, 1, 0 }};

// ----- Global Variables
volatile byte encoderPreviousValue = 0;
byte encoderCount = 0;
volatile bool buttonToggleValue = false;
volatile unsigned int buttonToggleOldMillis = 0;

volatile byte circularQueue[encoderQueueSize] = {0};
volatile byte head = 0; // Index of next empty byte in circular queue
volatile byte tail = 0; // Index of oldest item in circular queue

// ----- Interrupt Service Routines
void IRAM_ATTR ButtonChangeIsr() {
  if (digitalRead(buttonPin) == LOW
      && millis() - buttonToggleOldMillis > buttonToggleDebounceMillis)
  {
    buttonToggleValue = !buttonToggleValue;
    buttonToggleOldMillis = millis();
  }
}

void IRAM_ATTR EncoderChangeIsr() {
  byte encoderValue = (digitalRead(encoderDtPin) << 1) + digitalRead(encoderClkPin);

  circularQueue[head] = encoderValue;
  head++;
  if(head == encoderQueueSize) { head = 0; }
}

// ----- Setup
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(encoderDtPin, INPUT);
  pinMode(encoderClkPin, INPUT);
  
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(ledBuiltinPin, OUTPUT);

  buttonToggleOldMillis = millis();

  attachInterrupt(buttonPin, ButtonChangeIsr, CHANGE);
  attachInterrupt(encoderDtPin, EncoderChangeIsr, CHANGE);
  attachInterrupt(encoderClkPin, EncoderChangeIsr, CHANGE);

  Serial.begin(115200);
}


// ----- Main Loop
void loop() {
  while(tail != head) {
    short unsigned int encoderValue = circularQueue[tail];
    encoderCount += EncoderArray[encoderPreviousValue][encoderValue];
    encoderPreviousValue = encoderValue;
    tail++;
    if(tail == encoderQueueSize) { tail = 0; }
  }

  Serial.print(buttonToggleValue);
  Serial.print("  ");
  Serial.println(encoderCount);

  digitalWrite(ledBuiltinPin, buttonToggleValue);

  switch(encoderCount % 3) {
    case 0:
      digitalWrite(ledRedPin, HIGH);
      digitalWrite(ledGreenPin, LOW);
      digitalWrite(ledBluePin, LOW);
      break;
    case 1:
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledGreenPin, HIGH);
      digitalWrite(ledBluePin, LOW);
      break;
    case 2:
      digitalWrite(ledRedPin, LOW);
      digitalWrite(ledGreenPin, LOW);
      digitalWrite(ledBluePin, HIGH);
      break;
  }

  delay(50);
}
