#pragma once

#include "session.h"

#include <iostream>
#include <memory>
#include <boost/asio.hpp>

namespace otus {

using boost::asio::ip::tcp;

class Server {
public:
  Server(boost::asio::io_service& a_ioService, const tcp::endpoint& a_endPoint);

private:  
  void DoAccept();

private:
  tcp::acceptor m_acceptor;
  tcp::socket m_socket;
};

} // otus::
