#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

// Your Wi-Fi credentials
const char *ssid = "wifi-name";
const char *password = "wifi-password";

// API endpoint
const char *serverUrl = "local-python-server-ipv4-address-to-fetch-api";

void setup()
{
  // Start the Serial communication to debug and monitor
  // Serial.begin(115200);
  Serial.begin(9600);

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
  // Ensure we're connected to Wi-Fi
  if (WiFi.status() == WL_CONNECTED)
  {
    // Declare an HTTPClient object
    HTTPClient http;

    // Make the HTTP GET request
    http.begin(serverUrl);
    int httpResponseCode = http.GET();

    // Check for a valid response
    if (httpResponseCode > 0)
    {
      String response = http.getString(); // Get the response payload
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Response:");
      Serial.println(response); // Print the JSON response to the Serial Monitor

      // TODO: Parse JSON response and use the data as needed
    }
    else
    {
      Serial.println("Error on HTTP request, code: " + String(httpResponseCode));
    }

    // Close the connection
    http.end();
  }
  else
  {
    Serial.println("Wi-Fi disconnected, retrying...");
    WiFi.reconnect();
  }

  // Wait 5 seconds before making the next request
  delay(5000);
}

// // Define the LED pin (use the built-in LED for most ESP32 boards, which is GPIO 2)
// #define LED_PIN 2

// void setup() {
//   // Initialize the LED pin as an output
//   pinMode(LED_PIN, OUTPUT);
//   Serial.begin(115200);
// }

// void loop() {
//   // Turn the LED on (HIGH is the voltage level)
//   digitalWrite(LED_PIN, HIGH);
//   // Wait for a second
//   delay(1000);
//   // Turn the LED off by making the voltage LOW
//   digitalWrite(LED_PIN, LOW);
//   // Wait for a second
//   delay(1000);

//   Serial.println("Extremely sussy");
// }
