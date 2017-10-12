#include "Configuration.h"

#ifndef RESOLUTION_DELIMITER
#define RESOLUTION_DELIMITER "x";
#endif

namespace Config {
	/**
	 * @brief The location of the configuration file
	 */
	static char *configFileLocation = DEFAULT_CONFIG_FILE_LOCATION;

	/**
 	 * @brief A low level function which returns a pair of a key and a value read from the configuration file.
	 * @return A key value pair
	 */
	std::pair<std::string, std::string> getKeyValuePair(std::string key);

	std::string getConfigurationFileLocation() {
		return configFileLocation;
	}

	void setConfigurationFileLocation(char *fileLocation) {
		configFileLocation = fileLocation;
	}

	std::pair<std::string, std::string> getKeyValuePair(std::string key) {
		std::pair<std::string, std::string> keyValuePair;

		std::ifstream file;
		file.open(configFileLocation);

		// TODO: Handle case of file not existing
		if (!file) {
			throw FileNotFoundException(configFileLocation);
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
		// TODO
	}

	/**
	 * Exceptions
	 */
	FileNotFoundException::FileNotFoundException(char const *fileLocation) throw() : std::runtime_error("File not found") {};

	const char* FileNotFoundException::what() const throw() {
		return std::runtime_error::what();
	}

	char* FileNotFoundException::getFileLocation() const {
		return fileLocation;
	}
}