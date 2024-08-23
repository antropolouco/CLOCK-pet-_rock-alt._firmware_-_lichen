/// a nice compact lil dispay driver to make an 8x8 led  matrix count in mayan

#include <LedControl.h>

// Pin connections for MAX7219
const int DATA_IN = 11; // DIN pin of MAX7219
const int CLK = 13;     // CLK pin of MAX7219
const int LOAD = 10;    // CS pin of MAX7219

// Create a LedControl object
LedControl lc = LedControl(DATA_IN, CLK, LOAD, 1); // Only one MAX7219 is connected

// Function to clear the matrix
void clearMatrix() {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, 0);
  }
}

// Function to set a row with a pattern
void setRow(int row, byte pattern) {
  lc.setRow(0, row, pattern);
}

// Function to display a Mayan number
void displayMayanNumber(int number) {
  clearMatrix();

  if (number == 0) {
    // Display the shell symbol for 0 (approximation)
    setRow(2, B00111100);
    setRow(3, B01100110);
    setRow(4, B01100110);
    setRow(5, B00111100);
  } else {
    int bars = number / 5;
    int dots = number % 5;

    // Display bars (5 units each)
    for (int i = 0; i < bars; i++) {
      setRow(7 - i, B11111000); // 5 LEDs in a row for each bar
    }

    // Display dots (1 unit each)
    for (int i = 0; i < dots; i++) {
      setRow(7 - bars - i, B10000000); // 1 LED for each dot
    }
  }
}

void setup() {
  lc.shutdown(0, false);       // Wake up MAX7219
  lc.setIntensity(0, 8);       // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);          // Clear display register
}

void loop() {
  // Test: Display numbers from 0 to 19
  for (int i = 0; i < 20; i++) {
    displayMayanNumber(i);
    delay(2000);  // Wait 2 seconds between each number
  }
}
