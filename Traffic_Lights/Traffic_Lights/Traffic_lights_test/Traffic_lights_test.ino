  // Traffic lights timer definitions
// #define RED_SET_TIME 5000
// #define YELLOW_SET_TIME 2000
// #define GREEN_SET_TIME 5000

// Traffic lights colour definitions
#define LIGHT_1_RED 2
#define LIGHT_1_YELLOW 3
#define LIGHT_1_GREEN 4

// Light definitions
#define GREEN_LIGHT 0
#define YELLOW_LIGHT 1
#define RED_LIGHT 2

// Traffic light definitions

void setup() {
  // Traffic light serial setup
Serial.begin(9600);
  pinMode(LIGHT_1_RED, OUTPUT);
  pinMode(LIGHT_1_YELLOW, OUTPUT);
  pinMode(LIGHT_1_GREEN, OUTPUT);

  digitalWrite(LIGHT_1_GREEN, HIGH);
  digitalWrite(LIGHT_1_YELLOW, LOW);
  digitalWrite(LIGHT_1_RED, LOW);  
}

void loop() {
  // Traffic Light cycle
  digitalWrite(LIGHT_1_RED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LIGHT_1_RED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}
