addAndMakeVisible(saveButton);
addAndMakeVisible(loadButton);

saveButton.onClick = [this] {
    juce::FileChooser chooser("Save Preset", {}, "*.vox");
    if (chooser.browseForFileToSave(true)) {
        juce::File file = chooser.getResult();
        juce::MemoryBlock data;
        processor.getStateInformation(data);
        file.replaceWithData(data.getData(), data.getSize());
    }
};

loadButton.onClick = [this] {
    juce::FileChooser chooser("Load Preset", {}, "*.vox");
    if (chooser.browseForFileToOpen()) {
        juce::File file = chooser.getResult();
        juce::MemoryBlock data;
        file.loadFileAsData(data);
        processor.setStateInformation(data.getData(), (int)data.getSize());
    }
};

envelopeValues.resize(processor.getVocoderUnit()->getNumBands());
startTimerHz(30); // update 30 FPS

void VoxMystEditor::timerCallback() {
    auto* unit = processor.getVocoderUnit();
    for (int i = 0; i < envelopeValues.size(); ++i)
        envelopeValues.set(i, unit->getEnvelopeForBand(i));

    repaint(); // trigger paint() to draw visuals
}

void VoxMystEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    
    int width = getWidth() / envelopeValues.size();
    for (int i = 0; i < envelopeValues.size(); ++i) {
        float env = envelopeValues[i];
        int barHeight = (int)(env * getHeight());
        g.setColour(juce::Colours::cyan);
        g.fillRect(i * width, getHeight() - barHeight, width - 2, barHeight);
    }
}

float getEnvelopeForBand(int band) const {
    if (band >= 0 && band < envelopes.size())
        return envelopes[band];
    return 0.0f;
}

