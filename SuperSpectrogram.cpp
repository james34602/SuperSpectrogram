#include "SuperSpectrogram.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <limits>
#include "colormap.h"
Spectrogram::Spectrogram(SpectrumAnalyser *analyser, QWidget *parent) :
    paletteCount(0), QWidget(parent), m_analyser(analyser)
{
  connect(m_analyser, SIGNAL(spectrumReady()), SLOT(moreSpectrumLog()));
  isLog = true;
  m_min = std::numeric_limits<float>::max();
  m_max = std::numeric_limits<float>::min();
  ColormapChange(paletteCount);
}
void Spectrogram::moreSpectrumLinear()
{
    int w = width();
    int h = m_analyser->spectrum().size();
    QSize size(h, w); // rotate 90 degrees
    if (size == m_image.size()) {
        std::copy(m_image.bits() + m_image.bytesPerLine(), m_image.bits() + m_image.byteCount(), m_image.bits());
/*        void* dest = m_image.bits();
        for (int x = 1; x < w; ++x) {
            void* source = m_image.bits() + x * m_image.bytesPerLine();
            memcpy(dest, source, m_image.bytesPerLine());
            dest = source;
        }*/
    } else {
        m_image = QImage(size, QImage::Format_RGB32);
    }
    for (int y = 0; y < h; ++y) {
        m_image.setPixel(h-y-1, w-1, gradiantAt(m_analyser->spectrum()[y]));
    }
    update();
}

void Spectrogram::moreSpectrumLog()
{
    int w = width();
    int h = m_analyser->spectrum().size();
    float yscale = log(h) / h;
    QSize size(h, w); // rotate 90 degrees
    if (size == m_image.size()) {
        std::copy(m_image.bits() + m_image.bytesPerLine(), m_image.bits() + m_image.byteCount(), m_image.bits());
/*        void* dest = m_image.bits();
        for (int x = 1; x < w; ++x) {
            void* source = m_image.bits() + x * m_image.bytesPerLine();
            memcpy(dest, source, m_image.bytesPerLine());
            dest = source;
        }*/
    } else {
        m_image = QImage(size, QImage::Format_RGB32);
    }
    for (int y = 0; y < h; ++y) {
        float amp;
        int index = pow(2.7182818284590452354, y*yscale);
        amp = m_analyser->spectrum()[index];
        m_image.setPixel(h-y-1, w-1, gradiantAt(amp));
    }
    update();
}
void Spectrogram::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.rotate(90.0);
    painter.scale(1, -1);
    painter.drawImage(QRect(0, 0, height(), width()), m_image);
}
void Spectrogram::mouseReleaseEvent (QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
      isLog = !isLog;
      ColormapChange(paletteCount);
      if(isLog == false) {
      QObject::disconnect(m_analyser, SIGNAL(spectrumReady()), 0,0);
      connect(m_analyser, SIGNAL(spectrumReady()), SLOT(moreSpectrumLinear()));
        } else if (isLog == true) {
          QObject::disconnect(m_analyser, SIGNAL(spectrumReady()), 0,0);
          connect(m_analyser, SIGNAL(spectrumReady()), SLOT(moreSpectrumLog()));
        }
  }
}
void Spectrogram::mouseDoubleClickEvent (QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
  {
      paletteCount++;
      if(paletteCount > 8)
        paletteCount = 0;
      ColormapChange(paletteCount);
  }
}
void Spectrogram::ColormapChange(int count)
{
  m_palette.deleteMap();
  if (count == 0) {
      for(int i = 0; i < 32; i++)
        m_palette.setColorAt(scalar32[i], qRgb(redDawn32[i],greenDawn32[i],blueDawn32[i]));
    }
  else if(count == 1) {
      for(int i = 0; i < 32; i++)
        m_palette.setColorAt(scalar32[i], qRgb(redKindlmann32[i],greenKindlmann32[i],blueKindlmann32[i]));
    }
  else if (count == 2) {
        for(int i = 0; i < 32; i++)
          m_palette.setColorAt(scalar32[i], qRgb(redExtendedKindlmann32[i],greenExtendedKindlmann32[i],blueExtendedKindlmann32[i]));
    }
  else if (count == 3) {
          for(int i = 0; i < 32; i++)
            m_palette.setColorAt(scalar32[i], qRgb(redBlackBody32[i],greenBlackBody32[i],blueBlackBody32[i]));
    }
  else if (count == 4) {
      for(int i = 0; i < 32; i++)
        m_palette.setColorAt(scalar32[i], qRgb(redExtendedBlackBody32[i],greenExtendedBlackBody32[i],blueExtendedBlackBody32[i]));
    }
  else if (count == 5) {
      for(int i = 0; i < 32; i++)
        m_palette.setColorAt(scalar32[i], qRgb(redSmoothCoolWarm32[i],greenSmoothCoolWarm32[i],blueSmoothCoolWarm32[i]));
    }
  else if (count == 6) {
      for(int i = 0; i < 32; i++)
        m_palette.setColorAt(scalar32[i], qRgb(redBentCoolWarm32[i],greenBentCoolWarm32[i],blueBentCoolWarm32[i]));
    }
  else if (count == 7) {
      for(int i = 0; i < 32; i++)
        m_palette.setColorAt(scalar32[i], qRgb(redParula32[i],greenParula32[i],blueParula32[i]));
    }
  else if (count == 8) {
      for(int i = 0; i < 32; i++)
        m_palette.setColorAt(scalar32[i], qRgb(redJet32[i],greenJet32[i],blueJet32[i]));
    }
  else {
      for(int i = 0; i < 32; i++)
        m_palette.setColorAt(scalar32[i], qRgb(redKindlmann32[i],greenKindlmann32[i],blueKindlmann32[i]));
    }
}
QRgb Spectrogram::gradiantAt(float amp) //! a optimiser
{
    if (amp <= 0.0)
        amp = m_min;
    else
        amp = std::log10(amp);
    if (amp < m_min) {
        m_min = amp;
    }
    if (amp > m_max) {
        m_max = amp;
    }
    amp = (amp - m_min) / (m_max - m_min);
    return m_palette.getColorAt(amp);
}
