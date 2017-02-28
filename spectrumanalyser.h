#ifndef SPECTROGRAMANALYSER_H
#define SPECTROGRAMANALYSER_H

#include <QIODevice>
#include <QAudioFormat>
#include <QVector>
#include "fftw3.h"
#include <complex>

class SpectrumAnalyser : public QIODevice
{
    Q_OBJECT
public:
    explicit SpectrumAnalyser(QObject *parent = 0);
    ~SpectrumAnalyser();
    
    QAudioFormat audioFormat() const;
    void setAudioFormat(const QAudioFormat &audioFormat);

    void setParameters(int nfft, int overlap);

    const QVector<double>& spectrum() const;

    double frequenceUnit() const;

signals:
    void spectrumReady();
#ifdef TITLEBAR
    void titleBarUpdate(QString text);
#endif
private:
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
#ifdef TITLEBAR
    void changeTitle(QString text);
#endif
    void runFFT();

    int m_nFFT;
    int m_overlap;
    int m_needed;

    QAudioFormat m_audioFormat;
    QVector<double> m_fftin;

    fftw_plan m_plan;
    QVector<std::complex<double> > m_fftout;

    QVector<double> m_spectrum;
    double m_frequenceUnit;
};

#endif // SPECTROGRAMANALYSER_H
