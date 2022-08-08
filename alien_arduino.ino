/* Pocket Alien Arduino
 by Shalma Wegsman
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// CHANGE BASED ON CIRCUIT:
const int button1Pin = 9;
const int button2Pin = 8; 
const int button3Pin = 7; 

const int sound = 6; 

int button1State = 0;
int button2State = 0;
int button3State = 0;


/* Settings */
bool soundEnabled=true;
bool notification = false;
int notificationBlink=0;
int frameTime = 150;

/* Graphics */
extern uint8_t title[];
extern uint8_t friend_menu_1[];
extern uint8_t friend_menu_2[];
extern uint8_t menu_1[];
extern uint8_t menu_2[];
extern uint8_t menu_3[];
extern uint8_t menu_4[];
extern uint8_t status_menu[];
extern uint8_t alien_chewing_1[];
extern uint8_t alien_chewing_2[];
extern uint8_t alien_done_eating[];
extern uint8_t alien_eating_1[];
extern uint8_t alien_eating_2[];
extern uint8_t alien_eating_3[];
extern uint8_t alien_and_bebe[];
extern uint8_t alien_and_bebe_hug[];
extern uint8_t alien_and_bebe_jump_1[];
extern uint8_t alien_and_bebe_jump_2[];
extern uint8_t alien_and_slugie[];
extern uint8_t alien_and_slugie_hug[];
extern uint8_t alien_and_slugie_jump_1[];
extern uint8_t alien_and_slugie_jump_2[];
extern uint8_t alien_standing_1[];
extern uint8_t alien_standing_2[];
extern uint8_t moon_1[];
extern uint8_t moon_2[];
extern uint8_t moon_3[];
extern uint8_t moon_4[];
extern uint8_t moon_5[];
extern uint8_t alien_in_bed_asleep[];
extern uint8_t alien_in_bed_awake[];
extern uint8_t alien_sleeping_1[];
extern uint8_t alien_sleeping_2[];
extern uint8_t alien_smelling[];
extern uint8_t alien_walking_1[];
extern uint8_t alien_walking_2[];
extern uint8_t flower_1[];
extern uint8_t flower_2[];
extern uint8_t flower_3[];
extern uint8_t flower_4[];
extern uint8_t shooting_star_1[];
extern uint8_t shooting_star_2[];
extern uint8_t shooting_star_3[];
extern uint8_t shooting_star_4[];

const unsigned char* eating[12] = {
      alien_eating_1, alien_eating_2, alien_eating_3,
      alien_chewing_1, alien_chewing_2,
      alien_chewing_1, alien_chewing_2,
      alien_chewing_1, alien_chewing_2,
      alien_chewing_1, alien_chewing_2,
      alien_done_eating
    };

const unsigned char* sleeping[14] = {
      alien_in_bed_awake, alien_in_bed_asleep,
      alien_sleeping_1, alien_sleeping_2,
      alien_sleeping_1, alien_sleeping_2,
      alien_sleeping_1, alien_sleeping_2,
      alien_sleeping_1, alien_sleeping_2,
      alien_sleeping_1, alien_sleeping_2,
      alien_in_bed_asleep, alien_in_bed_awake
    };

const unsigned char* slugie[10] = {
      alien_and_slugie, 
      alien_and_slugie_jump_1, alien_and_slugie_jump_2,
      alien_and_slugie_jump_1, alien_and_slugie_jump_2,
      alien_and_slugie_jump_1, alien_and_slugie_jump_2,
      alien_and_slugie_jump_1, alien_and_slugie_jump_2,
      alien_and_slugie_hug
    };

const unsigned char* bebe[10] = {
      alien_and_bebe, 
      alien_and_bebe_jump_1, alien_and_bebe_jump_2,
      alien_and_bebe_jump_1, alien_and_bebe_jump_2,
      alien_and_bebe_jump_1, alien_and_bebe_jump_2,
      alien_and_bebe_jump_1, alien_and_bebe_jump_2,
      alien_and_bebe_hug
    };
    
const unsigned char* walkNormal[4] = {
      alien_walking_1, alien_walking_2,
      alien_walking_1, alien_walking_2
    };

const unsigned char* walkFlower[5] = {
      flower_1, flower_2, flower_3, flower_4,
      alien_walking_2
    };

