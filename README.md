# Youtuber-s-clock

===============================================================================================================================================  
__  __                  __             __                  _                           __                  __                   ___      ____ 
\ \/ /  ____   __  __  / /_  __  __   / /_   ___    _____ ( )   _____         _____   / /  ____   _____   / /__        _   __  <  /     / __ \
 \  /  / __ \ / / / / / __/ / / / /  / __ \ / _ \  / ___/ |/   / ___/        / ___/  / /  / __ \ / ___/  / //_/       | | / /  / /     / / / /
 / /  / /_/ // /_/ / / /_  / /_/ /  / /_/ //  __/ / /         (__  )        / /__   / /  / /_/ // /__   / ,<          | |/ /  / /   _ / /_/ / 
/_/   \____/ \__,_/  \__/  \__,_/  /_.___/ \___/ /_/         /____/         \___/  /_/   \____/ \___/  /_/|_|         |___/  /_/   (_)\____/  
                                                                                                                                                                                                                                                                      
===============================================================================================================================================                                                                                                 

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                        //
//                                      Youtuber's clock v1.0                                             //                                                                                            
//                                Coded by Artur Petrzak in August 2017                                   //
//                                                                                                        //
//  My YouTube channel:                                                                                   //
//  https://www.youtube.com/ArturPetrzak                                                                  //
//                                                                                                        // 
//  Feel free to use it and share! But please credit me and my Youtube channel aswell.                    //
//  Thank You!                                                                                            //
//                                                                                                        //
//  D1 mini WiFi ESP8266 pinout:                                                                          //
//    D8 - DataIn                                                                                         //
//    D7 - LOAD/CS                                                                                        //
//    D6 - CLK                                                                                            //
//                                                                                                        //
//  Designed for 8-digit 7 segment screen controlled by MAX7219.                                          //
//  Example:                                                                                              //
//  Aliexpress: http://bit.ly/2vaivKL                                                                     //
//  Ebay: http://ebay.to/2ws48RD                                                                          //
//                                                                                                        //
//  (These are reflinks. By using them You can support me a bit :))                                       //
//                                                                                                        //
//  It should work on boards with ESP8266 module, but I have tested it only on D1 mini clone.             //
//  If You use another board You may need to change the pinout.                                           //
//                                                                                                        //
//  There is only a few delays used at the beginning of the code.                                         //
//  I have programmed it using timers (especially in animations) so this program supports multitasking.   //
//  With this, You can easyly add a new functions running in background etc.                              //
//                                                                                                        //
//  Consider supporting me if You like this project: https://paypal.me/ArturPetrzak                       //
//                                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

=============================================================
    ______                 __                               
   / ____/  ___   ____ _  / /_  __  __   _____  ___    _____
  / /_     / _ \ / __ `/ / __/ / / / /  / ___/ / _ \  / ___/
 / __/    /  __// /_/ / / /_  / /_/ /  / /    /  __/ (__  ) 
/_/       \___/ \__,_/  \__/  \__,_/  /_/     \___/ /____/  
                                                            
=============================================================

- Multitasking ready.
- Auto DST switch.
- Randomly chosed animations.
- Shows time, actual date, Your subscription and views count.
- Time synchronized with NTP server
- WiFi Manager - You can easily change Wifi SSID & password without reprogramming Your board.

===========================================================================================================================
    _   __                   __             __           __    _     __                              _                    
   / | / /  ___   ___   ____/ /  ___   ____/ /          / /   (_)   / /_    _____  ____ _   _____   (_)  ___    _____   _ 
  /  |/ /  / _ \ / _ \ / __  /  / _ \ / __  /          / /   / /   / __ \  / ___/ / __ `/  / ___/  / /  / _ \  / ___/  (_)
 / /|  /  /  __//  __// /_/ /  /  __// /_/ /          / /   / /   / /_/ / / /    / /_/ /  / /     / /  /  __/ (__  )  _   
/_/ |_/   \___/ \___/ \__,_/   \___/ \__,_/          /_/   /_/   /_.___/ /_/     \__,_/  /_/     /_/   \___/ /____/  (_)  

===========================================================================================================================

