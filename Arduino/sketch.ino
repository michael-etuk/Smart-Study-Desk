#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 2;
const int breakButtonPin = 3;
const int buzzerPin = 8;

int sessionsCompleted = 0;
int productivityScore = 0;

int focusDuration = 30;
int breakDuration = 10;

int settingsOption = 0;

int menuOption = 0;

bool timerStarted = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(breakButtonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  showMenu();
}

void loop() {

  // Move through menu
  if (digitalRead(buttonPin) == LOW) {

    menuOption++;

    if (menuOption > 2) {
      menuOption = 0;
    }

    showMenu();

    delay(300);
  }

  // Select menu item
  if (digitalRead(breakButtonPin) == LOW) {

    lcd.clear();

    if (menuOption == 0) {

      runStudySession();

    } 
    else if (menuOption == 1) {

      lcd.setCursor(0,0);
      lcd.print("Sessions:");
      lcd.print(sessionsCompleted);

      lcd.setCursor(0,1);
      lcd.print("Score:");
      lcd.print(productivityScore);

      delay(3000);

      showMenu();

    } 
    else if (menuOption == 2) {

      runSettings();
    }

    delay(300);
  } 
}

void runStudySession() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FOCUS MODE");

  delay(1000);

  for (int seconds = focusDuration; seconds >= 0; seconds--) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("FOCUS MODE");

    lcd.setCursor(0, 1);
    lcd.print("00:");

    if (seconds < 10) {
      lcd.print("0");
    }

    lcd.print(seconds);

    delay(1000);
  }

  sessionsCompleted++;
  productivityScore += 10;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SESSION DONE");

  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1000);
    delay(300);
    noTone(buzzerPin);
    delay(200);
  }

  runBreakSession();

}

void runBreakSession() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PRESS BREAK");

  while (digitalRead(breakButtonPin) == HIGH) {
    // wait for break button
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BREAK MODE");

  delay(1000);

  for (int seconds = breakDuration; seconds >= 0; seconds--) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("BREAK MODE");

    lcd.setCursor(0, 1);
    lcd.print("00:");

    if (seconds < 10) {
      lcd.print("0");
    }

    lcd.print(seconds);

    delay(1000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BREAK DONE");

  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 1200);
    delay(300);
    noTone(buzzerPin);
    delay(200);
  }

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Sessions:");
  lcd.print(sessionsCompleted);

  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.print(productivityScore);

  delay(3000);

  showMenu();

}

void showMenu() {

  lcd.clear();

  if (menuOption == 0) {

    lcd.setCursor(0,0);
    lcd.print("> Start Study");

    lcd.setCursor(0,1);
    lcd.print("  View Stats");

  }
  else if (menuOption == 1) {

    lcd.setCursor(0,0);
    lcd.print("> View Stats");

    lcd.setCursor(0,1);
    lcd.print("  Settings");

  }
  else {

    lcd.setCursor(0,0);
    lcd.print("> Settings");

    lcd.setCursor(0,1);
    lcd.print("  Start Study");

  }
}

void runSettings() {

  while (digitalRead(breakButtonPin) == LOW) {}

  settingsOption = 0;

  showSettingsMenu();

  while (true) {

    if (digitalRead(buttonPin) == LOW) {

      settingsOption++;

      if (settingsOption > 2) {
        settingsOption = 0;
      }

      showSettingsMenu();

      delay(300);
    }

    if (digitalRead(breakButtonPin) == LOW) {

      lcd.clear();

      if (settingsOption == 0) {

        editFocusTime();
        showSettingsMenu();

      }
      else if (settingsOption == 1) {

        editBreakTime();
        showSettingsMenu();

      }
      else {

        showMenu();
        return;
      }

      delay(1500);

      showSettingsMenu();
    }
  }
}

void showSettingsMenu() {

  lcd.clear();

  if (settingsOption == 0) {

    lcd.setCursor(0,0);
    lcd.print("> Focus Time");

    lcd.setCursor(0,1);
    lcd.print("  Break Time");

  }
  else if (settingsOption == 1) {

    lcd.setCursor(0,0);
    lcd.print("> Break Time");

    lcd.setCursor(0,1);
    lcd.print("  Back");

  }
  else {

    lcd.setCursor(0,0);
    lcd.print("> Back");

    lcd.setCursor(0,1);
    lcd.print("  Focus Time");

  }
}

void editFocusTime() {

  while (digitalRead(breakButtonPin) == LOW) {}

  lcd.clear();

  while (true) {

    lcd.setCursor(0,0);
    lcd.print("Focus:");
    lcd.print(focusDuration);
    lcd.print("s   ");

    lcd.setCursor(0,1);
    lcd.print("+5   Save");

    if (digitalRead(buttonPin) == LOW) {

      focusDuration += 5;

      if (focusDuration > 60) {
        focusDuration = 15;
      }

      delay(300);

      lcd.clear();
    }

    if (digitalRead(breakButtonPin) == LOW) {

      lcd.clear();
      lcd.print("Saved!");

      delay(1000);

      return;
    }
  }
}

void editBreakTime() {

  while (digitalRead(breakButtonPin) == LOW) {}

  lcd.clear();

  while (true) {

    lcd.setCursor(0,0);
    lcd.print("Break:");
    lcd.print(breakDuration);
    lcd.print("s   ");

    lcd.setCursor(0,1);
    lcd.print("+5   Save");

    if (digitalRead(buttonPin) == LOW) {

      breakDuration += 5;

      if (breakDuration > 30) {
        breakDuration = 5;
      }

      delay(300);

      lcd.clear();
    }

    if (digitalRead(breakButtonPin) == LOW) {

      lcd.clear();
      lcd.print("Saved!");

      delay(1000);

      return;
    }
  }
}