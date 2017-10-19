#include "Configuration.h"

#ifndef RESOLUTION_DELIMITER
#define RESOLUTION_DELIMITER "x";
#endif

namespace Config {
	ConfigurationValues configurationValues;

	static boost::filesystem::path configFileLocation(DEFAULT_CONFIG_FILE_LOCATION);
	static boost::filesystem::path configFile(configFileLocation / boost::filesystem::path(DEFAULT_CONFIG_FILE_NAME));

	std::pair<std::string, std::string> getKeyValuePair(std::string key);

	void create() {
		if (boost::filesystem::is_directory(configFileLocation)) {
			std::ofstream file;
			file.open(configFile.string());
			file << CONFIG_DEFAULT;
			file.close();
		} else {
			boost::filesystem::create_directory(configFileLocation);

			std::ofstream file;
			file.open(configFile.string());
			file << CONFIG_DEFAULT;
			file.close();
		}
	}

	boost::filesystem::path getConfigurationFile() {
		return configFile;
	}

	void setConfigurationFile(char *fileLocation) {
		configFile = fileLocation;
	}

	ConfigurationValues read() {
		std::ifstream file;
		file.open(configFile.string());

		if (!file) {
			throw FileNotFoundException(configFile.string().c_str());
		}

		std::string line;
		while (std::getline(file, line)) {
			if (boost::starts_with(line, CONFIG_COMMENT_CHARACTER)) {
				continue;
			} else if (boost::starts_with(line, RESOLUTION_TEXT)) {
				configurationValues.resolution = parseResolution(parseKeyValue(line));
			} else {
				Console::warn("Unknown line while reading configuration file: \"" + line + "\". Skipping it.");
			}
		}

		file.close();

		return configurationValues;
	}

	std::pair<std::string, std::string> parseKeyValue(std::string line) {
		int delimiterPosition = line.find(CONFIG_DELIMITER);
		int endLinePosition = line.find("\r") | line.find("\n");

		return std::make_pair(
			line.substr(0, delimiterPosition),
			line.substr(delimiterPosition + 1, endLinePosition)
		);
	}

	std::pair<short, short> parseResolution(std::pair<std::string, std::string> keyValuePair) {
		int delimiterPosition = keyValuePair.second.find(RESOLUTION_DELIMITER);
		int endLinePosition = keyValuePair.second.find("\r") | keyValuePair.second.find("\r");

		return std::make_pair(
			std::stoi(keyValuePair.second.substr(0, delimiterPosition)),
			std::stoi(keyValuePair.second.substr(delimiterPosition + 1, endLinePosition))
		);
	}

	std::pair<std::string, std::string> getKeyValuePair(std::string key) {
		std::pair<std::string, std::string> keyValuePair;

		std::ifstream file;
		file.open(configFile.string());

		if (!file) {
			throw FileNotFoundException(configFile.string().c_str());
		}

		bool keyIsFound = false;

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream inputStreamLine(line);

			std::string k;

			if (std::getline(inputStreamLine, k, '=')) {
				if (k == key) {
					keyIsFound = true;

					std::string value;
					if (std::getline(inputStreamLine, value)) {
						int delimiterPosition = value.find(RESOLUTION_DELIMITER);

						keyValuePair = std::make_pair(
							value.substr(0, delimiterPosition),
							value.substr(delimiterPosition + sizeof(RESOLUTION_DELIMITER) - 1)
						);
					}
				}
			}
		}

		file.close();

		if (!keyIsFound)
			throw ConfigurationKeyNotFoundException(key.c_str());

		return keyValuePair;
	}

	std::pair<int, int> getResolution() {
		std::pair<std::string, std::string> stringResolution = getKeyValuePair(RESOLUTION_TEXT);

		return std::make_pair(std::stoi(stringResolution.first), std::stoi(stringResolution.second));
	}

	void setResolution(std::pair<int, int>) {

	}

	void setDefaultResolution() {
		std::ofstream file;
		file.open(configFile.string());

		if (!file) {
			throw FileNotFoundException(configFile.string().c_str());
		}

		file << RESOLUTION_TEXT CONFIG_DELIMITER RESOLUTION_DEFAULT << std::endl;

		file.close();
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

	ConfigurationKeyNotFoundException::ConfigurationKeyNotFoundException(char const *key) throw()
		: std::runtime_error("Configuration key not found") {};

	const char* ConfigurationKeyNotFoundException::what() const throw() {
		return std::runtime_error::what();
	}

	char* ConfigurationKeyNotFoundException::getKey() const {
		return key;
	}
}