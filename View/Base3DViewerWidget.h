#pragma once

#include <QInputEvent>
#include <QOpenGLWidget>

#include <osgViewer/Viewer>

namespace xStudio
{
    class Base3DViewerWidget
        : public QOpenGLWidget
        , public osgViewer::Viewer
    {
    public:
        Base3DViewerWidget(QWidget* parent);
        ~Base3DViewerWidget();

    protected:
        bool event(QEvent* evt);
        void setKeyboardModifiers(QInputEvent* evt);

        void keyPressEvent(QKeyEvent* evt) override;
        void keyReleaseEvent(QKeyEvent* evt) override;
        void mousePressEvent(QMouseEvent* evt) override;
        void mouseReleaseEvent(QMouseEvent* evt) override;
        void mouseDoubleClickEvent(QMouseEvent* evt) override;
        void mouseMoveEvent(QMouseEvent* evt) override;
        void wheelEvent(QWheelEvent* evt) override;
        void resizeEvent(QResizeEvent* evt) override;
        void moveEvent(QMoveEvent* evt) override;
        void timerEvent(QTimerEvent* evt) override;

        virtual void paintGL();

    private:
        void init3D();
        auto createCamera(int x, int y, int w, int h) -> osg::ref_ptr<osg::Camera>;

    protected:
        osg::ref_ptr<osgViewer::GraphicsWindow> _gw;
        osg::ref_ptr<osg::Group>                _root;
    };
} // namespace xStudio
