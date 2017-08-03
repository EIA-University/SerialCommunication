//Receiver Code
//ACM0


char str[4];

void setup() {
 
  Serial.begin(9600);
  
}

void loop() {
  int i=0;
  if (Serial.available()) { 
    delay(50);
    while ((Serial.available()) && (i < 5)) {
      str[i++] = Serial.read(); 
    }
    str[i++] = '\0';
  }

  if (i > 0) {

    Serial.println(str);
  }
}