const unsigned char* walkStar[4] = {
      shooting_star_1, shooting_star_2, shooting_star_3, shooting_star_4
    };


const unsigned char* backgroundSeq[11] = {
    alien_standing_1, alien_standing_1,
    alien_standing_1, alien_standing_1,
    alien_standing_1, alien_standing_1,
    moon_1, moon_2, moon_3, moon_4, moon_5
    };


/* Menus */
bool menuOpen = false;
bool statusOpen = false;
bool friendMenuOpen = false;
int menuOption = 0;
int friendMenuOption = 0;

/* Status */
int foodStatus=2;
int happinessStatus=2;
int sleepStatus=2;
int movesSinceFood = 0;
int movesSinceSleep = 0;
int movesSinceFriends = 0;
int backgroundStatus = 0;

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(sound, OUTPUT);

  pinMode(13,OUTPUT);

  //randomSeed(analogRead(0));

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // show title
  display.drawGrayscaleBitmap(0, 0, title , 128, 128);
  display.display();
  
  //title tone (CHANGE)

  tone(sound,500,200);
  delay(200);
  tone(sound,1000,200);
  delay(400);
  tone(sound,700,200);
  delay(200);
  tone(sound,1100,200);

  delay(2200);
  // end title
  
  display.clearDisplay();
  
}


void loop() {

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);

  if(button1State==HIGH){
    if(soundEnabled){
      tone(sound,300,80);
    }
    if(friendMenuOpened){
      if(friendMenuOption == 1){
        friendMenuOption = 2;
        display.clearDisplay();
        display.drawGrayscaleBitmap(0, 0, friend_menu_2 , 128, 128);
        display.display();
      }
      else if(friendMenuOption == 2){
        friendMenuOption = 1;
        display.clearDisplay();
        display.drawGrayscaleBitmap(0, 0, friend_menu_1 , 128, 128);
        display.display();
      }
    }
    else if(!menuOpen){
      menuOpen=true;
      menuOption = 1;
      display.clearDisplay();
      display.drawGrayscaleBitmap(0, 0, menu_1 , 128, 128);
      display.display();
    }
    else if(menuOption = 1){
      menuOption = 2;
      display.clearDisplay();
      display.drawGrayscaleBitmap(0, 0, menu_2 , 128, 128);
      display.display();
    }
    else if(menuOption = 2){
      menuOption = 3;
      display.clearDisplay();
      display.drawGrayscaleBitmap(0, 0, menu_3 , 128, 128);
      display.display();
    } 
    else if(menuOption = 3){
      menuOption = 4;
      display.clearDisplay();
      display.drawGrayscaleBitmap(0, 0, menu_4 , 128, 128);
      display.display();
    } 
    else if(menuOption = 4){
      menuOption = 1;
      display.clearDisplay();
      display.drawGrayscaleBitmap(0, 0, menu_1 , 128, 128);
      display.display();
    } 
    
  }
  else if(button2State==HIGH){
    if(soundEnabled){
      tone(sound,300,80);
    }
    if (friendMenuOpen){
      FriendAction(friendMenuOption);
    }
    else if(menuOpen){
      menuOption = 0;
      menuOpen = false;
      if(menuOption == 1){
        walkAction();
      }
      else if(menuOption == 2) {
        friendMenuOpen = true;
        friendMenuOption = 1;
        c
      }
      else if(menuOption == 3){
        EatAction();
      }
      else if(menuOption == 4) {
        SleepAction();
      }
    }
    else if (!statusOpen){
      statusOpen = true;
      DisplayStatusMenu();
    }
  }
  else if(button3State==HIGH){
    if(soundEnabled){
      tone(sound,300,80);
    }
    if(menuOpen){
      menuOption = 0;
      menuOpen = false;
      ClearDisplay();
    }
    else if (friendMenuOpen){
      friendMenuOption = 0;
      friendMenuOpen = false;
      ClearDisplay();
    }
    else if (statusOpen){
      statusOpen = false;
      ClearDisplay();
    }
  }
  else{
    display.clearDisplay();
    display.drawGrayscaleBitmap(0, 0, backgroundSeq[backgroundStatus] , 128, 128);
    display.display();

    backgroundStatus += 1;
    if (backgrounsStatus == 11){
      backgrounsStatus = 0;
    }
  }

  // Adjust character status:
  if (movesSinceFood > 3){
    foodStatus = 0;
  }
  else if (movesSinceFood > 0){
    foodStatus = 1;
  }
  else{
    foodStatus = 2;
  } 

  if (movesSinceSleep > 3){
    sleepStatus = 0;
  }
  else if (movesSinceFood > 0){
    sleepStatus = 1;
  }
  else{
    sleepStatus = 2;
  }

  if (movesSinceFriends > 3){
    happinessStatus = 0;
  }
  else if (movesSinceFriends > 0){
    happinessStatus = 1;
  }
  else{
    happinessStatus = 2;
  } 
}


