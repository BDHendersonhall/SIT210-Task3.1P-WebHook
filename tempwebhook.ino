// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11

unsigned long lastPublish = 0; // A time variable to know when we published to the cloud last
double temp = 0; // Current temperature
double humidity = 0; // Current humidity
char tempC[15]; // empty var to store temp as a char so we can publish to .publish(), since it requires a char and not an int
char humidityC[15]; // empty var to store humidity as a char so we can publish to .publish(), since it requires a char and not an int
        
int publishInterval = 30; // Temperature and humidity publish frequency, seconds

DHT dht(DHTPIN, DHTTYPE);

bool shouldPublish() {
        return Time.now() > lastPublish + publishInterval;
}

void publishAction() {
        Particle.publish("Temperature", tempC, PRIVATE); // Publish the temperature as an event
        Particle.publish("Humidity", humidityC, PRIVATE); // Publish the humidity as an event
        lastPublish = Time.now();
}

void setup() {
    Particle.variable("Temperature", tempC);    // Enables console to pull current Temperature value
    Particle.variable("Humidity", humidityC);   // Enables console to pull current Humidity value
}

void loop() {
    if(shouldPublish()) {
        publishAction();
    }
    humidity = dht.getHumidity();
    temp = dht.getTempCelcius();
    if(temp!=0) {
        sprintf(tempC, "%.1f", temp); // assign temp as a char to tempC
        sprintf(humidityC, "%.1f", humidity); // assign humidity as a char to humidityC
    }
    delay(100);
}