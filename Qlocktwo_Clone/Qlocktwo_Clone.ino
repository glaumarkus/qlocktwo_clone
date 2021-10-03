/*
 * Main File
 */




/*
 * Forward declarations RTC
 */
namespace RTC {
  
  struct CustomTime{
    int currMin, currHour;
    };

  static CustomTime CurrentTime;
    
  void setup();
  void refreshTime();
  void printTime();
  void printTimeStruct();
  void getTime(int& hour, int& min);
  void getTimeSec(int& sec, int& min);
  
}


/*
 * Forward declarations LED
 */
namespace LED {
  
  void setup_control();
  void setup_settings();
  
  void turnOnLED(const int& LED_ID);
  void turnOffLED(const int& LED_ID);
  
  void integrationTest();
  void update();
  
}


/*
 * Wait until Console is set up
 */
void setupSerial(uint32_t bw)
{
  Serial.begin(bw);
  while(!Serial)
  {
    }
}


/*
 * Setup all components
 */
void setup() {

  // set up output
  setupSerial(115200);
  

  // initialize RTC readings
  Serial.println("Starting RTC");
  RTC::setup();

  // initialize LED control
  Serial.println("Starting LED Control");  
  LED::setup_control();
  LED::integrationTest();
  LED::setup_settings();

}

/*
 * Run 
 */
void loop() {

  /*
   * Time Update
   */
   Serial.println("Updating Time");
   RTC::refreshTime();
   
  /*
   * Debug Time
   */
  Serial.println("Printing Time..");
  RTC::printTimeStruct();

  /*
   * Update LED State
   */
  Serial.println("Update LEDs..");
  LED::update();

  /*
   * Calculate wait time, wait until next change has to happen
   */
  int min, sec;
  RTC::getTimeSec(sec, min);
  unsigned int mins_to_wait = 5 - min % 5;
  unsigned int secs_to_wait = -sec;
  unsigned long waitTime2 = mins_to_wait * 60 + secs_to_wait;

  Serial.print("Waiting: ");
  Serial.print(waitTime2);
  Serial.print("seconds..\n");

  delay(waitTime2 * 1000);
  Serial.println("Waiting done");
    
}
