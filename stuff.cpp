// void displayColor(uint8_t red, uint8_t green, uint8_t blue)
// {
//   for (int i = 0; i < NUMPIXELS; i++)
//   {
//     pixels.setPixelColor(i, pixels.Color(red, green, blue));
//   }
//   pixels.show(); // Update the LEDs to show the color
// }

// void pureBlue()
// {
//   displayColor(74, 229, 254); // Light blue color
// }

// void alternateRedBlue()
// {
//   for (int i = 0; i < NUMPIXELS; i++)
//   {
//     if (i % 2 == 0)
//     {
//       pixels.setPixelColor(i, pixels.Color(253, 151, 103)); // Red color
//     }
//     else
//     {
//       pixels.setPixelColor(i, pixels.Color(74, 229, 254)); // Blue color
//     }
//   }
//   pixels.show(); // Update the LEDs to show the colors
// }

// void greyWithRed()
// {
//   int redCount = 0; // Counter to track the number of red LEDs

//   for (int i = 0; i < NUMPIXELS; i++)
//   {
//     if (redCount < 4 && i % (NUMPIXELS / 4) == 0)
//     {                                                       // Space out 4 red LEDs evenly
//       pixels.setPixelColor(i, pixels.Color(253, 151, 103)); // Red color
//       redCount++;
//     }
//     else
//     {
//       pixels.setPixelColor(i, pixels.Color(70, 70, 70)); // Grey color
//     }
//   }
//   pixels.show(); // Update the LEDs to show the colors
// }

// void pulsingGrey()
// {
//   for (int brightness = 50; brightness <= 255; brightness += 5)
//   {
//     pixels.setBrightness(brightness);
//     displayColor(70, 70, 70); // Grey color
//     delay(20);
//   }
//   for (int brightness = 255; brightness >= 50; brightness -= 5)
//   {
//     pixels.setBrightness(brightness);
//     displayColor(70, 70, 70); // Grey color
//     delay(20);
//   }
// }

// void trailingLight()
// {
//   int tailLength = 5;                                                                              // Number of LEDs to light up in the "trail"
//   uint32_t colors[] = {pixels.Color(255, 0, 0), pixels.Color(0, 255, 0), pixels.Color(0, 0, 255)}; // Red, Green, Blue
//   int numColors = sizeof(colors) / sizeof(colors[0]);

//   for (int pos = 0; pos < NUMPIXELS + tailLength; pos++)
//   {
//     // Clear all LEDs
//     pixels.clear();

//     // Draw the "trail"
//     for (int i = 0; i < tailLength; i++)
//     {
//       int currentPos = pos - i;

//       if (currentPos >= 0 && currentPos < NUMPIXELS)
//       {
//         // Pick a color for the current segment
//         int colorIndex = (currentPos / tailLength) % numColors;
//         pixels.setPixelColor(currentPos, colors[colorIndex]);
//       }
//     }

//     // Show the updated LED strip
//     pixels.show();
//     delay(100);
//   }
// }

// void breathingEffect(uint8_t red, uint8_t green, uint8_t blue, int speed)
// {
//   for (int brightness = 50; brightness <= 255; brightness += 5)
//   {
//     pixels.setBrightness(brightness);
//     displayColor(red, green, blue);
//     delay(speed); // Higher speed for quicker pulses
//   }
//   for (int brightness = 255; brightness >= 50; brightness -= 5)
//   {
//     pixels.setBrightness(brightness);
//     displayColor(red, green, blue);
//     delay(speed);
//   }
// }

// // Trailing Light Effect: Simulates increasing stress
// void trailingLightEffect(uint8_t stressLevel)
// {
//   int tailLength = map(stressLevel, 0, 100, 3, 10); // Tail grows as stress increases
//   uint8_t red = map(stressLevel, 0, 100, 0, 255);   // Color shifts to red as stress increases
//   uint8_t green = map(stressLevel, 0, 100, 255, 0); // Color shifts from green to red
//   uint8_t blue = 0;                                 // Blue remains off

//   for (int pos = 0; pos < NUMPIXELS + tailLength; pos++)
//   {
//     pixels.clear(); // Clear LEDs for each frame

//     // Draw the "trail"
//     for (int i = 0; i < tailLength; i++)
//     {
//       int currentPos = pos - i;

//       if (currentPos >= 0 && currentPos < NUMPIXELS)
//       {
//         pixels.setPixelColor(currentPos, pixels.Color(red, green, blue));
//       }
//     }

//     pixels.show();
//     delay(map(stressLevel, 0, 100, 100, 20)); // Speed increases with stress
//   }
// }

// // Generate colors across a spectrum
// uint32_t colorWheel(byte position)
// {
//   position = 255 - position;
//   if (position < 85)
//   {
//     return pixels.Color(255 - position * 3, 0, position * 3);
//   }
//   else if (position < 170)
//   {
//     position -= 85;
//     return pixels.Color(0, position * 3, 255 - position * 3);
//   }
//   else
//   {
//     position -= 170;
//     return pixels.Color(position * 3, 255 - position * 3, 0);
//   }
// }

