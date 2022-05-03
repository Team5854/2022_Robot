#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(22, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(22, 7, NEO_GRB + NEO_KHZ800);
char lastStatusByte;
const int colors[][3] = {{255, 0, 0}, {222, 116, 9}, {222, 204, 9}, {0, 200, 70}, {66, 212, 245}, {0, 0, 255}, {176, 66, 245}};

bool glitchMode = false;
int ledIndex = 0;
long lastTime = 0;
bool blinkBool = false;
int runwayStep = 0;

int wrapAround(int in) {
  if (in < 22) {
    return in;
  }
  else {
    return in - 22;
  }
}

void partyMode() {
  if (millis() >= lastTime + 100) {
    lastTime = millis();
    for (int i = 0; i < 22; i++) {
      int Rand = random(8);
      strip1.setPixelColor(i, colors[Rand][0], colors[Rand][1], colors[Rand][2]);
      strip2.setPixelColor(i, colors[Rand][0], colors[Rand][1], colors[Rand][2]);
    }
    for (int i = ledIndex; i < ledIndex + 3; i++) {
      strip1.setPixelColor(wrapAround(i), 0, 0, 0);
      strip1.setPixelColor(wrapAround(i + 10), 0, 0, 0);
      strip1.setPixelColor(wrapAround(i + 20), 0, 0, 0);
      strip2.setPixelColor(wrapAround(i), 0, 0, 0);
      strip2.setPixelColor(wrapAround(i + 10), 0, 0, 0);
      strip2.setPixelColor(wrapAround(i + 20), 0, 0, 0);
    }
    ledIndex = wrapAround(ledIndex + 2);
    strip1.show();
    strip2.show();
  }
}

void blinkLeds(int Red, int Green, int Blue) {
  if (millis() >= lastTime + 250) {
    lastTime = millis();
    if (blinkBool) {
      for (int i = 0; i < 11; i++) {
        if (i % 2 == 0) {
          strip1.setPixelColor(2 * i, Red, Green, Blue);
          strip1.setPixelColor((2 * i) + 1, Red, Green, Blue);
          strip2.setPixelColor(2 * i, Red, Green, Blue);
          strip2.setPixelColor((2 * i) + 1, Red, Green, Blue);
        }
        else {
          strip1.setPixelColor(2 * i, 0, 0, 0);
          strip1.setPixelColor((2 * i) + 1, 0, 0, 0);
          strip2.setPixelColor(2 * i, 0, 0, 0);
          strip2.setPixelColor((2 * i) + 1, 0, 0, 0);
        }
      }
    }
    else {
      for (int i = 0; i < 22; i++) {
        strip1.setPixelColor(i, 0, 0, 0, 0);
        strip2.setPixelColor(i, 0, 0, 0, 0);
      }
    }
    blinkBool = !blinkBool;
    strip1.show();
    strip2.show();
  }
}

void runway(int Red, int Green, int Blue) {
  if (millis() >= lastTime + 100) {
    lastTime = millis();
    for (int i = 0; i < 12; i++) {
      if (i % 2 == 0) {
        strip1.setPixelColor(wrapAround((2 * i) + ledIndex), Red, Green, Blue);
        strip1.setPixelColor(wrapAround((2 * i) + ledIndex + 1), Red, Green, Blue);
        strip2.setPixelColor(wrapAround((2 * i) + ledIndex), Red, Green, Blue);
        strip2.setPixelColor(wrapAround((2 * i) + ledIndex + 1), Red, Green, Blue);
      }
      else {
        strip1.setPixelColor(wrapAround((2 * i) + ledIndex), 0, 0, 0);
        strip1.setPixelColor(wrapAround((2 * i) + ledIndex + 1), 0, 0, 0);
        strip2.setPixelColor(wrapAround((2 * i) + ledIndex), 0, 0, 0);
        strip2.setPixelColor(wrapAround((2 * i) + ledIndex + 1), 0, 0, 0);
      }
    }
    ledIndex = wrapAround(ledIndex + 1);
    strip1.show();
    strip2.show();
  }
}

void ballIndication(bool top, bool bottom) {
  if (top) {
    for (int i = 11; i < 22; i++) {
      strip1.setPixelColor(i, 0, 0, 255);
      strip2.setPixelColor(i, 0, 0, 255);
    }
  }
  if (bottom) {
    for (int i = 0; i < 11; i++) {
      strip1.setPixelColor(i, 0, 0, 255);
      strip2.setPixelColor(i, 0, 0, 255);
    }
  }
  strip1.show();
  strip2.show();
}


void setup() {
  // put your setup code here, to run once:
  strip1.begin();
  strip1.show();
  strip1.setBrightness(150);
  strip2.begin();
  strip2.show();
  strip2.setBrightness(150);
  Serial.begin(115200);
  while (!Serial) {}
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    char received = Serial.read();
    if (received >= 48 && received <= 57) {
      strip1.setBrightness((received - 48) * (255 / 9));
      strip2.setBrightness((received - 48) * (255 / 9));
    }
    else {
      lastStatusByte = received;
      if (lastStatusByte == "G") {
        glitchMode = true;
      }
      if (lastStatusByte == "g"){
        glitchMode = false;
      }
    }
  }


  switch (lastStatusByte) {
    default:
      if (glitchMode == true){
        runway(30, 240, 10);
        break;
      }
    case 'b':
      partyMode();
      break;
    case 's':
      runway(255, 65, 8);
      break;
    case 'c':
      runway(178, 7, 235);
      break;
    case 'F':
      for (int i = 0; i < 22; i++) {
        strip1.setPixelColor(i, 178, 7, 235);
        strip2.setPixelColor(i, 178, 7, 235);
      }
      strip1.show();
      strip2.show();
      break;
    case 'l':
      blinkLeds(255, 0, 130);
      break;
    case 'i':
      blinkLeds(212, 103, 8);
      break;
    case 'I':
      blinkLeds(212, 103, 8);
      ballIndication(true, false);
      break;
    case 'n':
      ballIndication(true, true);
      break;
    case 'N':
      for (int i = 0; i < 22; i++) {
        strip1.setPixelColor(i, 255, 0, 0);
        strip2.setPixelColor(i, 255, 0, 0);

      }
      strip1.show();
      strip2.show();
      break;
    case 'o':
      for (int i = 0; i < 22; i++) {
        strip1.setPixelColor(i, 255, 0, 0);
        strip2.setPixelColor(i, 255, 0, 0);
      }
      strip1.show();
      strip2.show();
      ballIndication(true, false);
      break;
  }


    //runway(30, 240, 10);
  
}
