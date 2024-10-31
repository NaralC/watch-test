#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

// Your Wi-Fi credentials
const char *ssid = "ඞඞඞඞඞඞඞඞඞ";
const char *password = "12345678";

// API endpoint
const char *serverUrl = "http://192.168.82.36:8000/hrv/api/endpoint/";

// Define the pin connected to the NeoPixel Data In
#define LED_PIN 12   // Change this to the GPIO pin you’re using (e.g., GPIO 5)
#define NUMPIXELS 16 // Set this to the number of LEDs on your NeoPixel or NeoFruit ring

// Create the NeoPixel object
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRBW + NEO_KHZ800); // Use NEO_GRB for RGB, NEO_GRBW for RGBW

// Helper function to set all pixels to the same color
void displayColor(uint8_t red, uint8_t green, uint8_t blue)
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  pixels.show(); // Update the LEDs to show the color
}

// 1. Alternate Blue and Green Effect (entire ring alternates color)
void alternateBlueGreen()
{
  displayColor(0, 255, 0); // Green
  delay(500);
  displayColor(0, 0, 255); // Blue
  delay(500);
}

// 3. Grey with Random Colors Effect
void greyWithRandomColors()
{
  for (int i = 0; i < NUMPIXELS; i++)
  {
    displayColor(random(255), random(255), random(255));
  }
  pixels.show();
}

// 4. Grey with Lighting Effect (Pulsing Effect)
void greyLightingEffect()
{
  for (int brightness = 50; brightness <= 255; brightness += 5)
  {
    pixels.setBrightness(brightness);
    displayColor(70, 70, 70); // Grey color
    delay(20);
  }
  for (int brightness = 255; brightness >= 50; brightness -= 5)
  {
    pixels.setBrightness(brightness);
    displayColor(70, 70, 70); // Grey color
    delay(20);
  }
}

void setup()
{
  pixels.begin(); // Initialize the NeoPixel library
  pixels.show();  // Turn off all LEDs initially
  pixels.setBrightness(30);
}

void loop()
{
  // 1. Alternate between blue and green
  alternateBlueGreen();
  delay(1000);

  // 2. Solid orange
  displayColor(255, 145, 0); // Orange color
  delay(1000);

  // 3. Grey with random colors
  greyWithRandomColors();
  delay(1000);

  // 4. Grey with lighting effect
  greyLightingEffect();
  delay(1000);
}

// void setup()
// {
//   Serial.begin(9600);

//   // Initialize NeoPixel
//   pixels.begin();
//   pixels.show(); // Turn off all LEDs initially
//   pixels.setBrightness(50);

//   // Connect to Wi-Fi
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to Wi-Fi");
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(1000);
//     Serial.print(".");
//   }
//   Serial.println("\nConnected to Wi-Fi");
// }

// void loop()
// {
//   if (WiFi.status() == WL_CONNECTED)
//   {
//     HTTPClient http;
//     http.begin(serverUrl);
//     int httpResponseCode = http.GET();

//     if (httpResponseCode > 0)
//     {
//       String response = http.getString();
//       // Serial.println("HTTP Response code: " + String(httpResponseCode));
//       // Serial.println("Raw Response:");
//       // Serial.println(response);

//       // Clean up response by removing outer quotes and escape characters
//       if (response.startsWith("\"") && response.endsWith("\""))
//       {
//         response = response.substring(1, response.length() - 1); // Remove outer quotes
//       }
//       response.replace("\\n", "");    // Remove newlines
//       response.replace("\\\"", "\""); // Replace escaped quotes with normal quotes
//       response.trim();                // Remove any extra spaces

//       // Serial.println("Cleaned Response:");
//       // Serial.println(response); // Print cleaned response to confirm

//       // Parse the cleaned JSON response
//       StaticJsonDocument<1024> doc;
//       DeserializationError error = deserializeJson(doc, response);

//       if (!error)
//       {
//         // Debug print the full parsed JSON structure
//         // Serial.println("Parsed JSON:");
//         // serializeJsonPretty(doc, Serial);
//         // Serial.println();

//         // Check if 'sdnn' key exists and retrieve its value
//         if (doc.containsKey("sdnn"))
//         {
//           float sdnn = doc["sdnn"];
//           Serial.println("sdnn: " + String(sdnn));

//           // Set color based on sdnn value
//           if (sdnn < 20)
//           {
//             displayColor(255, 160, 60); // Warm, bright color for low stress
//           }
//           else if (sdnn >= 50 && sdnn <= 140)
//           {
//             displayColor(0, 0, 139); // Dark blue for moderate stress
//           }
//           else
//           {
//             displayColor(105, 105, 105); // Dark grey for high stress
//           }
//         }
//         else
//         {
//           Serial.println("Error: 'sdnn' key not found in JSON response.");
//         }
//       }
//       else
//       {
//         Serial.println("Error parsing JSON: " + String(error.c_str()));
//       }
//     }
//     else
//     {
//       Serial.println("Error on HTTP request, code: " + String(httpResponseCode));
//     }

//     http.end();
//   }
//   else
//   {
//     Serial.println("Wi-Fi disconnected, retrying...");
//     WiFi.reconnect();
//   }

//   delay(5000);
// }
