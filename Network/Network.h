#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <list>
#include <netinet/in.h>
#include "Entities/Entity.h"
#include "Network/Socket.h"
using namespace std;

class ServerClient : public Entity
{
public:
  ServerClient(int sockfd, struct sockaddr_in addr);
  bool update(double delta);
public:
  int sockfd;
  struct sockaddr_in addr;
};

class Network : public Entity
{
public:
};

class Server : public Network
{
public:
  Server(int port);
  bool update(double delta);
public:
  Socket socket;
  list <ServerClient *> clients;
};

#endif
