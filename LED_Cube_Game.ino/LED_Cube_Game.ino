/* Copyright 2017 Daniel Jeong (@taekb)

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#define LEDPIN_1 1 // LED Pin for Side 1 (OUT)
#define LEDPIN_2 2 // LED Pin for Side 2
#define LEDPIN_3 3 // LED Pin for Side 3
#define LEDPIN_4 4 // LED Pin for Side 4

#define BTNPIN_1 13 // BTN Pin for Side 1 (IN)
#define BTNPIN_2 12 // BTN Pin for Side 2
#define BTNPIN_3 11 // BTN Pin for Side 3
#define BTNPIN_4 10 // BTN Pin for Side 4

#define DEATH_LIMIT 3 // number of lives

double timeInterval = 0.0; // time interval between flashes of LEDs
int death = 0; // the number of lives you have before you lose the game
boolean isOver = false; // state of the game; indicates whether game is over or not

void setup() {
  // Start Up Sequence
  
  // side 1 setup
  pinMode(LEDPIN_1, OUTPUT);
  pinMode(BTNPIN_1, INPUT);
  digitalWrite(LEDPIN_1, HIGH);
  delay(500);

  // side 2 setup
  pinMode(LEDPIN_2, OUTPUT);
  pinMode(BTNPIN_2, INPUT);
  digitalWrite(LEDPIN_2, HIGH);
  delay(500);

  // side 3 setup
  pinMode(LEDPIN_3, OUTPUT);
  pinMode(BTNPIN_3, INPUT);
  digitalWrite(LEDPIN_3, HIGH);
  delay(500);

  // side 4 setup
  pinMode(LEDPIN_4, OUTPUT);
  pinMode(BTNPIN_4, INPUT);
  digitalWrite(LEDPIN_4, HIGH);
  
  delay(1000);

  // signal end of setup
  digitalWrite(LEDPIN_1, LOW);
  delay(500);
  digitalWrite(LEDPIN_2, LOW);
  delay(500);
  digitalWrite(LEDPIN_3, LOW);
  delay(500);
  digitalWrite(LEDPIN_4, LOW);
  delay(500);
}

void loop() {
  while (!isOver) {
    // generate random number to select a side
    randomSeed(analogRead(0));
    int sideNum = (int)random(4) + 1; // sideNum = 1~4
    timeInterval = 250;
    switch (sideNum) {
      case 1: // side 1
        digitalWrite(LEDPIN_1, HIGH);
        checkClick(BTNPIN_1);
        digitalWrite(LEDPIN_1, LOW);
        delay(timeInterval);
        break;
      case 2: // side 2
        digitalWrite(LEDPIN_2, HIGH);
        checkClick(BTNPIN_2);
        digitalWrite(LEDPIN_2, LOW);
        delay(timeInterval);
        break;
      case 3: // side 3
        digitalWrite(LEDPIN_3, HIGH);
        checkClick(BTNPIN_3);
        digitalWrite(LEDPIN_3, LOW);
        delay(timeInterval);
        break;
      case 4: // side 4
        digitalWrite(LEDPIN_4, HIGH);
        checkClick(BTNPIN_4);
        digitalWrite(LEDPIN_4, LOW);
        delay(timeInterval);
        break;
    }
    sideNum++;
  }

  displayEndOfGame();
}

// function to check whether a button has been pressed
void checkClick(int btnPinNum) {
  boolean isClicked = false;
  int timeCnt = 0;

  while (!isClicked && !(timeCnt == 1500)) {
   int btnState = digitalRead(btnPinNum);
   timeCnt++;
   isClicked = (btnState == HIGH)? true : false;
   delay(1);
  }
  if (!isClicked) {
    death += 1;
    if (death == DEATH_LIMIT) {
     isOver = true;
    }
  }
}

// function that defines LED behavior when the game is over
void displayEndOfGame() {
    digitalWrite(LEDPIN_1, HIGH);
    digitalWrite(LEDPIN_2, HIGH);
    digitalWrite(LEDPIN_3, HIGH);
    digitalWrite(LEDPIN_4, HIGH);

    delay(100);

    digitalWrite(LEDPIN_1, LOW);
    digitalWrite(LEDPIN_2, LOW);
    digitalWrite(LEDPIN_3, LOW);
    digitalWrite(LEDPIN_4, LOW);

    delay(100);
}
