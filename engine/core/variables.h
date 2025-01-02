#pragma once

// srr for anyone who gets confused with this variable.h feature shit
// old habbit from csgo cheats :O
// for future debug menu variables
namespace variables {
	inline bool menu_open = false;
	inline static bool was_insert_pressed = false; // for the menu functionality
	inline bool enable_movement = false;

	// cube settings
	inline float cube_angle = 0.0f;
	inline float cube_rotate_speed = 0.0f;
}