#include <LiquidCrystal.h>
#include <Keypad.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 2; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'A', 'B', 'C'},
  {'D', 'E', 'F'}
};
byte rowPins[ROWS] = {9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int button = 13;
char str[5];
int lectura = 0;
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  lcd.begin(16, 2);
  lcd.print("Hola!");
}

void enviar() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    lcd.clear();
    //Serial.println(key);
    Serial.write(key);
    lcd.write(key);
  }
  delay(50);
}

void recibir() {
  i = 0;


  if (Serial.available()) { //Si el canal está libre
    delay(50);
    while ((Serial.available()) && (i < 5)) {
      str[i++] = Serial.read(); //Leo el array enviado
    }
    str[i++] = '\0';
  }

  if (i > 0) {
    lcd.clear(); //Se imprime en el serial y en la LCD
    lcd.setCursor(0, 0);
    lcd.write(str);
    Serial.println(str);
  }
}

void loop() {

  lectura = digitalRead(button);
  Serial.print("Botón: ");
  Serial.println(lectura);
  delay(200);

  if (lectura == LOW) { //envío
    enviar();
  } else { //leo
    recibir();
  }
}
