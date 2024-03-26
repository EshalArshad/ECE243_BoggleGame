#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

volatile int* ps2_ptr = (int*) 0xFF200100; // Pointer to PS2
volatile int* pushButtons = (int *)0xFF200050; // Address for pushbutton keys

const char *englishwords[] = {"wikipedia",
    "women",
    "womens",
    "won",
    "wonder",
    "wonderful",
    "wondering",
    "wood",
    "wooden",
    "woods",
    "wool",
    "worcester",
    "word",
    "wordpress",
    "words",
    "work",
    "worked",
    "worker",
    "workers",
    "workflow",
    "workforce",
    "working",
    "workout",
    "workplace",
    "works",
    "workshop",
    "workshops",
    "workstation",
    "world",
    "worldcat",
    "worlds",
    "worldsex",
    "worldwide",
    "worm",
    "worn",
    "worried",
    "worry",
    "worse",
    "worship",
    "worst",
    "worth",
    "worthy",
    "would",
    "wound",
    "wow",
    "wp",
    "wr",
    "wrap",
    "wrapped",
    "wrapping",
    "wrestling",
    "wright",
    "wrist",
    "write",
    "writer",
    "writers",
    "writes",
    "writing",
    "writings",
    "written",
    "wrong",
    "wrote",
    "ws",
    "wt",
    "wto",
    "wu",
    "wv",
    "ww",
    "www",
    "wx",
    "wy",
    "wyoming",
    "x",
    "xanax",
    "xbox",
    "xerox",
    "xhtml",
    "xi",
    "xl",
    "xml",
    "xnxx",
    "xp",
    "xx",
    "xxx",
    "y",
    "ya",
    "yacht",
    "yahoo",
    "yale",
    "yamaha",
    "yang",
    "yard",
    "yards",
    "yarn",
    "ye",
    "yea",
    "yeah",
    "year",
    "yearly",
    "years",
    "yeast",
    "yellow",
    "yemen",
    "yen",
    "yes",
    "yesterday",
    "yet",
    "yield",
    "yields",
    "yn",
    "yo",
    "yoga",
    "york",
    "yorkshire",
    "you",
    "young",
    "younger",
    "your",
    "yours",
    "yourself",
    "youth",
    "yr",
    "yrs",
    "yu",
    "yugoslavia",
    "yukon",
    "z",
    "za",
    "zambia",
    "zdnet",
    "zealand",
    "zen",
    "zero",
    "zimbabwe",
    "zinc",
    "zip",
    "zoloft",
    "zone",
    "zones",
    "zoning",
    "zoo",
    "zoom",
    "zoophilia",
    "zope",
    "zshops",
    "zu",
    "zum",
    "zus"
};	

char generatedLetters[17]; // global array to store 16 random letters + null terminator

// Function prototypes
int readPushButtons();
void clearEdgeCapture();
int waitForKeyPressAndRelease();
void playGame();
void handleKeyboardInput(char *word);
void generateRandomLetters();
bool isValidWord(const char *word);
bool isLetterInGenerated(const char *word);

