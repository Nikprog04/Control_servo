#include <Servo.h>

struct Node {
  int angle;  //угол сервопривода
  bool flag;  //флагоая переменная отвечающая за убывание или увеличение угла
  Servo myservo;  //переменная привязанная к сервоприводу


  //прикрепление сервопривода к пину с шимом
  void init(int pin){
    myservo.attach(pin);
  }


  //задание угла сервопривода
  void rotate(int angle){
    this->angle = angle;
    myservo.write(angle);
  }
};


//инициализация переменных отвечающих за управление сервоприводами
Node muscle_1;
Node muscle_2;

void setup() {

  //инициализация пинов датчиков и пинов сервоприводов
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  muscle_1.init(10);
  muscle_2.init(11);
}

//инициализация переменных, отвечающих за таймер и хранение значений с датчика
static int tmp = 0;
static int val_1 = 0;
static int val_2 = 0;

void loop() {
  if (millis() - tmp >= 20)
  {
    tmp = millis();
    val_1  = analogRead(A0);  //чтение и сохранение значений с датчика
    val_2  = analogRead(A1);

    if ((val_1 > 1010)||(val_1 < 10)) {task(&muscle_1);}   //изменение угла сервопривода происходит при выходе значений с датчика из заданного диапозона
    if ((val_2 > 1010)||(val_2 < 10)) {task(&muscle_2);}
  }
}

void task (Node *muscle) {
  if (!muscle->flag){
    muscle->angle += 2; //увеличение переменной, отвечающей за угол сервопривода
  } else {
    muscle->angle -=2;  //уменьшение переменной, отвечающей за угол сервопривода
  }
  if ((muscle->angle <= 0) || (muscle->angle >= 180)) {muscle->flag = !muscle->flag;} //изменение флаговой переменной 

  muscle->rotate(muscle->angle); //поворот сервопривода на заданный угол

}