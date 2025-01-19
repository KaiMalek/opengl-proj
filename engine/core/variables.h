#pragma once
#include <string>

// srr for anyone who gets confused with this variable.h feature shit
// old habbit from csgo cheats :O
// for future debug menu variables
namespace variables {
	//console
	inline bool console_visible = false;
	inline bool was_grave_pressed = false;

	// menu
	inline bool menu_open = false;
	inline static bool was_insert_pressed = false; // for the menu functionality
	inline bool enable_movement = false;
	
	// audio
	inline const std::string background_audio_file = "test.wav";
	inline float background_audio = 0.01;
}