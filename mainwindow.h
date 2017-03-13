#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioInput>
#include "SuperSpectrogram.h"
#include "spectrumanalyser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
#ifdef TITLEBAR
    void titleBarUpdate(QString text);
#endif
private:
    QAudioFormat m_format;
    QAudioInput* m_audioinput;
    SpectrumAnalyser* m_spectrumanalyser;
    int desiredBuffer;
    Spectrogram* m_spectrogram;
};

#endif // MAINWINDOW_H