void ClearDisplay(){
  backgroundStatus = 0;
  display.clearDisplay();
  display.drawGrayscaleBitmap(0, 0, alien_standing , 128, 128);
  display.display();
}

void DisplayStatusMenu() {
  display.clearDisplay();
  display.drawGrayscaleBitmap(0, 0, status_menu , 128, 128);

  if (foodStatus == 2){
    display.fillRect(40,37,80,19,WHITE);
  }
  else if (foodStatus == 1){
    display.fillRect(40,37,53,19,WHITE);
  }
  else if (foodStatus == 0){
    display.fillRect(40,37,17,19,WHITE);
  }  


  if (moodStatus == 2){
    display.fillRect(40,66,80,19,WHITE);
  }
  else if (moodStatus == 1){
    display.fillRect(40,66,53,19,WHITE);
  }
  else if (moodStatus == 0){
    display.fillRect(40,66,17,19,WHITE);
  }  


  if (sleepStatus == 2){
    display.fillRect(40,97,80,19,WHITE);
  }
  else if (sleepStatus == 1){
    display.fillRect(40,97,53,19,WHITE);
  }
  else if (sleepStatus == 0){
    display.fillRect(40,97,17,19,WHITE);
  }  
  
  display.display();  
}



void EatAction(){
  movesSinceSleep += 1;
  movesSinceFood = 0;
  movesSinceFriends += 1;
  for(int i=0; i<12; i++){
    display.clearDisplay();
    display.drawGrayscaleBitmap(0, 0, eating[i] , 128, 128);
    delay(frameTime);
    display.display();
  }
}

void SleepAction(){
  movesSinceFood += 2;
  movesSinceSleep = 0;
  movesSinceFriends += 1;
  for(int i=0; i<14; i++){
    display.clearDisplay();
    display.drawGrayscaleBitmap(0, 0, sleeping[i] , 128, 128);
    delay(frameTime);
    display.display();
  }
}


void FriendAction(int friendID) {
  movesSinceFood += 1;
  movesSinceSleep += 1;
  movesSinceFriends = 0;
  if (friendID == 0){
    // Slugie
    for(int i=0; i<10; i++){
      display.clearDisplay();
      display.drawGrayscaleBitmap(0, 0, slugie[i] , 128, 128);
      delay(frameTime);
      display.display();
    }
  }
  else if (friendID == 1) {
    // Bebe
    for(int i=0; i<10; i++){
      display.clearDisplay();
      display.drawGrayscaleBitmap(0, 0, bebe[i] , 128, 128);
      delay(frameTime);
      display.display();
    }
  }
}

void WalkAction(){
  movesSinceFood += 1;
  movesSinceSleep += 1;
  movesSinceFriends += 1;

  for(int i=0; i<4; i++){
    display.clearDisplay();
    display.drawGrayscaleBitmap(0, 0, walkNormal[i] , 128, 128);
    delay(frameTime);
    display.display();
  }
  
  for (int i = 0; i < 3; i++){

    int r = random(10);

    if (r < 5){
      for(int i=0; i<4; i++){
        display.clearDisplay();
        display.drawGrayscaleBitmap(0, 0, walkNormal[i] , 128, 128);
        delay(frameTime);
        display.display();
      }
    }
    else if (r < 8){
      for(int i=0; i<5; i++){
        display.clearDisplay();
        display.drawGrayscaleBitmap(0, 0, walkFlower[i] , 128, 128);
        delay(frameTime);
        display.display();
      }
    }
    else {
      for(int i=0; i<4; i++){
        display.clearDisplay();
        display.drawGrayscaleBitmap(0, 0, walkStar[i] , 128, 128);
        delay(frameTime);
        display.display();
      }
    }
  }
}
