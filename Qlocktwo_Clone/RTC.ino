#include <DS3231.h>

/*
 * SDA pin -> Analog 4
 * SCL pin -> Analog 5
 */

namespace RTC {

  /*
   * Consts
   */
  const int WAIT_INTERVAL = 5000;

  /*
   * Statics
   */
  DS3231  rtc(SDA, SCL);
  Time tt;
  static uint32_t lastMillis = 0;

  /*
   * Setup RTC // set time if none available
   */
  void printTime();
  void setup()
  {
    // start rtc
    rtc.begin();
    
    
    // Setting Time
    /*
    printTime();
    if (true)
    {
      rtc.setDOW(TUESDAY);        // Set Day-of-Week to SUNDAY
      rtc.setTime(18, 9, 0);     // Set the time to 12:00:00 (24hr format)
      rtc.setDate(28, 9, 2021);   // Set the date to January 1st, 2014
    }
    */
    
  }

  void refreshTime()
  {
    tt = rtc.getTime();
    CurrentTime.currMin = tt.min;
    CurrentTime.currHour = tt.hour;
  }

  void getTime(int& hour, int& min)
  {
    min = tt.min;
    hour = tt.hour;
  }

  void getTimeSec(int& sec, int& min)
  {
    min = tt.min;
    sec = tt.sec;
  }

  void printTimeStruct()
  {
    Serial.print(CurrentTime.currHour);
    Serial.print(":");
    Serial.print(CurrentTime.currMin);
    Serial.print("\n");
  }
  
  void printTime()
  {
      // Send date over serial connection
      Serial.print("Today is the ");
      Serial.print(tt.date, DEC);
      Serial.print(". day of ");
      Serial.print(rtc.getMonthStr());
      Serial.print(" in the year ");
      Serial.print(tt.year, DEC);
      Serial.println(".");
      // Send Day-of-Week and time
      Serial.print("It is the ");
      Serial.print(tt.dow, DEC);
      Serial.print(". day of the week (counting monday as the 1th), and it has passed ");
      Serial.print(tt.hour, DEC);
      Serial.print(" hour(s), ");
      Serial.print(tt.min, DEC);
      Serial.print(" minute(s) and ");
      Serial.print(tt.sec, DEC);
      Serial.println(" second(s) since midnight.");
    
      // Send a divider for readability
      Serial.println("  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -");
  }


}
