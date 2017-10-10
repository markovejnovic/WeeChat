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

/**
 * The resolution delimiter in the config file.
 * This must be a string, not a character.
 */
#ifndef RESOLUTION_DELIMITER
#define RESOLUTION_DELIMITER "x"
#endif

/**
 * The name of the resolution option
 */
#ifndef RESOLUTION_TEXT
#define RESOLUTION_TEXT "Resolution"
#endif

/**
 * Default config file location
 */
#ifndef DEFAULT_CONFIG_FILE_LOCATION
#define DEFAULT_CONFIG_FILE_LOCATION strcat(std::getenv("HOME"), "/.config/WeeChat/WeeChat.conf")
#endif

/**
 * @brief The Config namespace contains all functions which configure the application
 * @details The Config namespace contains the functions for setting and getting data from the configuration file.
 */
namespace Config {
	/**
	 * @brief Returns the Configuration File Location
	 */
	std::string getConfigurationFileLocation();

	/**
	 * @brief Changes the Configuration File Location
	 * @details This function allows you to set a non-default configuration file location. Using it is discouraged
	 */
	void setConfigurationFileLocation(std::string fileLocation);

	/**
	 * @brief Returns the resolution of the app on startup
	 * @return The resolution of the app on startup
	 */
	std::pair<int, int> getResolution();

	/**
	 * @brief Sets the resolution of the app on startup
	 * 
	 * @param resolution - The resolution to set
	 */
	void setResolution(std::pair<int, int> resolution);
}