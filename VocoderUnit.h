enum CarrierMode { LiveInput, InternalSynth };
void setCarrierMode(CarrierMode mode);

void generateCarrier(juce::AudioBuffer<float>& buffer);
