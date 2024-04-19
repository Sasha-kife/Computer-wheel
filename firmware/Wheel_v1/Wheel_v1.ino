/*
  Скетч к проекту "Игровой руль для ПК на Arduino"
  Исходники на GitHub: https://github.com/Sasha-kife/Computer-wheel/
  Автор: Sasha-kife, 2024
*/

#include <Servo.h>         // Подключение библиотек
#include "HID-Project.h"
#include <EEPROM.h>

int pot_w = 1;      // Пины потенциометров
int pot_th = 2;
int pot_br = 3;

int pot_th_max;     // Максимальное значение показаний потенциометров педалей
int pot_br_max;

int BUTT_1 = 2;     // Пины кнопок
int BUTT_2 = 3;
int BUTT_3 = 4;
int BUTT_4 = 5;
int BUTT_5 = 6;
int BUTT_6 = 7;
int BUTT_7 = 8;
int BUTT_8 = 9;
int BUTT_9 = 14;
int BUTT_10 = 15;
int BUTT_11 = 16;
#define BUTT_12 A0

int serv = 10;      // Пин сервы

int count;
int count_game;

bool debug = 0;     // Режим отладки (1 - вкл, 0 - выкл)

Servo servo1;

void setup() {
  servo1.attach(serv);

  count_game = 0;

  if (debug) Serial.begin(9600);

  pinMode(pot_w, INPUT);        // Подключение потенциометров
  pinMode(pot_th, INPUT);
  pinMode(pot_br, INPUT);

  pinMode(BUTT_1, INPUT_PULLUP);    // Подключение кнопок
  pinMode(BUTT_2, INPUT_PULLUP);
  pinMode(BUTT_3, INPUT_PULLUP);
  pinMode(BUTT_4, INPUT_PULLUP);
  pinMode(BUTT_5, INPUT_PULLUP);
  pinMode(BUTT_6, INPUT_PULLUP);
  pinMode(BUTT_7, INPUT_PULLUP);
  pinMode(BUTT_8, INPUT_PULLUP);
  pinMode(BUTT_9, INPUT_PULLUP);
  pinMode(BUTT_10, INPUT_PULLUP);
  pinMode(BUTT_11, INPUT_PULLUP);
  pinMode(BUTT_12, INPUT_PULLUP);

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
    Serial.println(analogRead(pot_br));
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

  if (digitalRead(BUTT_1) != HIGH) Gamepad.press(1);
  else Gamepad.release(1);
  Gamepad.write();

  if (digitalRead(BUTT_2) != HIGH) Gamepad.press(2);
  else Gamepad.release(2);
  Gamepad.write();

  if (digitalRead(BUTT_3) != HIGH) Gamepad.press(3);
  else Gamepad.release(3);
  Gamepad.write();

  if (digitalRead(BUTT_4) != HIGH) Gamepad.press(4);
  else Gamepad.release(4);
  Gamepad.write();

  if (digitalRead(BUTT_5) != HIGH) Gamepad.press(5);
  else Gamepad.release(5);
  Gamepad.write();

  if (digitalRead(BUTT_6) != HIGH) Gamepad.press(6);
  else Gamepad.release(6);
  Gamepad.write();

  if (digitalRead(BUTT_7) != HIGH) Gamepad.press(7);
  else Gamepad.release(7);
  Gamepad.write();

  if (digitalRead(BUTT_8) != HIGH) Gamepad.press(8);
  else Gamepad.release(8);
  Gamepad.write();

  if (digitalRead(BUTT_9) == HIGH) Gamepad.press(9);
  else Gamepad.release(9);
  Gamepad.write();

  if (digitalRead(BUTT_10) != HIGH) Gamepad.press(10);
  else Gamepad.release(10);
  Gamepad.write();

  if (digitalRead(BUTT_11) != HIGH) Gamepad.press(11);
  else Gamepad.release(11);
  Gamepad.write();

  if (digitalRead(BUTT_12) != HIGH) Gamepad.press(12);
  else Gamepad.release(12);
  Gamepad.write();
}
