#include <NTPClient.h>
#include <Time.h> 
#include <TimeLib.h> 
#include <Timezone.h> 
#include <SimpleTimer.h> 
#include <Ticker.h>
#include <YoutubeApi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h> 
#include <WiFiClientSecure.h>
#include <WiFiUdp.h> 
#include <binary.h> 
#include "AnimationPlayer.h"

WiFiUDP ntpUDP;

/*
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
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Pinout settings
#define DIN_PIN 15  //pin D8
#define CS_PIN  13  //pin D7
#define CLK_PIN 12  //pin D6

#define API_KEY "YOUR_API_KEY_HERE" //Your YouTube API key
#define CHANNEL_ID "YOUR_CHANNEL_ID_HERE" //Your YouTube channel ID

const char intensity = 4;  //LCD brightness - You can chose from 0 to 15
const char deviceName[] = "Youtuber's clock v1.0"; //SSID of access point

const int showStatsTimer = 300000; //After this period of time the statistics will show (Value in milliseconds)
const int statsDisplayTime = 10000; //After this period of time the next value will be shown (Value in milliseconds)

//It is set to time in Poland. You need to adjust it if You are from other country.
//You can find more informations about it here: https://github.com/JChristensen/Timezone
TimeChangeRule myDST = {"CEST", Last, Sun, Mar, 1, 120}; //Summer time
TimeChangeRule mySTD = {"CET", Last, Sun, Oct, 1, 60}; //Winter time

//NTP server - Change it to the closest one for highest accuracy
NTPClient timeClient(ntpUDP, "pl.pool.ntp.org", 0, 60000);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int subs, views, menu = 4, tempMenu, stats_timer_id, switch_timer_id, startupAnimationCounter = 7;
bool one_sec = false, showTimeSwitch = true, state = true, config_mode = false;
time_t t;
Ticker ticker;

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);
LedControl LCD = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);
SimpleTimer timer;
AnimationPlayer *player;
Timezone myTZ(myDST, mySTD);

void setup() 
{ 
  LCD.shutdown(0, false); 
  LCD.setIntensity(0, intensity);
  player = new AnimationPlayer(&LCD);
  ticker.attach(0.5, startupAnimation);    
  
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect(deviceName);
  timeClient.begin(); 
  
  while (WiFi.status() != WL_CONNECTED) 
    delay(500);
     
  stats_timer_id = timer.setInterval(showStatsTimer, showStats);
  ticker.attach(1, one_sec_switch);
  sync();   
}

/*
menu:
0 - Animation
1 - showDate
2 - Show subs
3 - Show views
4 - ShowTime
 */

void loop() 
{
  timer.run();
  timeClient.update();
  
  switch(menu)
  {
    case 0:
      if(player->play())
      {
        tempMenu ++;
        menu = tempMenu;
        if(menu != 4)
          switch_timer_id = timer.setTimeout(statsDisplayTime, menu_switch);
      }
    break;
    
    case 1:
      showDate();
    break;

    case 2:
      showNumber(subs);
    break;

    case 3:
      showNumber(views);
    break;

    case 4:
      showTime();
      showTimeSwitch = true;
      timer.enable(stats_timer_id);
      timer.restartTimer(stats_timer_id);
      menu++;
    break;
  }
}


void showStats()
{
  sync();
  menu = 0;
  tempMenu = 0;
  showTimeSwitch = false;
  timer.disable(stats_timer_id);
}

void sync()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    timeClient.forceUpdate();
    setTime(timeClient.getEpochTime());
    api.getChannelStatistics(CHANNEL_ID);
    subs = api.channelStats.subscriberCount;
    views = api.channelStats.viewCount;
  }
}

void one_sec_switch()
{
  if(showTimeSwitch)
    showTime();
  one_sec = !one_sec;
}

void menu_switch()
{
  menu = 0;
}

void showTime()
{
  t = myTZ.toLocal(now());
  LCD.setChar(0, 0,' ', false);
  LCD.setDigit(0, 1, second(t)%10, false);
  LCD.setDigit(0, 2, second(t)/10%10, false);
  LCD.setDigit(0, 3, minute(t)%10, true);
  LCD.setDigit(0, 4, minute(t)/10%10, false);  
  LCD.setDigit(0, 5, hour(t)%10, true);  
  LCD.setDigit(0, 6, hour(t)/10%10, false); 
  LCD.setChar(0, 7, ' ', false);
}

void showDate()
{
  t = myTZ.toLocal(now());
  LCD.setDigit(0, 0, year(t)%10, false);
  LCD.setDigit(0, 1, year(t)/10%10, false);
  LCD.setDigit(0, 2, year(t)/100%10, false);
  LCD.setDigit(0, 3, year(t)/1000%10, false);
  LCD.setDigit(0, 4, month(t)%10, one_sec);  
  LCD.setDigit(0, 5, month(t)/10%10, false);  
  LCD.setDigit(0, 6, day(t)%10, one_sec); 
  LCD.setDigit(0, 7, day(t)/10%10, false);
}

void showNumber(int number)
{
  int j;
  int numberLenght = measureDigits(number);
  for(int i = 0; i < numberLenght; i++)
  {
    j = number/int(pow(10,i))%10;
    if(i%3 == 0 && i != 0 && one_sec)
      LCD.setDigit(0, i, j, true);
    else
      LCD.setDigit(0, i, j, false);
  }
}

void startupAnimation()
{
  if(config_mode)
  {
    state = !state;
    for(int i = 0; i < 8; i++)
    {
      LCD.setChar(0, i, ' ', state);
    } 
  }
  else
  {
    LCD.setChar(0, startupAnimationCounter,' ' , state);
    startupAnimationCounter--;
    if(startupAnimationCounter<0)
    {
      startupAnimationCounter=7;
      state = !state; 
    }
  }
}

void configModeCallback (WiFiManager *myWiFiManager) 
{
  config_mode = true;
  ticker.attach(1, startupAnimation);
}
