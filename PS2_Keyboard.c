#include <stdio.h>
#include <stdbool.h>

volatile int* ps2_ptr = (int*) 0xFF200100; // Pointer to PS2

// Function to handle keyboard input and add letters to the array
void handleKeyboardInput(char *word) {
    int keyData;
    bool enterPressed = false;
    int wordIndex = 0;
    bool keyReleased = false; // Track if the last key was released

    while (!enterPressed) {
        keyData = *ps2_ptr;
        if (keyData != 0) { // Check if data is available
            int key = keyData & 0xFF; // Extract the lower 8 bits
            
            if (key == 0xF0) { // Key release code
                keyReleased = true;
                // Ensure the next read is ignored by advancing past the release code
                while(*ps2_ptr == 0); // Wait until a new code is available
            } else if (keyReleased) {
                switch (key) {
                    case 0x1C: word[wordIndex++] = 'A'; printf("Letter A added\n"); break;
                    case 0x32: word[wordIndex++] = 'B'; printf("Letter B added\n"); break;
                    case 0x21: word[wordIndex++] = 'C'; printf("Letter C added\n"); break;
                    case 0x23: word[wordIndex++] = 'D'; printf("Letter D added\n"); break;
                    case 0x24: word[wordIndex++] = 'E'; printf("Letter E added\n"); break;
                    case 0x2B: word[wordIndex++] = 'F'; printf("Letter F added\n"); break;
                    case 0x34: word[wordIndex++] = 'G'; printf("Letter G added\n"); break;
                    case 0x33: word[wordIndex++] = 'H'; printf("Letter H added\n"); break;
                    case 0x43: word[wordIndex++] = 'I'; printf("Letter I added\n"); break;
                    case 0x3B: word[wordIndex++] = 'J'; printf("Letter J added\n"); break;
                    case 0x42: word[wordIndex++] = 'K'; printf("Letter K added\n"); break;
                    case 0x4B: word[wordIndex++] = 'L'; printf("Letter L added\n"); break;
                    case 0x3A: word[wordIndex++] = 'M'; printf("Letter M added\n"); break;
                    case 0x31: word[wordIndex++] = 'N'; printf("Letter N added\n"); break;
                    case 0x44: word[wordIndex++] = 'O'; printf("Letter O added\n"); break;
                    case 0x4D: word[wordIndex++] = 'P'; printf("Letter P added\n"); break;
                    case 0x15: word[wordIndex++] = 'Q'; printf("Letter Q added\n"); break;
                    case 0x2D: word[wordIndex++] = 'R'; printf("Letter R added\n"); break;
                    case 0x1B: word[wordIndex++] = 'S'; printf("Letter S added\n"); break;
                    case 0x2C: word[wordIndex++] = 'T'; printf("Letter T added\n"); break;
                    case 0x3C: word[wordIndex++] = 'U'; printf("Letter U added\n"); break;
                    case 0x2A: word[wordIndex++] = 'V'; printf("Letter V added\n"); break;
                    case 0x1D: word[wordIndex++] = 'W'; printf("Letter W added\n"); break;
                    case 0x22: word[wordIndex++] = 'X'; printf("Letter X added\n"); break;
                    case 0x35: word[wordIndex++] = 'Y'; printf("Letter Y added\n"); break;
                    case 0x1A: word[wordIndex++] = 'Z'; printf("Letter Z added\n"); break;
                    case 0x5A: enterPressed = true; break; // Enter key pressed
                }
                keyReleased = false; // Reset for next key press
            }
        }
    }

    word[wordIndex] = '\0'; // Null-terminate the string
}

int main() {
    char word[50]; // Array to store the entered word
    printf("Enter a word using the PS2 keyboard (press Enter to finish):\n");
    handleKeyboardInput(word); // Test the handleKeyboardInput function
    printf("Entered word: %s\n", word); // Display the entered word
    return 0;
}
