#include <IRremote.h>
#include <Servo.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
Servo foodServo;
Servo hookServo;
int state = 5;
bool unleashed = false;
int decode(long hex);

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  hookServo.attach(2);
  hookServo.write(180);
  foodServo.attach(12);
  foodServo.write(90);
}

void loop(){
  
  if (irrecv.decode(&results)){
    Serial.println(results.value);
        if(decode(results.value) != 0){
          state = decode(results.value);
        }
        
        irrecv.resume();
  }

  if(state == 5){
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  } else if(state == 1){
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(1000);
    foodServo.write(180);
    delay(1700);
    foodServo.write(90);
    state = 5;
  } else if(state == 3){
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(1000);
    if(!unleashed){
      hookServo.write(0);
      unleashed = true;
      delay(500);
    } else {
      hookServo.write(180);
      unleashed = false;
      delay(500);
    }
    state = 5;
  } else if(state == 2){
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  } else if(state == 6){
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  } else if(state == 4){
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  } else if(state == 8){
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
  }
  delay(50);
}

int decode(long hex){
  switch(hex){
    case 16582903:
      return 1;
    case 16615543:
      return 2;
    case 16599223:
      return 3;
    case 16591063:
      return 4;
    case 16623703:
      return 5;
    case 16607383:
      return 6;
    case 16619623:
      return 8;
    default:
      return 0;
  }
}
