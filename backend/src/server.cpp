// File: backend/src/server.cpp

#include <iostream>
#include <set>
#include <nlohmann/json.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using websocketpp::connection_hdl;
using message_ptr = websocketpp::server<websocketpp::config::asio>::message_ptr;
using json = nlohmann::json;

std::set<connection_hdl, std::owner_less<connection_hdl>> connections;
websocketpp::server<websocketpp::config::asio> server;

// Simplified placeholder tree
std::vector<int> tree;

void on_message(connection_hdl hdl, message_ptr msg) {
    try {
        json request = json::parse(msg->get_payload());
        std::string action = request["action"];
        int value = request["value"];

        if (action == "insert") {
            tree.push_back(value); // Replace with real tree logic
        }

        json response = {
            {"status", "ok"},
            {"tree", tree}
        };

        server.send(hdl, response.dump(), msg->get_opcode());
    } catch (std::exception& e) {
        json err = {{"status", "error"}, {"message", e.what()}};
        server.send(hdl, err.dump(), msg->get_opcode());
    }
}

int main() {
    server.init_asio();
    server.set_message_handler(&on_message);
    server.set_open_handler([](connection_hdl hdl) {
        connections.insert(hdl);
    });
    server.set_close_handler([](connection_hdl hdl) {
        connections.erase(hdl);
    });

    server.listen(9000);
    server.start_accept();
    std::cout << "Server running on port 9000...\n";
    server.run();

    return 0;
}
