#include <stdbool.h>

volatile int* ps2_ptr = (int*) 0xFF200100; // Pointer to PS2

// Function to handle keyboard input and add letters to the array
void handleKeyboardInput(char *word) {
    int keyData;
    bool enterPressed = false;
    int wordIndex = 0;

    while (!enterPressed) {
        keyData = *ps2_ptr;
        int key = keyData & 0xFF; // Extract the lower 8 bits

        // Check if any of the alphabet letters (A-Z) are pressed
        if ((keyData & 0xFF) == 0x1C) { // A
            word[wordIndex++] = 'A';
            printf("Letter A added\n");
        } else if ((keyData & 0xFF) == 0x32) { // B
            word[wordIndex++] = 'B';
            printf("Letter B added\n");
        } else if ((keyData & 0xFF) == 0x21) { // C
            word[wordIndex++] = 'C';
            printf("Letter C added\n");
        } else if ((keyData & 0xFF) == 0x23) { // D
            word[wordIndex++] = 'D';
            printf("Letter D added\n");
        } else if ((keyData & 0xFF) == 0x24) { // E
            word[wordIndex++] = 'E';
            printf("Letter E added\n");
        } else if ((keyData & 0xFF) == 0x2B) { // F
            word[wordIndex++] = 'F';
            printf("Letter F added\n");
        } else if ((keyData & 0xFF) == 0x34) { // G
            word[wordIndex++] = 'G';
            printf("Letter G added\n");
        } else if ((keyData & 0xFF) == 0x33) { // H
            word[wordIndex++] = 'H';
            printf("Letter H added\n");
        } else if ((keyData & 0xFF) == 0x43) { // I
            word[wordIndex++] = 'I';
            printf("Letter I added\n");
        } else if ((keyData & 0xFF) == 0x3B) { // J
            word[wordIndex++] = 'J';
            printf("Letter J added\n");
        } else if ((keyData & 0xFF) == 0x42) { // K
            word[wordIndex++] = 'K';
            printf("Letter K added\n");
        } else if ((keyData & 0xFF) == 0x4B) { // L
            word[wordIndex++] = 'L';
            printf("Letter L added\n");
        } else if ((keyData & 0xFF) == 0x3A) { // M
            word[wordIndex++] = 'M';
            printf("Letter M added\n");
        } else if ((keyData & 0xFF) == 0x31) { // N
            word[wordIndex++] = 'N';
            printf("Letter N added\n");
        } else if ((keyData & 0xFF) == 0x44) { // O
            word[wordIndex++] = 'O';
            printf("Letter O added\n");
        } else if ((keyData & 0xFF) == 0x4D) { // P
            word[wordIndex++] = 'P';
            printf("Letter P added\n");
        } else if ((keyData & 0xFF) == 0x15) { // Q
            word[wordIndex++] = 'Q';
            printf("Letter Q added\n");
        } else if ((keyData & 0xFF) == 0x2D) { // R
            word[wordIndex++] = 'R';
            printf("Letter R added\n");
        } else if ((keyData & 0xFF) == 0x1B) { // S
            word[wordIndex++] = 'S';
            printf("Letter S added\n");
        } else if ((keyData & 0xFF) == 0x2C) { // T
            word[wordIndex++] = 'T';
            printf("Letter T added\n");
        } else if ((keyData & 0xFF) == 0x3C) { // U
            word[wordIndex++] = 'U';
            printf("Letter U added\n");
        } else if ((keyData & 0xFF) == 0x2A) { // V
            word[wordIndex++] = 'V';
            printf("Letter V added\n");
        } else if ((keyData & 0xFF) == 0x1D) { // W
            word[wordIndex++] = 'W';
            printf("Letter W added\n");
        } else if ((keyData & 0xFF) == 0x22) { // X
            word[wordIndex++] = 'X';
            printf("Letter X added\n");
        } else if ((keyData & 0xFF) == 0x35) { // Y
            word[wordIndex++] = 'Y';
            printf("Letter Y added\n");
        } else if ((keyData & 0xFF) == 0x1A) { // Z
            word[wordIndex++] = 'Z';
            printf("Letter Z added\n");
        } else if ((keyData & 0xFF) == 0x1C) { // Enter
            enterPressed = true;
        }
    }

    //idk if needed - need to testtttttttttt
    word[wordIndex] = '\0';
}

int main() {
    char word[50]; // Array to store the entered word
    printf("Enter a word using the PS2 keyboard (press Enter to finish):\n");
    handleKeyboardInput(word); // Test the handleKeyboardInput function
    printf("Entered word: %s\n", word); // Display the entered word
    return 0;
}
