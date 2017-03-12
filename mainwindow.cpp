#include "mainwindow.h"
#include <QDebug>
#include <QObject>
extern int SamplingRate;
extern int OverlapSample;
extern int SamplLength;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QAudioDeviceInfo audioDevice = QAudioDeviceInfo::defaultInputDevice();
    m_format = audioDevice.preferredFormat();
    m_format.setByteOrder((QAudioFormat::Endian)QSysInfo::ByteOrder);
    m_format.setSampleType(QAudioFormat::SignedInt);
    m_format.setSampleSize(16);
    m_format.setChannelCount(1);
    m_format.setSampleRate(SamplingRate);
    qDebug() << m_format;
    if (!audioDevice.isFormatSupported(m_format)) {
        qDebug("Format not supported");
    }
    m_audioinput = new QAudioInput(audioDevice, m_format, this);
    m_spectrumanalyser = new SpectrumAnalyser(this);
    m_spectrumanalyser->setAudioFormat(m_format);
//    m_spectrumanalyser->setParameters(SamplLength, m_format.sampleRate() / 40);
    m_spectrumanalyser->setParameters(SamplLength, OverlapSample);
    m_spectrumanalyser->open(QIODevice::WriteOnly);
    m_audioinput->start(m_spectrumanalyser);
    m_spectrogram = new Spectrogram(m_spectrumanalyser, this);
    setCentralWidget(m_spectrogram);
#ifdef TITLEBAR
    QObject::connect(m_spectrumanalyser, SIGNAL(titleBarUpdate(QString)), this, SLOT(titleBarUpdate(QString)));
#endif
}

MainWindow::~MainWindow()
{
}
#ifdef TITLEBAR
void MainWindow::titleBarUpdate(QString text)
{
     this->setWindowTitle(text);
}
#endif
