#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Your Wi-Fi credentials
const char *ssid = "ඞඞඞඞඞඞඞඞඞ";
const char *password = "12345678";

// API endpoint
const char *serverUrl = "http://192.168.242.36:8000/hrv/api/endpoint/";

// Define the GPIO pin connected to the DIN of the WS2812B
#define LED_PIN 4    // Change this to the GPIO pin you are using (e.g., GPIO 5)
#define NUMPIXELS 15 // Set this to the number of LEDs in your WS2812B strip

// // Create the NeoPixel object
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800); // Use NEO_GRB for WS2812B

// Color Wave Effect
void colorWaveEffect(uint8_t red, uint8_t green, uint8_t blue, int speed)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.clear();
    for (int j = 0; j < NUMPIXELS; j++)
    {
      int position = (i + j) % NUMPIXELS;
      uint8_t brightness = map(j, 0, NUMPIXELS, 0, 255); // Gradual fade
      pixels.setPixelColor(position, pixels.Color(red * brightness / 255, green * brightness / 255, blue * brightness / 255));
    }
    pixels.show();
    delay(speed);
  }
}

// Function to convert hex color string to RGB values
void hexToRGB(const char *hex, uint8_t &red, uint8_t &green, uint8_t &blue)
{
  if (hex[0] == '#')
    hex++; // Skip the '#' if present

  unsigned int hexValue;
  if (sscanf(hex, "%06x", &hexValue) == 1)
  {
    red = (hexValue >> 16) & 0xFF;
    green = (hexValue >> 8) & 0xFF;
    blue = hexValue & 0xFF;
  }
  else
  {
    red = green = blue = 0; // Default to black if parsing fails
  }
}

// Generate colors across a spectrum
uint32_t colorWheel(byte position)
{
  position = 255 - position;
  if (position < 85)
  {
    return pixels.Color(255 - position * 3, 0, position * 3);
  }
  else if (position < 170)
  {
    position -= 85;
    return pixels.Color(0, position * 3, 255 - position * 3);
  }
  else
  {
    position -= 170;
    return pixels.Color(position * 3, 255 - position * 3, 0);
  }
}

void rainbowEffect(int delayTime)
{
  for (int j = 0; j < 256; j++)
  { // Cycle through the color wheel
    for (int i = 0; i < NUMPIXELS; i++)
    {
      int wheelPos = (i * 256 / NUMPIXELS + j) & 255;
      pixels.setPixelColor(i, colorWheel(wheelPos));
    }
    pixels.show();
    delay(delayTime);
  }
}

// Pulsing Gray Effect (Breathing Light)
void pulsingGrayEffect(int delayTime)
{
  for (int brightness = 0; brightness <= 255; brightness += 5)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness, brightness, brightness));
    }
    pixels.show();
    delay(delayTime);
  }
  for (int brightness = 255; brightness >= 0; brightness -= 5)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness, brightness, brightness));
    }
    pixels.show();
    delay(delayTime);
  }
}

void dimRedGlowEffect(int delayTime)
{
  for (int brightness = 0; brightness <= 100; brightness += 5)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness, 0, 0)); // Dim red
    }
    pixels.show();
    delay(delayTime);
  }
  for (int brightness = 100; brightness >= 0; brightness -= 5)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness, 0, 0)); // Dim red
    }
    pixels.show();
    delay(delayTime);
  }
}

void softPulsingOrange(int delayTime)
{
  for (int brightness = 50; brightness <= 150; brightness += 5)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness, brightness / 2, 0)); // Warm orange
    }
    pixels.show();
    delay(delayTime);
  }
  for (int brightness = 150; brightness >= 50; brightness -= 5)
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, pixels.Color(brightness, brightness / 2, 0));
    }
    pixels.show();
    delay(delayTime);
  }
}

void setup()
{
  Serial.begin(9600);

  // Initialize NeoPixel
  pixels.begin();
  pixels.show(); // Turn off all LEDs initially

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(serverUrl);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
      String response = http.getString();

      // Parse the JSON response
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (!error)
      {
        // Check if 'color' key exists and retrieve its value
        if (doc.containsKey("color"))
        {
          const char *colorHex = doc["color"];
          Serial.print("Received Color Hex: ");
          Serial.println(colorHex);

          // Check if the color is #FF69B4 (Hot Pink)
          if (strcmp(colorHex, "#FF69B4") == 0)
          {
            Serial.println("Triggering Rainbow Effect...");
            rainbowEffect(25); // Trigger rainbow effect
          }
          else if (strcmp(colorHex, "bad_signal") == 0)
          {
            Serial.println("Triggering Error Effect...");
            dimRedGlowEffect(25);
          }
          else if (strcmp(colorHex, "loading") == 0)
          {
            Serial.println("Triggering Pulsing Gray Effect...");
            pulsingGrayEffect(10);
          }
          else
          {
            // Convert hex to RGB and apply color wave effect
            uint8_t red, green, blue;
            hexToRGB(colorHex, red, green, blue);
            Serial.printf("Setting Color: R=%d, G=%d, B=%d\n", red, green, blue);
            colorWaveEffect(red, green, blue, 50); // Apply color wave effect
          }
        }
        else
        {
          Serial.println("Error: 'color' key not found in JSON response.");
        }
      }
      else
      {
        Serial.println("Error parsing JSON: " + String(error.c_str()));
      }
    }
    else
    {
      Serial.println("Error on HTTP request, code: " + String(httpResponseCode));
    }

    http.end();
  }
  else
  {
    Serial.println("Wi-Fi disconnected, retrying...");
    WiFi.reconnect();
  }

  delay(500); // Wait 0.5 seconds before the next request
}