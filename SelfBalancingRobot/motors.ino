#define MOTOR_QUANTITY 1

float motors[MOTOR_QUANTITY]; // normalized motor thrusts in range [0..1]

// Используй только PWM-пины UNO: 3, 5, 6, 9, 10, 11
//int motorPins[4] = {3, 5, 6, 9};

int motorPins[MOTOR_QUANTITY] = {3};

int pwmMin = 0;
int pwmMax = 255;   // для analogWrite
int pwmStop = 0;

const int MOTOR_REAR_LEFT  = 0;
const int MOTOR_REAR_RIGHT = 1;
const int MOTOR_FRONT_RIGHT = 2;
const int MOTOR_FRONT_LEFT  = 3;

void setupMotors() {
    Serial.println("Setup Motors");

    for (int i = 0; i < MOTOR_QUANTITY; i++) {
        pinMode(motorPins[i], OUTPUT);
    }

    sendMotors();
    Serial.println("Motors initialized");
}

void sendMotors() {
    for (int i = 0; i < MOTOR_QUANTITY; i++) {
        analogWrite(motorPins[i], getDutyCycle(motors[i]));
    }
}

int getDutyCycle(float value) {
    value = constrain(value, 0, 1);

    int pwm = mapFloat(value, 0, 1, pwmMin, pwmMax);

    if (value == 0) pwm = pwmStop;

    return pwm;
}

// аналог map для float
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

bool motorsActive() {
    for (int i = 0; i < MOTOR_QUANTITY; i++) {
        if (motors[MOTOR_QUANTITY] != 0) 
          return 1;
    }
    return 0;
    //return motors[0] != 0 || motors[1] != 0 || motors[2] != 0 || motors[3] != 0;
}

void testMotor(int n) {
    Serial.print("Testing motor ");
    Serial.println(n);

    motors[n] = 1;
    sendMotors();

    delay(3000);

    motors[n] = 0;
    sendMotors();

    Serial.println("Done");
}

void setMotor0(float n) {
    // normalized motor thrusts in range [0..1]
    motors[0] = n; 
    sendMotors();
}



    
