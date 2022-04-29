/*
  ==============================================================================

    Drawbar.h
    Created: 29 Apr 2022 3:20:54pm
    Author:  Lilian Ljungkvist

  ==============================================================================
*/

#pragma once
class Drawbar {
    Drawbar(float harmonic) {
        
    }
    ~ Drawbar(){}
public:
    void setVolumeLevel(int volumeNumber);
private:
    int volumeLevel;
    float harmonic;

};
