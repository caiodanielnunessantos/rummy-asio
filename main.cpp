#include "io.hpp"

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