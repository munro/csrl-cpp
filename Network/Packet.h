#ifndef __PACKET_H__
#define __PACKET_H__

#include <arpa/inet.h>

class Packet
{
public:
  Packet();
  ~Packet();
  bool is_done();
  int add_data(uint8_t *buffer, int length);
public:
  uint32_t length;
  uint8_t *buffer;
  uint32_t buffer_length;
};

#endif
