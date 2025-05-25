#include "AudioHelper.h"

namespace jarvis
{
namespace audiohelper
{

AudioHelper::AudioHelper(int nbChannels, int sampleRate, int framesPerBuffer) : 
    _sampleRate(sampleRate), 
    _framesPerBuffer(framesPerBuffer)
{
    PaError err = Pa_Initialize();
    if(err != paNoError)
        throw std::runtime_error(std::string("Failed to initialize PortAudio: ") + Pa_GetErrorText(err) + "\n");

    this->_params.device = Pa_GetDefaultInputDevice();
    if(this->_params.device == paNoDevice)
        throw std::runtime_error("No default input device found!\n");
    this->_params.channelCount = nbChannels;
    this->_params.sampleFormat = SAMPLE_TYPE;
    this->_params.suggestedLatency = Pa_GetDeviceInfo(this->_params.device)->defaultLowInputLatency;
    this->_params.hostApiSpecificStreamInfo = nullptr;
}

void AudioHelper::Record(int duration_seconds)
{
    PaError err = Pa_OpenStream(
        &this->_stream,
        &this->_params,
        nullptr,  // no output
        this->_sampleRate,
        this->_framesPerBuffer,
        paClipOff,
        nullptr,  // blocking read
        nullptr
    );
    if(err != paNoError)
        throw std::runtime_error(std::string("Failed to open stream: ") + Pa_GetErrorText(err) + "\n");

    err = Pa_StartStream(this->_stream);
    if(err != paNoError)
        throw std::runtime_error(std::string("Failed to start stream: ") + Pa_GetErrorText(err) + "\n");

    int totalFrames = this->_sampleRate * duration_seconds;
    this->_recordedSamples.resize(totalFrames);

    int numFramesRead = 0;
    while(numFramesRead < totalFrames)
    {
        int framesToRead = std::min(this->_framesPerBuffer, totalFrames - numFramesRead);
        err = Pa_ReadStream(this->_stream, this->_recordedSamples.data() + numFramesRead, framesToRead);
        if(err != paNoError)
            throw std::runtime_error(std::string("Failed to read stream: ") + Pa_GetErrorText(err) + "\n");
        numFramesRead += framesToRead;
    }

    Pa_StopStream(this->_stream);
    Pa_CloseStream(this->_stream);
    Pa_Terminate();
}

void AudioHelper::SaveToWAV(const char* filename)
{
    if(!jarvis::audiohelper::writeWAVFile(filename, this->_recordedSamples, this->_params.channelCount, this->_sampleRate))
        throw std::runtime_error(std::string("Failed to save recorded samples to WAV file: ") + filename + "\n");
}

}
}
