#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Network/Socket.h"
#include "Network/Packet.h"

Socket::Socket()
{
  // Create the TCP socket
  if((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  {
    throw "Failed to create socket";
  }
}

Socket::Socket(int sockfd, struct sockaddr_in addr)
{
  this->sockfd = sockfd;
  this->addr = addr;
  packet_buffer = NULL;
  set_nonblocking(sockfd);
}

bool Socket::update(double delta)
{
  ssize_t amount, amount_left;
  uint8_t *c = buffer;
  if((amount = read(sockfd, buffer, SOCKET_BUFFER_SIZE)) > 0)
  {
    while(amount)
    {
      // Create new packet buffer
      if(packet_buffer == NULL)
      {
        packet_buffer = new Packet();
      }

      // Add data to packet buffer
      amount_left = packet_buffer->add_data(c, amount);

      // Send packet away!
      if(amount_left > 0)
      {
        delete packet_buffer;
      }

      // Increment amount left
      c = buffer + amount - amount_left;
      amount = amount_left;
    }
    //CSRL::inst->console->add_line(out.str());
  }
  return true;
}

void Socket::bind_port(int port)
{
  // Construct the server sockaddr_in structure
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(port);

  // Bind the server socket
  if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0)
  {
    throw "Failed to bind the server socket.";
  }
}

void Socket::start_listening()
{
  if(listen(sockfd, 5) < 0)
  {
    throw "Failed to listen on server socket.";
  }
}

// Set socket to non-blocking
void Socket::set_nonblocking(int sockfd)
{
  int flags;
  if (-1 == (flags = fcntl(sockfd, F_GETFL, 0)))
  {
    flags = 0;
  }
  if(fcntl(sockfd, F_SETFL, flags | O_NONBLOCK))
  {
    throw "Can't set socket to non-blocking.";
  }
}
