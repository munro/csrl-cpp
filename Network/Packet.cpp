#include "Network/Packet.h"
#include <cstring>

Packet::Packet()
{
  length = 0;
  buffer = NULL;
  buffer_length = 0;
}

Packet::~Packet()
{
  if(buffer != NULL)
  {
    delete buffer;
  }
}

int Packet::add_data(uint8_t *buffer, int length)
{
  if(buffer_length < 4)
  {
    for(int i = buffer_length; i < buffer_length + length; i++)
    {
      this->length += uint32_t(buffer[0]) << ((3 - i) * 8);
      buffer++;
      buffer_length++;
      length--;
    }
    if(buffer_length + length >= 4)
    {
      this->buffer = new uint8_t[this->length];
    }
    add_data(buffer, length);
  }
  else
  {
    int maxlength = length;
    if(buffer_length + length > this->length + 4)
    {
      maxlength = length - buffer_length - 4;
    }
    memcpy(this->buffer + buffer_length, buffer, maxlength);
    buffer_length += maxlength;
    return length - maxlength;
  }
  return 0;
}
