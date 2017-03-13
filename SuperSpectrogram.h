#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <QWidget>
#include <QImage>
#include "palette.h"
#include "spectrumanalyser.h"

class Spectrogram : public QWidget
{
    Q_OBJECT
public:
    explicit Spectrogram(SpectrumAnalyser* analyser, QWidget *parent = 0);
    
private slots:
    void moreSpectrumLinear();
    void moreSpectrumLog();

private:
    bool isLog;
    void paintEvent(QPaintEvent *);
    QRgb gradiantAt(float amp);
    void mouseReleaseEvent (QMouseEvent *event);
    void mouseDoubleClickEvent (QMouseEvent *event);
    int paletteCount;
    void ColormapChange(int count);
    SpectrumAnalyser* m_analyser;
    Palette m_palette;
    float amp;
    QImage m_image;

    float m_min, m_max;
};

#endif // SPECTROGRAM_H
