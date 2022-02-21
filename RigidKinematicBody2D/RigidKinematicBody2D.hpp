/*===============================================
#            RigidKinematicBody2D.hpp           #
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

#ifndef RIGIDKINEMATICBODY2D_H
#define RIGIDKINEMATICBODY_H

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>

namespace godot {

class RigidKinematicBody2D : public KinematicBody2D {
	GODOT_CLASS(RigidKinematicBody2D, KinematicBody2D)

private: 
	KinematicCollision2D *collision;
	Vector2 remainder;

	void rigid_physics(float delta);

public:
	Vector2 linear_velocity;
	Vector2 gravity;
	float dampening;
	float bounciness;

	void set_linear_velocity(Vector2 value) {
		linear_velocity = value;
	};

	void set_gravity(Vector2 value) {
		gravity = value;
	};

	void apply_impulse(Vector2 value) {
		linear_velocity += value;
	};

	static void _register_methods();

	RigidKinematicBody2D();
	~RigidKinematicBody2D();

	void _init();

	void _physics_process(float delta);
};



} // namespace godot
#endif //RIGIDKINEMATICBODY_H