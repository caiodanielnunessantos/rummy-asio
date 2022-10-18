#include "game.h"
#include <mutex>
#include <shared_mutex>
#include <set>

std::mutex protect_global_data;
std::set<std::string> user_names;
std::set<std::string> rooms;

void game_handler(std::function<void(std::string)> write, std::function<std::string()> read) {
    std::string this_client_name;
    try{
        write("Digite seu nome para começar\n");
        while (this_client_name.empty()) {
            std::string name = read();

        }
        
        read();
    } catch(...) {
        protect_global_data.lock();
        user_names.erase(this_client_name);
        protect_global_data.unlock();
    }
}
