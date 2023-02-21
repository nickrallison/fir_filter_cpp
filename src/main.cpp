#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#include "../libs/AudioFile/AudioFile.h"
#include "../include/filter.h"

int main(int argc, char *argv[]) {
    AudioFile<double> audioFile;
    audioFile.load("assets/downloads/OSR_us_000_0010_8k.wav");
    audioFile.printSummary();



    int numChannels = audioFile.getNumChannels();
    static const int numSamplesPerChannel = audioFile.getNumSamplesPerChannel();
    float sampleRate = audioFile.getSampleRate();
    int bitDepth = audioFile.getBitDepth();
    double lengthInSeconds = audioFile.getLengthInSeconds();
    float newSampleRate = sampleRate / SAMPLE_RATE_DIVIDER;
    
    bool isMono = audioFile.isMono();
    bool isStereo = audioFile.isStereo();

    std::vector<double> savedIn, savedOut;

    savedIn = audioFile.samples[0];

    AudioFile<double>::AudioBuffer buffer;
    buffer.resize(1);
    buffer[0].resize(numSamplesPerChannel / SAMPLE_RATE_DIVIDER);
    
    double* filter = filter_taps;//new double(FILTER_TAP_NUM);
    filter[0] = 1.;

    static const int max_buffer_samples = numSamplesPerChannel / SAMPLE_RATE_DIVIDER;

    for (int buffer_sample = 0; buffer_sample < FILTER_TAP_NUM; buffer_sample++) {
        int audio_sample = buffer_sample * SAMPLE_RATE_DIVIDER;
        double sample_out = 0;
        for (int filter_sample = buffer_sample; filter_sample >= 0; filter_sample -= 1) {
            sample_out += filter[buffer_sample - filter_sample] * savedIn[audio_sample];
        }
        buffer[0][buffer_sample] = sample_out;
    }

    for (int buffer_sample = FILTER_TAP_NUM; buffer_sample < max_buffer_samples; buffer_sample++) {
        int audio_sample = buffer_sample * SAMPLE_RATE_DIVIDER;
        double sample_out = 0;
        for (int filter_sample = buffer_sample; filter_sample >= buffer_sample - FILTER_TAP_NUM + 1; filter_sample--) {
            sample_out += filter[buffer_sample - filter_sample] * savedIn[audio_sample];
        }
        buffer[0][buffer_sample] = sample_out;
    }

    bool ok = audioFile.setAudioBuffer (buffer);
    audioFile.setSampleRate(newSampleRate);
    audioFile.setNumSamplesPerChannel(numSamplesPerChannel / SAMPLE_RATE_DIVIDER);
    audioFile.printSummary();
    audioFile.save ("assets/clean/OSR_us_000_0010_8k_clean.wav", AudioFileFormat::Wave);
    savedOut = audioFile.samples[0];
    

    for (int i = 0; i < 256; i++) {
        // std::cout << "In: " << savedIn[i] << ", Out: " << savedOut[i] << std::endl;
        //printf("In: %f, Out: %f\n", savedIn[i], savedOut[i]);
    }
    return 1;   
}