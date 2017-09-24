////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                        //
//  My YouTube channel:                                                                                   //
//  https://www.youtube.com/ArturPetrzak                                                                  //
//                                                                                                        //
//  Coded by Artur Petrzak in August 2017                                                                 //
//                                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//15 means end of array
int designSize(const uint8_t *data)
{
  int temp_size = 0;
  while(pgm_read_byte(data + temp_size) != 15)
  {
    temp_size++;
  }
  return temp_size;
}

//Returns number of digits of int number
int measureDigits(int number)
{
  for(int i = 0; i < 8; i++)
  {
    if(number / pow(10,i) < 1)
      return i;
  }
}

