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

#ifndef GTKMM_BOX
#include <gtkmm/box.h>
#define GTKMM_BOX
#endif

#ifndef GTKMM_CSSPROVIDER
#include <gtkmm/cssprovider.h>
#define GTKMM_CSSPROVIDER
#endif

#ifndef CHAT_TITLE_WIDGET_WIDTH
#define CHAT_TITLE_WIDGET_WIDTH 200
#endif

#ifndef CHAT_TITLE_WIDGET_HEIGHT
#define CHAT_TITLE_WIDGET_HEIGHT 60
#endif

namespace WeeChat {
	class ChatTitleWidget : public Gtk::HBox {
	public:
		ChatTitleWidget();
		virtual ~ChatTitleWidget();

	protected:
		Gtk::SizeRequestMode get_request_mode_vfunc() const override;
		void get_preferred_width_vfunc(int &minimum_width, int &natural_width) const
			override;
		void get_preferred_width_for_height_vfunc(int height, int &minimum_width,
			int &natural_width) const override;
		void get_preferred_height_vfunc(int &minimum_height, int &natural_height)
			const override;
		void get_preferred_height_for_width_vfunc(int width, int &minimum_height,
			int &natural_height) const override;

		void on_css_parsing_error(const Glib::RefPtr<const Gtk::CssSection> &section,
			const Glib::Error &error);

	private:
		void get_style();
 	};
}
