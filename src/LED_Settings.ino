
template <typename T>
void fill_n(T* a, size_t n, T value)
{
    for (size_t i = 0; i < n; i++)
        a[i] = value;
}


namespace LED
{   

   /*
   * Consts
   */
    constexpr int RANGE_LED_IDS = 2;
    constexpr int RANGE_MIN_STATES = 3;
    constexpr int RANGE_HOUR_STATES = 2;
    constexpr int MAX_ACTIVE_LEDS = 20;


    /*
    * Mapping of State to LED
    */
    constexpr int state2LEDID[24][RANGE_LED_IDS] =
    {
        // LEDs for Mode 1
        {1,5},

        // LEDs for Mode 2
        {6,9},

        // LEDs for Mode 3
        {17,20},

        // LEDs for Mode 4
        {10,16},

        // LEDs for Mode 5
        {21,24},

        // LEDs for Mode 6
        {25,31},

        // LEDs for Mode 7
        {36,38},

        // LEDs for Mode 8
        {32,35},

        // LEDs for Mode 9
        {39,42},

        // LEDs for Mode 10
        {43,44},

        // LEDs for Mode 11
        {45,45},

        // LEDs for Mode 12
        {46,48},

        // LEDs for Mode 13
        {53,56},

        // LEDs for Mode 14
        {49,52},

        // LEDs for Mode 15
        {57,60},

        // LEDs for Mode 16
        {61,64},

        // LEDs for Mode 17
        {69,73},

        // LEDs for Mode 18
        {65,68},

        // LEDs for Mode 19
        {74,79},

        // LEDs for Mode 20
        {80,84},

        // LEDs for Mode 21
        {92,94},

        // LEDs for Mode 22
        {91,91},

        // LEDs for Mode 23
        {88,90},

        // LEDs for Mode 24
        {85,87}
    };


    /*
    * Active States for minutes
    */
    constexpr int minStates[12][RANGE_MIN_STATES] =
    {
        // 00
        {   1,  24, -1},

        // 05
        {   2,  8,  -1},

        // 10
        {   3,  8,  -1},

        // 15
        {   6,  -1, -1},

        // 20
        {   3,  7,  9},

        // 25
        {   2,  7,  9},

        // 30
        {   9,  -1, -1},

        // 35
        {   2,  8,   9},

        // 40
        {   4,  7,  -1},

        // 45
        {   5,  6,  -1},

        // 50
        {   3,  7,  -1},

        // 55
        {   2,  7,  -1},
    };


    /*
    * Active States for hours
    */
    constexpr int hourStates[12][RANGE_HOUR_STATES] =
    {
        // 1 Uhr
        {   13,  -1},

        // 2 Uhr
        {   14,  -1},

        // 3 Uhr
        {   15,  -1},

        // 4 Uhr
        {   16,  -1},

        // 5 Uhr
        {   11,  12},

        // 6 Uhr
        {   17,  -1},

        // 7 Uhr
        {   19,  -1},

        // 8 Uhr
        {   18,  -1},

        // 9 Uhr
        {   22,  23},

        // 10 Uhr
        {   21,  22},

        // 11 Uhr
        {   10,  11},

        // 12 Uhr
        {   20,  -1},
    };

    // how many LEDs maximum turned on? 20? 
    int activeLEDs[MAX_ACTIVE_LEDS] = {};

    void setup_settings()
    {
        fill_n<int>(&activeLEDs[0], MAX_ACTIVE_LEDS, -1);
    }

    
    /*
    * gets new time / turns off active LEDS / turns on new mode
    */
    void update()
    {
        int hour, min;
        RTC::getTime(hour, min);

        // get min idx 5=0, 10=1, 15=2 ...
        int min_idx = static_cast<int> ((float)min / 5);
        
        // get hour idx 
        int hour_idx = hour % 12;

        // increment hour if min_idx > 3
        if (min_idx > 2)
            hour_idx++;

        // reduce both due to index starting with 0
        hour_idx--;

        // get all min states
        int nextMinStates[RANGE_MIN_STATES];
        fill_n<int>(&nextMinStates[0], RANGE_MIN_STATES, -1);

        for (int i = 0; i < RANGE_MIN_STATES; i++)
        {
            if (minStates[min_idx][i] != -1)
                nextMinStates[i] = minStates[min_idx][i];
        }

        // get all hour states
        int nextHourStates[RANGE_HOUR_STATES] = { -1 };
        fill_n<int>(&nextHourStates[0], RANGE_HOUR_STATES, -1);

        for (int i = 0; i < RANGE_HOUR_STATES; i++)
        {
            if (hourStates[hour_idx][i] != -1)
                nextHourStates[i] = hourStates[hour_idx][i];
        }

        // get next active LEDs
        int nextActiveLEDs[MAX_ACTIVE_LEDS];
        fill_n<int>(&nextActiveLEDs[0], MAX_ACTIVE_LEDS, -1);

        int LED_counter = 0;

        // add minute LEDs
        for (int i = 0; i < RANGE_MIN_STATES; i++)
        {
            if (nextMinStates[i] != -1)
            {
                // add LEDs of State
                // decrement by one to get desired state, started counting with 1
                int state = nextMinStates[i] - 1;
                int start = state2LEDID[state][0];
                int end = state2LEDID[state][1];
                for (int k = start; k <= end; k++)
                {
                    nextActiveLEDs[LED_counter++] = k;
                }
            }
        }

        // add hour LEDs
        for (int i = 0; i < RANGE_HOUR_STATES; i++)
        {
            if (nextHourStates[i] != -1)
            {
                // add LEDs of State
                // decrement by one to get desired state, started counting with 1
                int state = nextHourStates[i] - 1;
                int start = state2LEDID[state][0];
                int end = state2LEDID[state][1];
                for (int k = start; k <= end; k++)
                {
                    nextActiveLEDs[LED_counter++] = k;
                }
            }
        }

        if (nextActiveLEDs == activeLEDs)
          return;

        // turn off all active LEDs
        for (int i = 0; i < MAX_ACTIVE_LEDS; i++)
        {
            // decrement by one to get desired state, started counting with 1 ?
            if (activeLEDs[i] != -1)
                turnOffLED(activeLEDs[i] - 1);
            else
                break;
        }

        // replace active LEDs
        memcpy(&activeLEDs, nextActiveLEDs, sizeof(activeLEDs));

        // turn on next active LEDs;
        for (int i = 0; i < MAX_ACTIVE_LEDS; i++)
        {
            // decrement by one to get desired state, started counting with 1 ?
            if (activeLEDs[i] != -1)
                turnOnLED(activeLEDs[i] - 1);
            else
                break;
        }

    }

}
