#include <iostream>
#include <iomanip>

// Constants
const int MAX_FRAMES = 10; // Maximum number of frames in a game
const int MAX_THROWS = 21; // Maximum possible throws in a game (21 for a perfect game)

// Function to calculate cumulative scores for each frame
void calculateScores(int throws[], int frameScores[], int currentThrow) {
    int frameIndex = 0;
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (throws[frameIndex] == 10) { // Strike
            frameScores[i] = 10 + throws[frameIndex + 1] + throws[frameIndex + 2];
            frameIndex++;
        } else if (throws[frameIndex] + throws[frameIndex + 1] == 10) { // Spare
            frameScores[i] = 10 + throws[frameIndex + 2];
            frameIndex += 2;
        } else { // Open frame
            frameScores[i] = throws[frameIndex] + throws[frameIndex + 1];
            frameIndex += 2;
        }
        if (i > 0) {
            frameScores[i] += frameScores[i - 1]; // Add previous frame's score to the current frame
        }
    }
}

// Function to print the header for the frames
void printFramesHeader() {
    std::cout << "Frame#: ";
    for (int i = 0; i < MAX_FRAMES; i++) {
        std::cout << std::setw(5) << i + 1; // Print frame numbers with padding
    }
    std::cout << std::endl;
}

// Function to print the throws
void printThrows(int throws[], int currentThrow) {
    std::cout << "Throws: ";
    for (int i = 0; i < currentThrow; i++) {
        std::cout << std::setw(2) << throws[i] << " "; // Print each throw with padding
    }
    std::cout << std::endl;
}

// Function to print the cumulative scores
void printScores(int frameScores[], int currentFrame) {
    std::cout << "Scores: ";
    for (int i = 0; i < currentFrame; i++) {
        std::cout << std::setw(5) << frameScores[i]; // Print each frame score with padding
    }
    std::cout << std::endl;
}

int main() {
    int throws[MAX_THROWS] = {0}; // Store the pins knocked down in each throw
    int frameScores[MAX_FRAMES] = {0}; // Store the cumulative scores for each frame
    int currentThrow = 0; // Index to track the current throw

    // Initial print of frames header, throws, and scores
    printFramesHeader();
    printThrows(throws, currentThrow);
    printScores(frameScores, 0);

    // Loop through each frame
    for (int frame = 0; frame < MAX_FRAMES; frame++) {
        std::cout << "\nTurn Frame " << frame + 1 << std::endl;
        std::cout << "1st Throw: ";
        std::cin >> throws[currentThrow]; // Input for the first throw of the frame

        if (throws[currentThrow] == 10) { // Strike
            if (frame < 9) {
                currentThrow++; // Move to the next throw
            } else { // 10th frame
                std::cout << "2nd Throw: ";
                std::cin >> throws[currentThrow + 1];
                std::cout << "3rd Throw: ";
                std::cin >> throws[currentThrow + 2];
                currentThrow += 3; // Move to the next set of throws
            }
        } else { // Not a strike
            std::cout << "2nd Throw: ";
            std::cin >> throws[currentThrow + 1]; // Input for the second throw of the frame
            currentThrow += 2; // Move to the next set of throws

            if (frame == 9 && throws[currentThrow - 2] + throws[currentThrow - 1] == 10) { // 10th frame spare
                std::cout << "3rd Throw: ";
                std::cin >> throws[currentThrow]; // Input for the third throw if spare
                currentThrow++;
            }
        }

        // Calculate scores after each frame
        calculateScores(throws, frameScores, currentThrow);

        // Print the updated frames header, throws, and scores
        printFramesHeader();
        printThrows(throws, currentThrow);
        printScores(frameScores, frame + 1);
    }

    return 0;
}
