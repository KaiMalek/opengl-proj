#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <unordered_map>
#include <vector>

#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum fade_direction {
    FADE_IN,
    FADE_OUT
};

class audio {
public:
    audio();
    ~audio();

    void init();
    void load_audio(const std::string& filename);
    void update(const glm::vec3& listener_position, const glm::vec3& listener_forward, const glm::vec3& listener_up);
    void play_audio(const std::string& filename, float volume = 1.0f, float frequency = 1.0f, bool loop_audio = false);
    void play_3d_audio(const std::string& filename, const glm::vec3& position, float volume = 1.0f, float max_distance = 50.0f, float fade_in_duration = 0.3f);
    void stop_audio(const std::string& filename);
    void set_audio_volume(float volume);

private:
    float calculate_volume(const glm::vec3& listener_position, const glm::vec3& sound_position, float max_distance, float initial_volume);

    struct audio_handle {
        FMOD::Sound* sound;
        FMOD::Channel* channel;
        std::string filename;
        glm::vec3 position;
        float initial_volume;
        bool is_3d;
        float max_distance;
        float fade_time;
        float fade_elapsed_time;
        fade_direction fade_direction;
    };

    FMOD::System* g_system;
    std::unordered_map<std::string, FMOD::Sound*> g_loaded_audio;
    std::vector<audio_handle> g_playing_audio;
    static constexpr int AUDIO_CHANNEL_COUNT = 1024;
};

#endif
