#include "Metronome.h"
#include "ClickSample.cpp"


Metronome::Metronome (QObject* parent) : QObject (parent)
{
    String audioError = m_deviceManager.initialise (0, 2, nullptr, true);
    jassert (audioError.isEmpty());

    m_deviceManager.addAudioCallback (&m_audioSourcePlayer);
    m_audioSourcePlayer.setSource (this);
}

Metronome::~Metronome()
{
    m_audioSourcePlayer.setSource (nullptr);
    m_deviceManager.removeAudioCallback (&m_audioSourcePlayer);

    m_deviceManager.closeAudioDevice();
}

void Metronome::prepareToPlay (int samplesPerBlockExpected, double sampleRate) noexcept
{
    // original click sound is in 48kHz, if the current sample rate
    // is different than this we need to convert it
    if (!qFuzzyCompare (m_sampleRate, sampleRate))
    {
        m_sampleRate = sampleRate;
        int originalClickLength = static_cast<int>(m_originalClick.size());

        m_resampler = std::make_unique<r8b::CDSPResampler24>(48000.0, m_sampleRate, originalClickLength);

        m_clickLength = static_cast<int>(originalClickLength * sampleRate / 48000.0);

        m_click.resize (static_cast<size_t>(m_clickLength));
        m_resampler->oneshot (originalClickLength, m_originalClick.data(), originalClickLength, m_click.data(), m_clickLength);
    }
    else
    {
        m_click = m_originalClick;
        m_clickLength = static_cast<int>(m_click.size());
    }

    calcCurrentSampleWithinPulse();

    String message;
    message << "sampleRate is: " << sampleRate << newLine;
    message << "Block size is: " << samplesPerBlockExpected << newLine;
    Logger::getCurrentLogger()->writeToLog (message);
}

void Metronome::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) noexcept
{
    if (!m_isPlaying) return;

    int currentSample = m_currentSample.load();
    int samplesPerClick = m_samplesPerClick.load();

    if ( (currentSample >= 1334) &&
         (currentSample + bufferToFill.numSamples < samplesPerClick) )
    {
        m_currentSample.store(currentSample + bufferToFill.numSamples);
        return;
    }

    float* ch1 = bufferToFill.buffer->getWritePointer(0);
    float* ch2 = bufferToFill.buffer->getWritePointer(1);

    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        float sampleValue = (currentSample < m_clickLength) ? m_click[ static_cast<unsigned int>(currentSample) ] : 0.0f;

        ch1[sample] = sampleValue;
        ch2[sample] = sampleValue;

        ++currentSample;

        if (currentSample > samplesPerClick)
        {
            currentSample = 0;
//            emit click(); // would it be ok to do this?
            m_signalClick.store(true);
        }
    }
    m_currentSample.store (currentSample);
}

void Metronome::releaseResources()
{
    Logger::getCurrentLogger()->writeToLog ("Releasing audio resources!");
}

void Metronome::setIsPLaying (bool isPlaying)
{
    if (m_isPlaying == isPlaying) return;

    m_isPlaying = isPlaying;
    if (m_isPlaying)
    {
        m_currentSample = m_samplesPerClick + 1;
        m_timerId = startTimer (m_interval, Qt::PreciseTimer);
    }
    else
    {
        killTimer (m_timerId);
    }

    emit isPlayingChanged (m_isPlaying);
}

void Metronome::setBpm (double bpm)
{
    if (qFuzzyCompare (m_bpm, bpm)) return;
    if (bpm < m_minBpm) bpm = m_minBpm;
    if (bpm > m_maxBpm) bpm = m_maxBpm;

    m_bpm = bpm;
    emit bpmChanged (m_bpm);

    calcCurrentSampleWithinPulse();
}

void Metronome::calcCurrentSampleWithinPulse()
{
    double currentSample   = m_currentSample.load();
    double samplesPerClick = m_samplesPerClick.load();

    double percentageWithinPulse = currentSample / samplesPerClick;

    m_samplesPerClick.store (static_cast<int>((60.0 / m_bpm) * m_sampleRate));
    m_currentSample.store   (static_cast<int>(m_samplesPerClick * percentageWithinPulse));
}

void Metronome::timerEvent (QTimerEvent* /*event*/)
{
    if (!m_signalClick) return;

    m_signalClick = false;
    emit click();
}
