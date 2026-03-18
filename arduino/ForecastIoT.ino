#include "DHT.h"
#include "WiFiS3.h"

// DHT11 sensor configuration
#define DHTPIN    2
#define DHTTYPE   DHT11
DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
char ssid[] = "<your-wifi-ssid>";
char pass[] = "<your-wifi-password>";

// Backend server
char server[] = "<your-backend-server-ip>";
int  port     = 3000;

WiFiClient client;

// Interval between sensor reads (milliseconds)
const unsigned long READ_INTERVAL = 5000;
unsigned long lastReadTime = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected to WiFi.");
  Serial.print("Device IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Ready. Sending readings every 5 seconds.\n");
}

void loop() {
  unsigned long now = millis();

  // Only read and send after the interval has elapsed
  if (now - lastReadTime < READ_INTERVAL) {
    return;
  }
  lastReadTime = now;

  float humidity    = dht.readHumidity();
  float temperature = dht.readTemperature();  // Celsius

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("[ERROR] Failed to read from DHT11 sensor. Check wiring.");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperature, 1);
  Serial.print(" C  |  Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  sendReading(temperature, humidity);
}

/*
 * Builds and sends an HTTP POST request with a JSON body to the backend.
 * Endpoint: POST /api/readings
 */
void sendReading(float temperature, float humidity) {
  if (!client.connect(server, port)) {
    Serial.println("[ERROR] Could not connect to backend server.");
    return;
  }

  // Build the JSON payload
  String body = "{\"temperature\":" + String(temperature, 2)
              + ",\"humidity\":"    + String(humidity, 2) + "}";

  // Send the HTTP request
  client.println("POST /api/readings HTTP/1.1");
  client.println("Host: " + String(server));
  client.println("Content-Type: application/json");
  client.println("Content-Length: " + String(body.length()));
  client.println("Connection: close");
  client.println();
  client.println(body);

  Serial.print("[POST] Body sent: ");
  Serial.println(body);

  // Read and print the server response status line
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("[ERROR] Server response timed out.");
      client.stop();
      return;
    }
  }

  // Print only the first response line (status) to Serial for debugging
  if (client.available()) {
    String statusLine = client.readStringUntil('\n');
    Serial.print("[RESPONSE] ");
    Serial.println(statusLine);
  }

  client.stop();
}
