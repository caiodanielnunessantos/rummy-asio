#ifndef IO_HPP
#define IO_HPP

#include <bits/stdc++.h>
#include <fmt/core.h>
#define ASIO_STANDALONE
#include <asio.hpp>

using namespace std;
using namespace asio;
using namespace asio::ip;

static string get_line_from_client(tcp::socket& skt) {
    string line;
    read_until(skt, dynamic_buffer(line), '\n');
    line.pop_back();
    return line;
}

template <typename... T>
static void put_to_client(tcp::socket& skt, string form, T... args) {
    write(skt, buffer(fmt::format(fmt::runtime(form), args...)));
}

static void server(io_context& ctx, unsigned short port, function<void(tcp::socket)> fn) {
    tcp::acceptor acpt(ctx, tcp::endpoint(tcp::v4(), port));
    for (;;) {
        std::thread(fn, acpt.accept()).detach();
    }
}

#endif