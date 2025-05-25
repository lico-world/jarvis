#pragma once

#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>

namespace jarvis
{

namespace audiohelper
{
typedef float SAMPLE;

struct WAVHeader
{
    char riff[4];           // "RIFF"
    uint32_t chunkSize;     // 36 + SubChunk2Size
    char wave[4];           // "WAVE"
    char fmt[4];            // "fmt "
    uint32_t subChunk1Size; // 16 for PCM
    uint16_t audioFormat;   // 3 for IEEE float
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;      // SampleRate * NumChannels * BitsPerSample/8
    uint16_t blockAlign;    // NumChannels * BitsPerSample/8
    uint16_t bitsPerSample; // 32 bits here
    char data[4];           // "data"
    uint32_t subChunk2Size; // NumSamples * NumChannels * BitsPerSample/8
};

bool writeWAVFile(const char* filename, const std::vector<SAMPLE>& samples, int nbChannels=1, int sampleRate=44100);

}
}