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

#include "ChatTitleWidget.h"

#ifndef GDKMM_GENERAL
#include <gdkmm/general.h>
#define GDKMM_GENERAL
#endif

#ifndef GTKMM_IMAGE
#include <gtkmm/image.h>
#define GTKMM_IMAGE
#endif

#ifndef GTKMM_LABEL
#include <gtkmm/label.h>
#define GTKMM_LABEL
#endif

#ifndef CONSOLE_PRINTER
#include "ConsolePrinter.h"
#define CONSOLE_PRINTER
#endif

#ifndef GTKMM_BOX
#include <gtkmm/box.h>
#define GTKMM_BOX
#endif

#ifndef GTKMM_PIXBUF
#include <gdkmm/pixbuf.h>
#define GTKMM_PIXBUF
#endif

#ifndef GDKMM_SCREEN
#include <gdkmm/screen.h>
#define GDKMM_SCREEN
#endif

#ifndef MINIMUM_WIDTH
#define MINIMUM_WIDTH 250
#endif

#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 60
#endif

#ifndef PROFILE_PICTURE_PADDING
#define PROFILE_PICTURE_PADDING 8
#endif

#ifndef PROFILE_PICTURE_PADDING_HORIZONTAL
#define PROFILE_PICTURE_PADDING_HORIZONTAL 0
#endif

#ifndef TEXT_PADDING
#define TEXT_PADDING 16
#endif

namespace WeeChat {
	ChatTitleWidget::ChatTitleWidget() : Gtk::HBox() {
		set_visible(true);
		set_size_request(200, DEFAULT_HEIGHT);
		set_name("chat-title-widget");

		// Create profile picture widget
		// TODO: Try Catches
		// TODO: Download picture from online

		Gtk::Image *profileImage = Gtk::manage(new Gtk::Image(
			Gdk::Pixbuf::create_from_file(DATADIR "/res/img/profilePicture.png")->
				scale_simple(DEFAULT_HEIGHT - PROFILE_PICTURE_PADDING, 
					DEFAULT_HEIGHT - PROFILE_PICTURE_PADDING, Gdk::InterpType::INTERP_BILINEAR)));

		Gtk::VBox *textContainer = Gtk::manage(new Gtk::VBox());
		textContainer->set_name("text-container");

		pack_start(*profileImage, false, false, PROFILE_PICTURE_PADDING + PROFILE_PICTURE_PADDING_HORIZONTAL);		
		pack_start(*textContainer, false, true, TEXT_PADDING);

		Gtk::Label *chatTitle = Gtk::manage(new Gtk::Label("Chat Title",
			Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_START, true));
		chatTitle->set_name("chat-title-text");
		Gtk::Label *chatDescription = Gtk::manage(new Gtk::Label("Chat Description",
			Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_START, false));
		chatDescription->set_name("chat-description-text");

		textContainer->set_spacing(0);
		textContainer->pack_start(*chatTitle, false, false, 0);
		textContainer->pack_start(*chatDescription, false, false, 0);

		// After overall layout is done, try styling
		get_style();
	}

	ChatTitleWidget::~ChatTitleWidget() {}

	Gtk::SizeRequestMode ChatTitleWidget::get_request_mode_vfunc() const {
		return Gtk::Widget::get_request_mode_vfunc();
	}

	void ChatTitleWidget::get_preferred_width_vfunc(int &minimum_width, int &natural_width) const {
		minimum_width = MINIMUM_WIDTH;
		natural_width = MINIMUM_WIDTH;
	}

	void ChatTitleWidget::get_preferred_width_for_height_vfunc(
		int height, int &minimum_width, int &natural_width) const {
		minimum_width = MINIMUM_WIDTH;
		natural_width = MINIMUM_WIDTH;
	}

	void ChatTitleWidget::get_preferred_height_vfunc(int &minimum_height, int &natural_height) const {
		minimum_height = DEFAULT_HEIGHT;
		natural_height = DEFAULT_HEIGHT;
	}

	void ChatTitleWidget::get_preferred_height_for_width_vfunc(
		int width, int &minimum_height, int &natural_height) const {
		minimum_height = DEFAULT_HEIGHT;
		natural_height = DEFAULT_HEIGHT;
	}

	void ChatTitleWidget::get_style() {
		Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();
		cssProvider->signal_parsing_error().connect(sigc::mem_fun(this, &ChatTitleWidget::on_css_parsing_error));
		try {
			cssProvider->load_from_path(DATADIR "/css/ChatTitleWidget.css");
		} catch (const Gtk::CssProviderError &cpe) {
			Console::lWarn("CssProviderError in ChatTitleWidget", cpe.what());
		} catch (const Glib::Error &e) {
			Console::lErr("Error in ChatTitleWidget", e.what());
		}

		Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
		if (!screen) {
			Console::err("There is no available screen. The widget most likely did not construct.");
		}

		Glib::RefPtr<Gtk::StyleContext> styleContext = get_style_context();
		styleContext->add_provider_for_screen(screen, cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	}

	void ChatTitleWidget::on_css_parsing_error(
		const Glib::RefPtr<const Gtk::CssSection> &section, const Glib::Error &error) {
		Console::lWarn("CSS Parsing Error in ChatTitleWidget", error.what());

		if (section) {
			const auto file = section->get_file();

			if (file) {
				Console::lWarn("CSS File:", file->get_uri());
			}

			Console::lWarn("Section starting line:", section->get_start_line() + 1);
			Console::lWarn("Section ending line:", section->get_end_line() + 1);
		}
	}


}