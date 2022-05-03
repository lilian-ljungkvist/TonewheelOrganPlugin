/*
  ==============================================================================

    TonewheelWavetableOscillator.h
    Created: 25 Apr 2022 9:01:16pm
    Author:  Lilian Ljungkvist

  ==============================================================================
*/

#pragma once
#include <vector>
class TonewheelWavetableOscillator
{
public:
    TonewheelWavetableOscillator(std::vector<float> wavetable, double sampleRate);
    void setFrequency(float frequency);
    float getSample();
    float linearInterpolate();
    void stop();
    bool isPlaying();
private:
    std::vector<float> wavetable;
    double sampleRate;
    float index = 0.f;
    float indexIncrement = 0.f;
};
