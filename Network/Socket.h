#ifndef __SOCKET_H__
#define __SOCKET_H__

#define SOCKET_BUFFER_SIZE 1024

#include <netinet/in.h>
#include "Entities/Entity.h"

class Packet;

class Socket : public Entity
{
public:
  Socket();
  Socket(int sockfd, struct sockaddr_in addr);
  void bind_port(int port);
  void start_listening();
  void on_accept(Socket &socket);
  void on_data(Packet &packet_buffer);
  bool update(double delta);
  static void set_nonblocking(int sockfd);
public:
  int sockfd;
  struct sockaddr_in addr;
  uint8_t buffer[SOCKET_BUFFER_SIZE];
  Packet *packet_buffer;

};

#endif
