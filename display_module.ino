#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define IR_SENSOR_PIN  13
#define ENTRY_BUTTON   14
#define EXIT_BUTTON    12

const int TOTAL_CAPACITY = 50;
int occupied = 0;

unsigned long lastIRTime = 0;
unsigned long lastEntryTime = 0;
unsigned long lastExitTime = 0;
const unsigned long DEBOUNCE_DELAY = 500;

int lastIRState = HIGH;
int lastEntryState = HIGH;
int lastExitState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(ENTRY_BUTTON, INPUT_PULLUP);
  pinMode(EXIT_BUTTON, INPUT_PULLUP);
  Wire.begin(21, 22);
  u8g2.begin();
  updateDisplay();
  Serial.println("System Ready!");
}

void loop() {
  unsigned long currentTime = millis();

  int irState = digitalRead(IR_SENSOR_PIN);
  if (irState == LOW && lastIRState == HIGH) {
    if (currentTime - lastIRTime > DEBOUNCE_DELAY) {
      if (occupied < TOTAL_CAPACITY) {
        occupied++;
        Serial.println("IR Entry detected!");
        updateDisplay();
      }
      lastIRTime = currentTime;
    }
  }
  lastIRState = irState;

  int entryState = digitalRead(ENTRY_BUTTON);
  if (entryState == LOW && lastEntryState == HIGH) {
    if (currentTime - lastEntryTime > DEBOUNCE_DELAY) {
      if (occupied < TOTAL_CAPACITY) {
        occupied++;
        Serial.println("Button Entry!");
        updateDisplay();
      }
      lastEntryTime = currentTime;
    }
  }
  lastEntryState = entryState;

  int exitState = digitalRead(EXIT_BUTTON);
  if (exitState == LOW && lastExitState == HIGH) {
    if (currentTime - lastExitTime > DEBOUNCE_DELAY) {
      if (occupied > 0) {
        occupied--;
        Serial.println("Button Exit!");
        updateDisplay();
      }
      lastExitTime = currentTime;
    }
  }
  lastExitState = exitState;
}

void updateDisplay() {
  int vacant = TOTAL_CAPACITY - occupied;
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(20, 12, "PARKING SYSTEM");
  u8g2.drawLine(0, 15, 128, 15);
  u8g2.drawStr(0, 30, "Capacity:");
  u8g2.setCursor(90, 30);
  u8g2.print(TOTAL_CAPACITY);
  u8g2.drawStr(0, 44, "Occupied:");
  u8g2.setCursor(90, 44);
  u8g2.print(occupied);
  u8g2.drawStr(0, 58, "Vacant:");
  u8g2.setCursor(90, 58);
  u8g2.print(vacant);
  u8g2.sendBuffer();
}