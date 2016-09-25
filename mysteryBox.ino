
#include <SpeechSynthesis.h> // Include the speech synth module library

#define DEBOUNCE_CLEAR      0x00
#define DEBOUNCE_START      0x01
#define DEBOUNCE_COMPLETE   0x80

#define BUTTON_INTERRUPT    0

#define PHRASE_COUNT        10

#define LOOP_DELAY_MS       30
#define LED_DELAY_MS        250
#define COUNTDOWN_DELAY_MS  1000

#define SYNTH_SBUF_SIZE     512

#define SYNTH_SEL_VOLUME    "9"
#define SYNTH_SEL_SPEED     "3"

#define SYNTH_CMD_VOLUME    4
#define SYNTH_CMD_SPEED     2
#define SYNTH_CMD_MUTE      1
#define SYNTH_CMD_ENGLISH   6
#define SYNTH_CMD_DEFAULT   5

#define SYNTH_ECMD_START    0
#define SYNTH_ECMD_STOP     1
#define SYNTH_ECMD_PAUSE    2
#define SYNTH_ECMD_RESUME   3
#define SYNTH_ECMD_CHKSTAT  4

#define SYNTH_TYPE_XPD      4
#define SYNTH_TYPE_SPELL    6
#define SYNTH_TYPE_SAY      7

#define SYNTH_VOICE_MALE1   0
#define SYNTH_VOICE_MALE2   1
#define SYNTH_VOICE_FEMALE1 2
#define SYNTH_VOICE_DUCK    3
#define SYNTH_VOICE_FEMALE2 4
#define SYNTH_VOICE_FEMALE3 5
#define SYNTH_VOICE_MALE3   6
#define SYNTH_VOICE_FEMALE4 7
#define SYNTH_VOICE_FEMALE5 8
#define SYNTH_VOICE_MALE4   17
#define SYNTH_VOICE_FEMALE6 18
#define SYNTH_VOICE_FEMALE8 19
#define SYNTH_VOICE_CD1     9
#define SYNTH_VOICE_CD2     10
#define SYNTH_VOICE_CD3     11
#define SYNTH_VOICE_CD4     12
#define SYNTH_VOICE_CD5     13
#define SYNTH_VOICE_CD6     14
#define SYNTH_VOICE_CD7     15
#define SYNTH_VOICE_CD8     16

#define PHRASE_0            "0"
#define PHRASE_1            "1"
#define PHRASE_2            "2"
#define PHRASE_3            "3"
#define PHRASE_4            "4"
#define PHRASE_5            "5"
#define PHRASE_6            "6"
#define PHRASE_7            "7"
#define PHRASE_8            "8"
#define PHRASE_9            "9"
#define PHRASE_10           "ten"

#define PHRASE_I1           "fool"
#define PHRASE_I2           "dork"
#define PHRASE_I3           "idiot"
#define PHRASE_I4           "dolt"
#define PHRASE_I5           "mouth breather"
#define PHRASE_I6           "knuckle drager"
#define PHRASE_I7           "weak sauce"
#define PHRASE_I8           "turd burgler"

#define PHRASE_HELLO        "hello world"

const int lampPin =         11;
const int ledPin =          10;
const int buttonPin =       1;


typedef struct boxStruct{
    byte            debounceByte;                   // Debounce debounce byte
    boolean         buttonPressed;                  // Button depressed flag
    int             phraseSeed;                     // Random phrase seed 
    boolean         playPhrase;                     // Play the phrase flag
    byte            synthBuffer[SYNTH_SBUF_SIZE];   // Synth buffer
} mysteryBox;

mysteryBox          boxData;                        // Declare the box data

// Initialization
void setup() {
    // Initialize the mystery box
    boxData.debounceByte = DEBOUNCE_CLEAR;
    boxData.buttonPressed = false;
    boxData.phraseSeed = 0;
    boxData.playPhrase = false;

    // Set up the interrupt button pullup
    pinMode(buttonPin, INPUT_PULLUP);

    // Set up the lamp output pin
    pinMode(lampPin, OUTPUT);

    // Set up the LED output pin
    pinMode(ledPin, OUTPUT);
    
    // Initialize the UART
    Serial.begin(115200);
    
    // Set up the random number generator
    randomSeed(analogRead(0));

    // Initialize the lamp pin
    digitalWrite(lampPin, LOW);
    digitalWrite(ledPin, LOW);

    // Say something
    synthPhrase(PHRASE_HELLO);

    // Test the LED
    digitalWrite(ledPin, HIGH);
    delay(LED_DELAY_MS);
    digitalWrite(ledPin, LOW);
}

// Polling loop
void loop() {
    // Start the loop with a delay
    delay(LOOP_DELAY_MS);

    // Process the button depress routine
    serviceButton();

    // Process the button debounce routine
    serviceDebounce();

    // Process the phrase routine
    servicePhrase();
}

// Record button press event, normally the button pressed flag will be clear
void serviceButton() {
    if((boxData.buttonPressed != true) && (digitalRead(buttonPin) == LOW)) {
        boxData.buttonPressed = true;
    }
}

// Service the mystery box button debounce
void serviceDebounce() {
    // The button has been pressed, start the debounce sequence
    if(boxData.buttonPressed) {
        boxData.debounceByte = DEBOUNCE_START;
        boxData.buttonPressed = false;
    }
    // No more bouncing, generate a phrase seed and set the phrase flag
    else if(boxData.debounceByte == DEBOUNCE_COMPLETE) {
        boxData.debounceByte = DEBOUNCE_CLEAR;
        boxData.playPhrase = true;
        boxData.phraseSeed = int(random(1,(PHRASE_COUNT+1)));
    }
    // Shift the debounce byte
    else if((boxData.debounceByte != DEBOUNCE_CLEAR) && (boxData.debounceByte != DEBOUNCE_COMPLETE)) {
        boxData.debounceByte = boxData.debounceByte << 1;
    }
}

// Synth the selected phrase
void synthPhrase(char *phrase) {

    // Clear the synth buffer
    SpeechSynthesis.buf_init(boxData.synthBuffer);  
    
    // Set the volume up
    SpeechSynthesis.English(boxData.synthBuffer,SYNTH_CMD_VOLUME,SYNTH_SEL_VOLUME);

    // Set the speech speed up
    SpeechSynthesis.English(boxData.synthBuffer,SYNTH_CMD_SPEED,SYNTH_SEL_SPEED);

    // Insert the phrase
    SpeechSynthesis.English(boxData.synthBuffer,SYNTH_CMD_ENGLISH,phrase);

    // Issue the speech process phrase
    SpeechSynthesis.Espeaking(SYNTH_ECMD_START,SYNTH_VOICE_MALE3,SYNTH_TYPE_SAY,boxData.synthBuffer);
    
}

// Service the phrase request if needed
void servicePhrase() {
    // Test phrase
    if(boxData.playPhrase) {
        boxData.playPhrase = false;
        digitalWrite(ledPin, HIGH);
        delay(LED_DELAY_MS);
        digitalWrite(ledPin, LOW);
        coundDown();
        synthPhrase(PHRASE_I5);
    }
}

// Issue the countdown
void coundDown() {
    synthPhrase(PHRASE_10);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_9);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_8);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_7);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_6);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_5);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_4);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_3);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_2);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_1);
    delay(COUNTDOWN_DELAY_MS);
    synthPhrase(PHRASE_0);
    delay(COUNTDOWN_DELAY_MS);
}
