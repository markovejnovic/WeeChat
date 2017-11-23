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
#include "ChatWidget.h"

#ifndef CONSOLE_PRINTER
#define CONSOLE_PRINTER
#include "ConsolePrinter.h"
#endif

#include <iostream>

#ifndef GDKMM_GENERAL
#define GDKMM_GENERAL
#include <gdkmm/general.h>
#endif

#ifndef MINIMUM_WIDTH
#define MINIMUM_WIDTH 100
#endif

#ifndef NATURAL_WIDTH
#define NATURAL_WIDTH 300
#endif

#ifndef MINIMUM_HEIGHT
#define MINIMUM_HEIGHT 60
#endif

#ifndef NATURAL_HEIGHT
#define NATURAL_HEIGHT 200
#endif

namespace WeeChat {
	ChatWidget::ChatWidget() :
		Glib::ObjectBase("chat-widget"),
		Gtk::Widget() {
		set_has_window(true);
		set_name("chat-widget");
		
		// Get CSS Provider
		m_refCssProvider = Gtk::CssProvider::create();
		auto refStyleContext = get_style_context();
		refStyleContext->add_provider(m_refCssProvider,
			GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		m_refCssProvider->signal_parsing_error().connect(
			sigc::mem_fun(*this, &ChatWidget::on_parsing_error));

		try {
			m_refCssProvider->load_from_path(DATADIR "/css/ChatWidget.css");
		} catch (const Gtk::CssProviderError &cpe) {
			Console::lWarn("CssProviderError in ChatWidget", cpe.what());
		} catch (const Glib::Error &e) {
			Console::lErr("Error in ChatWidget", e.what());
		}
	}
	
	ChatWidget::~ChatWidget() {
		// TODO Destroy
	}

	Gtk::SizeRequestMode ChatWidget::get_request_mode_vfunc() const {
		return Gtk::Widget::get_request_mode_vfunc();
	}

	void ChatWidget::get_preferred_width_vfunc(int &minimum_width, int
		&natural_width) const {
		minimum_width = MINIMUM_WIDTH;
		natural_width = NATURAL_WIDTH;
	}

	void ChatWidget::get_preferred_height_for_width_vfunc(int /* width */,
		int &minimum_height, int &natural_height) const {
		minimum_height = MINIMUM_HEIGHT;
		natural_height = NATURAL_HEIGHT;
	}

	void ChatWidget::get_preferred_height_vfunc(int &minimum_height,
		int &natural_height) const {
		minimum_height = MINIMUM_HEIGHT;
		natural_height = NATURAL_HEIGHT;
	}

	void ChatWidget::get_preferred_width_for_height_vfunc(int /* height */,
		int &minimum_height, int &natural_height) const {
		minimum_height = MINIMUM_WIDTH;
		natural_height = NATURAL_WIDTH;
	}

	void ChatWidget::on_size_allocate(Gtk::Allocation &allocation) {
		set_allocation(allocation);
	
		if (m_refGdkWindow) {
			m_refGdkWindow->move_resize(allocation.get_x(), allocation.get_y(),
				allocation.get_width(), allocation.get_height());
		}
	}

	void ChatWidget::on_map() {
		Gtk::Widget::on_map();
	}

	void ChatWidget::on_unmap() {
		Gtk::Widget::on_unmap();
	}

	void ChatWidget::on_realize() {
		set_realized();

		if (!m_refGdkWindow) {
			GdkWindowAttr attributes;
			memset(&attributes, 0, sizeof(attributes));

			Gtk::Allocation allocation = get_allocation();

			attributes.x = allocation.get_x();
			attributes.y = allocation.get_y();
			attributes.width = allocation.get_width();
			attributes.height = allocation.get_height();

			attributes.event_mask = get_events() | Gdk::EXPOSURE_MASK;
			attributes.window_type = GDK_WINDOW_CHILD;
			attributes.wclass = GDK_INPUT_OUTPUT;

			m_refGdkWindow = Gdk::Window::create(get_parent_window(), &attributes,
				GDK_WA_X | GDK_WA_Y);
			set_window(m_refGdkWindow);

			m_refGdkWindow->set_user_data(gobj());
		}
	}

	void ChatWidget::on_unrealize() {
		m_refGdkWindow.reset();

		Gtk::Widget::on_unrealize();
	}

	bool ChatWidget::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
		const Gtk::Allocation allocation = get_allocation();
		const double scale_x = (double)allocation.get_width() / 1000;
		const double scale_y = (double)allocation.get_height() / 1000;
		auto refStyleContext = get_style_context();

		refStyleContext->render_background(cr,
			allocation.get_x(), allocation.get_y(),
			allocation.get_width(), allocation.get_height());

		// Draw chatheads!

		return true;
	}

	void ChatWidget::on_parsing_error(
		const Glib::RefPtr<const Gtk::CssSection> &section,
		const Glib::Error &error) {
		Console::lWarn("CSS on_parsing_error() in ChatWidget", error.what());

		if (section) {
			const auto file = section->get_file();

			if (!file) {
				Console::lWarn("CSS File does not exists", file->get_uri());
			} else {
				Console::warn("Error in CSS File");
			}
		}
	}
}
