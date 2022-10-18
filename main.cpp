#include "game.hpp"
#include "server.hpp"

#include "pch.h"

int main(int argc, char* argv[]) {
    asio::io_context ctx;
    std::vector<server> servers;
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