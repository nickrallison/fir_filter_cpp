#include <iostream>
#include <cmath>

#include "../libs/AudioFile/AudioFile.h"

static const int filter_length = 256;

int main(int argc, char *argv[]) {
    AudioFile<double> audioFile;
    audioFile.load("assets/downloads/OSR_us_000_0010_8k.wav");
    audioFile.printSummary();

    int numChannels = audioFile.getNumChannels();
    int numSamplesPerChannel = audioFile.getNumSamplesPerChannel();
    float sampleRate = audioFile.getSampleRate();
    int bitDepth = audioFile.getBitDepth();
    double lengthInSeconds = audioFile.getLengthInSeconds();
    
    bool isMono = audioFile.isMono();
    bool isStereo = audioFile.isStereo();



    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(1);
    buffer[0].resize(numSamplesPerChannel);
    double* filter = new double(filter_length);
    filter[0] = 1.;

    for (int buffer_sample = 0; buffer_sample < filter_length; buffer_sample++) {
        double sample_out = 0;
        for (int filter_sample = buffer_sample; filter_sample >= 0; buffer_sample--) {
            sample_out += filter[buffer_sample - filter_sample] * audioFile.samples[0][filter_sample];
        }
        buffer[0][buffer_sample] = sample_out;
    }

    for (int buffer_sample = filter_length; buffer_sample < numSamplesPerChannel; buffer_sample++) {
        double sample_out = 0;
        for (int filter_sample = buffer_sample; filter_sample >= buffer_sample - filter_length; buffer_sample--) {
            sample_out += filter[buffer_sample - filter_sample] * audioFile.samples[0][filter_sample];
        }
        buffer[0][buffer_sample] = sample_out;
    }

    return 1;   
}