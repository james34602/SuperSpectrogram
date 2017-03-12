#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
int SamplingRate, OverlapSample, SamplLength;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox msgBox;
    if(argc < 3 || argc > 3)
      {
        msgBox.setText("Argument less then 2 or more then 2\nUse default config!\nCommand line example:SuperSpectrum [44100/48000] [Overlap]");
        msgBox.exec();
        SamplingRate = 48000;
#ifdef __ANDROID__
        OverlapSample = 750;
#else
        OverlapSample = 1000;
        msgBox.setText("FFTW pre-optimization stage...");
        msgBox.exec();
#endif
        SamplLength = 4800;
      }
    else
      {
        SamplingRate = atoi(argv[1]);
        if(SamplingRate > 48000 || SamplingRate < 44100)
          SamplingRate = 48000;
        OverlapSample = atoi(argv[2]);
        SamplLength = SamplingRate/9;
      }
    MainWindow w;
    w.show();
    return a.exec();
}
