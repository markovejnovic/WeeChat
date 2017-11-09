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

#include "ConsolePrinter.h"

namespace Console {
	void info(char *msg) {
		std::cout << INFO_TEXT << " " << msg << std::endl;
	}

	void info(std::string msg) {
		std::cout << INFO_TEXT << " " << msg << std::endl;
	}

	void warn(char *msg) {
		std::cout << WARN_TEXT << " " << msg << std::endl;
	}

	void warn(std::string msg) {
		std::cout << WARN_TEXT << " " << msg << std::endl;
	}

	void lWarn(char *msg, char *info) {
		std::cout << WARN_TEXT << " " << msg << std::endl;
		for (int i = 0; i < sizeof WARN_TEXT - sizeof TEXT_BACK_YELLOW - sizeof TEXT_BACK_DEFAULT + 2; i++) {
			std::cout << " ";
		}
		std::cout << info << std::endl;
	}

	void lWarn(std::string msg, std::string info) {
		std::cout << WARN_TEXT << " " << msg << std::endl;
		for (int i = 0; i < sizeof WARN_TEXT - sizeof TEXT_BACK_YELLOW - sizeof TEXT_BACK_DEFAULT + 2; i++) {
			std::cout << " ";
		}
		std::cout << info << std::endl;
	}

	void lWarn(std::string msg, int info) {
		std::cout << WARN_TEXT << " " << msg << std::endl;
		for (int i = 0; i < sizeof WARN_TEXT - sizeof TEXT_BACK_YELLOW - sizeof TEXT_BACK_DEFAULT + 2; i++) {
			std::cout << " ";
		}
		std::cout << info << std::endl;
	}

	void err(char *msg) {
		std::cout << ERR_TEXT << " " << msg << std::endl;
	}

	void err(std::string msg) {
		std::cout << ERR_TEXT << " " << msg << std::endl;
	}

	void lErr(char *msg, char *info) {
		std::cout << ERR_TEXT << " " << msg << std::endl;
		for (int i = 0; i < sizeof ERR_TEXT - sizeof TEXT_BACK_RED - sizeof TEXT_BACK_DEFAULT + 2; i++) {
			std::cout << " ";
		}
		std::cout << info << std::endl;
	}

	void lErr(std::string msg, std::string info) {
		std::cout << ERR_TEXT << " " << msg << std::endl;
		for (int i = 0; i < sizeof ERR_TEXT - sizeof TEXT_BACK_RED - sizeof TEXT_BACK_DEFAULT + 2; i++) {
			std::cout << " ";
		}
		std::cout << info << std::endl;
	}

	void lErr(std::string msg, int info) {
		std::cout << ERR_TEXT << " " << msg << std::endl;
		for (int i = 0; i < sizeof ERR_TEXT - sizeof TEXT_BACK_RED - sizeof TEXT_BACK_DEFAULT + 2; i++) {
			std::cout << " ";
		}
		std::cout << info << std::endl;
	}
}