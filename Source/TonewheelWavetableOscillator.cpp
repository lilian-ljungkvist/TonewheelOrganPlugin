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
    indexIncrement = frequency * static_cast<float>(wavetable.size()) / static_cast<double>(sampleRate); // frequency value * numsamples/samplerate
}

float TonewheelWavetableOscillator::getSample()
{
    const auto sample = linearInterpolate(); //lerp samples
    index += indexIncrement; //go through indices and add the frequency increment
    index = std::fmod(index, static_cast<float>(wavetable.size()));//Computes the floating-point remainder of the division operation index/wavetable.size
    return sample; //get the sample within the wavetable
}

float TonewheelWavetableOscillator::linearInterpolate()
{
    const auto truncIndex = static_cast<int>(index); //index cast to integer
    const auto nextIndex = (truncIndex + 1) % static_cast<int>(wavetable.size());
    
    const auto nextIndexWeight = index - static_cast<float>(truncIndex); // index minus float weight
    const auto truncIndexWeight = 1.f - nextIndexWeight;
    
    return truncIndexWeight * wavetable[truncIndex] + nextIndexWeight * wavetable[nextIndex]; //gets the interpolated value
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
