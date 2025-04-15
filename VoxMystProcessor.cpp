void VoxMystProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = getStateInformationTree();
    juce::MemoryOutputStream stream(destData, true);
    state.writeToStream(stream);
}

void VoxMystProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    auto state = juce::ValueTree::readFromData(data, sizeInBytes);
    if (state.isValid())
        setStateInformationTree(state);
}
