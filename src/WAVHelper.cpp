#include "WAVHelper.h"

namespace jarvis
{
namespace audiohelper
{

bool writeWAVFile(const char* filename, const std::vector<SAMPLE>& samples, int nbChannels, int sampleRate)
{
    if (samples.empty())
        throw std::logic_error("No samples to write to WAV file.\n");

    // Define the WAV header structure
    WAVHeader header;
    std::memcpy(header.riff, "RIFF", 4);
    std::memcpy(header.wave, "WAVE", 4);
    std::memcpy(header.fmt, "fmt ", 4);
    std::memcpy(header.data, "data", 4);

    header.subChunk1Size = 16; // PCM header size
    header.audioFormat = 3;    // 3 = IEEE float
    header.numChannels = nbChannels;
    header.sampleRate = sampleRate;
    header.bitsPerSample = 32;
    header.byteRate = sampleRate * nbChannels * (header.bitsPerSample / 8);
    header.blockAlign = nbChannels * (header.bitsPerSample / 8);
    header.subChunk2Size = samples.size() * sizeof(SAMPLE);
    header.chunkSize = 36 + header.subChunk2Size;

    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile)
        throw std::runtime_error(std::string("Failed to open file for writing: ") + filename + "\n");

    outFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    outFile.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(SAMPLE));
    outFile.close();

    std::cout << "WAV file written: " << filename << "\n";
    return true;
}

}
}
