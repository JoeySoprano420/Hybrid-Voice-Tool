juce::TextButton saveButton { "Save Preset" };
juce::TextButton loadButton { "Load Preset" };

juce::Array<float> envelopeValues;
juce::Timer envelopeTimer;

void timerCallback() override;
