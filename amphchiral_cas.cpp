#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_map>

// List of amphichiral elementary CAs
std::vector<int> amphichiralCAs = {
    0, 1, 4, 5, 18, 19, 22, 23, 32, 33, 36, 37, 50, 51, 54, 55,
    72, 73, 76, 77, 90, 91, 94, 95, 104, 105, 108, 109, 122, 123,
    126, 127, 128, 129, 132, 133, 146, 147, 150, 151, 160, 161,
    164, 165, 178, 179, 182, 183, 200, 201, 204, 205, 218, 219,
    222, 223, 232, 233, 236, 237, 250, 251, 254, 255
};

// Function to convert CA number to its bitwise rule
std::bitset<8> getRule(int caNumber) {
    return std::bitset<8>(caNumber);
}

// Function to store the CA rules in a compact structure
std::unordered_map<int, std::bitset<8>> createCARuleMap() {
    std::unordered_map<int, std::bitset<8>> ruleMap;
    for (int ca : amphichiralCAs) {
        ruleMap[ca] = getRule(ca);
    }
    return ruleMap;
}

// Function to display a rule in binary format
void displayRule(int caNumber, const std::bitset<8>& rule) {
    std::cout << "CA Rule " << caNumber << ": " << rule << std::endl;
}

int main() {
    // Create a map of CA rules
    auto ruleMap = createCARuleMap();

    // Example: Display a few CA rules
    for (int ca : {30, 90, 150}) {
        if (ruleMap.find(ca) != ruleMap.end()) {
            displayRule(ca, ruleMap[ca]);
        } else {
            std::cout << "CA Rule " << ca << " is not amphichiral." << std::endl;
        }
    }

    return 0;
}
