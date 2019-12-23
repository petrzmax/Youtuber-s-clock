# YouTuber's clock

Are You always curios how many subscribers You have on Your YouTube channel?
Me too, so I have made this YouTuber's clock! If You have one You don't have to smash F5 button so often.

You will need:
- [WeMos D1 Mini](http://bit.ly/2uKBDhp)
- [8-digit 7 segment screen](http://bit.ly/2PZD45k)

D1 mini WiFi ESP8266 pinout:
- D8 - DataIn
- D7 - LOAD/CS
- D6 - CLK

It has been designed for 8-digit 7 segment screen controlled by **MAX7219**.

It should work on boards with **ESP8266** module, but I have tested it only on **D1 mini clone**.
If You use another board You may need to change the pinout.

There is only a few delays used at the beginning of the code.
I have programmed it using timers (especially in animations) so this code supports multitasking.
With this, You can easily add a new functions running in background etc.

You can watch build **tutorial** here:
[![Watch the video](https://img.youtube.com/vi/jCqdFAKpAkU/maxresdefault.jpg)](https://www.youtube.com/watch?v=jCqdFAKpAkU)
It's in **Polish** language but it should be easy to follow.

If You like this project consider supporting me [here](https://paypal.me/ArturPetrzak).

## Features:
- Multitasking ready
- Auto DST switch
- Randomly chosen animations
- Shows time, actual date, Your subscription and views count
- Time synchronized with **NTP server**
- WiFi Manager - You can easily change Wifi SSID & password without reprogramming Your board

## Needed libraries:
You can download these libraries from library manager in Arduino IDE:
- [NTPClient](https://github.com/arduino-libraries/NTPClient)
- [Time](https://github.com/PaulStoffregen/Time)
- [YoutubeApi](https://github.com/witnessmenow/arduino-youtube-api)
- [WiFiManager](https://github.com/tzapu/WiFiManager)
- [LedControl](https://github.com/wayoda/LedControl)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (Version 5.13.5 - It **won't** compile on newer versions)
- ESP8266 (from Boards Manager. You need to add this URL:`http://arduino.esp8266.com/stable/package_esp8266com_index.json`
  first in Arduino IDE preferences -> Additional Boards Manager URLs. Then You will find ESP8266 in Boards Manager)

You need to download these libraries from github and put in Your Arduino libraries folder. 
- [Timezone](https://github.com/JChristensen/Timezone)
- [SimpleTimer](https://github.com/schinken/SimpleTimer)


If You get a compilation error related to avr/pgmspace.h, You need to change this line:

`#include <avr/pgmspace.h>`

in `\libraries\LedControl\src\LedControl.h` (Which should be located in your Arduino libraries folder)

To this part of the code:
```
#if (defined(AVR))
#include <avr\pgmspace.h>
#else
#include <pgmspace.h>
#endif
```

## You can find me on:
- [YouTube](http://bit.ly/SubskrybujArtka)
- [Facebook](http://bit.ly/ArtekDiy)
- [FB Group](http://bit.ly/MajstryArtka)
- [Instagram](http://bit.ly/IG_Artek)
- [Thingiverse](http://bit.ly/ArtekThingi)

## Credits:
- Sandeep Mistry - NTPClient
- Paul Stoffregen - Time
- Brian Lough - YoutubeApi
- tzapu - WiFiManager
- Eberhard Fahle - LedControl
- Benoît Blanchon - ArduinoJson
- Jack Christensen - Timezone
- Christopher Schirner - SimpleTimer

---
Coded by Artur Petrzak in August 2017