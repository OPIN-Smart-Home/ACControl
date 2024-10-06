#include <WiFi.h>
#include <Wire.h>
#include <IRac.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <WiFiManager.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MAX1704X.h>

#include <PicoMQTT.h>
#define PICOMQTT_MAX_MESSAGE_SIZE 3072

#define LED 14
#define SDA 21
#define SCL 22
#define RECEIVER 18
#define TRANSMITTER 19
#define WIFI_BUTTON 13

int push_count;
int kHzFreq = 38;
int wifi_timeout = 90; // seconds
const long intervalTemp = 3000; // milliseconds
unsigned long start_time;
unsigned long previousMillis = 0;
const uint8_t kTimeout = 50;
const uint8_t kTolerancePercentage = kTolerance;
const uint16_t kCaptureBufferSize = 1024;

String Wifissid;
String commandMsg = "";
Adafruit_BME280 bme;
Adafruit_MAX17048 maxlipo;
PicoMQTT::Server mqtt;
decode_results results;
IRsend ac(TRANSMITTER);
IRrecv irrecv(RECEIVER, kCaptureBufferSize, kTimeout, true);

// DEVICE ID
const char* topic_r2u = "opin/ACControl_bx97c/r2u";
const char* topic_d2u = "opin/ACControl_bx97c/d2u";
const char* topic_u2d = "opin/ACControl_bx97c/u2d";
const char* device_ssid = "OPIN-ACControl-bx97c";

void connect_mqtt() {
  Serial.println("\nStart MQTT Broker");
  const char* mqtt_server = WiFi.localIP().toString().c_str();

  // Subscribe to a topic pattern and attach a callback
  mqtt.subscribe(topic_u2d, [](const char * topic, const String & payload) {
    Serial.printf("Received message in topic '%s': %s\n", topic, payload.c_str());
    commandMsg = String(payload);
  });

  // Start the broker
  mqtt.begin();

  delay(130);
  Serial.println("MQTT Broker ready");
}

void connect_wifi() {
  Serial.println("\n Connecting...");
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  WiFiManager wm;
  wm.setConnectTimeout(5);
  wm.setConfigPortalTimeout(wifi_timeout);
  wm.startConfigPortal(device_ssid);

  if (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }else if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected");
    connect_mqtt();
  }
}

void reset_wifi() {
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);

  WiFiManager wm;
  WiFi.disconnect();
  wm.resetSettings();
}

void reconnect_wifi(String ssid, String pass) {
  delay(100);
  Serial.println("Reconnecting...");
  WiFi.disconnect();
  WiFi.begin(ssid, pass);

  unsigned long start_timeout = millis();
  while (WiFi.status() != WL_CONNECTED){
    if (millis() - start_timeout >= 3000){
      break;
    }
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("Connected");
    connect_mqtt();
  }
}

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  Serial.println("\n Starting up");
  pinMode(LED, OUTPUT);
  pinMode(WIFI_BUTTON, INPUT_PULLUP);

  ac.begin();
  Wire.begin(SDA, SCL);
  bme.begin(0x76, &Wire);
  maxlipo.begin();
  delay(100);

  assert(irutils::lowLevelSanityCheck() == 0);
  irrecv.setTolerance(kTolerancePercentage);
  irrecv.enableIRIn();
  delay(100);
}

