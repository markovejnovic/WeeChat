#include <gtkmm.h>
#include "Configuration.h"
#include "ConsolePrinter.h"

struct ConfigOpts {
	std::pair<int, int> res;
};

ConfigOpts getConfig() {
	ConfigOpts cOpts;
	cOpts.res = Config::getResolution();

	return cOpts;
}

int createApp(int argc, char **argv, ConfigOpts options) {
	Glib::RefPtr<Gtk::Application> app =
	Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

	Gtk::Window window;
	window.set_default_size(options.res.first, options.res.second);

	return app->run(window);
}

int main(int argc, char **argv)
{
	try {
		return createApp(argc, argv, getConfig());
	} catch (const Config::FileNotFoundException &fnfe) {
		Console::lWarn("Unable to find ~/.config/WeeChat/WeeChat.conf", "Trying to create a default configuration file.");
		Config::create();

		return createApp(argc, argv, getConfig());
	} catch (const Config::ConfigurationKeyNotFoundException &fknfe) {
		Console::lWarn("Unable to find the Resolution value in ~/.config/WeeChat/WeeChat.conf", "Trying to set the default value.");
		Config::setDefaultResolution();

		return createApp(argc, argv, getConfig());
	}

	return -1;
}
