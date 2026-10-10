#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo1;
Servo servo2;

SoftwareSerial BT(2, 3);  // Arduino RX, TX

int pos = 0;
int speedDelay = 5;
bool running = true;
int direction = 1;

void setup() {
  servo1.attach(9);
  servo2.attach(10);

  BT.begin(9600);

  servo1.write(0);
  servo2.write(0);

  delay(500);
}

void loop() {

  // Bluetooth commands
  if (BT.available()) {
    char cmd = BT.read();

    if (cmd == 'A' || cmd == 'a') {
      running = true;
    }

    if (cmd == 'S' || cmd == 's') {
      running = false;
    }

    if (cmd == 'L' || cmd == 'l') {
      running = false;
      pos = 0;
      servo1.write(0);
      servo2.write(0);
    }

    if (cmd == 'R' || cmd == 'r') {
      running = false;
      pos = 180;
      servo1.write(180);
      servo2.write(180);
    }
  }

  // Automatic 0° ↔ 180° movement
  if (running) {

    pos = pos + direction;

    if (pos >= 180) {
      pos = 180;
      direction = -1;
    }

    if (pos <= 0) {
      pos = 0;
      direction = 1;
    }

    servo1.write(pos);
    servo2.write(pos);

    delay(speedDelay);
  }
}
