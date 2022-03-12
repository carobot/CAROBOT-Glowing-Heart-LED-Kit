// declare and initialize an array to save all pin number
#if defined(__AVR_ATtiny85__) // for using ATtiny85 at 1MHz
int pins[4] = {0, 1, 2, 4};
#else
int pins[4] = {2, 3, 4, 5};
#endif

void setup() {
  // using a loop to set all the pins as output
  for (int i = 0; i < 4; ++i) {
    pinMode(pins[i], OUTPUT);
  }

  // code to test all LEDs
  // using bit shift and bit operation to determine which pin is HIGH/LOW
  int j = 1;
  while (j < 15) {
    for (int i = 0; i < 4; i++) {
      if (j >> i & 1) {
        digitalWrite(pins[i], HIGH);
      } else {
        digitalWrite(pins[i], LOW);
      }
    }
    delay(100);
    j = j << 1;
  }

  // turn all LED off
  for (int i = 0; i < 4; ++i) {
    digitalWrite(pins[i], LOW);
  }
  delay(1000);
  
}

void loop() {
  // since the circuit have 4 pin in a matrix onfiguration to control the LEDs
  // this means there are a total of 14 configuration
  // we'll use 1 to 14 or 0b0001 to 0b1110 to control the LEDs

  // declare static variable instead because we need to keep the value between loops
  static int last_mode;
  static int mode;
  
  // generate a random number from 1 to 14 that doesn't repeat from the last loop
  do {
    mode = random(1, 14);
  } while (mode == last_mode);
  last_mode = mode;

  // using bit shift and bit operation to determine which pin is ON/OFF
  // loop through i for each pin
  for (int i = 0; i < 4; ++i) {
    // read each bit of "mode" to determine HIGH/LOW of each pin
    // ie. if mode = 0b0110
    // 0110 >> 1 = 0110 & 1 = 0, pin 1 LOW
    // 0110 >> 2 = 011 & 1 = 1, pin 2 HIGH
    // 0110 >> 3 = 01 & 1 = 1, pin 3 HIGH
    // 0110 >> 4 = 0 & 1 = 0, pin 4 LOW
    // (&) is logic AND
    
    if (mode >> i & 1) {
      digitalWrite(pins[i], HIGH);
    } else {
      digitalWrite(pins[i], LOW);
    }
  }
  delay(100); // delay so we can see the flash

}
