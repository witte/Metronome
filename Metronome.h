#pragma once

#include <atomic>
#include <QObject>
#include "r8brain-free-src/CDSPResampler.h"
#include "JuceHeader.h"


class Metronome : public QObject, public AudioSource
{
    Q_OBJECT
    Q_PROPERTY(bool   isPlaying READ getIsPlaying WRITE setIsPLaying NOTIFY isPlayingChanged)
    Q_PROPERTY(double minBpm    READ getMinBpm                       NOTIFY minBpmChanged   )
    Q_PROPERTY(double maxBpm    READ getMaxBpm                       NOTIFY maxBpmChanged   )
    Q_PROPERTY(double bpm       READ getBpm       WRITE setBpm       NOTIFY bpmChanged      )


public:
    explicit Metronome (QObject* parent = nullptr);
    ~Metronome() override;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) noexcept override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) noexcept override;
    void releaseResources() override;

    bool   getIsPlaying() const { return m_isPlaying; }
    double getMinBpm()    const { return m_minBpm; }
    double getMaxBpm()    const { return m_maxBpm; }
    double getBpm()       const { return m_bpm; }


signals:
    void isPlayingChanged (bool isPlaying);
    void minBpmChanged (double bpm);
    void maxBpmChanged (double bpm);
    void bpmChanged (double bpm);
    void click();


public slots:
    void setIsPLaying (bool isPlaying);
    void setBpm (double bpm);


private:
    AudioDeviceManager m_deviceManager;
    AudioSourcePlayer m_audioSourcePlayer;

    std::unique_ptr<r8b::CDSPResampler24> m_resampler {nullptr};
    std::vector<float> m_click {0.0};
    int m_clickLength {0};

    double m_minBpm {40};
    double m_maxBpm {280};

    double m_sampleRate {48000};
    std::atomic<int> m_samplesPerClick {24000};
    std::atomic<int> m_currentSample {0};

    std::atomic_bool m_isPlaying {false};
    std::atomic<double> m_bpm {120.0};

    std::atomic_bool m_signalClick {false};

    void calcCurrentSampleWithinPulse();

    int m_timerId {0};
    int m_interval {16};
    void timerEvent (QTimerEvent* event) override;

    void addClickSamplesToBuffer(const AudioSourceChannelInfo& bufferToFill,
                                 int sourceStartSample, int destStartSample, int numSamples) noexcept;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Metronome)
};
