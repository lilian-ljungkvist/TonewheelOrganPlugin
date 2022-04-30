/*
  ==============================================================================

    Drawbar.h
    Created: 29 Apr 2022 3:20:54pm
    Author:  Lilian Ljungkvist

  ==============================================================================
*/

#pragma once
#include "TonewheelWavetableOscillator.h"
class Drawbar
{
public:
    Drawbar(float harmonic);
    void setVolumeLevel(int volumeNumber);
    int volumeLevel;
    std::vector <TonewheelWavetableOscillator> oscillators ;
    float harmonic;
private:

};
