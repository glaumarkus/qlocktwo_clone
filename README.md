# qlocktwo_clone
A lightweight implementation of a Qlocktwo Clone using Arduino Uno.

### History

<p>
	I wanted to gift my parents something handmade and special this year, so when I saw one of the Qlocktwos during a vacation, I was eager to rebuild something similar. I started with using one of the Arduinos I had laying around and implemented the software part. Even though, there are already implementations available, I wanted to do it myself, only using available libraries for the Real-Time Clock module and the control of the LED strip. 
</p>
<p>
	From the initial prototype I had a lot of learnings along the way. I counted all the letters that had to have a LED behind (94), so I just went with an LED strip with 100 lights. I totally underestimated the required time to scolder everything together. For next version I would rather accept having lights there, that are not on at anytime and just save a cupple of hours of scoldering LEDs - a very painful process. Additionally as this only should serve as a prototype, I would also use LEDs with a distance of 3cm instead of 1cm used in this version. 
</p>
<p>
	Next improvement should focus on the actual visibility of the time. Originally I went with an acryl glass top in combination with a semi transparent sticker. I discovered that semi-transparent means more or less totally transparent and that you could completely see through in lighter areas. Maybe for future I will go with something else here. For this one I just put a white photo paper in between the LED and glass to dampen the light and to reduce the see-through. Possible future options would be to laser out all letters in the acryl glass and completely ignore letters to rely on only the shine through of light. Other option might be to just have it lasered in wood and drop having a picture upfront. I will try both options and see what will work best. 
</p>


### Hardware:
1. Arduino Uno (https://store.arduino.cc/products/arduino-uno-rev3)
2. AZDelivery RTC Chip (https://www.amazon.de/dp/B01M2B7HQB/ref=twister_B07ZQGBH14?_encoding=UTF8&psc=1)
3. WS2812E LED Strip (https://www.amazon.de/gp/product/B088FJLRFP/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&th=1)
4. copper cables (https://www.amazon.de/gp/product/B01BI1G88C/ref=ppx_yo_dt_b_asin_title_o02_s01?ie=UTF8&psc=1)
5. power cable (https://www.amazon.de/gp/product/B075TXKC9D/ref=ppx_yo_dt_b_asin_title_o00_s01?ie=UTF8&psc=1)
6. WS2812E LED Strip (https://www.amazon.de/gp/product/B088FJLRFP/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&th=1)

### Materials:
1. Underground 20cm x 20cm x 6mm
2. Top / Bot seperator 20cm x 5cm x 2cm
3. LED plate 16cm x 11cm x 3mm
4. Acryl glass top plate 20cm x 20cm x 3mm
5. transparent sticker

All wood / glass from https://expresszuschnitt.de/Sperrholzplatten-Zuschnitt, sticker from https://www.myposter.de/klebefolie-transparent.


### Setup:
Time of the RTC module has to be set once, afterwards its periodically read every 5 minutes. Code Block is available in void RTC::setup(). Blueprint for sticker is available in media as png and gimp file. I replaced the background with the picture of my choice. 

### Images:

##### Final Prototype
<p align="center">
	<img width="50%" src="/media/final_prototype.jpg" alt="design" />
</p>

##### Without photo paper in between
<p align="center">
	<img width="50%" src="/media/acryl_with_sticker.jpg" alt="design" />
</p>

##### Under the hood
<p align="center">
	<img width="50%" src="/media/setup_noglass.jpg" alt="hardware" />
</p>

#####  Arduino & RTC module
<p align="center">
	<img width="50%" src="/media/arduino_setup.jpg" alt="arduino"  />
</p>

