#include <WiFi.h>
#include <SPI.h>
#include <PubSubClient.h>
#include <ESPping.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>


//esp pins
#define BME_SCK 18 //SCL
#define BME_MISO 19 //SDO
#define BME_MOSI 23 //SDA
#define BME_CS 5 //CSB

#define SEALEVELPRESSURE_HPA (1013.25)

/*ENVIRONMENT VARIABLES*/
constexpr char WIFI_SSID[] = "wifi-ssid";
constexpr char WIFI_PASSWORD[] = "wifi-password";
constexpr char TOKEN[] = "access token"; 
constexpr char DEVICE_ID[] = "device id";
constexpr char THINGSBOARD_SERVER[] = "thingsboard.cloud";
constexpr char THINGSBOARD_TELEMETRY_ENDPOINT[] = "v1/devices/me/telemetry";
constexpr uint16_t THINGSBOARD_PORT = 1883U;

/*wifi and bme libraries setup*/
WiFiClient wifiClient;
PubSubClient client(wifiClient);

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI


void setup() {
//initialize serial for debugging and print result
  Serial.begin(9600);
  
//initialize BME
  Serial.println(F("BME280 test"));
 
  bool status;
  status = bme.begin();  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

//WiFi Connection
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("[DONE]");

//thingsboard server initialization
  client.setServer( THINGSBOARD_SERVER, THINGSBOARD_PORT); 
}
  

/*function to get data and send it to thingsboard*/
void sendData()
{
// read bme returned values 
  float temperature = bme.readTemperature();
  float pression = bme.readPressure();
  float humidite = bme.readHumidity();

//string payloads to format telemetry in json
  String payload_temperature = "{";
  payload_temperature += "\"Temperature\":";
  payload_temperature += temperature;
  payload_temperature += "}";

  String payload_pression = "{";
  payload_pression += "\"Pression\":";
  payload_pression += pression/100.0F;
  payload_pression += "}";

  String payload_humidite = "{";
  payload_humidite += "\"Humidite\":";
  payload_humidite += humidite;
  payload_humidite += "}";

  char data_temperature[1000];
  char data_pression[1000];
  char data_humidite[1000];
  payload_temperature.toCharArray(data_temperature,1000);
  payload_pression.toCharArray(data_pression,1000);
  payload_humidite.toCharArray(data_humidite,1000);

//send json telemetry to thingsboard
  client.publish(THINGSBOARD_TELEMETRY_ENDPOINT,data_temperature);
  client.publish(THINGSBOARD_TELEMETRY_ENDPOINT,data_pression);
  client.publish(THINGSBOARD_TELEMETRY_ENDPOINT,data_humidite);

  Serial.println(data_temperature);
  Serial.println(data_pression);
  Serial.println(data_humidite);
}


void loop() {
  bool success = Ping.ping("google.com", 3);
  if(success){
    Serial.println();
    Serial.println("Connected to internet!");
    Serial.println();
  }
  else {
    Serial.println();
    Serial.println("Can't connect to internet");
    Serial.println();
    return;
  }

//if esp not connected to thingsboard, connect
  if ( !client.connected() )
  {
    tbConnect();
  }
//send data from bme to thingsboard
  sendData();

  delay(5000);
}


/*connection to thingsboard*/
void tbConnect() {
  Serial.print("Connecting to ThingsBoard node ...");
  if ( client.connect(DEVICE_ID, TOKEN, "") ) {
    Serial.println( "[DONE]" );
  } else {
    Serial.print( "[FAILED] [ rc = " );
    Serial.println( " : retrying in 5 seconds]" );
    delay( 5000 );
  }
}