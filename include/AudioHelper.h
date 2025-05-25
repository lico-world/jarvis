#pragma once

#include <stdexcept>
#include <vector>
#include "portaudio.h"
#include "WAVHelper.h"

namespace jarvis
{
namespace audiohelper
{
// Type definition
#define SAMPLE_TYPE  paFloat32

class AudioHelper
{
private:
    PaStream * _stream;
    PaStreamParameters _params;
    std::vector<SAMPLE> _recordedSamples;
    int _sampleRate,
        _framesPerBuffer;

public:
    AudioHelper(int nbChannels, int sampleRate=44100, int framesPerBuffer=512);
    void Record(int duration_seconds);
    void SaveToWAV(const char* filename);
};

}
}