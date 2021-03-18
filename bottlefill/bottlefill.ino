/*
  MIT License
  
  Copyright (c) 2021 AdamMW
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  End

  bottlefill
  Program for a 7 head bottle filling machine.
  MCU: Ardiuno Nano
  ------------ Change Log -------------
  -- AMW 202120318 -- Added some inline comments, Added a proper licence, Slight reformatting for readablity.
  --
  -------------------------------------
*/

  // Set a global threshold value to close water solenoids.
int threshold = 850; // Typical values from 5/8" spaced water shorted pins on analog inputs seems to be around 650(~1000 open circut)
                     
  // Variables to set and trigger water shutoff solenoids off and lockedout.
boolean Pin2Lockout = true;
boolean Pin3Lockout = true;
boolean Pin4Lockout = true;
boolean Pin5Lockout = true;
boolean Pin6Lockout = true; 
boolean Pin7Lockout = true;
boolean Pin8Lockout = true;

  // the setup function runs once on startup or reset.
void setup() {

  //initialize digital pins 11-12 as an input for start/stop buttons on wired pendant.
  pinMode(12, INPUT_PULLUP); //Start
  pinMode(11, INPUT_PULLUP); //Stop
  //initialize analog pins A0-A6 as inputs for water level pins. 
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  //initialize digital pins 2-8 as outputs for water shutoff solenoids.
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  
  //Serial.begin(9600); //Debug
}

// the loop function runs over and over again forever
void loop() {

  // First read the run/stop buttons on the wired pendant.
  if (digitalRead(12) == 0){TurnOnAllValves();} //Pin 12 == 0, LOW, Continuity
  if (digitalRead(11) == 0){ShutOffAllValves();} //Pin 11 == 0, LOW, Continuity
  
  // State machine
  if (analogRead(A0) < threshold && digitalRead(2) == 0 && Pin2Lockout == false){digitalWrite(2, HIGH); Pin2Lockout = true;}
  if (analogRead(A1) < threshold && digitalRead(3) == 0 && Pin3Lockout == false){digitalWrite(3, HIGH); Pin3Lockout = true;}
  if (analogRead(A2) < threshold && digitalRead(4) == 0 && Pin4Lockout == false){digitalWrite(4, HIGH); Pin4Lockout = true;}
  if (analogRead(A3) < threshold && digitalRead(5) == 0 && Pin5Lockout == false){digitalWrite(5, HIGH); Pin5Lockout = true;}
  if (analogRead(A4) < threshold && digitalRead(6) == 0 && Pin6Lockout == false){digitalWrite(6, HIGH); Pin6Lockout = true;}
  if (analogRead(A5) < threshold && digitalRead(7) == 0 && Pin7Lockout == false){digitalWrite(7, HIGH); Pin7Lockout = true;}
  if (analogRead(A6) < threshold && digitalRead(8) == 0 && Pin8Lockout == false){digitalWrite(8, HIGH); Pin8Lockout = true;}

/* Debug
  Serial.print(" PinA0 = ");
  Serial.print(analogRead(A0));
  Serial.print(" PinA1 = ");
  Serial.print(analogRead(A1));
  Serial.print(" PinA2 = ");
  Serial.print(analogRead(A2));
  Serial.print(" PinA3 = ");
  Serial.print(analogRead(A3));
  Serial.print(" PinA4 = ");
  Serial.print(analogRead(A4));
  Serial.print(" PinA5 = ");
  Serial.print(analogRead(A5));
  Serial.print(" PinA6 = ");
  Serial.print(analogRead(A6));
  Serial.print(" Pin2Lockout = ");
  Serial.print(Pin2Lockout);
  Serial.print(" StartButtonValue = ");
  Serial.print(digitalRead(12));
  Serial.print(" digitalReadPin2 = ");
  Serial.print(digitalRead(2));
  Serial.println();
*/
}

void TurnOnAllValves() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  Pin2Lockout = false;
  Pin3Lockout = false;
  Pin4Lockout = false;
  Pin5Lockout = false;
  Pin6Lockout = false;
  Pin7Lockout = false;
  Pin8Lockout = false;
}

void ShutOffAllValves() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  Pin2Lockout = true;
  Pin3Lockout = true;
  Pin4Lockout = true;
  Pin5Lockout = true;
  Pin6Lockout = true;
  Pin7Lockout = true;
  Pin8Lockout = true;
}



