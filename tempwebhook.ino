// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11

double temperature = 0; // temperature measurement
double humidity = 0; // humidity measurement
char temperatureCh[15]; // .publish() requires a char and not an int we make a char variable to put the measurement in
char humidityCh[15]; // .publish() requires a char and not an int we make a char variable to put the measurement in
        
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Particle.variable("Temperature", temperatureCh);    // Enables console to pull current Temperature value
    Particle.variable("Humidity", humidityCh);   // Enables console to pull current Humidity value
}

void loop() {

    temperature = dht.getTempCelcius();
    humidity = dht.getHumidity();

    if(temperature!=0) {
        sprintf(temperatureCh, "%.1f", temperature); // assign temperature as a char to temperatureCh
        sprintf(humidityCh, "%.1f", humidity); // assign humidity as a char to humidityCh
        
        Particle.publish("Temperature", temperatureCh, PRIVATE); // Publish the temperature as an event
        Particle.publish("Humidity", humidityCh, PRIVATE); // Publish the humidity as an event  
    }
  
    delay(30000); //wait for 30 seconds
}