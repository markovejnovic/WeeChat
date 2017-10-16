/**
 * MIT License
 *
 * Copyright (c) 2017 Marko Vejnovic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
#define RESOLUTION_DEFAULT "400" RESOLUTION_DELIMITER "300"
#endif

/**
 * The default text to write to the config file[WARNING] 
 */
#ifndef CONFIG_DEFAULT
#define CONFIG_DEFAULT \
	RESOLUTION_TEXT "=" RESOLUTION_DEFAULT "\n"
#endif

/**
 * @brief The Config namespace contains all functions which configure the application
 * @details The Config namespace contains the functions for setting and getting data from the configuration file.
 */
namespace Config {
	/**
	 * @brief Creates a default configuration file
	 * @details This method creates a default configuration in DEFAULT_CONFIG_FILE_LOCATION with the name
	 * DEFAULT_CONFIG_FILE_NAME and writes CONFIG_DEFAULT to it. If DEFAULT_CONFIG_FILE_LOCATION is
	 * !boost::filesystem::is_directory() then a directory is created and the file created in it.
	 */
	void create();

	/**
	 * @brief Returns the Configuration File Path
	 */
	boost::filesystem::path getConfigurationFile();

	/**
	 * @brief Changes the Configuration File Path
	 * @details This function allows you to set a non-default configuration file location. Using it is discouraged.
	 */
	void setConfigurationFile(std::string fileLocation);

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
	 * @brief Writes a default resolution denominated by RESOLUTION_TEXT CONFIG DELIMITER RESOLUTION_DEFAULT to the
	 * configuration file
	 */
	void setDefaultResolution();

	/**
	 * @brief An exception for when a file (usually accessed via ifstream) is not found
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
	 * @brief An exception for when a configuration key is not found in the configuration file
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