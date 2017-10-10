#include <gtkmm.h>
#include "Configuration.h"

int main(int argc, char **argv)
{
	std::pair<int, int> res = Config::getResolution();

	Glib::RefPtr<Gtk::Application> app =
		Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

	Gtk::Window window;
	window.set_default_size(res.first, res.second);

	return app->run(window);
}