void loop() {
  // WIFI and MQTT Connection
  push_count = 0;
  if (digitalRead(WIFI_BUTTON) == LOW) {
    start_time = millis();
    while (true) {
      if (millis() - start_time >= 100 && digitalRead(WIFI_BUTTON) == HIGH) {
        push_count = 1;
        break;
      }
      if (millis() - start_time >= 2000 && digitalRead(WIFI_BUTTON) == LOW) {
        push_count = 2;
        break;
      }
    }
  }

  if (push_count == 1) {
    connect_wifi();
  } else if (push_count == 2) {
    reset_wifi();
    connect_wifi();
  }

  if (WiFi.status() != WL_CONNECTED){
    WiFiManager wm;
    reconnect_wifi(wm.getWiFiSSID(), WiFi.psk());
  } else {
    mqtt.loop();
    digitalWrite(LED, HIGH);
  }

  // Main Program
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalTemp) {
    float vbatt = readBattVoltage();
    float lbatt = readBattLevel();
    float temp = readTemp();
    float humi = readHumidity();
    Serial.println();
    Serial.print(F("Batt Voltage: ")); Serial.print(vbatt, 3); Serial.println(" V");
    Serial.print(F("Batt Percent: ")); Serial.print(lbatt, 2); Serial.println(" %");
    Serial.print("Temperature = "); Serial.print(temp); Serial.println(" °C");
    Serial.print("Humidity = "); Serial.print(humi); Serial.println(" %");
    String json_data =  String("{") +
                        String("\"batt_voltage\":") + String(vbatt, 3) + String(",") +
                        String("\"batt_percent\":") + String(lbatt, 2) + String(",") +
                        String("\"temperature\":") + String(temp) + String(",") +
                        String("\"humidity\":") + String(humi) +
                        String("}");
    mqtt.publish(topic_d2u, json_data.c_str());
    previousMillis = currentMillis;
  }
  if (commandMsg.length() > 0) {
    controlAC(commandMsg);
  }
  if (irrecv.decode(&results) && WiFi.status() == WL_CONNECTED) {
    updateAC();
  }
  commandMsg = "";
  delay(10);
}

float readBattVoltage() {
  return maxlipo.cellVoltage();
}

float readBattLevel() {
  return maxlipo.cellPercent();
}

float readTemp() {
  return bme.readTemperature();
}

float readHumidity() {
  return bme.readHumidity();
}

String extractValue(String keyValuePair) {
    int colonIndex = keyValuePair.indexOf(":");
    return keyValuePair.substring(colonIndex + 2, keyValuePair.indexOf(","));
}

void updateAC() {
  String result_code = resultToSourceCode(&results);
  String description = IRAcUtils::resultAcToString(&results);
  String result_basic = resultToHumanReadableBasic(&results);
  
  Serial.print(result_basic);
  Serial.println(description);
  Serial.println(result_code);

  String protocol = result_basic.substring(result_basic.indexOf(":") + 2, result_basic.indexOf("\n"));
  if (protocol == "PANASONIC_AC") {
    String powerValue = extractValue(description.substring(description.indexOf("Power")));
    String tempValue = extractValue(description.substring(description.indexOf("Temp")));
    tempValue = tempValue.substring(0, tempValue.indexOf("C"));
    String fanValue = extractValue(description.substring(description.indexOf("Fan")));
    fanValue = fanValue.substring(0, fanValue.indexOf("(") - 1);
    String swingValue = extractValue(description.substring(description.indexOf("Swing")));
    swingValue = swingValue.substring(0, swingValue.indexOf("(") - 1);
    String json_data =  String("{") +
                        String("\"protocol\":") + String("\"") + protocol + String("\"") + String(",") +
                        String("\"power\":") + String("\"") + powerValue + String("\"") + String(",") +
                        String("\"temp\":") + String("\"") + tempValue + String("\"") + String(",") +
                        String("\"fan\":") + String("\"") + fanValue + String("\"") + String(",") +
                        String("\"swing\":") + String("\"") + swingValue + String("\"") + 
                        String("}");
    Serial.println("Sending remote data...");
    mqtt.publish(topic_r2u, json_data.c_str());
  }
}

void controlAC(String commandMsg) {
  Serial.println(commandMsg);

  int openBraceIndex = commandMsg.indexOf("{");
  int closeBraceIndex = commandMsg.indexOf("}");
  int rawDataLength = commandMsg.substring(0, openBraceIndex).toInt();
  String rawDatasString = commandMsg.substring(openBraceIndex+1, closeBraceIndex);
  
  int rawDataIndex = 0;
  int commaIndex = rawDatasString.indexOf(',');
  uint16_t rawData[rawDataLength];

  while (commaIndex != -1) {
    String rawDataStr = rawDatasString.substring(0, commaIndex);
    rawData[rawDataIndex] = rawDataStr.toInt();
    rawDatasString = rawDatasString.substring(commaIndex + 1);
    commaIndex = rawDatasString.indexOf(',');
    rawDataIndex++;
  }
  rawData[rawDataIndex] = rawDatasString.toInt();
  Serial.println("Sending user request...");
  ac.sendRaw(rawData, rawDataLength, kHzFreq);
}