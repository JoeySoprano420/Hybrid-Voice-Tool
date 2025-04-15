juce::Synthesiser synth;
CarrierMode carrierMode = LiveInput;

void VocoderUnit::prepare(double sr, int blockSize) {
    sampleRate = sr;

    synth.clearVoices();
    for (int i = 0; i < 8; ++i)
        synth.addVoice(new juce::SamplerVoice());

    synth.clearSounds();
    // Example: add a sine wave synth tone (can be replaced with real sample)
    synth.addSound(new juce::SynthesiserSound());
    synth.setCurrentPlaybackSampleRate(sr);
}

void VocoderUnit::generateCarrier(juce::AudioBuffer<float>& buffer) {
    if (carrierMode == InternalSynth) {
        juce::MidiBuffer midi;
        midi.addEvent(juce::MidiMessage::noteOn(1, 60, (juce::uint8)100), 0);
        synth.renderNextBlock(buffer, midi, 0, buffer.getNumSamples());
    }
}

if (carrierMode == InternalSynth)
    generateCarrier(carrierBuffer);

juce::ToggleButton synthCarrierToggle { "Use Synth Carrier" };
synthCarrierToggle.onClick = [this] {
    processor.getVocoderUnit()->setCarrierMode(
        synthCarrierToggle.getToggleState() ? VocoderUnit::InternalSynth : VocoderUnit::LiveInput
    );
};
