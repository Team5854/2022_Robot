#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(57, 6, NEO_GRB + NEO_KHZ800);
const int colors[][3] = {{255,0,0},{222, 116, 9},{222, 204, 9},{0,255,0},{66, 212, 245},{0,0,255},{176, 66, 245}};
int pos = 0;
void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  strip.setBrightness(150);
}

int wrapAround(int in){
  if(in < 57){
    return in;
  }
  else{
    return 0+(in-57);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 57; i++){
    int Rand = random(8);
    strip.setPixelColor(i, colors[Rand][0], colors[Rand][1], colors[Rand][2]);
  }
  for(int i = pos; i < pos+3; i++){
    strip.setPixelColor(wrapAround(i), 0,0,0);
    strip.setPixelColor(wrapAround(i+10), 0,0,0);
    strip.setPixelColor(wrapAround(i+20), 0,0,0);
    strip.setPixelColor(wrapAround(i+30), 0,0,0);
    strip.setPixelColor(wrapAround(i+40), 0,0,0);
    strip.setPixelColor(wrapAround(i+50), 0,0,0);
  }
  if(pos < 56){
    pos+=2;
  }
  else{
    pos = 0;
  }
  strip.show();
  delay(100);
}
