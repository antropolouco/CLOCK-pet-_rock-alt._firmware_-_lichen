import numpy as np
import math

# Function to calculate binary entropy H(X)
def binary_entropy(p):
    if p == 0 or p == 1:
        return 0.0  # log(0) is undefined
    return -p * math.log2(p) - (1 - p) * math.log2(1 - p)

class CellularAutomaton:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.grid = np.zeros((height, width), dtype=int)

    # Function to initialize the grid with a pattern
    def initialize_pattern(self):
        # Example: a single active cell in the center
        self.grid[self.height // 2, self.width // 2] = 1

    # Function to calculate the probability p in the neighborhood of a cell
    def calculate_probability(self, x, y):
        active_neighbors = 0
        total_neighbors = 0

        # Moore neighborhood (8 neighbors)
        for dy in range(-1, 2):
            for dx in range(-1, 2):
                if dx == 0 and dy == 0:
                    continue  # Skip the current cell itself
                nx = x + dx
                ny = y + dy

                if 0 <= nx < self.width and 0 <= ny < self.height:
                    active_neighbors += self.grid[ny, nx]
                    total_neighbors += 1

        return active_neighbors / total_neighbors if total_neighbors > 0 else 0

    # Function to update the grid based on entropy
    def update_grid(self):
        new_grid = np.copy(self.grid)

        for y in range(self.height):
            for x in range(self.width):
                p = self.calculate_probability(x, y)
                entropy = binary_entropy(p)

                # Example update rule based on entropy:
                # Higher entropy makes it more likely for a cell to become active
                if entropy > 0.5:
                    new_grid[y, x] = 1
                elif entropy < 0.3:
                    new_grid[y, x] = 0
                else:
                    new_grid[y, x] = self.grid[y, x]  # No change

        self.grid = new_grid

    # Function to print the grid
    def print_grid(self):
        for row in self.grid:
            print("".join("█" if cell else " " for cell in row))
        print("\n")

# Main function to run the automaton
if __name__ == "__main__":
    width = 20
    height = 20
    automaton = CellularAutomaton(width, height)

    automaton.initialize_pattern()

    for step in range(10):
        print(f"Step: {step}")
        automaton.print_grid()
        automaton.update_grid()
