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

#ifndef GTKMM_WIDGET
#define GTKMM_WIDGET
#include <gtkmm/widget.h>
#endif

#ifndef GTKMM_CSSPROVIDER
#define GTKMM_CSSPROVIDER
#include <gtkmm/cssprovider.h>
#endif

#ifndef GTKMM_STYLEPROPERTY
#define GTKMM_STYLEPROPERTY
#include <gtkmm/styleproperty.h>
#endif

namespace WeeChat {
	class ChatWidget : public Gtk::Widget {
	public:
		ChatWidget();
		virtual ~ChatWidget();

	protected:
		Gtk::SizeRequestMode get_request_mode_vfunc() const override;
		void get_preferred_width_vfunc(int &minimum_width, int &natural_width) const
			override;
		void get_preferred_height_for_width_vfunc(int width, int &minimum_height,
			int& natural_height) const  override;
		void get_preferred_height_vfunc(int &minimum_height, int &natural_height)
			const override;
		void get_preferred_width_for_height_vfunc(int height, int &minimum_width,
			int& natural_width) const override;
		void on_size_allocate(Gtk::Allocation& allocation) override;
		void on_map() override;
		void on_unmap() override;
		void on_realize() override;
		void on_unrealize() override;
		bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

		void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection> &section,
			const Glib::Error &error);

		Glib::RefPtr<Gdk::Window> m_refGdkWindow;
		Glib::RefPtr<Gtk::CssProvider> m_refCssProvider;
	};
}
