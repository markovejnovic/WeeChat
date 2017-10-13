#include "Configuration.h"

#ifndef RESOLUTION_DELIMITER
#define RESOLUTION_DELIMITER "x";
#endif

namespace Config {
	static boost::filesystem::path configFileLocation(DEFAULT_CONFIG_FILE_LOCATION);
	static boost::filesystem::path configFile(configFileLocation / boost::filesystem::path(DEFAULT_CONFIG_FILE_NAME));

	std::pair<std::string, std::string> getKeyValuePair(std::string key);

	void create() {
		if (boost::filesystem::is_directory(configFileLocation)) {
			std::ofstream file;
			file.open(configFile.string());
			file << CONFIG_DEFAULT;
		} else {
			boost::filesystem::create_directory(configFileLocation);

			std::ofstream file;
			file.open(configFile.string());
			file << CONFIG_DEFAULT;
		}
	}

	boost::filesystem::path getConfigurationFile() {
		return configFile;
	}

	void setConfigurationFile(char *fileLocation) {
		configFile = fileLocation;
	}

	std::pair<std::string, std::string> getKeyValuePair(std::string key) {
		std::pair<std::string, std::string> keyValuePair;

		std::ifstream file;
		file.open(configFile.string());

		if (!file) {
			throw FileNotFoundException(configFile.string().c_str());
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream inputStreamLine(line);

			std::string k;
			if (std::getline(inputStreamLine, k, '=')) {
				if (k == key) {
					std::string value;
					if (std::getline(inputStreamLine, value)) {
						int delimiterPosition = value.find(RESOLUTION_DELIMITER);

						keyValuePair = std::make_pair(
							value.substr(0, delimiterPosition),
							value.substr(delimiterPosition + sizeof(RESOLUTION_DELIMITER) - 1)
						);
					} else {
						// TODO: Handle case of value of resolution not being set
					}
				}
			}
		}

		// TODO: Handle case of key not existing

		file.close();

		return keyValuePair;
	}

	std::pair<int, int> getResolution() {
		std::pair<std::string, std::string> stringResolution = getKeyValuePair(RESOLUTION_TEXT);

		return std::make_pair(std::stoi(stringResolution.first), std::stoi(stringResolution.second));
	}

	void setResolution(std::pair<int, int>) {

	}

	/**
	 * Exceptions
	 */
	FileNotFoundException::FileNotFoundException(char const *fileLocation) throw()
		: std::runtime_error("File not found") {};

	const char* FileNotFoundException::what() const throw() {
		return std::runtime_error::what();
	}

	char* FileNotFoundException::getFileLocation() const {
		return fileLocation;
	}
}