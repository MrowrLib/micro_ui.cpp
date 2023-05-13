function install_ui_library_global_dependency()
    add_requires("brew::fltk")
end

function setup_target_for_ui_library()
    add_deps("gooey-fltk")
    add_defines("GOOEY_USE_FLTK")
    add_packages("brew::fltk")
end