// void rainbowEffect(int delayTime)
// {
//   for (int j = 0; j < 256; j++)
//   { // Cycle through the color wheel
//     for (int i = 0; i < NUMPIXELS; i++)
//     {
//       int wheelPos = (i * 256 / NUMPIXELS + j) & 255;
//       pixels.setPixelColor(i, colorWheel(wheelPos));
//     }
//     pixels.show();
//     delay(delayTime);
//   }
// }

// void colorWaveEffect(uint8_t red, uint8_t green, uint8_t blue, int speed)
// {
//   for (int i = 0; i < NUMPIXELS; i++)
//   {
//     pixels.clear();
//     for (int j = 0; j < NUMPIXELS; j++)
//     {
//       int position = (i + j) % NUMPIXELS;
//       uint8_t brightness = map(j, 0, NUMPIXELS, 0, 255); // Gradual fade
//       pixels.setPixelColor(position, pixels.Color(red * brightness / 255, green * brightness / 255, blue * brightness / 255));
//     }
//     pixels.show();
//     delay(speed);
//   }
// }

// void stressPulseEffect(int stressLevel)
// {
//   uint8_t red = map(stressLevel, 0, 100, 0, 255);
//   uint8_t green = map(stressLevel, 0, 100, 255, 0);

//   for (int size = 1; size <= NUMPIXELS / 2; size++)
//   {
//     pixels.clear();

//     // Illuminate the "pulse"
//     for (int i = NUMPIXELS / 2 - size; i <= NUMPIXELS / 2 + size; i++)
//     {
//       if (i >= 0 && i < NUMPIXELS)
//       {
//         pixels.setPixelColor(i, pixels.Color(red, green, 0));
//       }
//     }

//     pixels.show();
//     delay(50);
//   }

//   // Shrink back
//   for (int size = NUMPIXELS / 2; size >= 1; size--)
//   {
//     pixels.clear();

//     for (int i = NUMPIXELS / 2 - size; i <= NUMPIXELS / 2 + size; i++)
//     {
//       if (i >= 0 && i < NUMPIXELS)
//       {
//         pixels.setPixelColor(i, pixels.Color(red, green, 0));
//       }
//     }

//     pixels.show();
//     delay(50);
//   }
// }

// void waveSweepEffect(uint8_t red, uint8_t green, uint8_t blue, int speed)
// {
//   for (int i = 0; i < NUMPIXELS; i++)
//   {
//     pixels.clear();

//     // Light up the current LED and fade the previous ones
//     for (int j = 0; j <= i; j++)
//     {
//       uint8_t fade = map(j, 0, i, 50, 255); // Gradual fade
//       pixels.setPixelColor(j, pixels.Color(red * fade / 255, green * fade / 255, blue * fade / 255));
//     }

//     pixels.show();
//     delay(speed);
//   }
// }

// void fireEffect()
// {
//   for (int i = 0; i < NUMPIXELS; i++)
//   {
//     uint8_t red = random(200, 255); // Flickering red-orange
//     uint8_t green = random(50, 150);
//     uint8_t blue = 0; // Fire has no blue
//     pixels.setPixelColor(i, pixels.Color(red, green, blue));
//   }
//   pixels.show();
//   delay(50); // Rapid flickering
// }

// // Simulates user stress transitioning from low to high
// void stressSimulation()
// {
//   for (uint8_t stressLevel = 0; stressLevel <= 100; stressLevel += 5)
//   {
//     // Use one of the effects (trailingLightEffect or waterfallEffect)
//     Serial.print("Stress Level: ");
//     Serial.println(stressLevel);
//     trailingLightEffect(stressLevel);
//     // rainbowEffect(stressLevel);
//     // stressPulseEffect(stressLevel);
//   }
// }

// void setup()
// {
//   pixels.begin(); // Initialize the NeoPixel library
//   pixels.show();  // Turn off all LEDs initially
//   pixels.setBrightness(255); // Default brightness
// }

// void loop()
// {
//   stressSimulation(); // Run the stress simulation
//   delay(1000);        // Pause before repeating

//   // pureBlue();
//   // delay(1000);

//   // alternateRedBlue();
//   // delay(1000);

//   // greyWithRed();
//   // delay(1000);

//   // pulsingGrey();
//   // delay(1000);

//   // trailingLight();
//   // delay(1000);

//   // colorWaveEffect(0, 0, 255, 50); // Blue wave moving across strip
//   // delay(1000);

//   // rainbowEffect(20); // Beautiful rainbow gradient
//   // delay(1000);

//   // stressPulseEffect(50); // Pulsing LEDs
//   // delay(1000);
// }
