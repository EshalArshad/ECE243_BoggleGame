#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Pre-selected arrays of words for each difficulty level
const char *easyWords[] = {"word1", "word2", "word3"};
const char *mediumWords[] = {"word4", "word5", "word6"};
const char *hardWords[] = {"word7", "word8", "word9"};

// Function to check if a word is valid for the given difficulty level //
bool isValidWord(const char *word, const char **words, int numWords) {
    // Loop through the array of valid words for the given level
    for (int i = 0; i < numWords; i++) {
        // If the input word matches any of the valid words, return true
        if (strcmp(words[i], word) == 0) { // If the strings are equal, it returns 0
            return true;
        }
    }
    // If no match is found, return false
    return false;
}

// Function to play the game for a given difficulty level //
void playGame(const char **words, int numWords) {
    char input[50]; // Assuming maximum word length is 50 characters

    // Game loop
    while (true) {
        printf("Enter a word: ");

        // Read the whole word from the user
        scanf("%s", input);

		// Did this instead of interrupts, not sure if it works?
        // Check if the user wants to return to the level selection
        if (strcmp(input, "exit") == 0) {  // OR RESET
            printf("Returning to level selection screen.\n");
            break; // Exit the loop
        }

        // Check if the word is valid
        if (isValidWord(input, words, numWords)) {
            printf("Congratulations! '%s' is a valid word.\n", input);
        } else {
            printf("Error: '%s' is not a valid word.\n", input);
        }
    }
}

// Function to read the state of the pushbuttons (keys) //
int readPushButtons() {
    // Address for pushbutton keys
    volatile int *pushButtons = (int *)0xFF200050;

    // Read the state of the pushbuttons
    return *pushButtons & 0x7;
	// Not sure if needed, & 0x7 is just added to ignore and other key presses
}

// Function to check which key is pressed //
int checkKeyPressed() {
    // Loop until a key is pressed
    while (true) {
        // Read the state of the pushbuttons
        int keyState = readPushButtons();

        // Check which key is pressed
        if (keyState & 0x1) {
            return 0; // key0 pressed
        } else if (keyState & 0x2) {
            return 1; // key1 pressed
        } else if (keyState & 0x4) {
            return 2; // key2 pressed
        }
    }
}

int main() {
    int choice;

    // Display level selection screen
    printf("Welcome to the Boggle Game!\n");
    printf("Press key0 for Easy level, key1 for Medium level, key2 for Hard level.\n");

    // Loop until a valid difficulty level is chosen
    while (true) {
        // Check which key is pressed
        int key = checkKeyPressed();

        // Play the corresponding level
        if (key == 0) {
            printf("You chose Easy level.\n");
			// This is where we can add code for background image?
			// Maybe we should have seperate playGame modules for each level?
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
