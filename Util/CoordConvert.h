/*****************************************************************/ /**
 * \file   CoordConvert.h
 * \brief  ����ת�����ߡ�
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
        // ��Ļ����ת��������
        static osg::Vec3d ScreenToWorld(osgViewer::Viewer* view, osg::Vec3d screen);

        // ��������ת��Ļ����
        static osg::Vec3d WorldToScreen(osgViewer::Viewer* view, osg::Vec3d world);

        // ��������ת��γ��
        static osg::Vec3d WorldToLonLatAlt(osg::Vec3d world);

        // ��γ��ת��������
        static osg::Vec3d LLHToWorld(osg::Vec3d lon_lat_alt);

        // ��Ļ����ת��γ��
        static osg::Vec3d ScreenToLLH(osgViewer::Viewer* view, osg::Vec3d screen);

        // ��γ��ת��Ļ����
        static osg::Vec3d LLHToScreen(osgViewer::Viewer* view, osg::Vec3d lon_lat_alt);
    };
} // namespace xStudio
