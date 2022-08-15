// Dpp include
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>

// Using shorten
using json = nlohmann::json;

// Cpp include
#include <iostream>
#include <fstream>

int main()
{
	// JSON reading setup
	json reader;
	{
		std::ifstream reading("config.json");
		reading >> reader;
		reading.close();
	}

	// Constant variables
	const std::string token = reader["token"];

	// Bot access, with intents 32767 like JS
	dpp::cluster client(token, dpp::i_all_intents);

	// Console log (if you don't want to log, just do the note like me)
	client.on_log(dpp::utility::cout_logger());

	// Bot start
	client.start(false);
	return 0;
}