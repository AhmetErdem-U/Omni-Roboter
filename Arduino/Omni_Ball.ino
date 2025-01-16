// Pin-Zuweisung für das RAMPS 1.4 Shield Board

#define stepPinX 54  // STEP Pin für X-Achse (Arduino Pin D2)
#define dirPinX 55   // DIR Pin für X-Achse (Arduino Pin D3)
#define stepPinY 60  // STEP Pin für Y-Achse (Arduino Pin D26)
#define dirPinY 61   // DIR Pin für Y-Achse (Arduino Pin D28)
#define stepPinZ 46  // STEP Pin für Z-Achse (Arduino Pin D36)
#define dirPinZ 48   // DIR Pin für Z-Achse (Arduino Pin D34)
#define stepPinE 26  // STEP Pin für E-Achse (Arduino Pin D36)
#define dirPinE 28   // DIR Pin für E-Achse (Arduino Pin D34)

// Bluetooth HC-05
#define bluetoothRX 0  // RX Pin des Arduino Mega (Arduino Pin RX0)
#define bluetoothTX 1  // TX Pin des Arduino Mega (Arduino Pin TX0)

// Schrittweite (Anzahl Schritte pro Umdrehung)
const int stepsPerRevolution = 200;  // Beispielwert, anpassen je nach Motor

void setup() {
  // STEP- und DIR-Pins als Ausgang definieren
  pinMode(stepPinX, OUTPUT);
  pinMode(dirPinX, OUTPUT);
  pinMode(stepPinY, OUTPUT);
  pinMode(dirPinY, OUTPUT);
  pinMode(stepPinZ, OUTPUT);
  pinMode(dirPinZ, OUTPUT);
  pinMode(stepPinE, OUTPUT);
  pinMode(dirPinE, OUTPUT);

  // Initialisierung der seriellen Kommunikation für das Bluetooth-Modul
  Serial.begin(9600);  // Start der seriellen Kommunikation bei 9600 Baud
}

// Funktion zur Steuerung eines Motors
void moveMotor(int stepPin, int dirPin, int steps, bool direction) {
  digitalWrite(dirPin, direction);  // Setze die Drehrichtung
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);  // Bestimmt die Geschwindigkeit
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}

// Vorwärtsbewegung
void forward() {
  moveMotor(stepPinX, dirPinX, stepsPerRevolution, true);
  moveMotor(stepPinY, dirPinY, stepsPerRevolution, true);
  moveMotor(stepPinZ, dirPinZ, stepsPerRevolution, true);
  moveMotor(stepPinE, dirPinE, stepsPerRevolution, true);
}
// Rückwärtsbewegung
void backward() {
  moveMotor(stepPinX, dirPinX, stepsPerRevolution, false);
  moveMotor(stepPinY, dirPinY, stepsPerRevolution, false);
  moveMotor(stepPinZ, dirPinZ, stepsPerRevolution, false);
  moveMotor(stepPinE, dirPinE, stepsPerRevolution, false);
}
// Linksbewegung
void left() {
  moveMotor(stepPinX, dirPinX, stepsPerRevolution, false);
  moveMotor(stepPinY, dirPinY, stepsPerRevolution, true);
  moveMotor(stepPinZ, dirPinZ, stepsPerRevolution, false);
  moveMotor(stepPinE, dirPinE, stepsPerRevolution, true);
}
// Rechtsbewegung
void right() {
  moveMotor(stepPinX, dirPinX, stepsPerRevolution, true);
  moveMotor(stepPinY, dirPinY, stepsPerRevolution, false);
  moveMotor(stepPinZ, dirPinZ, stepsPerRevolution, true);
  moveMotor(stepPinE, dirPinE, stepsPerRevolution, false);
}
// Drehung im Uhrzeigersinn (CW)
void rotateCW() {
  moveMotor(stepPinX, dirPinX, stepsPerRevolution, true);
  moveMotor(stepPinY, dirPinY, stepsPerRevolution, true);
  moveMotor(stepPinZ, dirPinZ, stepsPerRevolution, false);
  moveMotor(stepPinE, dirPinE, stepsPerRevolution, false);
}
// Drehung gegen den Uhrzeigersinn (CCW)
void rotateCCW() {
  moveMotor(stepPinX, dirPinX, stepsPerRevolution, false);
  moveMotor(stepPinY, dirPinY, stepsPerRevolution, false);
  moveMotor(stepPinZ, dirPinZ, stepsPerRevolution, true);
  moveMotor(stepPinE, dirPinE, stepsPerRevolution, true);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();  // Lese den empfangenen Befehl

    switch (command) {
      case 'F':  // Vorwärts
        forward();
        break;
      case 'B':  // Rückwärts
        backward();
        break;
      case 'L':  // Links
        left();
        break;
      case 'R':  // Rechts
        right();
        break;
      case 'C':  // Drehung im Uhrzeigersinn (CW)
        rotateCW();
        break;
      case 'A':  // Drehung gegen den Uhrzeigersinn (CCW)
        rotateCCW();
        break;
    }
  }
}
