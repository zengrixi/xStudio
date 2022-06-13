#include "Main3DWidget.h"

#include <osgDB/ReadFile>
#include <osgEarth/MapNode>
#include <osgEarth/EarthManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgEarth/AutoClipPlaneHandler>
#include <osgUtil/Optimizer>
#include <osgEarth/Sky>

Main3DWidget::Main3DWidget(QWidget* parent)
    : Base3DViewerWidget(parent)
{
}

Main3DWidget::~Main3DWidget()
{
}

osg::Group* Main3DWidget::GetRootNode() const
{
    return _root;
}

void Main3DWidget::AddNodeToRoot(const osg::ref_ptr<osg::Node>& node)
{
    _root->addChild(node);
}

bool Main3DWidget::OpenEarthFile(const QString& file)
{
    auto node = osgDB::readNodeFile(file.toStdString());
    if (node)
    {
        auto _mapNode = osgEarth::MapNode::findMapNode(node);
        _mapNode->setName("MapNode");
        auto _mapSrs = _mapNode->getMapSRS();

        _root->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

        addEventHandler(new osgViewer::StatsHandler);
        addEventHandler(new osgGA::StateSetManipulator(getCamera()->getOrCreateStateSet()));
        getCamera()->addCullCallback(new osgEarth::Util::AutoClipPlaneCullCallback(_mapNode));
        getCamera()->setNearFarRatio(0.0000002);
        setUpViewerAsEmbeddedInWindow(0, 0, width(), height());

        _gw = static_cast<osgViewer::GraphicsWindow*>(getCamera()->getGraphicsContext());

        auto _manipulator = new osgEarth::Util::EarthManipulator();
        setCameraManipulator(_manipulator);
        _manipulator->setViewpoint(osgEarth::Util::Viewpoint("", 105, 33, 0, 0, -90, 9000000));

        auto _skyNode = osgEarth::SkyNode::create();
        _skyNode->setName("SkyNode");
        // 设置时间;
        auto ephemeris = new osgEarth::Util::Ephemeris;
        _skyNode->setEphemeris(ephemeris);
        _skyNode->setDateTime(osgEarth::DateTime());
        _skyNode->attach(this, 0);
        // 关闭光照
        _skyNode->setLighting(false);
        _skyNode->addChild(_mapNode);

        _root->addChild(_skyNode);

        osgUtil::Optimizer optimizer;
        optimizer.optimize(_root);

        return true;
    }

    return false;
}
