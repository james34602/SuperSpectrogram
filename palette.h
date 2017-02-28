#ifndef PALETTE_H
#define PALETTE_H

#include <QVector3D>
#include <QColor>
#include <QMap>

class Palette
{
public:
    Palette();
    void setVectorAt(double pos, QVector3D color);
    void setColorAt(double pos, QColor color);
    QVector3D getVectorAt(double pos) const;
    QRgb getColorAt(double pos) const;

private:
    QMap<double, QVector3D> m_table;
};

#endif // PALETTE_H
