// Выводы кнопок 
// 1-4 - круглые, 5 - квадратная (старт)
#define BUTTON1 7
#define BUTTON2 8
#define BUTTON3 11
#define BUTTON4 10
#define BUTTON5 9

// Выводы светодиодов
// 1-4 - кнопочные, 5 - "ошибка"
#define LED1 2
#define LED2 3
#define LED3 6
#define LED4 5
#define LED5 4

void setupIO()
{
  // Кнопки на вход
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
  pinMode(BUTTON5, INPUT);
  // Включаем поддяжку
  digitalWrite(BUTTON1, HIGH);
  digitalWrite(BUTTON2, HIGH);
  digitalWrite(BUTTON3, HIGH);
  digitalWrite(BUTTON4, HIGH);
  digitalWrite(BUTTON5, HIGH);
  // Светодиоды на вывод
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  // Стартовая комбинация - зажечь каждый светодиод
  Lighting(1);delay(100);
  Lighting(2);delay(100);
  Lighting(4);delay(100);
  Lighting(8);delay(100);
  Lighting(16);delay(100);

  // Serial.begin(9600); // для отладки
}

int keyStatus = 0;    // Битовый буфер нажатых клавиш

// Получает текущую карту нажатий
int getKey()
{
  /*
   * Круглые кнопки по умолчанию замкнуты
   * Квадратная по умолчанию разомкнута
   */
  keyStatus = 0;
  keyStatus |= ((digitalRead(BUTTON1) != LOW ) ? 1  : 0);
  keyStatus |= ((digitalRead(BUTTON2) != LOW ) ? 2  : 0);
  keyStatus |= ((digitalRead(BUTTON3) != LOW ) ? 4  : 0);
  keyStatus |= ((digitalRead(BUTTON4) != LOW ) ? 8  : 0);
  keyStatus |= ((digitalRead(BUTTON5) != HIGH) ? 16 : 0);

  Lighting(keyStatus & (0b00001111 | ((aStatus == FAIL) ? 16 : 0) ));
  return keyStatus;
}

// Ждёт, пока пользователь не нажмёт и не отпустит кнопку. 
int inKey()
{
  int _key = 0;
  while((_key = getKey()) == 0);
  delay(200);
  while(getKey() != 0);
  return _key;
}

// Преобразует битовую карту в номер нажатой кнопки
int inKeyGame()
{
  int _key = inKey();
  // Serial.write(48 + _key); // для отладки
  if ((_key & 1) != 0) return 1;
  if ((_key & 2) != 0) return 2;
  if ((_key & 4) != 0) return 3;
  if ((_key & 8) != 0) return 4;
  
  return 0;
}

// Зажигает светодиоды по битовой карте
void Lighting(int code)
{
  digitalWrite(LED1, ((code & 0b00000001) != 0) ? HIGH : LOW);
  digitalWrite(LED2, ((code & 0b00000010) != 0) ? HIGH : LOW);
  digitalWrite(LED3, ((code & 0b00000100) != 0) ? HIGH : LOW);
  digitalWrite(LED4, ((code & 0b00001000) != 0) ? HIGH : LOW);
  digitalWrite(LED5, ((code & 0b00010000) != 0) ? HIGH : LOW);
}

// Зажигает светодиод по номеру
void Light(int code)
{
  switch(code)
  {
    case 0:
      Lighting(0 |  ((aStatus == FAIL) ? 16 : 0) );
      break;
    case 1:
      Lighting(1 |  ((aStatus == FAIL) ? 16 : 0) );
      break;
    case 2:
      Lighting(2 |  ((aStatus == FAIL) ? 16 : 0) );
      break;
    case 3:
      Lighting(4 |  ((aStatus == FAIL) ? 16 : 0) );
      break;
    case 4:
      Lighting(8 |  ((aStatus == FAIL) ? 16 : 0) );
      break;
  }
}


