/* WeeChat
 * Copyright (C) 2017 Marko Vejnovic
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * This file contains the functions necessary for manipulating the application configuration file usually found in
 * ~/.config/WeeChat/WeeChat.conf
 */

#ifndef IOSTREAM
#include <iostream>
#define IOSTREAM
#endif

#ifndef FSTREAM
#include <fstream>
#define FSTREAM
#endif

#ifndef SSTREAM
#include <sstream>
#define SSTREAM
#endif

#ifndef STRING
#include <string>
#define STRING
#endif

#ifndef CSTRING
#include <cstring>
#define CSTRING
#endif

#ifndef BOOST_FILESYSTEM
#include <boost/filesystem.hpp>
#define BOOST_FILESYSTEM
#endif

#ifndef BOOST_ALGORITHM_STRING_PREDICATE
#include <boost/algorithm/string/predicate.hpp>
#define BOOST_ALGORITHM_STRING_PREDICATE
#endif

#ifndef CONSOLE_PRINTER
#include "ConsolePrinter.h"
#define CONSOLE_PRINTER
#endif

/**
 * Default config file name
 */
#ifndef DEFAULT_CONFIG_FILE_NAME
#define DEFAULT_CONFIG_FILE_NAME "WeeChat.conf"
#endif

/**
 * Default config file location
 */
#ifndef DEFAULT_CONFIG_FILE_LOCATION
#define DEFAULT_CONFIG_FILE_LOCATION strcat(std::getenv("HOME"), "/.config/WeeChat/")
#endif

/**
 * The comment character for the config file
 */
#ifndef CONFIG_COMMENT_CHARACTER
#define CONFIG_COMMENT_CHARACTER "#"
#endif

/**
 * The delimiter for config strings
 */
#ifndef CONFIG_DELIMITER
#define CONFIG_DELIMITER "="
#endif

/**
 * The name of the resolution option
 */
#ifndef RESOLUTION_TEXT
#define RESOLUTION_TEXT "Resolution"
#endif

/**
 * The resolution delimiter in the config file.
 * This must be a string, not a character.
 */
#ifndef RESOLUTION_DELIMITER
#define RESOLUTION_DELIMITER "x"
#endif

/**
 * The default resolution to write to the config file
 */
#ifndef RESOLUTION_DEFAULT
#define RESOLUTION_DEFAULT "700" RESOLUTION_DELIMITER "500"
#endif

/**
 * The default text to write to the config file[WARNING] 
 */
#ifndef CONFIG_DEFAULT
#define CONFIG_DEFAULT \
	RESOLUTION_TEXT "=" RESOLUTION_DEFAULT "\n"
#endif

/**
 * @brief The Config namespace contains all functions which configure the
 * application.
 * @details The Config namespace contains the functions for setting and getting
 * data from the configuration file.
 */
namespace Config {
	/**
	 * @brief A struct which contains all of the configuration values
	 */
	struct ConfigurationValues {
		std::pair<int, int> resolution;
	};

	/**
	 * @brief Creates a default configuration file
	 * @details This method creates a default configuration in
	 * DEFAULT_CONFIG_FILE_LOCATION with the name DEFAULT_CONFIG_FILE_NAME and
	 * writes CONFIG_DEFAULT to it. If DEFAULT_CONFIG_FILE_LOCATION is
	 * !boost::filesystem::is_directory() then a directory is created and the file
	 * created in it.
	 */
	void create();

	/**
	 * @brief Returns the Configuration File Path
	 */
	boost::filesystem::path getConfigurationFile();

	/**
	 * @brief Changes the Configuration File Path
	 * @details This function allows you to set a non-default configuration file
	 * location. Using it is discouraged.
	 */
	void setConfigurationFile(std::string fileLocation);

	/**
	 * @brief Reads the configuration file line by line, returniing all the
	 * configuration values.
	 * @return ConfigurationValues All ConfigurationValues read
	 */
	ConfigurationValues read();

	/**
	 * @brief Parses key and value from a line in the configuration file
	 * 
	 * @param line A line to parse
	 * @return An std::pair of the key and the value
	 */
	std::pair<std::string, std::string> parseKeyValue(std::string line);

	/**
	 * @brief Tries to parse the resolution
	 * 
	 * @param keyValuePair The pair of a key and value in the config file
	 * @return A pair of resolutions (width and height)
	 */
	std::pair<short, short> parseResolution(
		std::pair<std::string, std::string> keyValuePair);

	/**
	 * @brief Returns the resolution of the app on startup
	 * @return The resolution of the app on startup
	 * 
	 * @todo Implement the same functionality using boost
	 */
	std::pair<int, int> getResolution();

	/**
	 * @brief Sets the resolution of the app on startup
	 * 
	 * @param resolution - The resolution to set
	 */
	void setResolution(std::pair<int, int> resolution);

	/**
	 * @brief Writes a default resolution denominated by
	 * RESOLUTION_TEXT CONFIG DELIMITER RESOLUTION_DEFAULT to the configuration
	 * file.
	 */
	void setDefaultResolution();

	/**
	 * @brief An exception for when a file (usually accessed via ifstream) is not
	 * found.
	 */
	class FileNotFoundException : public std::runtime_error {
	public:
		/**
		 * @brief Constructs the exception
		 * 
		 * @param fileLocation Holds the location of the file in a C-style string
		 */
		FileNotFoundException(char const *fileLocation) throw();

		/**
		 * @brief Echoes the exception message including the missing file
		 */
		virtual const char* what() const throw();

		/**
		 * @brief Returns the static file location
		 * @return C-style string containing the static file location
		 */
		char *getFileLocation() const;
	
	private:
		char *fileLocation;
	};

	/**
	 * @brief An exception for when a configuration key is not found in the
	 * configuration file.
	 */
	class ConfigurationKeyNotFoundException : public std::runtime_error {
	public:
		/**
		 * @brief Constructs the exception
		 * 
		 * @param key The missing key
		 */
		ConfigurationKeyNotFoundException(char const *key) throw();

		/**
		 * @brief Echoes the exception message including the missing key
		 */
		virtual const char* what() const throw();

		/**
		 * @brief Returns the key that was searched
		 * @return C-style string containing the key
		 */
		char *getKey() const;
	
	private:
		char *key;
	};
}
