bool fwd;
bool pressed;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT); //red
  pinMode(12, OUTPUT); //green
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  fwd = true;
}

void loop() {

  if(fwd){
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
  }
  else{
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
  }
  if(!digitalRead(9)){
    if(!pressed) fwd=!fwd;
    pressed = true;
    delay(50);
  } else {
    pressed = false;
  }
  
  if(!digitalRead(2) && !digitalRead(4)){
    if(fwd){
      digitalWrite(11,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(10,LOW);
      digitalWrite(6,LOW);
    } else{
      digitalWrite(11,LOW);
      digitalWrite(5,LOW);
      digitalWrite(10,HIGH);
      digitalWrite(6,HIGH);
    }
  } 
  else if(!digitalRead(2)){
    if(fwd){
    digitalWrite(11,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(6,LOW);}
    else{
    digitalWrite(11,LOW);
    digitalWrite(5,LOW);
    digitalWrite(10,LOW);
    digitalWrite(6,HIGH);
    }
    
  }  
  else if(!digitalRead(4)){
    if(fwd){
    digitalWrite(11,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(10,LOW);
    digitalWrite(6,LOW);
  }
  else{
    digitalWrite(11,LOW);
    digitalWrite(5,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(6,LOW);
  }
  }  else {
    
    digitalWrite(11,LOW);
    digitalWrite(5,LOW);
    digitalWrite(10,LOW);
    digitalWrite(6,LOW);
  } 

  
       
}
