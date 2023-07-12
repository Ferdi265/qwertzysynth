#include <cstdint>
#include <fmt/format.h>
#include "state.h"

constexpr uint32_t SAMPLE_RATE = 48000;

void audio_update(void * userdata, uint8_t * raw_buffer, int raw_len);
void audio_init() {
    SDL_AudioSpec audio_config {
        .freq = SAMPLE_RATE,
        .format = AUDIO_S16SYS,
        .channels = 1,
        .silence = 0,
        .samples = 0,
        .padding = 0,
        .size = 0,
        .callback = audio_update,
        .userdata = nullptr
    };

    state.audio = SDL_OpenAudioDevice(
        nullptr, false, &audio_config, &audio_config, SDL_AUDIO_ALLOW_SAMPLES_CHANGE | SDL_AUDIO_ALLOW_FREQUENCY_CHANGE
    );
    if (state.audio <= 0) {
        fmt::print("error: failed to open audio device\n");
        return;
    }

    if (audio_config.freq != SAMPLE_RATE) {
        fmt::print("warn: samplerate changed to {} Hz\n", audio_config.freq);
    }

    fmt::print("info: buffer size is {} samples\n", audio_config.samples);

    SDL_PauseAudioDevice(state.audio, false);
}

void audio_fini() {
    SDL_CloseAudioDevice(state.audio);
}

void audio_update(void * userdata, uint8_t * raw_buffer, int raw_len) {
    (void)userdata;
    std::span<int16_t> buffer((int16_t *)raw_buffer, (int16_t *)(raw_buffer + raw_len));
    synth_update(buffer);
}