int main() {
    printf("Welcome to the Boggle Game!\n");
    printf("Press key0 to start Easy level.\n");

    srand(time(NULL)); // Seed the random number generator

    while (true) {
        int key = waitForKeyPressAndRelease(); // Wait for a key press and release
        if (key == 0) {
            printf("Starting Easy level.\n");
            generateRandomLetters(); // Generate a new set of random letters
            playGame();
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

void generateRandomLetters() {
    for (int i = 0; i < 16; ++i) {
        generatedLetters[i] = 'A' + (rand() % 26); // Generate random uppercase letter
    }
    generatedLetters[16] = '\0'; // Null-terminate the string
    printf("Generated Letters: %s\n", generatedLetters);
}

bool isLetterInGenerated(const char *word) {
    for (int i = 0; word[i] != '\0'; ++i) {
        if (!strchr(generatedLetters, word[i])) {
            return false; // Letter not found in generatedLetters
        }
    }
    return true; // All letters found
}

bool isValidWord(const char *word) {
    int wordCount = sizeof(englishwords) / sizeof(englishwords[0]);
    for (int i = 0; i < wordCount; ++i) {
        if (strcmp(englishwords[i], word) == 0) {
            return true; // Word found in the list
        }
    }
    return false; // Word not found
}

void playGame() {
    char input[50]; // Assuming maximum word length is 50 characters
    char enteredWords[100][50]; // Array to store up to 100 entered valid words
    int enteredCount = 0; // Count of valid words entered

    while (true) {
        printf("Enter a word (or type EXIT to finish): ");
        handleKeyboardInput(input);

        if (strcmp(input, "EXIT") == 0) {
            printf("Exiting to level selection.\n");
            break;
        }

        if (!isLetterInGenerated(input)) {
            printf("Error: The word '%s' contains letters not in the generated set.\n", input);
            continue;
        }

        if (!isValidWord(input)) {
            printf("Error: '%s' is not a valid English word.\n", input);
            continue;
        }

        bool wordAlreadyEntered = false;
        for (int i = 0; i < enteredCount; ++i) {
            if (strcmp(enteredWords[i], input) == 0) {
                wordAlreadyEntered = true;
                printf("Error: '%s' has already been entered.\n", input);
                break;
            }
        }

        if (!wordAlreadyEntered) {
            strcpy(enteredWords[enteredCount++], input); // Add the valid word to the list of entered words
            printf("'%s' is a valid word!\n", input);
        }
    }
}

// Remaining functions (readPushButtons, clearEdgeCapture, waitForKeyPressAndRelease, handleKeyboardInput)
// are assumed to be implemented as before.
// Function to handle keyboard input and add letters to the array
void handleKeyboardInput(char *word) {
    int keyData;
    bool enterPressed = false;
    int wordIndex = 0;
    bool keyReleased = false; // Track if the last key was released
    char letter;

    while (!enterPressed) { // While "ENTER" has not been pressed
        keyData = *ps2_ptr; // keyData contains the scan code of the key address
        if (keyData != 0) { // Check if the key has data, meaning it has been pressed
            int key = keyData & 0xFF; // Extract the lower 8 bits

            if (key == 0xF0) { // Key release code
                keyReleased = true;
            } else if (keyReleased) {
                // Map the key press to a character, default to '\0' if not a letter
                letter = '\0';
                switch (key) {
                    case 0x1C: letter = 'A'; break;
                    case 0x32: letter = 'B'; break;
                    case 0x21: letter = 'C'; break;
                    case 0x23: letter = 'D'; break;
                    case 0x24: letter = 'E'; break;
                    case 0x2B: letter = 'F'; break;
                    case 0x34: letter = 'G'; break;
                    case 0x33: letter = 'H'; break;
                    case 0x43: letter = 'I'; break;
                    case 0x3B: letter = 'J'; break;
                    case 0x42: letter = 'K'; break;
                    case 0x4B: letter = 'L'; break;
                    case 0x3A: letter = 'M'; break;
                    case 0x31: letter = 'N'; break;
                    case 0x44: letter = 'O'; break;
                    case 0x4D: letter = 'P'; break;
                    case 0x15: letter = 'Q'; break;
                    case 0x2D: letter = 'R'; break;
                    case 0x1B: letter = 'S'; break;
                    case 0x2C: letter = 'T'; break;
                    case 0x3C: letter = 'U'; break;
                    case 0x2A: letter = 'V'; break;
                    case 0x1D: letter = 'W'; break;
                    case 0x22: letter = 'X'; break;
                    case 0x35: letter = 'Y'; break;
                    case 0x1A: letter = 'Z'; break;
                    case 0x5A: enterPressed = true; break; // Enter key pressed
                }

                // Check if letter is in the generatedLetters array before appending
                if (strchr(generatedLetters, letter) != NULL || letter == '\0') {
                    if (!enterPressed && letter != '\0') { // Append if it's a valid letter and not the ENTER key
                        word[wordIndex++] = letter;
                    }
                } else {
                    // Optionally, inform the user that the entered letter is not valid
                    printf("Entered letter '%c' is not in the generated letters.\n", letter);
                }

                keyReleased = false; // Reset for next key press
            }
        }
    }

    word[wordIndex] = '\0'; // End of String
}

