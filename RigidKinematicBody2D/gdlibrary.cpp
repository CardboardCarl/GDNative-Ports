/*===============================================
#                 gdlibrary.cpp                 #
#-----------------------------------------------#
#                                               #
#   A port of RigidKinematicBody2D to GDNative  #
#           by Ludicorde (PlugN'Play).          #
#         Special thanks to Agnis Aldins        #
#       for the original GDScript version!      #
#                                               #
#  (C) 2020 Ludicorde / Agnis "NeZvers" Aldins  #
#          PROTECTED UNDER MIT LICENSE          #
#                                               #
===============================================*/

#include "RigidKinematicBody2D.hpp"

//This stuff is needed for Godot to recognize the library.

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_class<godot::RigidKinematicBody2D>();
}