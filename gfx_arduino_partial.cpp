#include <LedControl.h>

// Pin connections for MAX7219
const int DATA_IN = 11; // DIN pin of MAX7219
const int CLK = 13;     // CLK pin of MAX7219
const int LOAD = 10;    // CS pin of MAX7219

// Create a LedControl object
LedControl lc = LedControl(DATA_IN, CLK, LOAD, 1);

// Define the mushroom cloud bitmap (8x8)
byte mushroomCloud[8] = {
  B00111100,  //   ****  
  B01111110,  //  ****** 
  B11111111,  // ********
  B11111111,  // ********
  B01111110,  //  ****** 
  B00111100,  //   ****  
  B00111100,  //   ****  
  B00011000   //    **   
};

// Function to display a bitmap on the LED matrix
void displayBitmap(byte bitmap[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, bitmap[row]);
  }
}

void setup() {
  lc.shutdown(0, false);       // Wake up MAX7219
  lc.setIntensity(0, 8);       // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);          // Clear display register
}

void loop() {
  // Example: Check if today is a significant Mayan date
  if (isSignificantMayanDate()) {
    displayBitmap(mushroomCloud);
    delay(5000);  // Display for 5 seconds
  }

  lc.clearDisplay(0);  // Clear the matrix after displaying
  delay(1000);         // Short delay before re-checking the date
}

bool isSignificantMayanDate() {
  // Implement your date-checking logic here
  // For now, we'll just return true for demonstration
  return true;
}

void loop() {
  // Display the mushroom cloud on significant Mayan dates
  // (For demonstration purposes, we'll just display it in the loop)
  displayBitmap(mushroomCloud);
  delay(5000);  // Keep the image displayed for 5 seconds

  lc.clearDisplay(0);  // Clear the matrix
  delay(1000);         // Wait before displaying it again
}
