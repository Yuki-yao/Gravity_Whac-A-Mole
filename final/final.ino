#include <Servo.h>
#define my_Serial Serial

#define PIN_SERVO 6
#define PIN_BUZZER 8
#define PIN_LED_1 4
#define PIN_LED_2 10
#define PIN_LED_3 12
#define PIN_SEN_1 A6
#define PIN_SEN_2 A2
#define PIN_SEN_3 A0
#define BRIGHT 800
#define LIGHT_TIME 1000
#define STOP_TIME 1000

Servo myServo;
int current;
unsigned long last_begin, last_stop;
unsigned long last_light;
bool isStopped;

void setup() {
    my_Serial.begin(9600);
    myServo.attach(PIN_SERVO);
    current = 90;
    myServo.write(current);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED_1, OUTPUT);
    pinMode(PIN_LED_2, OUTPUT);
    pinMode(PIN_LED_3, OUTPUT);
    pinMode(PIN_SEN_1, INPUT);
    pinMode(PIN_SEN_2, INPUT);
    pinMode(PIN_SEN_3, INPUT);
    last_begin = last_stop = millis();
    isStopped = false;
    digitalWrite(PIN_LED_1, HIGH);
    last_light = 1;
}

void loop() {
    //Serial.println("millis()");
    if(my_Serial.available() > 0) {
        String msg;
        msg = my_Serial.readStringUntil('\n');
        current += msg.toInt();
        if(current > 180)
            current = 180;
        if(current < 0)
            current = 0;
        Serial.println(current);
        myServo.write(current);
    }
    int light[3] = {
        analogRead(PIN_SEN_1),
        analogRead(PIN_SEN_2),
        analogRead(PIN_SEN_3)
    };
    Serial.println(light[1]);
    //delay(200);
    bool flag = false;
    for(int i = 0; i < 3; ++ i) {
        if(light[i] < BRIGHT && !isStopped && i == last_light - 1) {
            tone(PIN_BUZZER, 800);
            flag = true;
            delay(200);
            //Serial.println("1");
            isStopped = true;
            last_stop = millis();
            digitalWrite(PIN_LED_1, LOW);
            digitalWrite(PIN_LED_2, LOW);
            digitalWrite(PIN_LED_3, LOW);
            return;
        }
    }
    if(!flag)
        noTone(PIN_BUZZER);
    //Serial.println(last_stop);
    //Serial.println(last_begin);
    if(isStopped && millis() - last_stop > STOP_TIME) {
        //Serial.println("2");
        isStopped = false;
        last_begin = millis();
        int randnum = (random(2) + last_light) % 3;
        switch(randnum) {
            case 0:
                digitalWrite(PIN_LED_1, HIGH);
                break;
            case 1:
                digitalWrite(PIN_LED_2, HIGH);
                break;
            case 2:
                digitalWrite(PIN_LED_3, HIGH);
                break;
            default:
                break;
        }
        last_light = randnum + 1;
    }
    else if(!isStopped && millis() - last_begin > LIGHT_TIME) {
        //Serial.println("3");
        isStopped = true;
        last_stop = millis();
        digitalWrite(PIN_LED_1, LOW);
        digitalWrite(PIN_LED_2, LOW);
        digitalWrite(PIN_LED_3, LOW);
    }
    //Serial.println(isStopped);
}
