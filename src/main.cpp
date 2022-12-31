#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Keyboard_fr_FR.h>
#include <Keypad.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LED_BUILTIN 17

#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {10, 16, 14, 15};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

unsigned long lastUpdate = 0;
unsigned long clickDelay = 100;
unsigned long blinkUpdate = 500;
uint8_t mouseButton = MOUSE_LEFT;
uint8_t ledState = HIGH;

bool bourinage = false;

void initOled()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.cp437(true); // https://en.wikipedia.org/wiki/Code_page_437
  display.display();
}

void refreshScreen()
{
  display.clearDisplay();
  display.setTextColor(SSD1306_BLACK);
  display.fillRect(0, 0, SCREEN_WIDTH, 16, SSD1306_WHITE);
  display.setCursor(1, 1);
  display.print(bourinage ? "CLICK" : "STOP");
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(1, 20);
  display.print(String(clickDelay));
  display.setCursor(1, 40);
  display.print((mouseButton == MOUSE_LEFT) ? "GAUCHE" : "DROITE");
  display.display();
}

void setup()
{
  Serial.begin(9600);

  Keyboard.begin(KeyboardLayout_fr_FR);
  Mouse.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  initOled();

  refreshScreen();
}

void loop()
{
  char customKey = kpd.getKey();
  if (customKey)
  {
    switch (customKey)
    {
    case 'A':
      bourinage = false;
      break;
    case 'B':
      bourinage = true;
      break;
    case '1':
      if (clickDelay < 500)
      {
        clickDelay += 10;
      }
      break;
    case '4':
      if (clickDelay > 10)
      {
        clickDelay -= 10;
      }
      break;
    case '2':
      mouseButton = MOUSE_LEFT;
      break;
    case '5':
      mouseButton = MOUSE_RIGHT;
      break;
    case '#':
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.write('r');
      Keyboard.releaseAll();
      delay(200);
      Keyboard.println("cmd.exe");
      delay(1000);
      Keyboard.println("dir");
      break;
    }
    Serial.println(customKey);

    refreshScreen();
  }

  if ((millis() - lastUpdate) > clickDelay)
  {
    if (bourinage)
    {
      Mouse.click(mouseButton);
    }
    lastUpdate = millis();
  }

  if (millis() - blinkUpdate > clickDelay * 10)
  {
    if (bourinage)
    {
      digitalWrite(LED_BUILTIN, ledState);
      if (ledState == HIGH)
      {
        ledState = LOW;
      }
      else
      {
        ledState = HIGH;
      }
      blinkUpdate = millis();
    }
  }
}
