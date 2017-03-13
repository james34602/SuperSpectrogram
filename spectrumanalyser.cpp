#include "spectrumanalyser.h"
SpectrumAnalyser::SpectrumAnalyser(QObject *parent) :
    QIODevice(parent)
{
    m_plan = NULL;
}

SpectrumAnalyser::~SpectrumAnalyser()
{
    fftwf_destroy_plan(m_plan);
}

qint64 SpectrumAnalyser::readData(char *data, qint64 maxlen)
{
    return 0;
}

qint64 SpectrumAnalyser::writeData(const char *data, qint64 len)
{
    int samplesReady = len >> 1; // 16bit = 2bytes (len / 2)
    const qint16* ptr = reinterpret_cast<const qint16*>(data);
    while (samplesReady > 0) {
              m_fftin[m_nFFT - m_needed] = *ptr * 0.0001;
              --m_needed;
              --samplesReady;
              ++ptr;
        if (m_needed == 0) {
            runFFT();
            m_needed = m_overlap;
            std::copy(m_fftin.begin() + m_overlap, m_fftin.end(), m_fftin.begin());
        }
    }
    return len - samplesReady;
}
void SpectrumAnalyser::runFFT()
{
    fftwf_execute(m_plan);
#ifdef TITLEBAR
    float peakFrec = 0.0;
    float peakAmplitude = 0.0;
    for (int i = 0; i < m_fftout.size(); ++i) {
        m_spectrum[i] = std::norm(m_fftout[i] / float(m_nFFT)); // The norm value of a complex number is the squared magnitude
        if (m_spectrum[i] > peakAmplitude) {
            peakFrec = m_frequenceUnit * i;
            peakAmplitude = m_spectrum[i];
        }
    }
    QString str = QString("SuperSpectrogram::Peak:%1Hz dB:%3").arg(peakFrec).arg(log10(peakAmplitude)*20.0);
    changeTitle(str);
#else
    for (int i = 0; i < m_fftout.size(); ++i)
      m_spectrum[i] = std::norm(m_fftout[i] / float(m_nFFT)); // The norm value of a complex number is the squared magnitude
#endif
    emit spectrumReady();
}
#ifdef TITLEBAR
void SpectrumAnalyser::changeTitle(QString text)
{
      emit titleBarUpdate(text);
}
#endif
QAudioFormat SpectrumAnalyser::audioFormat() const
{
    return m_audioFormat;
}
void SpectrumAnalyser::setAudioFormat(const QAudioFormat &audioFormat)
{
    m_audioFormat = audioFormat;
}

void SpectrumAnalyser::setParameters(int nfft, int overlap)
{
    m_nFFT = nfft;
    m_overlap = overlap;
    m_fftin.fill(0.0, m_nFFT);
    m_needed = overlap;
    m_fftout.resize(m_nFFT / 2 + 1);
    m_spectrum.resize(m_fftout.size());
#ifdef __ANDROID__
    m_plan = fftwf_plan_dft_r2c_1d(m_nFFT, m_fftin.data(), reinterpret_cast<fftwf_complex*>(m_fftout.data()), FFTW_ESTIMATE);
#else
    m_plan = fftwf_plan_dft_r2c_1d(m_nFFT, m_fftin.data(), reinterpret_cast<fftwf_complex*>(m_fftout.data()), FFTW_PATIENT);
#endif
    m_frequenceUnit = m_audioFormat.sampleRate() / m_nFFT;
}
const QVector<float> &SpectrumAnalyser::spectrum() const
{
    return m_spectrum;
}
float SpectrumAnalyser::frequenceUnit() const
{
    return m_frequenceUnit;
}