You can download these libraries from library manager in Arduino IDE:
- NTPClient: https://github.com/arduino-libraries/NTPClient
- Time: https://github.com/PaulStoffregen/Time
- YoutubeApi: https://github.com/witnessmenow/arduino-youtube-api
- WiFiManager: https://github.com/tzapu/WiFiManager
- LedControl: https://github.com/wayoda/LedControl
- ArduinoJson: https://github.com/bblanchon/ArduinoJson
- ESP8266 (from Boards Manager. You need to add this URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
  first in Arduino IDE preferences -> Additional Boards Manager URLs. Then You will find ESP8266 in Boards Manager)

You need to download these libraries from github and put in Your Arduino libraries folder. 
- Timezone: https://github.com/JChristensen/Timezone  
- SimpleTimer: https://github.com/schinken/SimpleTimer
                                                                                                                        
=======================================================================================================================================
   ______                                _     __           __     _                                                              ___ 
  / ____/  ____    ____ ___     ____    (_)   / /  ____ _  / /_   (_)  ____    ____          ___    _____   _____  ____    _____ /__ \
 / /      / __ \  / __ `__ \   / __ \  / /   / /  / __ `/ / __/  / /  / __ \  / __ \        / _ \  / ___/  / ___/ / __ \  / ___/  / _/
/ /___   / /_/ / / / / / / /  / /_/ / / /   / /  / /_/ / / /_   / /  / /_/ / / / / /       /  __/ / /     / /    / /_/ / / /     /_/  
\____/   \____/ /_/ /_/ /_/  / .___/ /_/   /_/   \__,_/  \__/  /_/   \____/ /_/ /_/        \___/ /_/     /_/     \____/ /_/     (_)   
                            /_/                                                                                                       
=======================================================================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                          //
//  If You get a compile error related to avr/pgmspace.h, You need to change this line:                     //
//                                                                                                          //
  #include <avr/pgmspace.h>"
//                                                                                                          //
//  in "\libraries\LedControl\src\LedControl.h" (Which should be located in your Arduino libraries folder.) //
//                                                                                                          //
//  To this part of the code:                                                                               //
//                                                                                                          //
  #if (defined(AVR))
  #include <avr\pgmspace.h>
  #else
  #include <pgmspace.h>
  #endif
//                                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

===========================================================================================================================
    __     _     __                              _                                                  __    _    __         
   / /    (_)   / /_    _____  ____ _   _____   (_)  ___    _____         _____   _____  ___   ____/ /   (_)  / /_   _____
  / /    / /   / __ \  / ___/ / __ `/  / ___/  / /  / _ \  / ___/        / ___/  / ___/ / _ \ / __  /   / /  / __/  / ___/
 / /___ / /   / /_/ / / /    / /_/ /  / /     / /  /  __/ (__  )        / /__   / /    /  __// /_/ /   / /  / /_   (__  ) 
/_____//_/   /_.___/ /_/     \__,_/  /_/     /_/   \___/ /____/         \___/  /_/     \___/ \__,_/   /_/   \__/  /____/  
                                                                                                                                                                              
===========================================================================================================================

- Sandeep Mistry - NTPClient
- Paul Stoffregen - Time
- Brian Lough - YoutubeApi
- tzapu - WiFiManager
- Eberhard Fahle - LedControl
- Benoît Blanchon - ArduinoJson
- Jack Christensen - Timezone
- Christopher Schirner - SimpleTimer

======================================================================================================================================
__  __                                               __    __     _                                     __                           
\ \/ /  ____   __  __   _____          _____  ___   / /_  / /_   (_)   ____    ____ _   _____          / /_   ___    _____  ___    _ 
 \  /  / __ \ / / / /  / ___/         / ___/ / _ \ / __/ / __/  / /   / __ \  / __ `/  / ___/         / __ \ / _ \  / ___/ / _ \  (_)
 / /  / /_/ // /_/ /  / /            (__  ) /  __// /_  / /_   / /   / / / / / /_/ /  (__  )         / / / //  __/ / /    /  __/ _   
/_/   \____/ \__,_/  /_/            /____/  \___/ \__/  \__/  /_/   /_/ /_/  \__, /  /____/         /_/ /_/ \___/ /_/     \___/ (_)  
                                                                            /____/                                                   
======================================================================================================================================