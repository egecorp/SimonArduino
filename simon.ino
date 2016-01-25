// Статусы контроллера
#define WAIT 0
#define PLAY 1
#define FAIL 2
#define WINN 3

// Текущий статус контроллера
int aStatus = WAIT;

void setup() {
  randomSeed(analogRead(0));
  setupIO();
  Lighting(255);
  delay(1000);
}


void loop() {
  int k;
 
  switch(aStatus)
  {
    case WAIT:
      // Ждём нажатия кнопки Старт
      Lighting(0);
      if ( (inKey() & 16) != 0) aStatus = PLAY;
      break;
    case PLAY:
      // Зажжем все светодиоды на 5 секунд как признак начала игры
      Lighting(255);
      delay(5000);
      Light(0);
      startGame();    
      // Всего 10 раундов
      for (k = 0; k < 10; k++)
      {
        getNext();
        if (inKeyNext()== false)
        {
          aStatus = FAIL;
          return;
        }
        delay(1000);
       }

       aStatus = WINN;
      break;      
    case FAIL:
      // При ошибочном вводе загорается светодиод "ошибка"
      Lighting(16);
      delay(5000);
      aStatus = WAIT;
    break;      
    default:  
      // В случае успеха 30 раз помигаем всеми светодиодами
      for (k = 0; k < 30; k++)
      {
        Lighting(255);
        delay(300);
        Lighting(0);
        delay(300);        
      }
      aStatus = WAIT;
  }
}
