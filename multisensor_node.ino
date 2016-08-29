
#define MY_DEBUG // enabling debug
#define MY_NODE_ID 1 // node id 
#define MY_RADIO_NRF24 // enabling support for NRF radio module
#define CHILD_ID_MOIST 1 // Moisture sensor id
#define CHILD_ID_LIGHT 2 // Light sensor id
#define CHILD_ID_TEMP 3 // Temp sensor id
#define CHILD_ID_HUM 4 // Humidity sensor id
#define MOIST_SENS 2
#define LIGHT_SENS 3
#define HUM_SENS 4
#define VAL_MOIST A0
#define VAL_LIGHT A1
#define DIGITAL_HUM 8
#include <MySensors.h>
#include <SPI.h>
#include <DHT.h>
#define DHTTYPE DHT11 

DHT dht(DIGITAL_HUM,DHTTYPE);
MyMessage msgMoist(CHILD_ID_MOIST, V_LEVEL); // constructing the msg
MyMessage msgLux(CHILD_ID_LIGHT, V_LIGHT_LEVEL);
MyMessage msgHum(CHILD_ID_HUM, V_HUM);
MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);

void setup()
{
 pinMode(MOIST_SENS, OUTPUT);
 pinMode(LIGHT_SENS, OUTPUT);
 pinMode(HUM_SENS, OUTPUT);
 dht.begin();
}

void presentation()
{
 present(CHILD_ID_MOIST, S_MOISTURE); // presenting the sensor 
 present(CHILD_ID_LIGHT, S_LIGHT_LEVEL); 
 present(CHILD_ID_HUM, S_HUM); 
 present(CHILD_ID_TEMP, S_TEMP); 
 sendSketchInfo("SoilSensor", "0.1"); //meta data 
}

void loop()
{
 digitalWrite(MOIST_SENS, HIGH);
 delay(50);
 int moisture = analogRead(VAL_MOIST); //measuring the moisture 
 digitalWrite(MOIST_SENS, LOW); 
 send(msgMoist.set(moisture)); // sending the data 

 digitalWrite(LIGHT_SENS, HIGH);
 delay(50);
 int light = analogRead(VAL_LIGHT); //measuring the moisture 
 digitalWrite(LIGHT_SENS, LOW); 
 send(msgLux.set(light)); // sending the data 
 
 digitalWrite(HUM_SENS, HIGH); 
 delay(1000); // delay to get Humidity sensor ready to read data
 float humidity = dht.readHumidity(); //measuring the humidity 
 float temperature = dht.readTemperature(); //measuring the temperature 
 digitalWrite(HUM_SENS, LOW); 
 send(msgHum.set(humidity,1)); // sending the data 
 send(msgTemp.set(temperature,1)); // sending the data
 
 sleep(300000); // sleeping for 5 minutes
}
