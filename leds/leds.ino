int firstLedPin = 2;
int lastLedPin = 11;

void setup() {
  // put your setup code here, to run once:
  for (int pin = firstLedPin; pin <= lastLedPin; ++pin){
    pinMode(pin, OUTPUT);
  }
}

void loop() {

  int tempLastLedPin = lastLedPin;
  for(int tempLastLedPin = lastLedPin; tempLastLedPin >= 0; tempLastLedPin--){
    for(int pin = firstLedPin; pin <= tempLastLedPin; pin++){
  
      digitalWrite(pin, HIGH);
      delay(200);
      digitalWrite(pin, LOW);

      if(pin == tempLastLedPin){
        digitalWrite(pin, HIGH);
      }
    }
  }
  
  tempLastLedPin = lastLedPin;
  for(int tempLastLedPin = lastLedPin; tempLastLedPin >= 0; tempLastLedPin--){
    for(int pin = firstLedPin; pin <= tempLastLedPin; pin++){

      digitalWrite(pin, LOW);
      delay(200);
      digitalWrite(pin, HIGH);

      if(pin == tempLastLedPin){
        digitalWrite(pin, LOW);
      }
    }
  }
}