#pragma once

#include <memory>

#include "../gooey.h"

#define uint unsigned int
#define cstring const char*

namespace gooey {

    struct UIGridCellBase : public UIGridCell {
        virtual ~UIGridCellBase() = default;

        // UIGridCell
        bool     set_text(cstring text) override { return false; }
        UILabel* get_text() override { return nullptr; }
    };

    struct UIGridBase : public UIGrid {
        virtual ~UIGridBase() = default;

        // UIGrid
        UIGridCell* add_cell(
            uint x, uint y, uint columnCount = 1, uint rowCount = 1, bool visible = true
        ) override {
            return nullptr;
        }
    };

    struct UILabelBase : public UILabel {
        virtual ~UILabelBase() = default;

        // UITextInput
        bool     set_text(cstring text) override { return false; }
        cstring* get_text() override { return nullptr; }

        // UIWidget
        bool set_size(uint width, uint height) override { return false; }
        bool set_position(uint x, uint y) override { return false; }

        // UI Component
        bool set_background_color(UIColor color) override { return false; }
        bool unset_background_color() override { return false; }
        bool add_background_image(cstring imagePath) override { return false; }
        bool remove_background_image(cstring imagePath) override { return false; }
    };

    struct UITextInputBase : public UITextInput {
        virtual ~UITextInputBase() = default;

        // UITextInput
        bool     set_text(cstring text) override { return false; }
        cstring* get_text() override { return nullptr; }

        // UIWidget
        bool set_size(uint width, uint height) override { return false; }
        bool set_position(uint x, uint y) override { return false; }

        // UI Component
        bool set_background_color(UIColor color) override { return false; }
        bool unset_background_color() override { return false; }
        bool add_background_image(cstring imagePath) override { return false; }
        bool remove_background_image(cstring imagePath) override { return false; }
    };

    struct UIPanelBase : public UIPanel {
        // UIWidgetContainer
        UILabel*     add_label(cstring text) override { return nullptr; }
        UITextInput* add_text_input() override { return nullptr; }
        UIPanel*     add_vertical_panel(bool absolute) override { return nullptr; }
        UIPanel*     add_horizontal_panel(bool absolute) override { return nullptr; }
        UIGrid*      add_grid(uint columnCount, uint rowCount, uint cellSize = 0, uint padding = 0)
            override {
            return nullptr;
        }

        // UI Component
        bool set_background_color(UIColor color) override { return false; }
        bool unset_background_color() override { return false; }
        bool add_background_image(cstring imagePath) override { return false; }
        bool remove_background_image(cstring imagePath) override { return false; }
    };

    struct UIApplication;
    class UIWindowBase : public UIWindow {
        UIApplication* _base_uiApplication;

    public:
        UIWindowBase(UIApplication* uiApplication) : _base_uiApplication(uiApplication) {}

        // UIWindow
        UIApplication* get_application() override { return _base_uiApplication; }
        bool           set_title(cstring title) override { return false; }
        bool           show() override { return false; }

        // Move these:
        bool set_size(uint width, uint height) override { return false; }
        bool set_position(uint x, uint y) override { return false; }

        // UI Component
        bool set_background_color(UIColor color) override { return false; }
        bool unset_background_color() override { return false; }
        bool add_background_image(cstring imagePath) override { return false; }
        bool remove_background_image(cstring imagePath) override { return false; }

        // UIWidgetContainer
        UILabel*     add_label(cstring text) override { return nullptr; }
        UITextInput* add_text_input() override { return nullptr; }
        UIPanel*     add_vertical_panel(bool absolute) override { return nullptr; }
        UIPanel*     add_horizontal_panel(bool absolute) override { return nullptr; }
        UIGrid*      add_grid(uint columnCount, uint rowCount, uint cellSize = 0, uint padding = 0)
            override {
            return nullptr;
        }
    };

    class UIApplicationBase : public UIApplication {
        std::unique_ptr<UIDefaults> _base_uiDefaults;

    public:
        UIApplicationBase() : _base_uiDefaults(std::make_unique<UIDefaults>()) {}
        UIDefaults* get_defaults() override { return _base_uiDefaults.get(); }
        UIWindow*   add_window() override { return nullptr; }
        bool        render() override { return false; }
        bool        run_blocking() override { return false; }
        bool        destroy() override { return false; }
    };
}

#undef uint
#undef cstring
