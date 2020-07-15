#include "session.h"

namespace otus {

Session::Session(tcp::socket a_Socket)
  : m_Socket(std::move(a_Socket)) 
  , m_Done{false}
{ 

}

void Session::Start() 
{
  m_WriteThread = std::move(std::thread(&Session::ProcessWrite, this));
  DoRead();
}

void Session::Stop() 
{
  m_Socket.close();
  m_Done = true;
  if (m_WriteThread.joinable()){
    m_WriteThread.join();
  }
}

void Session::DoRead()
{
  auto self(shared_from_this());
  boost::asio::async_read_until(m_Socket, m_Buffer, '\n',
    [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
      if (!ec) {
        Deliver();

        DoRead();
      } 
      else {      
        Stop();
      }      
    }
  );
}

void Session::Deliver()
{

}

void Session::ProcessWrite()
{
  while (!m_Done) {
    // if (GetWriteQueue()) {
      DoWrite();
    // }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void Session::DoWrite()
{
  auto self(shared_from_this());

  boost::asio::async_write(m_Socket,
    boost::asio::buffer("Ok", 2),
    // boost::asio::buffer(mWriteMsgs.front().c_str(), mWriteMsgs.front().size()),
  [this, self](boost::system::error_code ec, std::size_t /*length*/)
  {
      if (ec)
          Stop();
  });
  // mWriteMsgs.pop_front();
}

} // otus::
