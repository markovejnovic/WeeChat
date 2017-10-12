#include <gtkmm.h>
#include "Configuration.h"
#include "ConsolePrinter.h"

int createApp(int argc, char **argv, std::pair<int, int> res) {
	Glib::RefPtr<Gtk::Application> app =
	Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

	Gtk::Window window;
	window.set_default_size(res.first, res.second);

	return app->run(window);
}

int main(int argc, char **argv)
{
	try {
		std::pair<int, int> res = Config::getResolution();

		return createApp(argc, argv, res);
	} catch (const Config::FileNotFoundException &fnfe) {
		Console::lWarn("Unable to find ~/.config/WeeChat/WeeChat.conf", "Trying to create configuration file.");
	}

	return -1;
}
