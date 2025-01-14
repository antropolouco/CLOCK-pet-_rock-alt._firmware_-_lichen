#include <Wire.h>
#include <Adafruit_MCP4728.h>

// Assuming 8 MCP4728 DACs, each with 4 channels (total 64 channels)
Adafruit_MCP4728 dacArray[8];

// CA grid pattern (8x8)
uint8_t caPattern[8];

// DAC voltage conversion function
float voltageToDACValue(float voltage) {
    // Assuming 12-bit DAC (0-4095)
    // 10V corresponds to the maximum value of the DAC
    return (voltage / 10.0) * 4095;
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

// Function to output the DAC voltages for each grid square
void outputGridVoltages(uint8_t pattern[8]) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            // Determine which DAC and channel to use
            int dacIndex = (y * 8 + x) / 4;
            int channel = (y * 8 + x) % 4;
            
            // Map grid state to voltage
            float voltage = (pattern[y] & (1 << x)) ? 10.0 : 0.0;
            
            // Set the DAC output
            dacArray[dacIndex].setChannelValue(channel, voltageToDACValue(voltage));
        }
    }
}

void setup() {
    // Initialize all DACs
    for (int i = 0; i < 8; ++i) {
        dacArray[i].begin(i + 0x60);  // Assuming DAC addresses start at 0x60 and increment by 1
    }

    // Generate CA pattern (example: Rule 30)
    generateCAPattern(caPattern, 30);

    // Output the CA pattern to the grid
    outputGridVoltages(caPattern);
}

void loop() {
    // No need for continuous loop unless the CA pattern updates in real-time
}
