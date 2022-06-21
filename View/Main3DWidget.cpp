#include "Main3DWidget.h"

#include <QMimeData>

#include <Util/CoordConvert.h>
#include <osgDB/ReadFile>
#include <osgEarth/AutoClipPlaneHandler>
#include <osgEarth/EarthManipulator>
#include <osgEarth/MapNode>
#include <osgEarth/Sky>
#include <osgGA/StateSetManipulator>
#include <osgUtil/Optimizer>
#include <osgViewer/ViewerEventHandlers>

namespace xStudio
{
    Main3DWidget::Main3DWidget(QWidget* parent)
        : Base3DViewerWidget(parent)
    {
        _scene = new MScene(nullptr);

        setAcceptDrops(true);
    }

    Main3DWidget::~Main3DWidget()
    {
        if (_scene)
            delete _scene;
    }

    osg::Group* Main3DWidget::GetRootNode() const { return _root; }

    void Main3DWidget::AddNodeToRoot(const osg::ref_ptr<osg::Node>& node) { _root->addChild(node); }

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

    void Main3DWidget::dragEnterEvent(QDragEnterEvent* evt)
    {
        if (evt->mimeData()->hasUrls())
        {
            evt->acceptProposedAction();
        }
        else
        {
            evt->ignore();
        }
    }

    void Main3DWidget::dragMoveEvent(QDragMoveEvent* evt) { Base3DViewerWidget::dragMoveEvent(evt); }

    void Main3DWidget::dropEvent(QDropEvent* evt)
    {
        const auto mimeData = evt->mimeData();
        if (mimeData->hasUrls())
        {
            auto urls = mimeData->urls();
            for (auto& url : urls)
            {
                auto fileName = url.toLocalFile();
                auto x        = evt->pos().x();
                auto y        = evt->pos().y();
                auto pos      = CoordConverter::ScreenToWorld(this, osg::Vec3d(x, y, 0));
                auto entity   = _scene->GenerateEntityFromFile(fileName, QVector3D(pos.x(), pos.y(), pos.z()));
                emit SelectEntity(entity);
            }
        }
    }

    void Main3DWidget::showEvent(QShowEvent* evt)
    {
        Base3DViewerWidget::showEvent(evt);

        if (_firstShowed)
        {
            _OnFirstShowed();
            _firstShowed = false;
        }
    }

    void Main3DWidget::keyPressEvent(QKeyEvent* evt)
    {
        Base3DViewerWidget::keyPressEvent(evt);
        if (evt->modifiers() == Qt::ControlModifier)
        {
            if (evt->key() == Qt::Key_Z)
            {
                CommandManager::GetSingleton().Undo();
            }
            else if (evt->key() == Qt::Key_Y)
            {
                CommandManager::GetSingleton().Redo();
            }
        }
    }

    void Main3DWidget::_OnFirstShowed()
    {
        OpenEarthFile("./Resources/out.earth");

        _root->addChild(_scene->GetScene());
    }
} // namespace xStudio