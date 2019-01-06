#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 204
CRGB leds[NUM_LEDS];

void setup() {  
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<WS2812B, 13, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 50 );
}

void four_colors_smooth(){
  FastLED.setBrightness(80);
  int i;
  for(i=0; i<NUM_LEDS; i++){
    leds[i] = CHSV((((i/51)*50) +millis()/30)%255, 255, 255);
  }
}

void four_colors_smooth_dark(){
  FastLED.setBrightness(40);
  int i;
  for(i=0; i<NUM_LEDS; i++){
    leds[i] = CHSV((((i/51)*50) +millis()/30)%255, 255, 255);
  }
}

void rainbow(){
  FastLED.setBrightness(80);
  
  int i;
  for(i=0; i<NUM_LEDS; i++){
    leds[i] = CHSV((i +millis()/5)%255, 255, 255);
  }
}

void rainbow_dark(){
  FastLED.setBrightness(40);
  
  int i;
  for(i=0; i<NUM_LEDS; i++){
    leds[i] = CHSV((i +millis()/5)%255, 255, 255);
  }
}

void blink_random(){ 
  FastLED.setBrightness(255);
  
  int i;
  for(i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }  

  int seg = (millis()/150) %4;

  if(seg == 1) seg = 2;
  else if(seg == 2) seg = 1;
  
  for(i=seg*51; i<(seg*51+51); i++){
    leds[i] = CHSV((((i/51)*50) +millis()/30)%255, 255, 255);
  }  
}


void sequence(){ 
  FastLED.setBrightness(255);  

  int i;
  for(i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }

  int seg = (millis()/600) %4;

  if(seg == 1) seg = 2;
  else if(seg == 2) seg = 1;
  
  CRGB c;
  for(i=seg*51; i<(seg*51+51); i++){
    if((millis()/60)%10==0){
      c = CHSV(millis()/10,255,80);
    }else{      
      leds[i] = c;
    }
  }
  CRGB color = CHSV((millis()/20) % 255, 255, 255);

  for(i=0; i<NUM_LEDS; i++){
    if((millis()/5)%(NUM_LEDS) == i){
      leds[i] = color;
      if(i < NUM_LEDS-1) leds[i+1] = color;
      if(i < NUM_LEDS-2)  leds[i+2] = color;
      if(i < NUM_LEDS-3) leds[i+3] = color;
      if(i < NUM_LEDS-4) leds[i+4] = color;
      if(i < NUM_LEDS-5) leds[i+5] = color;
      if(i < NUM_LEDS-6) leds[i+6] = color;
      leds[NUM_LEDS-i] = color;
      if(i < NUM_LEDS-1) leds[NUM_LEDS-(i+1)] = color;
      if(i < NUM_LEDS-2) leds[NUM_LEDS-(i+2)] = color;
      if(i < NUM_LEDS-3) leds[NUM_LEDS-(i+3)] = color;
      if(i < NUM_LEDS-4)  leds[NUM_LEDS-(i+4)] = color;
      if(i < NUM_LEDS-5)  leds[NUM_LEDS-(i+5)] = color;
      if(i < NUM_LEDS-6)  leds[NUM_LEDS-(i+6)] = color;
    }     
  }

}

void strobo(){ 
  int seg = (millis()/50) %4;
  
  FastLED.setBrightness(255);

  int i;
  for(i=0; i<NUM_LEDS; i++){
    leds[i] = (seg==0)? CRGB::White:CRGB::Black;
  }  
}

void loop(){
    switch(analogRead(5)/160){
      case 0:
        rainbow_dark();
      break;
      case 1:
        four_colors_smooth_dark();
      break;
      case 2:
        rainbow();
      break;
      case 3:
        four_colors_smooth();
      break;
      case 4:
        blink_random();
      break;
      case 5:
        sequence();
      break;
      default:
        strobo();
    }
    FastLED.show();
    delay(20);
}