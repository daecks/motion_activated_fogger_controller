    // Handy defines for readability
    #define TURN_LED_ON HIGH
    #define TURN_LED_OFF LOW
    #define TURN_RELAY_ON LOW
    #define TURN_RELAY_OFF HIGH
    #define MOTION_DETECTED HIGH
    #define NO_MOTION_DETECTED LOW
    #define SAMPLE_DELAY 10   // 10 ms delay before sampling again

    
    int LED = 13;                // specify output pin for LED, for debugging purposes while fogger not attached
    int RELAY = 3;               // output pin for relay to turn fogger on
    int IR_SENSOR = 7;           // input pin for motion sensor
    int previousSensorState = NO_MOTION_DETECTED;          // start with no motion detected
    int currentSensorValue = 0;    // variable for reading IR sensor status
    int FOGGER_ON_TIME = 30000;  // 30 seconds "on" time
    int FOGGER_REPLENISH_TIME = 60000; // timeout while motion won't be acted on
     
    void setup()
    {
      pinMode(LED, OUTPUT);  
      pinMode(RELAY, OUTPUT); 
      pinMode(IR_SENSOR, INPUT);
     
      Serial.begin(9600);
    }

// Loop to detect and act on motion.  If motion is detected, turn on fogger for FOGGER_ON_TIME.
// Then, force a delay of FOGGER_REPLENISH_TIME to ensure fogger will be ready before motion is acted upon.
     
    void loop()
    {
      currentSensorValue = digitalRead(IR_SENSOR);
      if (currentSensorValue == MOTION_DETECTED) {
        digitalWrite(LED, TURN_LED_ON);
        digitalWrite(RELAY, TURN_RELAY_ON);
        if (previousSensorState == NO_MOTION_DETECTED)
        {
          previousSensorState = MOTION_DETECTED;
          Serial.println("Turning on fogger");
          delay(FOGGER_ON_TIME);
          Serial.println("Turning off fogger");
        }
        delay(SAMPLE_DELAY);
      }
      else 
      {
        digitalWrite(LED, TURN_LED_OFF); 
        digitalWrite(RELAY, TURN_RELAY_OFF); // turn relay off
        if (previousSensorState == MOTION_DETECTED)
        {
          previousSensorState = NO_MOTION_DETECTED;
          Serial.println("Wait for fogger to replenish");
          delay(FOGGER_REPLENISH_TIME);
          Serial.println("Fogger is ready");
        }
      }
    }
