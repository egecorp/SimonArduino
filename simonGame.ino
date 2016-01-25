 int gameRound = 0;   // Текущий раунд игры
 int simonButtons[10];   // Буфер клавиш, которые нужно нажать

 // Начало игры
 void startGame()
 {
  gameRound = 0;
 }

 // Показать следующую комбинацию
 void getNext()
 {
   simonButtons[gameRound++] = random(1,5);   // номер кнопки случайным образом от 1 до 4
   showSimonButtons();
 }

 // Зажечь светодиоды из буфера клавиш
 void showSimonButtons()
 { 
   for (int i = 0; i < gameRound; i++) 
   {
      Light(0);
      delay(400);
      Light(simonButtons[i]);
      delay(1000);
   }
   Light(0);
   delay(400);
 }
 
 // Проверить ввод пользователя
 bool inKeyNext()
 {
   for (int i = 0; i < gameRound; i++) 
   {
     if (inKeyGame() != simonButtons[i]) return false;
      delay(400);
   }
   
   return true;
  }

