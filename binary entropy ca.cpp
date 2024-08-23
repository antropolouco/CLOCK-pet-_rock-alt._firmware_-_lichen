#include <iostream>
#include <vector>
#include <cmath>

// Function to calculate binary entropy H(X)
double binary_entropy(double p) {
    if (p == 0 || p == 1) return 0.0; // log(0) is undefined
    return -p * std::log2(p) - (1 - p) * std::log2(1 - p);
}

class CellularAutomaton {
public:
    CellularAutomaton(int width, int height) : width(width), height(height) {
        grid.resize(height, std::vector<int>(width, 0));
    }

    // Function to initialize the grid with a pattern
    void initialize_pattern() {
        // Example: a single active cell in the center
        grid[height / 2][width / 2] = 1;
    }

    // Function to calculate the probability p in the neighborhood of a cell
    double calculate_probability(int x, int y) {
        int active_neighbors = 0;
        int total_neighbors = 0;

        // Moore neighborhood (8 neighbors)
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue; // Skip the current cell itself
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    active_neighbors += grid[ny][nx];
                    ++total_neighbors;
                }
            }
        }

        return static_cast<double>(active_neighbors) / total_neighbors;
    }

    // Function to update the grid based on entropy
    void update_grid() {
        std::vector<std::vector<int>> new_grid = grid;

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double p = calculate_probability(x, y);
                double entropy = binary_entropy(p);

                // Example update rule based on entropy:
                // Higher entropy makes it more likely for a cell to become active
                if (entropy > 0.5) {
                    new_grid[y][x] = 1;
                } else if (entropy < 0.3) {
                    new_grid[y][x] = 0;
                } else {
                    new_grid[y][x] = grid[y][x]; // No change
                }
            }
        }

        grid = new_grid;
    }

    // Function to print the grid
    void print_grid() {
        for (const auto &row : grid) {
            for (int cell : row) {
                std::cout << (cell ? "█" : " ");
            }
            std::cout << "\n";
        }
    }

private:
    int width, height;
    std::vector<std::vector<int>> grid;
};

int main() {
    int width = 20;
    int height = 20;
    CellularAutomaton automaton(width, height);

    automaton.initialize_pattern();

    for (int step = 0; step < 10; ++step) {
        automaton.print_grid();
        std::cout << "Step: " << step << "\n";
        automaton.update_grid();
    }

    return 0;
}
