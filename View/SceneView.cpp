#include "SceneView.h"

#include <QApplication>
#include <QInputEvent>
#include <QMessageBox>

#include <osg/LightModel>
#include <osg/MatrixTransform>
#include <osg/ValueObject>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Renderer>
#include <osgViewer/ViewerEventHandlers>

SceneView::SceneView(QWidget* parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSamples(16);
    setFormat(format);

    init3D();

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

osg::Group* SceneView::GetRootNode() const
{
    return _root;
}

void SceneView::AddNodeToRoot(const osg::ref_ptr<osg::Node>& node)
{
    _root->addChild(node);
}

bool SceneView::event(QEvent* evt)
{
    switch (evt->type())
    {
    case QEvent::TouchBegin:
    case QEvent::TouchEnd:
    case QEvent::TouchUpdate:
    {
        auto     touchPoints = static_cast<QTouchEvent*>(evt)->touchPoints();
        uint32_t id          = 0;
        uint32_t tapCount    = touchPoints.size();

        osg::ref_ptr<osgGA::GUIEventAdapter> osgEvent(nullptr);
        osgGA::GUIEventAdapter::TouchPhase   phase = osgGA::GUIEventAdapter::TOUCH_UNKNOWN;
        foreach (const QTouchEvent::TouchPoint& touchPoint, touchPoints)
        {
            if (!osgEvent)
            {
                if (evt->type() == QEvent::TouchBegin)
                {
                    phase    = osgGA::GUIEventAdapter::TOUCH_BEGAN;
                    osgEvent = _gw->getEventQueue()->touchBegan(id,
                                                                osgGA::GUIEventAdapter::TOUCH_BEGAN,
                                                                touchPoint.pos().x(),
                                                                touchPoint.pos().y());
                }
                else if (evt->type() == QEvent::TouchEnd)
                {
                    phase    = osgGA::GUIEventAdapter::TOUCH_ENDED;
                    osgEvent = _gw->getEventQueue()->touchEnded(id,
                                                                osgGA::GUIEventAdapter::TOUCH_ENDED,
                                                                touchPoint.pos().x(),
                                                                touchPoint.pos().y(),
                                                                tapCount);
                }
                else if (evt->type() == QEvent::TouchUpdate)
                {
                    phase    = osgGA::GUIEventAdapter::TOUCH_MOVED;
                    osgEvent = _gw->getEventQueue()->touchMoved(id,
                                                                osgGA::GUIEventAdapter::TOUCH_MOVED,
                                                                touchPoint.pos().x(),
                                                                touchPoint.pos().y());
                }
            }
            else
            {
                osgEvent->addTouchPoint(id,
                                        osgGA::GUIEventAdapter::TOUCH_ENDED,
                                        touchPoint.pos().x(),
                                        touchPoint.pos().y());
                osgEvent->addTouchPoint(id, phase, touchPoint.pos().x(), touchPoint.pos().y());
            }
            id++;
        }
        break;
    }
    default:
        break;
    }
    return QOpenGLWidget::event(evt);
}

void SceneView::setKeyboardModifiers(QInputEvent* evt)
{
    int32_t  modkey = evt->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
    uint32_t mask   = 0;
    if (modkey & Qt::ShiftModifier)
    {
        mask |= osgGA::GUIEventAdapter::MODKEY_SHIFT;
    }
    if (modkey & Qt::ControlModifier)
    {
        mask |= osgGA::GUIEventAdapter::MODKEY_CTRL;
    }
    if (modkey & Qt::AltModifier)
    {
        mask |= osgGA::GUIEventAdapter::MODKEY_ALT;
    }

    _gw->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
    update();
}

void SceneView::keyPressEvent(QKeyEvent* evt)
{
    setKeyboardModifiers(evt);
    _gw->getEventQueue()->keyPress(evt->key());
    QOpenGLWidget::keyPressEvent(evt);
    update();
}

void SceneView::keyReleaseEvent(QKeyEvent* evt)
{
    setKeyboardModifiers(evt);
    _gw->getEventQueue()->keyRelease(evt->key());
    QOpenGLWidget::keyReleaseEvent(evt);
    update();
}

void SceneView::mousePressEvent(QMouseEvent* evt)
{
    int button = 0;
    switch (evt->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MidButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    case Qt::NoButton:
        button = 0;
        break;
    default:
        button = 0;
        break;
    }
    setKeyboardModifiers(evt);
    _gw->getEventQueue()->mouseButtonPress(evt->x(), evt->y(), button);
    update();
}

void SceneView::mouseReleaseEvent(QMouseEvent* evt)
{
    int button = 0;
    switch (evt->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MidButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    case Qt::NoButton:
        button = 0;
        break;
    default:
        button = 0;
        break;
    }
    setKeyboardModifiers(evt);
    _gw->getEventQueue()->mouseButtonRelease(evt->x(), evt->y(), button);

    QOpenGLWidget::mouseReleaseEvent(evt);
    update();
}

void SceneView::mouseDoubleClickEvent(QMouseEvent* evt)
{
    int button = 0;
    switch (evt->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MidButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    case Qt::NoButton:
        button = 0;
        break;
    default:
        button = 0;
        break;
    }
    setKeyboardModifiers(evt);
    _gw->getEventQueue()->mouseDoubleButtonPress(evt->x(), evt->y(), button);

    QOpenGLWidget::mouseDoubleClickEvent(evt);
    update();
}

void SceneView::mouseMoveEvent(QMouseEvent* evt)
{
    setKeyboardModifiers(evt);
    _gw->getEventQueue()->mouseMotion(evt->x(), evt->y());
    QOpenGLWidget::mouseMoveEvent(evt);
    update();
}

void SceneView::wheelEvent(QWheelEvent* evt)
{
    setKeyboardModifiers(evt);
    _gw->getEventQueue()->mouseScroll(
        evt->orientation() == Qt::Vertical
            ? (evt->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN)
            : (evt->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_LEFT : osgGA::GUIEventAdapter::SCROLL_RIGHT));
    QOpenGLWidget::wheelEvent(evt);
    update();
}

void SceneView::resizeEvent(QResizeEvent* evt)
{
    const QSize& size = evt->size();
    _gw->resized(x(), y(), size.width(), size.height());
    _gw->getEventQueue()->windowResize(x(), y(), size.width(), size.height());
    _gw->requestRedraw();

    QOpenGLWidget::resizeEvent(evt);
}

void SceneView::moveEvent(QMoveEvent* evt)
{
    const QPoint& pos = evt->pos();
    _gw->resized(pos.x(), pos.y(), width(), height());
    _gw->getEventQueue()->windowResize(pos.x(), pos.y(), width(), height());

    QOpenGLWidget::moveEvent(evt);
}

void SceneView::timerEvent(QTimerEvent* evt)
{
    update();
}

void SceneView::paintGL()
{
    if (isVisibleTo(QApplication::activeWindow()))
    {
        frame();
    }
}

void SceneView::init3D()
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration                          = false;
    traits->x                                         = 0;
    traits->y                                         = 0;
    traits->width                                     = width();
    traits->height                                    = height();
    traits->doubleBuffer                              = true;
    traits->sharedContext                             = 0;

    _gw = new osgViewer::GraphicsWindowEmbedded(traits);

    auto camera = getCamera();
    camera->setGraphicsContext(_gw);
    camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->setCamera(camera); //这两句话的先后顺序
    _root = new osg::Group;
    this->setSceneData(_root);

    this->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    this->setCameraManipulator(new osgGA::TrackballManipulator);
    this->addEventHandler(new osgViewer::WindowSizeHandler());

    startTimer(20);
}

auto SceneView::createCamera(int x, int y, int w, int h) -> osg::ref_ptr<osg::Camera>
{
    _gw = new osgViewer::GraphicsWindowEmbedded(x, y, w, h);

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(_gw);
    camera->setViewport(new osg::Viewport(0, 0, w, h));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera->setProjectionMatrixAsPerspective(30.0f, double(w) / double(h), 1.0f, 10000.0f);
    camera->setClearColor(osg::Vec4(0.3, 0.3, 0.6, 0.1));

    return camera.release();
}
