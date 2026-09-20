int ldrPin = A0; 

void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);
}

void loop() {
  int nilaiLDR = analogRead(ldrPin);

  Serial.print("Nilai sensor LDR: ");
  Serial.println(nilaiLDR);
  
  delay(500);
}