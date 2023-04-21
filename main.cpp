#include <M5StickCPlus.h>
#include <FastLED.h>

#define NUM_LEDS 8

#define DATA_PIN 26
CRGB leds[NUM_LEDS];


RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

/* After M5StickC Plus is started or reset
  the program in the setUp () function will be run, and this part will only be
  run once. 在 M5StickC Plus
  启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin();             // Init M5StickC Plus.  初始化 M5StickC Plus
    M5.Lcd.setRotation(3);  // Rotate the screen. 将屏幕旋转
    M5.Lcd.setCursor(60, 10, 2);  // set the cursor location.  设置光标位置
    M5.Lcd.println("RTC TEST");
    RTC_TimeTypeDef TimeStruct;
    TimeStruct.Hours   = 18;  // Set the time.  设置时间
    TimeStruct.Minutes = 56;
    TimeStruct.Seconds = 10;
    M5.Rtc.SetTime(&TimeStruct);  // writes the set time to the real time clock.
                                  // 将设置的时间写入实时时钟
    RTC_DateTypeDef DateStruct;
    DateStruct.WeekDay = 3;  // Set the date.  设置日期
    DateStruct.Month   = 3;
    DateStruct.Date    = 22;
    DateStruct.Year    = 2019;
    M5.Rtc.SetData(&DateStruct);  // writes the set date to the real time clock.
                                  // 将设置的日期写入实时时钟

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    M5.Rtc.GetTime(&RTC_TimeStruct);  // Gets the time in the real-time clock.
                                      // 获取实时时钟内的时间
    M5.Rtc.GetData(&RTC_DateStruct);
    M5.Lcd.setCursor(30, 35);
    M5.Lcd.printf("Data : %04d-%02d-%02d\n", RTC_DateStruct.Year,
                  RTC_DateStruct.Month, RTC_DateStruct.Date);
    M5.Lcd.setCursor(30, 55);
    M5.Lcd.printf("Week : %d\n", RTC_DateStruct.WeekDay);
    M5.Lcd.setCursor(30, 75);
    M5.Lcd.printf("Time : %02d : %02d : %02d\n", RTC_TimeStruct.Hours,
                  RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
    delay(50);

    for (size_t i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::White;
    }
  FastLED.show();
  delay(10000);
  // Now turn the LED off, then pause
  for (size_t i = 0; i < NUM_LEDS; i++)
    {
      leds[i] = CRGB::Black;
    }
  FastLED.show();
  delay(1000);
}