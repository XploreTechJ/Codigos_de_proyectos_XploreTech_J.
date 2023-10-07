
//*****PROGRAMADO POR: XploreTech J.*****//

//*****Siguenos en Facebook como XploreTech J.*****//

//Valores para el conteo ascendente:
int dtI = 1; // Coloca aqui el número con el cual quieres que inicie el conteo ascendente (puedes ser del 0 al 9)
int dtT = 5; // Coloca aqui el número con el cual quieres que termine el conteo

//Valores para el conteo descendente:
int dtF = 3; // Coloca aqui el número con el cual quieres que inicie el conteo descendente (puedes ser del 0 al 9)
int dtS = 0; // Coloca aqui el número con el cual quieres que termine el conteo

int switch1 = 5;
int switch2 = 6; 
int relay = 7;
int dataPin = 8;
int latchPin = 9;
int clockPin = 10;
int dt = 1000;
int i = 0;

byte numbers[] = {
  0b11111100, // 0 
  0b01100000, // 1 
  0b11011010, // 2 
  0b11110010, // 3 
  0b01100110, // 4 
  0b10110110, // 5 
  0b10111110, // 6 
  0b11100000, // 7 
  0b11111110, // 8 
  0b11110110  // 9 
};

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(relay, OUTPUT);

  turnOffDisplay();
  turnOffRelay();
}

void checkSwitch1() {
  if (digitalRead(switch1) == HIGH) {
    for (int count = dtI; count <= dtT; count++) {  
      displayNumber(count);
      delay(dt);
    }
    turnOffDisplay(); 
    digitalWrite(relay, HIGH); 
    delay(150);
    turnOffDisplay();
  }
}

void checkSwitch2() {
  if (digitalRead(switch2) == HIGH) {
    for (int count = dtF; count >= dtS; count--) { 
      displayNumber(count);
      delay(dt);
    }
    turnOffDisplay(); 
    turnOffRelay(); 
    delay(150);
    turnOffDisplay(); 
  }
}

void displayNumber(int num) {
  if (num >= 0 && num <= 9) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, numbers[num]);
    digitalWrite(latchPin, HIGH);
  }
}

void turnOffDisplay() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, 0b00000000); 
  digitalWrite(latchPin, HIGH);
}

void turnOffRelay() {
  digitalWrite(relay, LOW); 
}

void loop() {
  checkSwitch1();
  checkSwitch2();
}