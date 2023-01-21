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
                                      Youtuber's clock v1.1-rc.1                                                                                                                              
                                Coded by Artur Petrzak in August 2017                                   
                                                                                                                                                                                                                                   
  D1 mini WiFi ESP8266 pinout:                                                                       
    D8 - DataIn                                                                                       
    D7 - LOAD/CS                                                                                        
    D6 - CLK                                                                                          
                                                                                                                                                                                                        
  It has been designed for 8-digit 7 segment screen controlled by MAX7219.
  It should work on boards with ESP8266 module, but I have tested it only on D1 mini clone.
  If You use another board You may need to change the pinout.
  
  There is only a few delays used at the beginning of the code.
  I have programmed it using timers (especially in animations) so this code supports multitasking. 
  With this, You can easily add a new functions running in background etc.                
  
  Consider supporting me if You like this project: https://paypal.me/ArturPetrzak                      
                                                                                                       
  Needed libraries:
    You can download these libraries from library manager in Arduino IDE:
    - NTPClient (3.2.1): https://github.com/arduino-libraries/NTPClient
    - Time (1.6.1): https://github.com/PaulStoffregen/Time
    - YoutubeApi (2.0.0): https://github.com/witnessmenow/arduino-youtube-api
    - WiFiManager (2.0.15-rc.1): https://github.com/tzapu/WiFiManager
    - LedControl (1.0.6): https://github.com/wayoda/LedControl
    - ArduinoJson (6.20.0): https://github.com/bblanchon/ArduinoJson
    - ESP8266 (3.1.0) (from Boards Manager. You need to add this URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
      first in Arduino IDE preferences -> Additional Boards Manager URLs. Then You will find ESP8266 in Boards Manager)
    
    You need to download these libraries from github and put in Your Arduino libraries folder. 
    - Timezone (1.2.4): https://github.com/JChristensen/Timezone  
    - SimpleTimer (Nov 6, 2018): https://github.com/schinken/SimpleTimer


  Changelog:
  21.01.2023 - version 1.1 released
    - Updated libraries.
    - Described compatible libraries versions.
    - Support for Arduino IDE 2.0.3

  Notes:
  - On Arduino IDE 2.0.3 some of the libraries might not be possible to downlaod via Library manager. In this case go to github and download them manually.
  For board choose: LOLIN(WEMOS) D1 mini (clone)

  Bug:
  - Nothing is displayed when YT subs should be displayed.

  Your settings here:
*/

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

// End of settings section

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
  client.setInsecure(); 
  
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
