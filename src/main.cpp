#include <Arduino.h>

/*************************************************************

Run following commands on Pio terminal  
  pio lib install  https://github.com/adafruit/Adafruit_Sensor
  pio lib install https://github.com/adafruit/DHT-sensor-library
 *************************************************************/


#define BLYNK_TEMPLATE_ID "TMPLtOsP0fb2"
#define BLYNK_DEVICE_NAME "DHTProjectTemp"
#define BLYNK_AUTH_TOKEN "1JsKuRc_9wciYaTxa3jmCsurlvm_nfzv"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "internetSaving";
char pass[] = "hamza455w";

#define DHTPIN 22          

#define DHTTYPE DHT11     // DHT 11 being used


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println(t);

  Blynk.virtualWrite(V0, t);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
