#include <gtkmm.h>
#include "Configuration.h"
#include "ConsolePrinter.h"

int createApp(int argc, char **argv, Config::ConfigurationValues vals) {
	Glib::RefPtr<Gtk::Application> app =
	Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

	Gtk::Window window;
	window.set_default_size(vals.resolution.first, vals.resolution.second);

	return app->run(window);
}

int main(int argc, char **argv)
{
	try {
		return createApp(argc, argv, Config::read());
	} catch (const Config::FileNotFoundException &fnfe) {
		Console::lWarn("Unable to find ~/.config/WeeChat/WeeChat.conf", "Trying to create a default configuration file.");
		Config::create();

		return createApp(argc, argv, Config::read());
	}


	return -1;
}
