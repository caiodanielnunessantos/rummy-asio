#include <string>
#include <asio/ip/tcp.hpp>
#include <fmt/core.h>

std::string get_line_from_client(asio::ip::tcp::socket& skt);

template <typename... T>
static void put_to_client(asio::ip::tcp::socket& skt, std::string form, T... args) {
    write(skt, buffer(fmt::format(fmt::runtime(form), args...)));
}

void server(asio::io_context& ctx, unsigned short port, std::function<void(asio::ip::tcp::socket)> fn);