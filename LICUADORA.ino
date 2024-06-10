#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if defined(ESP8266)
  #define BUTTON_A  0
  #define BUTTON_B 16
  #define BUTTON_C  2
  #define WIRE Wire
#elif defined(ESP32)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
  #define WIRE Wire
#elif defined(ARDUINO_STM32_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
  #define WIRE Wire
#elif defined(TEENSYDUINO)
  #define BUTTON_A  4
  #define BUTTON_B  3
  #define BUTTON_C  8
  #define WIRE Wire
#elif defined(ARDUINO_FEATHER52832)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
  #define WIRE Wire
#elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
  #define BUTTON_A  9
  #define BUTTON_B  8
  #define BUTTON_C  7
  #define WIRE Wire1
#else // 32u4, M0, M4, nrf52840 and 328p
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
  #define WIRE Wire
#endif

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);

#define TRIGGER_PIN 10 // Pin del trigger del sensor
#define ECHO_PIN 9    // Pin del echo del sensor
#define RELAY_PIN 7  //pin del rele
#define pinVerde 2
#define pinAmarillo 3
#define pinRojo 4

NewPing sonar(TRIGGER_PIN, ECHO_PIN);

bool ledState = LOW;      // Estado inicial del LED

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);

  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  Serial.println("IO test");

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
}

void loop() {
  delay(100); // Puedes ajustar este valor según tus necesidades
  
  unsigned int distance = sonar.ping_cm();

  if (distance >= 20) {
    digitalWrite(RELAY_PIN, HIGH);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Distancia: ");
    display.print(distance);
    display.println(" cm");
    display.setCursor(0, 20); // Establece una nueva posición en el display
    display.println("ESTAS A SALVO");
    display.display();
  } else {
    digitalWrite(RELAY_PIN, LOW);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Distancia: ");
    display.print(distance);
    display.println(" cm");
    display.setCursor(0, 20); // Establece una nueva posición en el display
    display.println("HAY ALGO CERCA CUIDADO");
    display.display();
  }
  delay(500);
}
