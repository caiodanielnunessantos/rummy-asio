#include "server.h"
#include "game.h"

#include <asio/buffer.hpp>
#include <string>
#include <set>
#include <mutex>

#include <fmt/core.h>

#ifndef ASIO_STANDALONE
#define ASIO_STANDALONE
#endif
#include <asio/buffer.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/io_context.hpp>
#include <asio/read_until.hpp>
#include <asio/write.hpp>

int main(int argc, char* argv[]) {
    asio::io_context ctx;
    server(ctx, 1234, [](asio::ip::tcp::socket skt) {
        game_handler([&](std::string str) -> void {
            asio::write(skt, asio::buffer(str));
        }, [&]() -> std::string {
            std::string str;
            asio::read_until(skt, asio::dynamic_buffer(str), '\n');
            return str;
        });
    });
}