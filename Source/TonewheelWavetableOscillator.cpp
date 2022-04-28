/*
  ==============================================================================

    TonewheelWavetableOscillator.cpp
    Created: 25 Apr 2022 9:01:16pm
    Author:  Lilian Ljungkvist

  ==============================================================================
*/

#include "TonewheelWavetableOscillator.h"
#include <cmath>
TonewheelWavetableOscillator::TonewheelWavetableOscillator(std::vector<float> wavetable, double sampleRate) : wavetable{std::move (wavetable)}, sampleRate {sampleRate}
{
    
};

void TonewheelWavetableOscillator::setFrequency(float frequency)
{
    indexIncrement = frequency * static_cast<float>(wavetable.size()) / static_cast<double>(sampleRate);
}

float TonewheelWavetableOscillator::getSample()
{
    const auto sample = interpolateLinearly();
    index += indexIncrement;
    index = std::fmod(index, static_cast<float>(wavetable.size()));
    return sample;
}

float TonewheelWavetableOscillator::interpolateLinearly()
{
    const auto truncatedIndex = static_cast<int>(index);
    const auto nextIndex = (truncatedIndex + 1) % static_cast<int>(wavetable.size());
    
    const auto nextIndexWeight = index - static_cast<float>(truncatedIndex);
    const auto truncatedIndexWeight = 1.f - nextIndexWeight;
    
    return truncatedIndexWeight * wavetable[truncatedIndex] + nextIndexWeight * wavetable[nextIndex];
}
void TonewheelWavetableOscillator::stop()
{
    index = 0.f;
    indexIncrement = 0.f;
}
bool TonewheelWavetableOscillator::isPlaying()
{
    return indexIncrement != 0.f;
}
