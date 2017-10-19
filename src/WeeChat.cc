#include <gtkmm.h>
#include "Configuration.h"
#include "ConsolePrinter.h"

Gtk::ApplicationWindow *appWindow = nullptr;

int createApp(int argc, char **argv, Config::ConfigurationValues vals) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

	Glib::RefPtr<Gtk::Builder> uiBuilder = Gtk::Builder::create();
	uiBuilder->add_from_file(DATADIR "/ui.glade");

	uiBuilder->get_widget("MainApplicationWindow", appWindow);

	if (appWindow) {
		return app->run(*appWindow);
	} else {
		return -2;
	}
}

int main(int argc, char **argv)
{
	try {
		return createApp(argc, argv, Config::read());
	} catch (const Config::FileNotFoundException &fnfe) {
		Console::lWarn("Unable to find ~/.config/WeeChat/WeeChat.conf", "Trying to create a default configuration file.");
		Config::create();

		return createApp(argc, argv, Config::read());
	} catch (const Glib::FileError &fe) {
		Console::lErr("No Glade UI File found. Exiting.", fe.what());
	} catch (const Glib::MarkupError &me) {
		Console::lErr("Bad Glade UI File Markup. Exiting.", me.what());
	} catch (const Gtk::BuilderError &be) {
		Console::lErr("There's a builder error", be.what());
	}

	return -1;
}
