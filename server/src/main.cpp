#include "../include/server.hpp"

using namespace std;

const string PATH_JSON = "../json_files/";

int main(int argc, char const *argv[]) {
    Server server = Server(PATH_JSON + "config.json", PATH_JSON + "Roomsinfo.json", PATH_JSON + "Usersinfo.json");
    server.run();
    return 0;
}