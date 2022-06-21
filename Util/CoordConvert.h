/*****************************************************************/ /**
 * \file   CoordConvert.h
 * \brief  坐标转换工具。
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <osg/Matrix>
#include <osg/Vec3d>
#include <osgViewer/Viewer>

namespace xStudio
{
    class CoordConverter
    {
    public:
        // 屏幕坐标转世界坐标
        static osg::Vec3d ScreenToWorld(osgViewer::Viewer* view, osg::Vec3d screen);

        // 世界坐标转屏幕坐标
        static osg::Vec3d WorldToScreen(osgViewer::Viewer* view, osg::Vec3d world);

        // 世界坐标转经纬度
        static osg::Vec3d WorldToLonLatAlt(osg::Vec3d world);

        // 经纬度转世界坐标
        static osg::Vec3d LLHToWorld(osg::Vec3d lon_lat_alt);

        // 屏幕坐标转经纬度
        static osg::Vec3d ScreenToLLH(osgViewer::Viewer* view, osg::Vec3d screen);

        // 经纬度转屏幕坐标
        static osg::Vec3d LLHToScreen(osgViewer::Viewer* view, osg::Vec3d lon_lat_alt);
    };
} // namespace xStudio
