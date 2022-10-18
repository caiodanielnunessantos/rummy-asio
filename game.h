#include <string>
#include <functional>

void game_handler(std::function<void(std::string)> write, std::function<std::string()> read);