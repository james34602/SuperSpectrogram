#include "palette.h"
#include <QColor>

Palette::Palette()
{
}

void Palette::setVectorAt(double pos, QVector3D color)
{
    m_table.insert(pos, color);
}

void Palette::setColorAt(double pos, QColor color)
{
    m_table.insert(pos, QVector3D(color.redF(), color.greenF(), color.blueF()));
}

QVector3D Palette::getVectorAt(double pos) const
{
    QMap<double, QVector3D>::const_iterator i = m_table.constBegin();
    double lastKey = i.key();
    QVector3D lastValue = i.value();
    if (pos < lastKey)
        return lastValue;
    while (i != m_table.constEnd()) {
        if (pos <= i.key()) {
            double coeff = (pos - lastKey) / (i.key() - lastKey);
            return coeff * i.value() + (1.0 - coeff) * lastValue;
        }
        lastKey = i.key();
        lastValue = i.value();
        ++i;
    }
    return lastValue;
}

QRgb Palette::getColorAt(double pos) const
{
    QVector3D vec = getVectorAt(pos);
    QColor col;
    col.setRedF(vec.x());
    col.setGreenF(vec.y());
    col.setBlueF(vec.z());
    return col.rgb();
}
