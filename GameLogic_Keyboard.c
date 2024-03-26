#include <stdio.h>
#include <stdbool.h>
#include <string.h>

volatile int* ps2_ptr = (int*) 0xFF200100; // Pointer to PS2
volatile int* pushButtons = (int *)0xFF200050; // Address for pushbutton keys

// Comment: This code is filled with all the cases I can think of for the game logic
// Updated: Checks if the word has already been inputted.

// Pre-selected arrays of words for each difficulty level
const char *easyWords[] = {"A", "B", "C"};
const char *mediumWords[] = {"word4", "word5", "word6"};
const char *hardWords[] = {"word7", "word8", "word9"};

// Functions
int readPushButtons();
void clearEdgeCapture();
int waitForKeyPressAndRelease();
void playGame(const char **words, int numWords);
void handleKeyboardInput(char *word);

// Main
int main() {

    printf("Welcome to the Boggle Game!\n");
    printf("Press key0 for Easy level, key1 for Medium level, key2 for Hard level.\n");

    while (true) {
        int key = waitForKeyPressAndRelease(); // Wait for a key press and release
        if (key == 0) {
            printf("You chose Easy level.\n");
            playGame(easyWords, sizeof(easyWords) / sizeof(easyWords[0]));
        } else if (key == 1) {
            printf("You chose Medium level.\n");
            playGame(mediumWords, sizeof(mediumWords) / sizeof(mediumWords[0]));
        } else if (key == 2) {
            printf("You chose Hard level.\n");
            playGame(hardWords, sizeof(hardWords) / sizeof(hardWords[0]));
        }
    }
    return 0;
}

// Function to read the state of the pushbuttons (keys)
int readPushButtons() {
    volatile int *pushButtons = (int *)0xFF200050; // Address for pushbutton keys
    return *pushButtons & 0x7; // Read the state of the pushbuttons
}

// Function to clear the edge capture register
void clearEdgeCapture() {
    volatile int *KEYs = (int *)0xFF200050; // pushbutton base address
    *(KEYs + 3) = 0x7; // Clear edge capture register by writing back the same value
}

// Function to wait for a key press and release
int waitForKeyPressAndRelease() {
    volatile int *KEYs = (int *)0xFF200050; // pushbutton base address
    int edge_cap;
    
    // Wait for an edge (press and release) to be captured
    while (true) {
        edge_cap = *(KEYs + 3); // Read the edge capture register
        
        if (edge_cap & 0x1) {
            clearEdgeCapture(); // Clear the edge capture register for KEY0
            return 0; // Key 0 pressed and released
        } else if (edge_cap & 0x2) {
            clearEdgeCapture(); // Clear the edge capture register for KEY1
            return 1; // Key 1 pressed and released
        } else if (edge_cap & 0x4) {
            clearEdgeCapture(); // Clear the edge capture register for KEY2
            return 2; // Key 2 pressed and released
        }
    }
}

// Function to play the game for a given difficulty level
void playGame(const char **words, int numWords) {
    char input[50]; // Assuming maximum word length is 50 characters
    bool enteredWords[numWords]; // Track which words have been entered
    int enteredCount = 0; // Count of how many unique words have been entered

    // Initialize all words as not entered
    for(int i = 0; i < numWords; i++) {
        enteredWords[i] = false;
    }

    while (true) {
        printf("Enter a word (Press Enter to finish): ");
        handleKeyboardInput(input);

        if (strcmp(input, "EXIT") == 0) {
            printf("Returning to level selection screen.\n");
            break;
        }

        bool wordFound = false;
        bool wordAlreadyEntered = false;
        for (int i = 0; i < numWords; i++) {
            if (strcmp(words[i], input) == 0) {
                wordFound = true;
                if (!enteredWords[i]) {
                    printf("Congratulations! '%s' is a valid word.\n", input);
                    enteredWords[i] = true; // Mark this word as entered
                    enteredCount++; // Increment the count of entered words
                } else {
                    wordAlreadyEntered = true; // The word was found but has already been entered
                }
                break; // Exit loop once word is found
            }
        }

        // Inform user based on word status
        if (!wordFound) {
            printf("Error: '%s' is not in the word list.\n", input);
        } else if (wordAlreadyEntered) {
            printf("'%s' has already been entered.\n", input);
        }

        // Check if all words have been entered
        if (enteredCount == numWords) {
            printf("All words have been entered! Returning to level selection screen.\n");
            break; // Exit the while loop to return to level selection
        }
    }
}

// Function to handle keyboard input and add letters to the array
void handleKeyboardInput(char *word) {
    int keyData;
    bool enterPressed = false;
    int wordIndex = 0;
    bool keyReleased = false; // Track if the last key was released

    while (!enterPressed) { // While "ENTER" has not been pressed
        keyData = *ps2_ptr; // keyData contains the scan code of the key address
        if (keyData != 0) { // Check if the key has data, meaning it has been pressed/
            int key = keyData & 0xFF; // Extract the lower 8 bits
            
            if (key == 0xF0) { // Key release code
				// If the scan code is 0xF0, it signifies that the next key event will be a key release
                keyReleased = true;
                // Ensure the next read is ignored by advancing past the release code
            while(*ps2_ptr == 0); // Wait until a new code is available
            } else if (keyReleased) {
                switch (key) {
                    case 0x1C: word[wordIndex++] = 'A'; break;
                    case 0x32: word[wordIndex++] = 'B'; break;
                    case 0x21: word[wordIndex++] = 'C'; break;
                    case 0x23: word[wordIndex++] = 'D'; break;
                    case 0x24: word[wordIndex++] = 'E'; break;
                    case 0x2B: word[wordIndex++] = 'F'; break;
                    case 0x34: word[wordIndex++] = 'G'; break;
                    case 0x33: word[wordIndex++] = 'H'; break;
                    case 0x43: word[wordIndex++] = 'I'; break;
                    case 0x3B: word[wordIndex++] = 'J'; break;
                    case 0x42: word[wordIndex++] = 'K'; break;
                    case 0x4B: word[wordIndex++] = 'L'; break;
                    case 0x3A: word[wordIndex++] = 'M'; break;
                    case 0x31: word[wordIndex++] = 'N'; break;
                    case 0x44: word[wordIndex++] = 'O'; break;
                    case 0x4D: word[wordIndex++] = 'P'; break;
                    case 0x15: word[wordIndex++] = 'Q'; break;
                    case 0x2D: word[wordIndex++] = 'R'; break;
                    case 0x1B: word[wordIndex++] = 'S'; break;
                    case 0x2C: word[wordIndex++] = 'T'; break;
                    case 0x3C: word[wordIndex++] = 'U'; break;
                    case 0x2A: word[wordIndex++] = 'V'; break;
                    case 0x1D: word[wordIndex++] = 'W'; break;
                    case 0x22: word[wordIndex++] = 'X'; break;
                    case 0x35: word[wordIndex++] = 'Y'; break;
                    case 0x1A: word[wordIndex++] = 'Z'; break;
                    case 0x5A: enterPressed = true; break; // Enter key pressed
                }
				// After handling the key press, keyReleased is set to false 
				//to indicate that any 0xF0 codes should be treated as the start of a new key release.
                keyReleased = false; // Reset for next key press
            }
        }
    }

    word[wordIndex] = '\0'; // End of String
}
