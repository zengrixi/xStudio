/*****************************************************************/ /**
 * \file   TypeConvert.h
 * \brief  类型转换工具
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <QVector3D>

#include <osg/Vec3d>

namespace xStudio
{
    class TypeConvert
    {
    public:
        static osg::Vec3d QVector3DToVec3d(const QVector3D& v) { return osg::Vec3d(v.x(), v.y(), v.z()); }
        static QVector3D  Vec3dToQVector3D(const osg::Vec3d& v) { return QVector3D(v.x(), v.y(), v.z()); }
    };
} // namespace xStudio
