#include "Network/Network.h"
#include "Engine/CSRL.h"
#include "Entities/Console.h"
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fcntl.h>
using namespace std;

Server::Server(int port)
{
  // Bind socket to port
  socket.bind_port(port);

  // Listen on the server socket
  socket.start_listening();

  // Set socket to nonblocking
  //Network::set_nonblocking(sockfd);
}

bool Server::update(double delta)
{

  int clientfd;
  struct sockaddr_in clientaddr;
  unsigned int clientlen = sizeof(clientaddr);

  // Wait for client connection
/*  if((clientfd = accept(sockfd, (struct sockaddr *) &clientaddr, &clientlen)) >= 0)
  {
    // Accept new client!
    CSRL::inst->console->add_line(string("Client connected: ") + inet_ntoa(clientaddr.sin_addr));
//    clients.push_back(new ServerClient(clientfd, clientaddr));
  }*/

  // Update clients
  for(list <ServerClient *>::iterator it = clients.begin(); it != clients.end(); it++)
  {
    (*it)->update(delta);
  }
  return true;
}


