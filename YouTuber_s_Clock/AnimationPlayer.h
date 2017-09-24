////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                        //
//  My YouTube channel:                                                                                   //
//  https://www.youtube.com/ArturPetrzak                                                                  //
//                                                                                                        //
//  Coded by Artur Petrzak in August 2017                                                                 //
//                                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <LedControl.h>
#include "functions.h"
#include "designs.h"
#define DesignsAmount  3
#define RandomDesignsAmount  8

class AnimationPlayer
{
  private:
    int animationStep;
    int RandomAnimationStep;
    int designNumber;
    int temp_size = 0;
    int temp_digit = 0;
    int randomDigits[8] = {8,8,8,8,8,8,8,8};
    int randomDigitsDesign[8];
    bool random_animation = false;
    bool playStarted = false;
    const uint8_t *data;//
    LedControl *LCD;//
    unsigned long interval = 0;  //
    unsigned long previousMillis = 0;//
    const uint8_t *designs[DesignsAmount] = {ring_mem, snake_mem, zigZag_mem};
    const uint8_t *RandomDesigns[RandomDesignsAmount] = {upRectLeft_mem, upRectRight_mem, botRectRight_mem, botRectLeft_mem, botRectSidesLeft_mem, botRectSidesRight_mem, topRectSidesLeft_mem, topRectSidesRight_mem};
    void reset();
    void upRect(int digit, bool right);
    void botRect(int digit, bool right);
    
  public:
    AnimationPlayer(LedControl *LCD);
    bool play();
};

AnimationPlayer::AnimationPlayer(LedControl *LCD)
{
  this->LCD = LCD;
  reset();
}

void AnimationPlayer::reset()
{
  animationStep = 1;
  RandomAnimationStep = 0;
  previousMillis = 0;
  playStarted = false;
  random_animation = false;
  designNumber = random(0,DesignsAmount + 1);
  if(designNumber == DesignsAmount)
    random_animation = true;
  
  if(random_animation)
  {
    for(int i = 0; i < 8; i++)
      randomDigits[i] = 8;
      
    int temp;
    bool check;
    for(int i = 0; i < 8; i++)
    {
      do
      {
        temp = random(0,8);
        check=true;
        for(int j = 0; j < i; j++)
        {
          if(randomDigits[j] == temp)
          {
            check = false;
            break;
          }
        }
      } while(!check);
      
      randomDigitsDesign[i] = random(0,RandomDesignsAmount);
      randomDigits[i] = temp;
    }
    
  }
  else
  {
    temp_size = designSize(designs[designNumber]);
    this->data = designs[designNumber];
    this->interval = pgm_read_byte(data + 0);
  }
  LCD->clearDisplay(0);
}
bool AnimationPlayer::play()
{
  if(playStarted == false)
  {
    LCD->clearDisplay(0);
    playStarted = true;
    if(random_animation)
    {
      data = RandomDesigns[randomDigitsDesign[animationStep-1]];
      interval = pgm_read_byte(data + 0);
    }
  }
  if(random_animation)
  {
    if(animationStep <= 8)
    {
      if((unsigned long)(millis() - previousMillis) >= interval)
      {        
        if(pgm_read_byte(data + RandomAnimationStep + 1) == 15) 
        {
          RandomAnimationStep = 0;
          data = RandomDesigns[randomDigitsDesign[animationStep-1]];
          interval = pgm_read_byte(data + 0);
          animationStep++;
        }
        else
        {
          LCD->setRow(0, randomDigits[animationStep-1], pgm_read_byte(data + RandomAnimationStep + 1));
          RandomAnimationStep++;
        }
        previousMillis = millis();
      }
      return false;
    }
    else
    {
      reset();
      return true;
    }
  }
  else
  {
    if(animationStep <= temp_size - 1)
    {
      if((unsigned long)(millis() - previousMillis) >= interval)
      {
        temp_digit = pgm_read_byte(data + animationStep);
        LCD->setRow(0, temp_digit, pgm_read_byte(data + animationStep + 1));
        animationStep += 2;
        previousMillis = millis();
      }
      return false;
    }
    else
    {
      reset();
      return true;
    }
  }
}
