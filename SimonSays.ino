//input pins for corresponding buttons
const int buttonPinB = 3;
const int buttonPinG = 2;
const int buttonPinR = 1;
const int buttonPinY = 0;

//output pins for lights
int ledPinB = 13;
int ledPinG = 12;
int ledPinR = 11;
int ledPinY = 10;

//output pins for buzzers
int buzzPin1 = 8;
int buzzPin2 = 7;

//frequencies corresponding to each light
int bFreq = 392;// high g
int gFreq = 247;//b
int rFreq = 196; //g
int yFreq = 294;//d
int iFreq = 587; //frequency when input is required
int correctFreq = 784; //frequency for inputting correct sequence

int buttonStateR = 0;
int buttonStateB = 0;
int buttonStateG = 0;
int buttonStateY = 0;
 
const int length = 11; //max length of sequence
int sequence[length]; //initializes array to hold sequence
int n = 0; 
int input = 0; //input from buttons
int count = 0;
int t = 40; //acceleration of light speed

int check = 0;
int correct = 1; //flag for whether the user has lost

//initial sound
void openingTune(){
  tone(buzzPin1, 622);
  delay(250);
  tone(buzzPin1, 233);
  delay(250);
  noTone(buzzPin1);
  tone(buzzPin1, 208);
  delay(250);
  tone(buzzPin1, 622);
  delay(250);
  tone(buzzPin1, 233);
  delay(250);
  noTone(buzzPin1);
  delay(250);
}

//final sound
void closingTune(){
  /*
   * g# d# low g# low a#
   */
   tone(buzzPin1, 415);
   delay(200);
   tone(buzzPin1, 311);
   delay(200);
   tone(buzzPin1, 208);
   delay(200);
   tone(buzzPin1, 233);
   delay(600);
   noTone(buzzPin1);
   
}

//initializes lights and buttons
void setup() {
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(buttonPinR, INPUT);
  pinMode(buttonPinB, INPUT);
  pinMode(buttonPinG, INPUT);
  pinMode(buttonPinY, INPUT);

  digitalWrite(ledPinR, LOW);
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinB, LOW);
  digitalWrite(ledPinY, LOW);

  openingTune(); 
  delay(1000);
  
  Serial.begin(9600);
  
  randomSeed(analogRead(0));

  //generate random sequence of numbers 1-4 to correspond with the pattern for the lights to flash in
  for (int i = 0; i<length; i++) {
    sequence[i] = random(1,5);
  }

}

//checks if the input is correct
int checkP(int input, int count){
  int flag = 1;
      if (input != sequence[count]){
         flag = 0;
      }
  return flag;
}

