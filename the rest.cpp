class CustomOscillator {
public:
    enum Waveform { Sine, Saw, Noise };
    void setWaveform(Waveform wf) { waveform = wf; }
    void prepare(double sampleRate);
    float getNextSample();

private:
    Waveform waveform = Sine;
    double phase = 0.0;
    double phaseIncrement = 0.0;
    double sampleRate = 44100.0;
    juce::Random random;
};

float CustomOscillator::getNextSample() {
    float sample = 0.0f;
    switch (waveform) {
        case Sine:
            sample = std::sin(phase);
            break;
        case Saw:
            sample = 2.0f * (phase / (2.0 * juce::MathConstants<double>::pi)) - 1.0f;
            break;
        case Noise:
            sample = random.nextFloat() * 2.0f - 1.0f;
            break;
    }
    phase += phaseIncrement;
    if (phase >= 2.0 * juce::MathConstants<double>::pi)
        phase -= 2.0 * juce::MathConstants<double>::pi;
    return sample;
}

juce::ComboBox waveformSelector;
waveformSelector.addItem("Sine", 1);
waveformSelector.addItem("Saw", 2);
waveformSelector.addItem("Noise", 3);
waveformSelector.onChange = [this]() {
    auto selected = waveformSelector.getSelectedId();
    vocoderUnit.setWaveform(static_cast<CustomOscillator::Waveform>(selected - 1));
};

bool acceptsMidi() const override { return true; }
bool producesMidi() const override { return false; }

void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override {
    for (const auto metadata : midiMessages) {
        const auto msg = metadata.getMessage();
        if (msg.isNoteOn()) {
            // Trigger carrier oscillator or synth
        } else if (msg.isNoteOff()) {
            // Handle note off
        }
    }
}

class FormantMatrixEditor : public juce::Component {
public:
    void paint(juce::Graphics& g) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;

private:
    std::vector<float> bandGains;
    int selectedBand = -1;
};

void FormantMatrixEditor::paint(juce::Graphics& g) {
    auto area = getLocalBounds();
    int bandWidth = area.getWidth() / bandGains.size();
    for (size_t i = 0; i < bandGains.size(); ++i) {
        int x = i * bandWidth;
        int height = static_cast<int>(bandGains[i] * area.getHeight());
        g.setColour(juce::Colours::blue);
        g.fillRect(x, area.getHeight() - height, bandWidth, height);
    }
}

void FormantMatrixEditor::mouseDown(const juce::MouseEvent& event) {
    int bandWidth = getWidth() / bandGains.size();
    selectedBand = event.x / bandWidth;
}

void FormantMatrixEditor::mouseDrag(const juce::MouseEvent& event) {
    if (selectedBand >= 0 && selectedBand < bandGains.size()) {
        float gain = 1.0f - static_cast<float>(event.y) / getHeight();
        bandGains[selectedBand] = juce::jlimit(0.0f, 1.0f, gain);
        repaint();
        // Update vocoder band gain accordingly
    }
}

// VoiceModulator.h
class VoiceModulator {
public:
    void prepare(double sampleRate);
    void process(juce::AudioBuffer<float>& buffer);
    // Additional methods...
};

// PitchCorrectionEngine.h
class PitchCorrectionEngine {
public:
    void prepare(double sampleRate);
    void process(juce::AudioBuffer<float>& buffer);
    // Additional methods...
};

// VocoderUnit.h
class VocoderUnit {
public:
    enum CarrierMode { LiveInput, InternalSynth };
    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& inputBuffer, juce::AudioBuffer<float>& outputBuffer, juce::MidiBuffer& midiMessages);
    void setCarrierMode(CarrierMode mode);
    void setWaveform(CustomOscillator::Waveform waveform);
    float getEnvelopeForBand(int band) const;
    // Additional methods...
};

// CustomOscillator.h
class CustomOscillator {
public:
    enum Waveform { Sine, Saw, Noise };
    void setWaveform(Waveform wf);
    void prepare(double sampleRate);
    float getNextSample();
    // Additional methods...
};

// FormantMatrixEditor.h
class FormantMatrixEditor : public juce::Component {
public:
    FormantMatrixEditor();
    void paint(juce::Graphics& g) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    // Additional methods...
};

