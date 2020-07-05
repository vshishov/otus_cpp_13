#include "server.h"

namespace otus {

Server::Server(boost::asio::io_service& a_ioService, const tcp::endpoint& a_endPoint)
  : m_acceptor(a_ioService, a_endPoint)
  , m_socket(a_ioService)
{
  DoAccept();
}

void Server::DoAccept()
{
  m_acceptor.async_accept(m_socket,
    [this](boost::system::error_code ec)
    {
      if (!ec) {
        std::make_shared<Session>(std::move(m_socket))->Start();
      }

      DoAccept();
    });
}

} // otus::
