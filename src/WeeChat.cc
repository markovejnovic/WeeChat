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

#include <gtkmm.h>
#include "Configuration.h"
#include "ConsolePrinter.h"
#include "ChatTitleWidget.h"

Gtk::ApplicationWindow *appWindow = nullptr;

int createApp(int argc, char **argv, Config::ConfigurationValues vals) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

	Glib::RefPtr<Gtk::Builder> uiBuilder = Gtk::Builder::create();
	uiBuilder->add_from_file(DATADIR "/ui.glade");

	uiBuilder->get_widget("MainApplicationWindow", appWindow);

	WeeChat::ChatTitleWidget *ctw = Gtk::manage(new WeeChat::ChatTitleWidget());
	WeeChat::ChatTitleWidget *ctw2 = Gtk::manage(new WeeChat::ChatTitleWidget());
	WeeChat::ChatTitleWidget *ctw3 = Gtk::manage(new WeeChat::ChatTitleWidget());
	WeeChat::ChatTitleWidget *ctw4 = Gtk::manage(new WeeChat::ChatTitleWidget());
	WeeChat::ChatTitleWidget *ctw5 = Gtk::manage(new WeeChat::ChatTitleWidget());
	WeeChat::ChatTitleWidget *ctw6 = Gtk::manage(new WeeChat::ChatTitleWidget());
	WeeChat::ChatTitleWidget *ctw7 = Gtk::manage(new WeeChat::ChatTitleWidget());
	WeeChat::ChatTitleWidget *ctw8 = Gtk::manage(new WeeChat::ChatTitleWidget());

	if (appWindow) {
		appWindow->set_default_size(vals.resolution.first, vals.resolution.second);

		Gtk::ListBox* chatTitleContainer = nullptr;
		uiBuilder->get_widget("ChatTitleContainer", chatTitleContainer);

		auto mRefCssProvider = Gtk::CssProvider::create();
		try {
			mRefCssProvider->load_from_path(DATADIR "/css/WeeChat.css");
		} catch (const Gtk::CssProviderError &cpe) {
			Console::lErr("CssProviderError", cpe.what());
		} catch (const Glib::Error &e) {
			Console::lErr("Glib::Error", e.what());
		}

		auto screen = Gdk::Screen::get_default();
		auto refStyleContext = chatTitleContainer->get_style_context();
		refStyleContext->add_provider_for_screen(screen, mRefCssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

		chatTitleContainer->append(*ctw);
		chatTitleContainer->append(*ctw2);
		chatTitleContainer->append(*ctw3);
		chatTitleContainer->append(*ctw4);
		chatTitleContainer->append(*ctw5);
		chatTitleContainer->append(*ctw6);
		chatTitleContainer->append(*ctw7);
		chatTitleContainer->append(*ctw8);

		appWindow->show_all_children();

		return app->run(*appWindow);
	} else {
		return -2;
	}
}

int main(int argc, char **argv) {
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
