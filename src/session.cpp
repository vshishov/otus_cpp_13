#include "session.h"

namespace otus {

Session::Session(tcp::socket a_Socket)
  : m_Socket(std::move(a_Socket)) 
{ 

}

void Session::Start() 
{
  DoRead();
}

void Session::DoRead()
{
  auto self(shared_from_this());
  boost::asio::async_read_until(m_Socket, m_Buffer, '\n',
    [this, self](boost::system::error_code ec, std::size_t length)
    {
      // m_ssInputStream.write(m_Buffer, length);
      if (ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset) {
        Close();
      } 
      else {      
        Proccess();
      }
      
      if (!ec) {
        // Deliver();
        DoWrite(length);
        
        // DoRead();
      }
    }
  );
}

void Session::Deliver()
{

}

void Session::DoWrite(std::size_t /*a_szLength*/)
{
  auto self(shared_from_this());
  boost::asio::async_write(m_Socket, m_Buffer,
    [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
      if (!ec) {
        DoRead();
      }
    });
}

void Session::Proccess()
{
  std::string line;
  m_ssInputStream.seekp(0);
  while (!std::getline(m_ssInputStream, line).eof()) {
    if (line.length() > 0 && line[line.length() - 1] == '\r') {
      line = line.substr(0, line.length() - 1);
    }
  }
  m_ssInputStream.clear();
  m_ssInputStream.str("");
  m_ssInputStream.write(line.c_str(), line.size());
}

void Session::Close()
{
}

} // otus::
