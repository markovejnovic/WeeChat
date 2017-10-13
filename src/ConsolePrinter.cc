#include "ConsolePrinter.h"

namespace Console {
	void info(char *msg) {
		std::cout << INFO_TEXT << " " << msg << std::endl;
	}

	void warn(char *msg) {
		std::cout << WARN_TEXT << " " << msg << std::endl;
	}

	void lWarn(char *msg, char *info) {
		std::cout << WARN_TEXT << " " << msg << std::endl;
		for (int i = 0; i < sizeof WARN_TEXT - sizeof TEXT_BACK_YELLOW - sizeof TEXT_BACK_DEFAULT + 2; i++) {
			std::cout << " ";
		}
		std::cout << info << std::endl;
	}

	void err(char *msg) {
		std::cout << ERR_TEXT << " " << msg << std::endl;
	}

	void lErr(char *msg, char *info) {
		std::cout << ERR_TEXT << " " << msg << std::endl;
		for (int i = 0; i < sizeof ERR_TEXT - sizeof TEXT_BACK_RED - sizeof TEXT_BACK_DEFAULT + 2; i++) {
			std::cout << " ";
		}
		std::cout << info << std::endl;
	}
}