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
  void DoWrite(std::size_t a_szLength);
  void Deliver();
  void Proccess();
  void Close();

private:
  tcp::socket m_Socket;

  boost::asio::streambuf m_Buffer;
  std::stringstream m_ssInputStream;
};

} // otus::
