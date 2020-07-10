#pragma once

#include <iostream>
#include <memory>
#include <boost/asio.hpp>

namespace otus {

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
  Session(tcp::socket a_Socket);
  
  void Start();

private:
  void DoRead();
  void Deliver();
  void Proccess();
  void Close();

private:
  tcp::socket m_Socket;

  char m_buffer[1];
  std::stringstream m_ssInputStream;
};

} // otus::
