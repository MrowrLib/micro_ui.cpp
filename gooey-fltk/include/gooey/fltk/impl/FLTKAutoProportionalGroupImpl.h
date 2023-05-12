#pragma once

#include <cstdint>  // for Fl.H use of intptr_t
//

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_draw.H>

namespace gooey::fltk::impl {

    class FLTKAutoProportionalGroupImpl : public Fl_Group {
        Fl_Color* _backgroundColor;

        bool _absolute         = false;
        bool scale_all_content = true;
        bool manage_width;
        bool manage_height;

    public:
        FLTKAutoProportionalGroupImpl(
            bool absolute, int X, int Y, int W, int H, bool manage_width = false,
            bool manage_height = false, bool scale_all_content = true, const char* L = 0
        )
            : Fl_Group(X, Y, W, H, L),
              _absolute(absolute),
              manage_width(manage_width),
              manage_height(manage_height),
              scale_all_content(scale_all_content) {
            end();
        }

        void set_background_color(Fl_Color color) { _backgroundColor = new Fl_Color(color); }

        void set_visible(bool visible) { visible ? Fl_Group::show() : Fl_Group::hide(); }

        void draw() override {
            if (_backgroundColor) {
                fl_color(*_backgroundColor);
                fl_rectf(x(), y(), w(), h());
            }

            // Fl_Group::draw();

            int num_children = children();
            for (int i = 0; i < num_children; ++i) {
                Fl_Widget* child_widget = child(i);
                draw_child(*child_widget);
            }
        }

        void resize(int X, int Y, int W, int H) override {
            Fl::lock();
            Fl_Group::resize(X, Y, W, H);

            int num_children                                 = children();
            int other_children_which_are_not_absolute_panels = num_children;

            int parentChildrenThatAreNotAbsolutePanels = 0;
            if (parent()) {
                int allParentChildren = parent()->children();
                for (int i = 0; i < allParentChildren; ++i) {
                    Fl_Widget* child_widget = parent()->child(i);
                    if (FLTKAutoProportionalGroupImpl* childAutoProportionalGroup =
                            dynamic_cast<FLTKAutoProportionalGroupImpl*>(child_widget)) {
                        if (childAutoProportionalGroup->_absolute) continue;
                    }
                    ++parentChildrenThatAreNotAbsolutePanels;
                }
            }

            int max_width    = 0;
            int max_height   = 0;
            int total_width  = 0;
            int total_height = 0;
            for (int i = 0; i < num_children; ++i) {
                Fl_Widget* child_widget = child(i);

                if (FLTKAutoProportionalGroupImpl* childAutoProportionalGroup =
                        dynamic_cast<FLTKAutoProportionalGroupImpl*>(child_widget)) {
                    if (childAutoProportionalGroup->_absolute) {
                        other_children_which_are_not_absolute_panels--;
                        continue;
                    }
                }

                total_width += child_widget->w();
                total_height += child_widget->h();
                if (child_widget->w() > max_width) {
                    max_width = child_widget->w();
                }
                if (child_widget->h() > max_height) {
                    max_height = child_widget->h();
                }
            }

            int cur_x = X;
            int cur_y = Y;
            for (int i = 0; i < num_children; ++i) {
                Fl_Widget* child_widget = child(i);

                if (FLTKAutoProportionalGroupImpl* childAutoProportionalGroup =
                        dynamic_cast<FLTKAutoProportionalGroupImpl*>(child_widget)) {
                    if (childAutoProportionalGroup->_absolute) {
                        child_widget->size(parent()->w(), parent()->h());
                        continue;
                    }
                }

                int child_width  = child_widget->w();
                int child_height = child_widget->h();

                if (manage_width) {
                    child_width = static_cast<int>(
                        W * (static_cast<double>(child_widget->w()) / total_width)
                    );
                }

                if (manage_height) {
                    child_height = static_cast<int>(
                        H * (static_cast<double>(child_widget->h()) / total_height)
                    );
                    // if (scale_all_content) child_height = H / num_children;
                }

                // if (scale_all_content) child_height = parent()->h() / num_children;
                // if (scale_all_content) child_height = parent()->h() / num_children;
                // if (scale_all_content && manage_width)
                //     client_he

                if (scale_all_content) {
                    if (manage_height)
                        if (_absolute) {
                            child_widget->resize(X, cur_y, parent()->w(), child_height);
                        } else {
                            child_widget->resize(
                                X, cur_y, parent()->w() / parent()->children(), child_height
                                // X, cur_y, parent()->w() / parent()->children(), child_height
                                // X, cur_y, parent()->w() / parentChildrenThatAreNotAbsolutePanels,
                            );
                        }
                    else
                        child_widget->resize(
                            cur_x, Y, child_width, H
                        );  // replace with true proportions
                } else {
                    child_widget->resize(cur_x, cur_y, child_width, child_height);
                }

                if (manage_width) {
                    cur_x += child_width;
                }
                if (manage_height) {
                    cur_y += child_height;
                }
            }
            Fl::unlock();
            Fl::awake();
        }
    };
}
