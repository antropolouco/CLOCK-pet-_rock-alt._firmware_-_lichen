#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <LedControl.h>

// DAC objects (Assuming you're using Adafruit MCP4725 DACs)
Adafruit_MCP4725 dacX;
Adafruit_MCP4725 dacY;

// Pins for the LED matrix
const int DIN_PIN = 12;
const int CLK_PIN = 11;
const int CS_PIN = 10;
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// 8x8 CA grid
uint8_t caPattern[8];

// Clock pin (e.g., an external clock source)
const int CLOCK_PIN = 2;

// DAC voltage conversion
float voltageToDACValue(float voltage) {
    // Assuming 10-bit DAC (0-1023)
    // 10V corresponds to the maximum value of the DAC
    return (voltage / 10.0) * 1023;
}

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

// Function to generate the CA pattern based on a selected rule
void generateCAPattern(uint8_t pattern[8], int caRule) {
    std::bitset<8> ruleSet(caRule);
    pattern[0] = 0b00011000; // Initial state (can be modified)
    
    for (int row = 1; row < 8; ++row) {
        pattern[row] = applyCARule(pattern[row - 1], ruleSet);
    }
}

// Function to output the DAC voltages for a given grid coordinate
void outputDACVoltages(int x, int y, bool state) {
    float voltageX = (x / 7.0) * 10.0;  // Map X coordinate to 0-10V
    float voltageY = (y / 7.0) * 10.0;  // Map Y coordinate to 0-10V

    if (!state) {
        voltageX = 0.0;
        voltageY = 0.0;
    }

    dacX.setVoltage(voltageToDACValue(voltageX), false);
    dacY.setVoltage(voltageToDACValue(voltageY), false);
}

void setup() {
    // Initialize DACs
    dacX.begin(0x62);  // I2C address of the first DAC
    dacY.begin(0x63);  // I2C address of the second DAC

    // Initialize LED matrix
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);
    
    // Generate CA pattern (example: Rule 30)
    generateCAPattern(caPattern, 30);

    // Setup clock input pin
    pinMode(CLOCK_PIN, INPUT);
}

void loop() {
    // Wait for a clock pulse
    if (digitalRead(CLOCK_PIN) == HIGH) {
        static int currentIndex = 0;

        // Compute X and Y coordinates
        int x = currentIndex % 8;
        int y = currentIndex / 8;

        // Get the state of the current grid square
        bool state = caPattern[y] & (1 << x);

        // Output the DAC voltages
        outputDACVoltages(x, y, state);

        // Update the LED matrix display
        lc.setRow(0, y, caPattern[y]);

        // Move to the next grid square
        currentIndex++;
        if (currentIndex >= 64) {
            currentIndex = 0;  // Loop back to the beginning
        }

        // Wait for the clock to go low before continuing
        while (digitalRead(CLOCK_PIN) == HIGH);
    }
}