//main loop
void loop() {

  //reads input from buttons
  buttonStateR = digitalRead(buttonPinR);
  buttonStateB = digitalRead(buttonPinB);
  buttonStateG = digitalRead(buttonPinG);
  buttonStateY = digitalRead(buttonPinY);

  while (check == 0){
    for (int i = 0; i<length; i++) {
      
      digitalWrite(ledPinY, HIGH);
      digitalWrite(ledPinR, HIGH);
      digitalWrite(ledPinG, HIGH);
      digitalWrite(ledPinB, HIGH);
      tone(buzzPin1, correctFreq);
      delay(200);
        
      digitalWrite(ledPinY, LOW);
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinB, LOW);
      noTone(buzzPin1);
      delay(500);

      //outputs the first n elements of the pattern 
      while (n<=i){
        if (sequence[n] == 1){
          digitalWrite(ledPinY, HIGH);
          tone(buzzPin1, yFreq);
          delay(500 - t);
          digitalWrite(ledPinY, LOW);
          noTone(buzzPin1);
        }
        else if (sequence[n] == 2){
          digitalWrite(ledPinR, HIGH);
          tone(buzzPin1, rFreq);
          delay(500 - t);
          digitalWrite(ledPinR, LOW);
          noTone(buzzPin1);
        }
        else if (sequence[n] == 3){
          digitalWrite(ledPinG, HIGH);
          tone(buzzPin1, gFreq);
          delay(500 - t);
          digitalWrite(ledPinG, LOW);
          noTone(buzzPin1);
        }
        else if (sequence[n] == 4){
          digitalWrite(ledPinB, HIGH);
          tone(buzzPin1, bFreq);
          delay(500 - t);
          digitalWrite(ledPinB, LOW);
          noTone(buzzPin1);
        }
        delay(500);
        n++;
      } 

      digitalWrite(ledPinY, HIGH);
      digitalWrite(ledPinR, HIGH);
      digitalWrite(ledPinG, HIGH);
      digitalWrite(ledPinB, HIGH);
      tone(buzzPin1, iFreq);
      delay(600);
        
      digitalWrite(ledPinY, LOW);
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinB, LOW);
      noTone(buzzPin1);
    
      check = 1; //indicates that input from the user is required
      
      if (check == 1){
        unsigned long curtime = millis(); //gets the current time
    
         count = 0; //counts the number of times that the user pushes a button

         //gets user input 
         while ((count <= i)&&(millis() - curtime < 10000)){
 
                buttonStateR = digitalRead(buttonPinR);
                buttonStateB = digitalRead(buttonPinB);
                buttonStateG = digitalRead(buttonPinG);
                buttonStateY = digitalRead(buttonPinY);
              
               //turns on the corresponding light/buzzer when the user presses a button
               if (buttonStateY == LOW){
                 digitalWrite(ledPinY, HIGH);
                 tone(buzzPin1, yFreq);
                 correct = checkP(1, count);
                 count++;
                 delay(400);
                 digitalWrite(ledPinY, LOW);
                 noTone(buzzPin1);
                 curtime = millis();
               }
               
               else if (buttonStateR == LOW){
                 digitalWrite(ledPinR, HIGH);
                 tone(buzzPin1, rFreq);
                 correct = checkP(2, count);
                 count++;
                 delay(400);
                 digitalWrite(ledPinR, LOW);
                 noTone(buzzPin1);
                 curtime = millis();
               }
    
               else if (buttonStateG == LOW){
                 digitalWrite(ledPinG, HIGH);
                 tone(buzzPin1, gFreq);
                 correct = checkP(3, count);
                 count++;
                 delay(400);
                 digitalWrite(ledPinG, LOW);
                 noTone(buzzPin1);
                 curtime = millis();
               }
    
               
               else if (buttonStateB == LOW){
                 digitalWrite(ledPinB, HIGH);
                 tone(buzzPin1, bFreq);
                 correct = checkP(4, count);
                 count++;
                 delay(400);
                 digitalWrite(ledPinB, LOW);
                 noTone(buzzPin1);
                 curtime = millis();
               }
        }

        //ends the game if it has been more than 10 seconds since the user pressed a button
        if (millis() - curtime >= 10000){
          delay(100);
          correct = 0;
        }
        
        delay(400);

        //run when the user has lost
        while (correct == 0){
          //flashes the lights the number of times the user inputted the pattern correctly
          for (int j = 0; j<i; j++){
            digitalWrite(ledPinY, HIGH);
            digitalWrite(ledPinR, HIGH);
            digitalWrite(ledPinG, HIGH);
            digitalWrite(ledPinB, HIGH);
            delay(300);
            digitalWrite(ledPinY, LOW);
            digitalWrite(ledPinR, LOW);
            digitalWrite(ledPinG, LOW);
            digitalWrite(ledPinB, LOW);
            delay(500);
          }

          int m = 0;

          //displays the correct pattern
          for (int k = 0; k<i+1; k++){
              if (sequence[k] == 1){
                digitalWrite(ledPinY, HIGH);
                delay(500 - t);
                digitalWrite(ledPinY, LOW);
              }
              else if (sequence[k] == 2){
                digitalWrite(ledPinR, HIGH);
                delay(500 - t);
                digitalWrite(ledPinR, LOW);
              }
              else if (sequence[k] == 3){
                digitalWrite(ledPinG, HIGH);
                delay(500 - t);
                digitalWrite(ledPinG, LOW);
              }
              else if (sequence[k] == 4){
                digitalWrite(ledPinB, HIGH);
                delay(500 - t);
                digitalWrite(ledPinB, LOW);
              }
              delay(500);
          }
            
          digitalWrite(ledPinY, HIGH);
          digitalWrite(ledPinR, HIGH);
          digitalWrite(ledPinG, HIGH);
          digitalWrite(ledPinB, HIGH);

          closingTune();
          digitalWrite(ledPinY, LOW);
          digitalWrite(ledPinR, LOW);
          digitalWrite(ledPinG, LOW);
          digitalWrite(ledPinB, LOW);
                      
          while (!correct){
          }
        }
    
    }

    n = 0;
    t += 25;

    digitalWrite(ledPinY, LOW);
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinB, LOW);
    }

    //RAVE when the user wins
    for (int i = 0; i<10; i++){

      digitalWrite(ledPinB, HIGH);
      tone(buzzPin1, 440);
      delay(50);
      digitalWrite(ledPinB, LOW);
      digitalWrite(ledPinG, HIGH);
      tone(buzzPin1, 392);
      delay(50);
      digitalWrite(ledPinG, LOW);
      digitalWrite(ledPinR, HIGH);
      tone(buzzPin1, 349);
      delay(50);
      digitalWrite(ledPinR, LOW);
      digitalWrite(ledPinY, HIGH);
      tone(buzzPin1, 262);
      delay(50);
      digitalWrite(ledPinY, LOW);
    }

    closingTune();            
    while (!correct){
    }
  }
}
