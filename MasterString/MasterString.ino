#include <LiquidCrystal.h>
#include <Keypad.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const byte ROWS = 2; //four rows
const byte COLS = 2; //three columns
char keys[ROWS][COLS] = {
  {'A', 'B',},
  {'D', 'E',}
};
byte rowPins[ROWS] = {9, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int button = 13;
int sendButton = 6;
char str[5];
int lecturaPermiso = 0,lecturaEnter = 0 ;
int i = 0;
static String mensaje = "";

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  lcd.begin(16, 2);
  lcd.print("Hola!");
}
void builtWord(String msg){
  char key = keypad.getKey();  
  if (key != NO_KEY){
    mensaje = msg + key;
    lcd.print(key);
    }
  }

  
void enviar() {
  lcd.clear();
  //Serial.print(mensaje);
  Serial.print(mensaje);
  lcd.print(mensaje);
  mensaje = "";
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
  lecturaPermiso = digitalRead(button);
  lecturaEnter = digitalRead(sendButton);
  
  
  /*Serial.print("Botón permiso: ");
  Serial.println(lecturaPermiso);
  Serial.print("Botón Enter: ");
  Serial.println(lecturaEnter);
  */
  delay(200);
  
  
  if (lecturaPermiso == LOW && lecturaEnter == HIGH) { //envío
    enviar();
    delay(500);
  } else if(lecturaPermiso == HIGH) { //leo
    recibir();
  }else 
    builtWord(mensaje);
  /*lectura = digitalRead(button);
  Serial.print("Botón: ");
  Serial.println(lectura);
  delay(200);

  if (lectura == LOW) { //envío
    enviar();
  } else { //leo
    recibir();
  }*/


  /*if ( lecturaEnter == HIGH){
      lcd.clear();
      delay(50);
      lcd.print(mensaje);
    }*/
}
