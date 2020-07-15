#pragma once

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <thread>
#include <string>
#include <deque>
#include <atomic>

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
  void DoWrite();
  void ProcessWrite();
  void Close();
  void Stop();

private:
  tcp::socket m_Socket;
  boost::asio::streambuf m_Buffer;

  std::deque<std::string> m_WriteMsgs;
  std::thread m_WriteThread;
  std::atomic<bool> m_Done{false};
};

} // otus::
