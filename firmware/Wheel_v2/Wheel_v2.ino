#include <Servo.h>         // Подключение библиотек
#include "HID-Project.h"
#include <EEPROM.h>

int pot_w = 1;      // Пины потенциометров
int pot_th = 2;
int pot_br = 3;

int pot_th_max;     // Максимальное значение показаний потенциометров педалей
int pot_br_max;

#define BUTTONS A0     // Пин кнопок

int serv = 10;      // Пин сервы

int count;
int count_game;

bool debug = 0;     // Режим отладки (1 - вкл, 0 - выкл)

Servo servo1;

void setup() {
  servo1.attach(serv);

  count_game = 1;

  if (debug) Serial.begin(9600);

  pinMode(pot_w, INPUT);        // Подключение потенциометров
  pinMode(pot_th, INPUT);
  pinMode(pot_br, INPUT);

  pinMode(BUTTONS, INPUT_PULLUP);    // Подключение кнопок

  EEPROM.get(0, pot_th_max);     // Получение констант из EEPROM
  EEPROM.get(2, pot_br_max);
  EEPROM.get(4, count);

  Gamepad.begin();               // Подключение связи

}

void loop() {

  if (count_game == 0) {         // Выравнивание руля

    if (analogRead(pot_w) < 512) {
      while (analogRead(pot_w) < 512) {
      servo1.attach(serv);
      servo1.write(0);
      }
    servo1.detach();
    }

    if (analogRead(pot_w) > 512) {
      while (analogRead(pot_w) > 512) {
      servo1.attach(serv);
      servo1.write(360);
      }
    servo1.detach();
    }

    count_game ++;

  }

  if (count != 1) {     // Калибровка педалей
    calibrate();
    EEPROM.put(4, 1);
    count = 1;
  }

  if (not debug) {      // Запуск программы
    gamepad();
    buttons();
  }

  else {                // Режим отладки
    Serial.print("Wheel: ");
    Serial.print(analogRead(pot_w));
    Serial.print("; ");
    Serial.print("Throttle: ");
    Serial.print(analogRead(pot_th));
    Serial.print("; ");
    Serial.print("Brake: ");
    Serial.print(analogRead(pot_br));
    Serial.print("; ");
    Serial.println(analogRead(BUTTONS));
  }

}

void calibrate() {    // Калибровка педалей

  int timer = 0;      // Счетчик проходов

  while (timer != 5000) {
    int pt = analogRead(pot_th);
    int pb = analogRead(pot_br);
    if (pt > pot_th_max) pot_th_max = pt;
    EEPROM.put(0, pot_th_max);              // Запись констант в EEPROM
    if (pb > pot_br_max) pot_br_max = pb;
    EEPROM.put(0, pot_br_max);              // Запись констант в EEPROM
    timer ++;
  }

}

void gamepad() {      // Связь с компьютером руля и педалей

  int pot_v_w = analogRead(pot_w);
  int pot_v_th = analogRead(pot_th);
  int pot_v_br = analogRead(pot_br);

  if (pot_v_w < 510) {
    servo1.attach(serv);
    servo1.write(0);
  }
  else {
    if (pot_v_w > 514) {
      servo1.attach(serv);
      servo1.write(360);
    }
    else {
      servo1.detach();
    }
  }

  int throttle = map(pot_v_th, 0, pot_th_max, -128, 127);
  Gamepad.zAxis(throttle);
  Gamepad.write();

  int brake = map(pot_v_br, 0, pot_br_max, -128, 127);
  Gamepad.rzAxis(brake);
  Gamepad.write();

  int wheel = map(pot_v_w, 0, 1023, -32768, 32767);
  Gamepad.xAxis(wheel);
  Gamepad.write();

}

void buttons() {      // Связь с компьютером кнопок

  int butt_val = analogRead(BUTTONS);

  if (12 <= butt_val and butt_val <= 18) Gamepad.press(1);
  else Gamepad.release(1);
  Gamepad.write();

  if (37 <= butt_val and butt_val <= 43) Gamepad.press(2);
  else Gamepad.release(2);
  Gamepad.write();

  if (61 <= butt_val and butt_val <= 67) Gamepad.press(3);
  else Gamepad.release(3);
  Gamepad.write();

  if (286 <= butt_val and butt_val <= 292) Gamepad.press(4);
  else Gamepad.release(4);
  Gamepad.write();

  if (272 <= butt_val and butt_val <= 278) Gamepad.press(5);
  else Gamepad.release(5);
  Gamepad.write();

  if (297 <= butt_val and butt_val <= 303) Gamepad.press(6);
  else Gamepad.release(6);
  Gamepad.write();

  if (310 <= butt_val and butt_val <= 316) Gamepad.press(7);
  else Gamepad.release(7);
  Gamepad.write();

  if (228 <= butt_val and butt_val <= 234) Gamepad.press(8);
  else Gamepad.release(8);
  Gamepad.write();

  if (244 <= butt_val and butt_val <= 250) Gamepad.press(9);
  else Gamepad.release(9);
  Gamepad.write();
  
  if (257 <= butt_val and butt_val <= 263) Gamepad.press(10);
  else Gamepad.release(10);
  Gamepad.write();

  if (180 <= butt_val and butt_val <= 186) Gamepad.press(11);
  else Gamepad.release(11);
  Gamepad.write();

  if (197 <= butt_val and butt_val <= 203) Gamepad.press(12);
  else Gamepad.release(12);
  Gamepad.write();

  if (162 <= butt_val and butt_val <= 166) Gamepad.press(13);
  else Gamepad.release(13);
  Gamepad.write();

  if (126 <= butt_val and butt_val <= 132) Gamepad.press(14);
  else Gamepad.release(14);
  Gamepad.write();

  if (105 <= butt_val and butt_val <= 111) Gamepad.press(15);
  else Gamepad.release(15);
  Gamepad.write();

  if (144 <= butt_val and butt_val <= 150) Gamepad.press(16);
  else Gamepad.release(16);
  Gamepad.write();

  if (167 <= butt_val and butt_val <= 169) Gamepad.press(17);
  else Gamepad.release(17);
  Gamepad.write();

  if (333 <= butt_val and butt_val <= 339) Gamepad.press(18);
  else Gamepad.release(18);
  Gamepad.write();

  if (322 <= butt_val and butt_val <= 328) Gamepad.press(19);
  else Gamepad.release(19);
  Gamepad.write();
}
