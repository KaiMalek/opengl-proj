#pragma once

// srr for anyone who gets confused with this variable.h feature shit
// old habbit from csgo cheats :O
// for future debug menu variables
namespace variables {
	inline bool menu_open = false;
	inline static bool was_insert_pressed = false; // for the menu functionality
	inline bool enable_movement = false;

	// world model settings
	inline float cube_angle = 0.0f;
	inline float cube_rotate_speed = 0.0f;

	// movement
	inline float movement_speed = 8.f;
	inline float mouse_sens = 0.1f;
}