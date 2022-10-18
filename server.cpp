#include <string>
#include <functional>
#include <thread>

#include <fmt/core.h>

#ifndef ASIO_STANDALONE
#define ASIO_STANDALONE
#endif
#include <asio/ip/tcp.hpp>
#include <asio/buffer.hpp>
#include <asio/io_context.hpp>
#include <asio/read_until.hpp>

#include "server.h"

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