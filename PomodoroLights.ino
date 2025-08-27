
#include <time.h>


#include <FastLED.h>

  #define LED_COUNT 29
  #define LED_PIN 4


// ---------------------------------------------------------------------------------------------
// Global variables for the LED strip
// ---------------------------------------------------------------------------------------------
CRGB leds[LED_COUNT];
unsigned int ledBrightness = 80;


enum state {STUDYING = 25, RESTING = 10};
state studyState = STUDYING;

// This color palette handles the transition between colors
DEFINE_GRADIENT_PALETTE(studyColors) { 
  0,   225,  0,  0,    // rest orange
  STUDYING,   225,  70,  10,    // rest orange
  RESTING, 150, 150, 250,       // study blue (white for now)
  255, 150, 150, 250 // ERROR HANDLING
};
CRGBPalette16 studyPalette = studyColors;




// The number of LEDs that are currently lit, default to max.
unsigned int numOfLitLEDs = LED_COUNT,
             studyTimer = 0;
float timerProgress = 0;


// ---------------------------------------------------------------------------------------------



// ---------------------------------------------------------------------------------------------
// FUNCTIONS
// ---------------------------------------------------------------------------------------------



// Function to loop through the led's on the lightstrip and set their color based on the current time.
void updateLights(){
  for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB::Black;
    }
    timerProgress = float(studyTimer)  / float(studyState * 60);
   
    numOfLitLEDs = LED_COUNT - floor(timerProgress * LED_COUNT);
    if(numOfLitLEDs < 0){numOfLitLEDs = 0;}
    
    for (int i = 0; i < numOfLitLEDs; i++) {
      leds[i] = ColorFromPalette(studyPalette, studyState);
    }
  FastLED.show();
}

void flipStudyState(){
  if(studyState == STUDYING){
    studyState = RESTING;
  }
  else{
    studyState = STUDYING;
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  // Set up the light strip with FastLED
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(ledBrightness);

}


void loop() {
  studyTimer++;
  if(studyTimer > (studyState * 60)){
    studyTimer = 0;
    flipStudyState();
  }
  updateLights();
  delay(1000);
}







