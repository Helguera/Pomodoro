/*
 * ---------------------- POMODORO ----------------------
 * 
 * Made by Javier Helguera (javier@javierhelguera.com)
 * Source code and rest of files: https://github.com/helguera/pomodoro
 * 20/01/2019
 */


//--- EDIT THIS CODE TO ADJUST IT TO YOUR NEEDS ---
int work = 1500;      //25 minutes
int sortbreak = 300;  //5 minutes
int longbreak = 900;  //15 minutes
int myloops = 4;      //Number of loops until long break
//-------------------------------------------------------

int seconds;
const int LED = 11;

void setup() {
  Serial.begin(9600);    //serial port
  
  pinMode(4, OUTPUT);   //Vibrator 
  pinMode(13, OUTPUT);  //Vibrator
  pinMode(LED, OUTPUT); //Led


}

void loop() {
  
  myloops++;
  for (int loops=1; loops<myloops; loops++){  //times until long break
    
    fade(5, 2);
    initial();

    workTime();

    vibrate(loops, 400, 400);
    if(loops!=myloops){
      sortBreak();
    }
  }

  longBreak();
  
}

//------------------------------------------------------
void initial(){
  vibrate(4, 80, 80);
}

//------------------------------------------------------
/* 25 minutes working. LED is full brightness and not fading */
void workTime(){
  seconds=work; //25 minutes
  while(seconds>0){
    seconds--;
    delay(1000); //wait one second
  }
}

//------------------------------------------------------
/* 5 minutes break. LED is fading */
void sortBreak(){
  seconds=sortbreak;  //5 minutes
  while(seconds>0){
      for (int i = 0; i < 255; i++){ //if i is less than 255 then increase i with 1
        analogWrite(LED, i); //write the i value to pin 11
        delay(2); //wait 5 ms then do the for loop again
      }
      if(seconds!=1){
        for (int i = 255; i > 0; i--){ //descrease i with 1
          analogWrite(LED, i);
          delay(2);
        }
      }
    seconds--;
  }
}

//------------------------------------------------------
/* 15 minutes break after 4 loops. LED is 10% brightness and not fading */
void longBreak(){
  seconds = longbreak;  //15 minutes
  analogWrite(LED, 10);
  while(seconds>0){
    Serial.println(seconds);
    seconds--;
    delay(1000);
  }
}

//------------------------------------------------------
void vibrate(int times, int intensity, int mDelay){
  for (int i=0; i<times; i++){
    digitalWrite(4, HIGH);
    digitalWrite(13, HIGH);
    delay(intensity);
    digitalWrite(4, LOW);
    digitalWrite(13, LOW);
    delay(mDelay);
  }
}

//------------------------------------------------------
void fade(int times, int mDelay){
  for(int j=0; j<times; j++){
    for (int i = 0; i < 255; i++){ 
      analogWrite(LED, i); 
      delay(mDelay); 
    }
    if(j!=(times-1)){
      for (int i = 255; i > 0; i--){ 
        analogWrite(LED, i);
        delay(mDelay);
      }
    }
  }
}



