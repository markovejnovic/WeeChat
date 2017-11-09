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

#ifndef IOSTREAM
#include <iostream>
#define IOSTREAM
#endif

/**
 * Posix Colors
 */
#ifndef TEXT_DEFAULT
#define TEXT_DEFAULT "\e[0m"
#endif

#ifndef TEXT_BOLD
#define TEXT_BOLD "\e[1m"
#endif

#ifndef TEXT_DIM
#define TEXT_DIM "\e[2m"
#endif

#ifndef TEXT_BACK_DEFAULT
#define TEXT_BACK_DEFAULT "\e[49m"
#endif

#ifndef TEXT_BACK_YELLOW
#define TEXT_BACK_YELLOW "\e[43m"
#endif

#ifndef TEXT_BACK_RED
#define TEXT_BACK_RED "\e[41m"
#endif

#ifndef INFO_TEXT
#define INFO_TEXT "[INFO]"
#endif

#ifndef WARN_TEXT
#define WARN_TEXT "[" TEXT_BACK_YELLOW "WARNING" TEXT_BACK_DEFAULT "]"
#endif

#ifndef ERR_TEXT
#define ERR_TEXT "[" TEXT_BACK_RED "ERROR" TEXT_BACK_DEFAULT "]"
#endif

namespace Console {

	/**
	 * @brief Prints an informational message to the console
	 * 
	 * @param msg A C-style string of the message to print
	 */
	void info(char *msg);

	/**
	 * @brief Prints an informational message to the console
	 * 
	 * @param msg A std::string to print
	 */
	void info(std::string msg);

	/**
	 * @brief Prints a warning message to the console
	 * 
	 * @param msg A C-style string of the message to print
	 */
	void warn(char *msg);

	/**
	 * @brief Prints a warning message to the console
	 * 
	 * @param msg A std::string of the message to print
	 */
	void warn(std::string msg);

	/**
	 * @brief Prints a warning message with extra info to the console
	 * 
	 * @param msg A C-style string of the message to print
	 * @param info A C-style string of the extra info to print
	 */
	void lWarn(char *msg, char *info);

	/**
	 * @brief Prints a warning message with extra info to the console
	 * 
	 * @param msg A std::string of the message to print
	 * @param info A std::string of the extra info to print
	 */
	void lWarn(std::string msg, std::string info);

	/**
	 * @brief Prints a warning message with extra info to the console
	 * 
	 * @param msg A std::string of the message to print
	 * @param infoInt An integer of the extra info to print
	 */
	void lWarn(std::string msg, int infoInt);

	/**
	 * @brief Prints an error message to the console
	 * 
	 * @param msg A C-style string of the message to print
	 */
	void err(char *msg);

	/**
	 * @brief Prints an error message to the console
	 * 
	 * @param msg A std::string of the message to print
	 */
	void err(std::string msg);

	/**
	 * @brief Prints an error message with extra info to the console
	 * 
	 * @param msg A C-style string of the message to print
	 * @param info A C-style string of the extra info to print
	 */
	void lErr(char *msg, char *info);

	/**
	 * @brief Prints an error message with extra info to the console
	 * 
	 * @param msg An std::string of the message to print
	 * @param info An std::tring of the extra info to print
	 */
	void lErr(std::string msg, std::string info);

	/**
	 * @brief Prints a error message with extra info to the console
	 * 
	 * @param msg A std::string of the message to print
	 * @param infoInt An integer of the extra info to print
	 */
	void lErr(std::string msg, int infoInt);
}