#include "AudioHelper.h"

int main()
{
    try
    {
        jarvis::audiohelper::AudioHelper audioHelper(1);
        audioHelper.Record(5); // Record for 5 seconds
        audioHelper.SaveToWAV("output/output.wav");
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what();
        return 1;
    }

    return 0;
}
