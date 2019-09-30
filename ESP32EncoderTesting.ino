#define PIN_SW 5
#define PIN_DT 18
#define PIN_CLK 19

volatile bool changeFlag = false;

void IRAM_ATTR OnSwChange() {
  changeFlag = true;
}

void IRAM_ATTR OnDtChange() {
  changeFlag = true;
}

void IRAM_ATTR OnClkChange() {
  changeFlag = true;
}

void setup() {
  pinMode(PIN_SW, INPUT);
  pinMode(PIN_DT, INPUT);
  pinMode(PIN_CLK, INPUT);

  attachInterrupt(PIN_SW, OnSwChange, CHANGE);
  attachInterrupt(PIN_DT, OnDtChange, CHANGE);
  attachInterrupt(PIN_CLK, OnClkChange, CHANGE);

  Serial.begin(115200);
}

void loop() {
  if(changeFlag) {
    int value = digitalRead(PIN_SW) << 2;
    value += digitalRead(PIN_DT) << 1;
    value += digitalRead(PIN_CLK);
    Serial.println(value, BIN);
    changeFlag = false;
  }
}
