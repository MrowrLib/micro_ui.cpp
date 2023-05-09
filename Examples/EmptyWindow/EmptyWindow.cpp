#include "example_setup.h"

using namespace gooey;

int main() {
    UIApplication* app    = create_gooey_application();
    UIWindow*      window = app->add_window();
    window->set_title("Empty Window");
    window->set_size(640, 480);
    window->set_position(100, 100);
    window->show();
    return app->run_blocking();
}
