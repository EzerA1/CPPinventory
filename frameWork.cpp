#include <iostream>
#include <vector>
#include <memory>
#include <asio.hpp>

using namespace std;
using namespace asio;
using namespace asio::ip;

class Session : public enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket) : socket_(move(socket)) {}

    void start() {
        doRead();
    }

private:
    void doRead() {
        auto self(shared_from_this());
        socket_.async_read_some(buffer(data_, max_length),
            [this, self](error_code ec, size_t length) {
                if (!ec) {
                    doWrite(length);
                }
            });
    }

    void doWrite(size_t length) {
        auto self(shared_from_this());
        async_write(socket_, buffer(data_, length),
            [this, self](error_code ec, size_t /*length*/) {
                if (!ec) {
                    doRead();
                }
            });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};

class Server {
public:
    Server(io_context& io_context, short port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
          socket_(io_context) {
        doAccept();
    }

private:
    void doAccept() {
        acceptor_.async_accept(socket_,
            [this](error_code ec) {
                if (!ec) {
                    make_shared<Session>(move(socket_))->start();
                }
                doAccept();
            });
    }

    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

int main() {
    try {
        io_context io_context;
        Server server(io_context, 8080);
        io_context.run();
    } catch (exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
