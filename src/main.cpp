#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// TODO: have a placeholder color for when data's not ready
// TODO: colors 40-60 for orange/yellow

// Your Wi-Fi credentials
const char *ssid = "ඞඞඞඞඞඞඞඞඞ";
const char *password = "12345678";

// API endpoint
const char *serverUrl = "http://192.168.84.36:8000/hrv/api/endpoint/";

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

// // Generate colors across a spectrum
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
  for (int j = 0; j < 256; j++) // Cycle through the color wheel
  {
    for (int i = 0; i < NUMPIXELS; i++)
    {
      int wheelPos = (i * 256 / NUMPIXELS + j) & 255;
      pixels.setPixelColor(i, colorWheel(wheelPos));
    }
    pixels.show();
    delay(delayTime); // Adjust speed of the rainbow effect
  }
}

// void mockStressSimulation()
// {
//   for (float sdnn = 0; sdnn <= 90; sdnn += 5) // Simulating SDNN from 0 to 100
//   {
//     Serial.print("Mock SDNN: ");
//     Serial.println(sdnn);

//     uint8_t red, green, blue;

//     // Determine color mapping based on SDNN range
//     // High stress
//     if (sdnn <= 0)
//     {
//       red = 0;
//       green = 0;
//       blue = 0;
//     }
//     else if (sdnn <= 20)
//     {
//       // Blue
//       red = 0;
//       green = 0;
//       blue = 255;
//     }
//     else if (sdnn > 20 && sdnn <= 30)
//     {
//       // Purple
//       red = 128;
//       green = 0;
//       blue = 128;
//     }
//     else if (sdnn > 30 && sdnn <= 40)
//     {
//       // Pink
//       red = 255;
//       green = 105;
//       blue = 180;
//     }
//     else if (sdnn > 40 && sdnn <= 50)
//     {
//       // Yellow
//       red = 255;
//       green = 158;
//       blue = 0;
//     }
//     else if (sdnn > 50 && sdnn <= 70)
//     {
//       // Orange
//       red = 255;
//       green = 100;
//       blue = 0;
//     }
//     else
//     {
//       rainbowEffect(20);
//     }
//     // Low stress

//     // Call colorWaveEffect with the mapped colors
//     colorWaveEffect(red, green, blue, 70); // Speed of the wave

//     delay(5); // Delay to visualize the change
//   }

//   for (float sdnn = 90; sdnn >= 0; sdnn -= 5) // Simulating SDNN back from 100 to 0
//   {
//     Serial.print("Mock SDNN: ");
//     Serial.println(sdnn);

//     uint8_t red, green, blue;

//     // Determine color mapping based on SDNN range
//     // High stress
//     if (sdnn <= 0)
//     {
//       red = 0;
//       green = 0;
//       blue = 0;
//     }
//     else if (sdnn <= 20)
//     {
//       // Blue
//       red = 0;
//       green = 0;
//       blue = 255;
//     }
//     else if (sdnn > 20 && sdnn <= 30)
//     {
//       // Purple
//       red = 128;
//       green = 0;
//       blue = 128;
//     }
//     else if (sdnn > 30 && sdnn <= 40)
//     {
//       // Pink
//       red = 255;
//       green = 105;
//       blue = 140;
//     }
//     else if (sdnn > 40 && sdnn <= 50)
//     {
//       // Yellow
//       red = 255;
//       green = 158;
//       blue = 0;
//     }
//     else if (sdnn > 50 && sdnn <= 70)
//     {
//       // Orange
//       red = 255;
//       green = 100;
//       blue = 0;
//     }
//     else
//     {
//       rainbowEffect(20);
//     }
//     // Low stress

//     // Call colorWaveEffect with the mapped colors
//     colorWaveEffect(red, green, blue, 70); // Speed of the wave

//     delay(5); // Delay to visualize the change
//   }
// }

// void setup()
// {
//   Serial.begin(9600);

//   // Initialize NeoPixel
//   pixels.begin();
//   pixels.show();             // Turn off all LEDs initially
//   pixels.setBrightness(100); // Set brightness for vibrant colors
// }

// void loop()
// {
//   // Run the mock stress simulation
//   mockStressSimulation();
// }

void setup()
{
  Serial.begin(9600);

  // Initialize NeoPixel
  pixels.begin();
  pixels.show(); // Turn off all LEDs initially
  // pixels.setBrightness(50);

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

      // Clean up response by removing outer quotes and escape characters
      if (response.startsWith("\"") && response.endsWith("\""))
      {
        response = response.substring(1, response.length() - 1); // Remove outer quotes
      }
      response.replace("\\n", "");    // Remove newlines
      response.replace("\\\"", "\""); // Replace escaped quotes with normal quotes
      response.trim();                // Remove any extra spaces

      // Parse the cleaned JSON response
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, response);

      if (!error)
      {
        // Check if 'sdnn' key exists and retrieve its value
        if (doc.containsKey("sdnn"))
        {
          float sdnn = doc["sdnn"];
          Serial.println("sdnn: " + String(sdnn));

          if (sdnn > 70)
          {
            // Rainbow effect for low stress
            rainbowEffect(20);
          }
          else
          {
            // Map SDNN to colors based on the specified ranges
            uint8_t red = 0, green = 0, blue = 0;

            if (sdnn <= 0) {
              // No signal or high stress
              red = 0;
              green = 0;
              blue = 0;
            }
            else if (sdnn <= 20)
            {
              // Blue
              red = 0;
              green = 0;
              blue = 255;
            }
            else if (sdnn > 20 && sdnn <= 30)
            {
              // Purple
              red = 128;
              green = 0;
              blue = 128;
            }
            else if (sdnn > 30 && sdnn <= 40)
            {
              // Pink
              red = 255;
              green = 105;
              blue = 140;
            }
            else if (sdnn > 40 && sdnn <= 50)
            {
              // Yellow
              red = 255;
              green = 158;
              blue = 0;
            }
            else if (sdnn > 50 && sdnn <= 70)
            {
              // Orange
              red = 255;
              green = 100;
              blue = 0;
            }

            // Call colorWaveEffect with the mapped colors
            colorWaveEffect(red, green, blue, 50); // Speed of the wave
          }
        }
        else
        {
          Serial.println("Error: 'sdnn' key not found in JSON response.");
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

// TODO: have a placeholder liht when switching the watch