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
