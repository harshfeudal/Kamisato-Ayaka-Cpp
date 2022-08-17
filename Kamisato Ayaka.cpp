// External include
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/bundled/format.h>

// Cpp include
#include <iostream>
#include <fstream>
#include <map>

// Project include
#include "commands/handler.h"
#include "commands/ping.h"

// Using shorten
using json = nlohmann::json;

// Building slash commands
std::map<std::string, cmd_def> commands
{
	// Inspired JSON style, remember the name is lowercase
	{
		"ping", { "Check Asuna latecy", ping_h }
	},
};

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

	/* ------------ After here, we can use client ------------ */

	// Bot ready
	client.on_ready([&client](const dpp::ready_t& event) {
		fmt::print("{} has launched!\n", client.me.format_username());
		client.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_game, "Genshin Impact"));

		if (dpp::run_once<struct bulk_register>())
		{
			std::vector<dpp::slashcommand> slash_cmds;

			/*
				- This is the setup of the commands.
				- If you want to delete it, guild or global command(s),
				you just put the note here so that it will pass blank vector.
			*/
			for (auto& def : commands)
			{
				// Make slash commands
				dpp::slashcommand cmd;

				// Slash commands template
				cmd
					.set_name(def.first)
					.set_description(def.second.des)
					.set_application_id(client.me.id);

				// Option if added
				cmd.options = def.second.param;

				// Push back the vector
				slash_cmds.push_back(cmd);
			}

			// Global slash command create
			client.global_bulk_command_create(slash_cmds);
		}
		});

	// Slash command ready
	client.on_slashcommand([&client](const dpp::slashcommand_t& event)
		{
			const dpp::command_interaction cmd_data = event.command.get_command_interaction();

			// Command existence check
			const auto cmd_filter = commands.find(cmd_data.name);

			// Calling a handler when matching
			if (cmd_filter != commands.end())
			{
				cmd_filter->second.func(client, event);
			}
		});

	// Bot start
	client.start(false);
	return 0;
}