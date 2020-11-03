#include <Arduino.h>

#define R 11
#define G 9
#define B 10

#define ModeValFade             0
#define ModeValSmoothRed        1
#define ModeValTechno           2
#define ModeValTechnoRandColor  3

#define MenuPin 6
#define ModeVal 3

int Rval = 0;
int Gval = 0;
int Bval = 0;

int MenuVal = 0;

bool ButtonPressed = false;

void SmoothRed();
void SmoothAll();
void fade();
void Techno();
void TechnoRandColor();

void Mode();
void CheckMenuButton();
void FlashForRecognize();
void DelayForNextClick();

void setup() {
  Serial.begin(115200);
  
  pinMode(R, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(G, OUTPUT);

  pinMode(MenuPin, INPUT);
}

void loop() {
  Mode();
}
void Mode(){
  if(MenuVal == ModeValFade){
    fade();
  }
  DelayForNextClick();
  if (MenuVal == ModeValSmoothRed){
    SmoothRed();
  }
  DelayForNextClick();
  if(MenuVal == ModeValTechno){
    Techno();
  }
  DelayForNextClick();
  if(MenuVal == ModeValTechnoRandColor){
    TechnoRandColor();
  }
}

void SmoothRed(){   
  analogWrite(R, 255);
  for (int i=0; i <= 255; i++){
    if(ButtonPressed){
      break;
    } 
    CheckMenuButton();
    analogWrite(G, i);
    delay(10);
  }
  for (int i=0; i <= 255; i++){
    if(ButtonPressed){
      break;
    } 
    CheckMenuButton();
    analogWrite(B, i);
    delay(10);
  }
  for (int i=255; i >= 0; i--){
    if(ButtonPressed){
      break;
    } 
    CheckMenuButton();
    analogWrite(B, i);
    delay(10);
  }
  for (int i=255; i >= 0; i--){
    if(ButtonPressed){
      break;
    } 
    CheckMenuButton();
    analogWrite(G, i);
    delay(10);
  }
  ButtonPressed = false;
}

void fade() {
  int r, g, b;
 
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    if(ButtonPressed){
      break;
    }
    CheckMenuButton();
    analogWrite(R, r);
    delay(50);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    if(ButtonPressed){
      break;
    }
    CheckMenuButton();
    analogWrite(B, b);
    delay(50);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    if(ButtonPressed){
      break;
    }
    CheckMenuButton();
    analogWrite(G, g);
    delay(50);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) {
    if(ButtonPressed){
      break;
    } 
    CheckMenuButton();
    analogWrite(R, r);
    delay(50);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) {
    if(ButtonPressed){
      break;
    } 
    CheckMenuButton();
    analogWrite(B, b);
    delay(50);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    if(ButtonPressed){
      break;
    }
    CheckMenuButton();
    analogWrite(G, g);
    delay(50);
  } 
  ButtonPressed = false;
} 

void Techno(){
  while (!ButtonPressed){
    if (!ButtonPressed){
      CheckMenuButton();
      analogWrite(R, 0);
      analogWrite(G, 255);
      delay(100);
    }
    if (!ButtonPressed){
      analogWrite(G, 0);
      analogWrite(B, 255);
      delay(100);
    }
    if (!ButtonPressed){
      CheckMenuButton();  
      analogWrite(B, 0);
      analogWrite(R, 255);
      delay(100);
    }
  }
  ButtonPressed = false;
}

void CheckMenuButton(){
  //Serial.println(digitalRead(MenuPin));
  if (digitalRead(MenuPin) == 1 && MenuVal <= ModeVal){
    FlashForRecognize();
    ButtonPressed = true;
    MenuVal++;
  } 
  if(digitalRead(MenuPin) == 1 && MenuVal > ModeVal){
    FlashForRecognize();
    ButtonPressed = true;
    MenuVal = 0;
  }
  Serial.print(MenuVal);
  Serial.println(ButtonPressed);
}


void DelayForNextClick(){
  delay(200);
}

void FlashForRecognize(){
  
  for (int i = 0; i < 2; i++){
    analogWrite(R, 255);
    analogWrite(G, 255);
    analogWrite(B, 255);
    delay (50);
    analogWrite(R, 0);
    analogWrite(G, 0);
    analogWrite(B, 0);
    delay(50);
  }
}

void TechnoRandColor(){
   while (!ButtonPressed){
    if (!ButtonPressed){
      int randR = random(0, 256);
      int randG = random(0, 256);
      int randB = random(0, 256);

      CheckMenuButton();
      analogWrite(R,randR);
      analogWrite(G,randG);
      analogWrite(B,randB);
      delay(100);
    }  
  }
  ButtonPressed = false;  
}