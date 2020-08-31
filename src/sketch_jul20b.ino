#include <Wire.h>
#include <SPI.h>

const int slaveSelectPin = 10;
unsigned long adf_rx[6] = {0x02940C80, 0x00007531, 0x14010EC2, 0x000004B3, 0x00E14124, 0x00580005};
//unsigned long adf_tx[6] = {0x00C48008, 0x00000029, 0x14004EC2, 0x000004B3, 0x009501FC, 0x00580005};   // fract. mode, strong spurs +/- 46kHz
unsigned long adf_tx[6] = {0x03D70000, 0x08008011, 0x00014F42, 0x004004B3, 0x00910024, 0x00580005};     // int div, OK

const byte txrx_pin = 2;

void setup() {
  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, LOW);

  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.begin();

  writeAdf(adf_rx);

  pinMode(txrx_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(txrx_pin), isr_ptt, CHANGE);
}

void loop() {
}

// PTT ISR
volatile int prev_ptt = HIGH;

void isr_ptt() {
  noInterrupts();
  int current_ptt = digitalRead(txrx_pin);
  unsigned long* regs;
  bool update_needed;
  if (current_ptt == HIGH && prev_ptt == LOW) {
    regs = adf_tx;
    update_needed = true;
  } else if (current_ptt == LOW && prev_ptt == HIGH) {
    regs = adf_rx;
    update_needed = true;
  } else {
    update_needed = false;
  }

  if (update_needed) {
    writeAdf(regs);
  }

  prev_ptt = current_ptt;
  interrupts();
}

void writeAdf(unsigned long regs[]) {
  for (int ct = 5; ct >= 0; ct--) {
    writeRegister(regs, ct);
  }
}

void writeRegister(unsigned long regs[], int idx) {
  digitalWrite(slaveSelectPin, LOW);
  for (int i=3; i>=0; i--) {
    SPI.transfer((byte)(regs[idx] >> (i * 8)));
  }
  digitalWrite(slaveSelectPin, HIGH);
  digitalWrite(slaveSelectPin, LOW);
}
