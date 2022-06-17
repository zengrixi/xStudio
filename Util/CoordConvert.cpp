#include "CoordConvert.h"

namespace xStudio
{
    // 屏幕坐标转世界坐标
    osg::Vec3d CoordConverter::ScreenToWorld(osgViewer::Viewer* view, osg::Vec3d screen)
    {
        osg::Camera* camera = view->getCamera();
        osg::Matrix  VPW    = camera->getViewMatrix() * camera->getProjectionMatrix() *
                          camera->getViewport()->computeWindowMatrix();
        osg::Matrix inverseVPW = osg::Matrix::inverse(VPW);
        osg::Vec3d  world      = screen * inverseVPW;
        return world;
    }

    // 世界坐标转屏幕坐标
    osg::Vec3d CoordConverter::WorldToScreen(osgViewer::Viewer* view, osg::Vec3d world)
    {
        osg::Camera* camera = view->getCamera();
        osg::Matrix  VPW    = camera->getViewMatrix() * camera->getProjectionMatrix() *
                          camera->getViewport()->computeWindowMatrix();
        osg::Vec3d screen = world * VPW;
        return screen;
    }

    // 世界坐标转经纬度
    osg::Vec3d CoordConverter::WorldToLonLatAlt(osg::Vec3d world)
    {
        osg::EllipsoidModel* em = new osg::EllipsoidModel();
        osg::Vec3d           llh;
        em->convertXYZToLatLongHeight(world.x(), world.y(), world.z(), llh.y(), llh.x(), llh.z());
        llh.x() = osg::RadiansToDegrees(llh.x());
        llh.y() = osg::RadiansToDegrees(llh.y());
        return llh;
    }

    // 经纬度转世界坐标
    osg::Vec3d CoordConverter::LLHToWorld(osg::Vec3d llh)
    {
        osg::Vec3d           world;
        osg::EllipsoidModel* em = new osg::EllipsoidModel();
        em->convertLatLongHeightToXYZ(osg::DegreesToRadians(llh.y()),
                                      osg::DegreesToRadians(llh.x()),
                                      llh.z(),
                                      world.x(),
                                      world.y(),
                                      world.z());
        return world;
    }

    // 屏幕坐标转经纬度
    osg::Vec3d CoordConverter::ScreenToLLH(osgViewer::Viewer* view, osg::Vec3d screen)
    {
        return WorldToLonLatAlt(ScreenToWorld(view, screen));
    }

    // 经纬度转屏幕坐标
    osg::Vec3d CoordConverter::LLHToScreen(osgViewer::Viewer* view, osg::Vec3d llh)
    {
        return WorldToScreen(view, LLHToWorld(llh));
    }
} // namespace xStudio