#include "LVec3.h"
#include <QVector3D>

namespace Lumin::Math
{
    LVec3::LVec3() : x(0), y(0), z(0) {}
    LVec3::LVec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    LVec3 LVec3::operator+(const LVec3& rhs) const
    {
        QVector3D a(x, y, z);
        QVector3D b(rhs.x, rhs.y, rhs.z);
        QVector3D r = a + b;
        return { r.x(), r.y(), r.z() };
    }

    LVec3 LVec3::operator-(const LVec3& rhs) const
    {
        QVector3D a(x, y, z);
        QVector3D b(rhs.x, rhs.y, rhs.z);
        QVector3D r = a - b;
        return { r.x(), r.y(), r.z() };
    }

    LVec3 LVec3::operator*(float s) const
    {
        QVector3D r = QVector3D(x, y, z) * s;
        return { r.x(), r.y(), r.z() };
    }

    float LVec3::Length() const
    {
        return QVector3D(x, y, z).length();
    }

    LVec3 LVec3::Normalized() const
    {
        QVector3D r = QVector3D(x, y, z).normalized();
        return { r.x(), r.y(), r.z() };
    }

    float LVec3::Dot(const LVec3& a, const LVec3& b)
    {
        return QVector3D::dotProduct(
            QVector3D(a.x, a.y, a.z),
            QVector3D(b.x, b.y, b.z)
        );
    }

    LVec3 LVec3::Cross(const LVec3& a, const LVec3& b)
    {
        QVector3D r = QVector3D::crossProduct(
            QVector3D(a.x, a.y, a.z),
            QVector3D(b.x, b.y, b.z)
        );
        return { r.x(), r.y(), r.z() };
    }
}
