#include "pch.h"

template <typename... T>
static void put_to_client(asio::ip::tcp::socket& skt, std::string form, T... args) {
    write(skt, buffer(fmt::format(fmt::runtime(form), args...)));
}

std::string get_line_from_client(asio::ip::tcp::socket& skt) {
    std::string line;
    asio::read_until(skt, asio::dynamic_buffer(line), '\n');
    line.pop_back();
    return line;
}

void server(asio::io_context& ctx, unsigned short port, std::function<void(asio::ip::tcp::socket)> fn) {
    asio::ip::tcp::acceptor acpt(ctx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
    for (;;) {
        std::thread(fn, acpt.accept()).detach();
    }
}