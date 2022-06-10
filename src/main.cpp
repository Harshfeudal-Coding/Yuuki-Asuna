// Cpp include
#include <iostream>
#include <fstream>

// Project include
#include "../commands/ping.h"

// Dpp include
#include <dpp/dpp.h>
#include <dpp/fmt/format.h>
#include <dpp/nlohmann/json.hpp>

// Using shorten
using json = nlohmann::json;

int main()
{
	// JSON reading setup
	json reader;
	std::ifstream reading("../config.json", std::ifstream::binary);
	reading >> reader;
	reading.close();

	// Constant variables
	const std::string token = reader["token"];

	// Bot access
	dpp::cluster client(token);
	client.start(false);

	return 0;
}