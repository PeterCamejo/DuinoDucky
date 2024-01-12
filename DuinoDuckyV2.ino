#include <Keyboard.h>
  
  //button pins
  const int button0Pin = 0;  //detonate payload
  const int button1Pin = 11; //cycle current payload back by one
  const int button2Pin = 12; //cycle forward payload forward by one

  //status light pins
  const int statusPin[10] = {1,2,3,4,5,6,7,8,9,10};
  
  //button states
  int button0State = 0; //detonate payload button current state
  int button1State = 0; //cycle payload back button current state
  int button2State = 0; //cycle payload forward button current state

  //tracking previous button states
  int lastButton0State = HIGH; //detonate payload button previous state
  int lastButton1State = HIGH; //cycle payload back button previous state
  int lastButton2State = HIGH; //cycle payload forward button previous state

  //button debounce variables
  unsigned long lastDebounce0Time = 0; 
  unsigned long lastDebounce1Time = 0;
  unsigned long lastDebounce2Time = 0;
  unsigned long debounceDelay = 50;

  int currentPayload = 0;  //tracks which payload is active;

  bool payloadFired = false;   //tracks when payload as been detonated. Used to prevent payload detonating a second time when button is depressed/raised
  bool payloadCycled = false; //tracks when payload selection has changed. Used to prevent payload selection from triggering twice when cycle forward/back buttons are depressed/raised

void setup() {

  pinMode(button0Pin, OUTPUT);
  pinMode(button1Pin, OUTPUT);
  pinMode(button2Pin, OUTPUT);
  for(int i = 0; i < 10; i++){
    pinMode(statusPin[i], OUTPUT);
  }

  digitalWrite(statusPin[0], HIGH);
  Serial.begin(9600);

}

void loop() {

  setCurrentPayload(); //activated when pressing cycle payload buttons
  detonatePayload(); //activated when pressing detonate payload button
}

//payload detonation function
void detonatePayload(){
  int readButton0State = digitalRead(button0Pin);

  //reset debounce timer when switch changes
  if(readButton0State != lastButton0State){
    lastDebounce0Time = millis();
  }

  if((millis() - lastDebounce0Time) > debounceDelay){
    if(readButton0State != button0State){
      button0State = readButton0State;
      if(payloadFired != true){
        /***** Payloads Go Here *****/
        switch(currentPayload){
          //Payload 0 slot
          case 0 : rickRoll();
                   break;
          //Payload 1 slot
          case 1 : notepadMessage("Heh. Nothing personal, kid.");
                   break;
          //Payload 2 slot
          case 2 : savedNotepadMessage("Gotcha!!" , "Fun Message For you!");
                   break;
          //Payload 3 slot
          case 3 : break;
          //Payload 4 slot
          case 4 : break;
          //Payload 5 slot
          case 5 : break;
          //Payload 6 slot
          case 6 : break;
          //Payload 7 slot
          case 7 : break;
          //Payload 8 slot
          case 8 : break;
          //Payload 9 slot
          case 9 : break;
          default: //do nothing
                   break;
        }
        payloadFired = true;
      }else{
        payloadFired = false;
      }
    }
  }

  lastButton0State = readButton0State;
}

/***** Payloads List *****/

/*** Windows Payloads ***/

//Windows
//Opens the Rick Roll youtube video, starts the video, and puts the video into fullscreen
void rickRoll(){
  Keyboard.begin();

  delay(100);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('d');
  Keyboard.releaseAll();

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(200);

  Keyboard.press(KEY_BACKSPACE);

  Keyboard.print("https://youtu.be/dQw4w9WgXcQ");

  typeKey(KEY_RETURN);

  delay(500);

  Keyboard.print("k");

  delay(4000);

  Keyboard.print("f");

}

//Windows
//Opens notepad.exe and types out the message[] param
void notepadMessage(char message[]){
  Keyboard.begin();

  delay(100);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('d');
  Keyboard.releaseAll();

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(200);

  Keyboard.press(KEY_BACKSPACE);

  Keyboard.print("notepad.exe");

  typeKey(KEY_RETURN);

  delay(1000);

  Keyboard.print(message);
}

//Windows
//Opens notepad.exe, types out the message[] param, then saves the file with the filename[] param as the file name
//Does not choose a directory to save the file to. File is saved in whatever directory comes up first when pressing Ctrl+S
void savedNotepadMessage(char message[], char filename[]){
  Keyboard.begin();

  delay(100);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('d');
  Keyboard.releaseAll();

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(200);

  Keyboard.press(KEY_BACKSPACE);

  Keyboard.print("notepad.exe");

  typeKey(KEY_RETURN);

  delay(200);

  Keyboard.print(message);

  delay(200);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('s');
  Keyboard.releaseAll();

  Keyboard.print(filename);

  typeKey(KEY_RETURN);

  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F4);
  Keyboard.releaseAll();
}

//used to make ENTER/RETURN keypresses work better in payloads
void typeKey(int key){
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

//functions that set the status lights
void setCurrentPayload(){
  cyclePayloadBack(); //triggers when button 1 is pressed to cycle current payload back one mode
  cyclePayloadForward(); //triggers when button 2 is pressed to cycle current payload forward one mode
}

void cyclePayloadBack(){
  int readButton1State = digitalRead(button1Pin);

  //reset debounce timer when switch changes
  if(readButton1State != lastButton1State){
    lastDebounce1Time = millis();
  }

  if((millis() - lastDebounce1Time) > debounceDelay){
    if(readButton1State != button1State){
      button1State = readButton1State;
      if(payloadCycled != true){
        if(currentPayload-1 < 0 ){
          currentPayload = 9;
        }else{
          currentPayload--;
        }
        setStatusLightOn(currentPayload);
        payloadCycled = true;
      }else{
        payloadCycled = false;
      }
    }
  }

  lastButton1State = readButton1State;
}

void cyclePayloadForward(){
  int readButton2State = digitalRead(button2Pin);

  //reset debounce timer when switch changes
  if(readButton2State != lastButton2State){
    lastDebounce2Time = millis();
  }

  if((millis() - lastDebounce2Time) > debounceDelay){
    if(readButton2State != button2State){
      button2State = readButton2State;
      if(payloadCycled != true){
        if(currentPayload+1 > 9 ){
          currentPayload = 0;
        }else{
          currentPayload++;
        }
        setStatusLightOn(currentPayload);
        payloadCycled = true;
      }else{
        payloadCycled = false;
      }
    }
  }

  lastButton2State = readButton2State;
}

void setStatusLightOn(int pin){
  for(int i = 0; i < 10; i++){
    digitalWrite(statusPin[i], LOW);
  }

  digitalWrite(statusPin[pin], HIGH);
}

