// External include
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
#include <spdlog/fmt/fmt.h>

// Cpp include
#include <iostream>
#include <fstream>

// Using shorten
using json = nlohmann::json;

int main(int argc, char* argv[])
{
	// JSON reading setup
	json reader;
	{
		std::ifstream reading("config.json");
		reading >> reader;
		reading.close();
	}

	// Constant
	const std::string token = reader["token"];

	// Intents for bot
	dpp::cluster client(token, dpp::i_all_intents);

	// Logging announcement
	client.on_ready([&client](const dpp::ready_t& event) {
		fmt::print("{} has launched!\n", client.me.format_username());
		client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_game, "Genshin Impact"));
		});

	// Starting the bot
	client.start(false);
	return 0;
}