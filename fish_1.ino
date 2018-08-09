#define BLINKER_PRINT Serial
#define BLINKER_MQTT

#include <Blinker.h>
#include<Servo.h>
#include <modules/dht/DHT.h>

char auth[] = "d4e0a1ef092d";
char ssid[] = "iot";
char pswd[] = "fubo1996";

#define BENG1 D3
#define BENG2 D6
#define DHTPIN 4
#define SERVO 5
#define DHTTYPE DHT11
#define ZD A0

#define TEMP "temp"
#define HUMI "humi"
#define FOOD "food"
#define WATERIN "water-in"
#define WATEROUT "water-out"
#define READ "read"

DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

void setup() {
    Serial.begin(115200);
    myServo.attach(SERVO);
    myServo.write(60);
    pinMode(BENG1, OUTPUT);
    pinMode(BENG2, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(BENG1, LOW);
    digitalWrite(BENG2, LOW);
    pinMode(ZD, INPUT);

    Blinker.begin(auth, ssid, pswd);
    dht.begin();
    
    Blinker.wInit(FOOD, W_BUTTON);
    Blinker.wInit(READ, W_BUTTON);
    Blinker.wInit(WATERIN, W_TOGGLE);
    Blinker.wInit(WATEROUT, W_TOGGLE);
}

void loop()
{
    Blinker.run();
 
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int sensorValue = analogRead(ZD);// read the input on analog pin 0:
    float voltage = sensorValue * (5.0 / 1024.0);
    if (Blinker.button(READ)) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
           
        BLINKER_LOG3("Humidity: ", h, " %");
        BLINKER_LOG3("Temperature: ", t, " *C");
        BLINKER_LOG3("Zhuodu: ", voltage, " V");
        
        Blinker.beginFormat();
        Blinker.print("humi", h, " ％");
        Blinker.print("temp", t, " *C");
        Blinker.print("zhuodu", voltage, " *C");
        Blinker.endFormat();
    }
    
    if (Blinker.button(FOOD)) {
        myServo.write(90);
    }
    else{
        myServo.write(60);
    }
    

    if (Blinker.toggle(WATEROUT)) {
        digitalWrite(BENG1,HIGH);
    }
    else{
        digitalWrite(BENG1,LOW);
    }
     
     if (Blinker.toggle(WATERIN)) {
        digitalWrite(BENG2,HIGH);
     }
    else{
        digitalWrite(BENG2,LOW);
    }
   
}

        
        
        

