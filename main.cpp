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

mutex protect_global_data;
set<string> user_names;
set<string> rooms;

int main(int argc, char* argv[]) {
    io_context ctx;
    server(ctx, 1234, [](tcp::socket skt) {
        string this_client_name;
        try{
            put_to_client(skt, "Digite seu nome para começar\n");
            while (this_client_name.empty()) {
                string name = get_line_from_client(skt);
                if (name.empty()) continue;
                protect_global_data.lock();
                if (user_names.contains(name)) {
                    protect_global_data.unlock();
                    put_to_client(skt, "Esse nome já está em uso, digite outro\n");
                    continue;
                } else {
                    user_names.insert(name);
                    protect_global_data.unlock();
                    this_client_name = name;
                }
            }
            
            get_line_from_client(skt);
        } catch(...) {
            protect_global_data.lock();
            user_names.erase(this_client_name);
            protect_global_data.unlock();
        }
    });
}