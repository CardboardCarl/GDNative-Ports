/*===============================================
#            RigidKinematicBody2D.cpp           #
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

#include <ClassDB.hpp>
using namespace godot;

void RigidKinematicBody2D::_register_methods() {
	register_signal<RigidKinematicBody2D>((char *)"collided", "collision", GODOT_VARIANT_TYPE_OBJECT, "strength", GODOT_VARIANT_TYPE_REAL);

	register_property<RigidKinematicBody2D, Vector2>("linear_velocity", &RigidKinematicBody2D::linear_velocity, Vector2(0, 0));
	register_property<RigidKinematicBody2D, Vector2>("gravity", &RigidKinematicBody2D::gravity, Vector2(0, 9.8));
	register_property<RigidKinematicBody2D, float>("dampening", &RigidKinematicBody2D::dampening, 0.005);
	register_property<RigidKinematicBody2D, float>("bounciness", &RigidKinematicBody2D::bounciness, 0.5);

	register_method("_physics_process", &RigidKinematicBody2D::_physics_process);
	register_method("set_linear_velocity", &RigidKinematicBody2D::set_linear_velocity);
	register_method("set_gravity", &RigidKinematicBody2D::set_gravity);
	register_method("apply_impulse", &RigidKinematicBody2D::apply_impulse);
}

void RigidKinematicBody2D::_init() {

	linear_velocity = Vector2(0, 0);
	gravity = Vector2(0, 9.8);
	dampening = 0.005;
	bounciness = 0.5;

}

void RigidKinematicBody2D::_physics_process(float delta) {
	rigid_physics(delta);
}

void RigidKinematicBody2D::rigid_physics(float delta) {
	linear_velocity += gravity; //add gravity
	collision = *move_and_collide(linear_velocity * delta + remainder); //apply physics
	linear_velocity = linear_velocity * (1 - dampening); //reduce speed over time
	if (collision) { //collision detected
		Vector2 normal = collision->get_normal(); //surface normal
		float strength = -normal.dot(linear_velocity);
		linear_velocity += normal * strength * (1 - bounciness); //dampen velocity in floor direction
		linear_velocity = linear_velocity.bounce(normal); //bounce off the surface
		remainder = collision->get_remainder().bounce(normal); //add in next frame
		emit_signal("collided", collision, strength);
	} else {
		remainder = Vector2(0, 0); //No collision means no remainder
	}
}

RigidKinematicBody2D::RigidKinematicBody2D() {

}

RigidKinematicBody2D::~RigidKinematicBody2D() {
}