#include "audio.h"
#include <iostream>

//Examples on how to use the audio method of this engine:
//Play regular audio: 
//c_audio->play_audio("background_music.wav"); 
//
//Play 3d audio, plays from a maps coordinate (for radios, etc.):
//glm::vec3 sound_position(10.0f, 0.0f, 5.0f);
//c_audio->play_3d_audio("ambient_sound.wav", sound_position, 1.0f, 50.0f);
//glm::vec3 camera_pos = c_camera->get_position();
//c_audio->update(camera_pos);

// NOTE: messed with this thing ALOT during dev, after changing stuff couldnt hear changes anymore

audio::audio() : g_system(nullptr) {}

audio::~audio() {
    for (auto& pair : g_loaded_audio) {
        pair.second->release();
    }
    if (g_system) {
        g_system->close();
        g_system->release();
    }
}

void audio::init() {
    FMOD_RESULT result = FMOD::System_Create(&g_system);
    if (result != FMOD_OK) {
        std::cerr << "FMOD: Failed to create system object: " << FMOD_ErrorString(result) << "\n";
        return;
    }
    result = g_system->init(AUDIO_CHANNEL_COUNT, FMOD_INIT_NORMAL, nullptr);
    if (result != FMOD_OK) {
        std::cerr << "FMOD: Failed to initialize system object: " << FMOD_ErrorString(result) << "\n";
        return;
    }

    g_system->setDSPBufferSize(AUDIO_CHANNEL_COUNT, 4);

    g_system->setSoftwareFormat(44100, FMOD_SPEAKERMODE_STEREO, 2);
}

void audio::load_audio(const std::string& filename) {
    FMOD_MODE e_mode = FMOD_3D | FMOD_3D_LINEARROLLOFF;
    FMOD::Sound* sound = nullptr;
    g_system->createSound(("resources/audio/" + filename).c_str(), e_mode, nullptr, &sound);
    g_loaded_audio[filename] = sound;
}

void audio::update(const glm::vec3& listener_position) {
    FMOD_VECTOR listener_pos = { listener_position.x, listener_position.y, listener_position.z };
    g_system->set3DListenerAttributes(0, &listener_pos, nullptr, nullptr, nullptr);
    g_system->update();

    for (auto& handle : g_playing_audio) {
        if (handle.is_3d) {
            float volume = calculate_volume(listener_position, handle.position, handle.max_distance, handle.initial_volume);

            if (handle.fade_time > 0.0f) {
                float current_time = handle.fade_elapsed_time / handle.fade_time;
                if (handle.fade_direction == FADE_IN) {
                    volume = volume * current_time;
                }
                else if (handle.fade_direction == FADE_OUT) {
                    volume = volume * (1.0f - current_time);
                }
                handle.fade_elapsed_time += 1.0f / 60.0f; // 60 fps
                if (handle.fade_elapsed_time >= handle.fade_time) {
                    handle.fade_elapsed_time = handle.fade_time;
                }
            }

            handle.channel->setVolume(volume);
        }
    }
}

void audio::play_audio(const std::string& filename, float volume, float frequency) {
    if (g_loaded_audio.find(filename) == g_loaded_audio.end()) {
        load_audio(filename);
    }
    audio_handle handle = {};
    handle.sound = g_loaded_audio[filename];
    handle.filename = filename;
    handle.is_3d = false;
    g_system->playSound(handle.sound, nullptr, false, &handle.channel);
    handle.channel->setVolume(volume);
    float current_frequency = 0.0f;
    handle.channel->getFrequency(&current_frequency);
    handle.channel->setFrequency(current_frequency * frequency);
    g_playing_audio.push_back(handle);
}

void audio::play_3d_audio(const std::string& filename, const glm::vec3& position, float volume, float max_distance, float fade_in_duration) {
    if (g_loaded_audio.find(filename) == g_loaded_audio.end()) {
        load_audio(filename);
    }
    audio_handle handle = {};
    handle.sound = g_loaded_audio[filename];
    handle.filename = filename;
    handle.position = position;
    handle.is_3d = true;
    handle.max_distance = max_distance;
    handle.initial_volume = volume;
    g_system->playSound(handle.sound, nullptr, false, &handle.channel);
    handle.channel->setMode(FMOD_3D);
    FMOD_VECTOR pos = { position.x, position.y, position.z };
    handle.channel->set3DAttributes(&pos, nullptr);
    handle.channel->set3DMinMaxDistance(0.0f, max_distance);
    handle.channel->setVolume(volume);

    if (fade_in_duration > 0.0f) {
        handle.channel->setVolume(0.0f);
    }

    g_playing_audio.push_back(handle);
}

void audio::stop_audio(const std::string& filename) {
    for (auto it = g_playing_audio.begin(); it != g_playing_audio.end(); ++it) {
        if (it->filename == filename) {
            it->fade_time = 1.0f;
            it->fade_direction = FADE_OUT;
            it->fade_elapsed_time = 0.0f;

            it->channel->stop();
            g_playing_audio.erase(it);
            break;
        }
    }
}

void audio::set_audio_volume(const std::string& filename, float volume) {
    for (auto& handle : g_playing_audio) {
        if (handle.filename == filename) {
            handle.channel->setVolume(volume);
        }
    }
}

float audio::calculate_volume(const glm::vec3& listener_position, const glm::vec3& sound_position, float max_distance, float initial_volume) {
    float distance = glm::distance(listener_position, sound_position);

    if (distance > max_distance) return 0.0f;

    // after 1/4th of the distance to the object, limit the volume
    if (distance <= max_distance * 0.25f) {
        return initial_volume;
    }

    float normalized_distance = distance / max_distance;
    return initial_volume * (1.0f - normalized_distance);
}