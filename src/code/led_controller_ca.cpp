#include <LedControl.h>

// Pins for the LED matrix
const int DIN_PIN = 12;
const int CLK_PIN = 11;
const int CS_PIN = 10;
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// Function to apply a CA rule to generate the next row
uint8_t applyCARule(uint8_t currentRow, std::bitset<8> ruleSet) {
    uint8_t nextRow = 0;
    for (int i = 0; i < 8; ++i) {
        int left = (i == 0) ? (currentRow & 0x01) << 7 : (currentRow >> (i - 1)) & 0x01;
        int center = (currentRow >> i) & 0x01;
        int right = (i == 7) ? (currentRow >> 7) & 0x01 : (currentRow >> (i + 1)) & 0x01;
        
        int neighborhood = (left << 2) | (center << 1) | right;
        nextRow |= (ruleSet[neighborhood] << i);
    }
    return nextRow;
}

// Function to display the CA pattern on the LED matrix
void displayCAPattern(uint8_t pattern[8]) {
    for (int row = 0; row < 8; ++row) {
        lc.setRow(0, row, pattern[row]);
    }
}

// Function to generate the CA pattern based on a selected rule
void generateCAPattern(uint8_t pattern[8], int caRule) {
    std::bitset<8> ruleSet(caRule);
    pattern[0] = 0b00011000; // Initial state (can be modified)
    
    for (int row = 1; row < 8; ++row) {
        pattern[row] = applyCARule(pattern[row - 1], ruleSet);
    }
}

void setup() {
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);
    
    // Example: Generate and display CA Rule 30
    uint8_t pattern[8];
    int selectedRule = 30;  // You can change this to any amphichiral CA rule
    generateCAPattern(pattern, selectedRule);
    displayCAPattern(pattern);
}

void loop() {
    // The LED matrix will continue to display the pattern
}
