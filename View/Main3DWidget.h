#pragma once

#include <Model/MScene.h>

#include "Base3DViewerWidget.h"

namespace xStudio
{
    class Main3DWidget : public Base3DViewerWidget
    {
    public:
        Main3DWidget(QWidget* parent);
        ~Main3DWidget();

        osg::Group* GetRootNode() const;

        void AddNodeToRoot(const osg::ref_ptr<osg::Node>& node);

        bool OpenEarthFile(const QString& file);

    protected:
        void dragEnterEvent(QDragEnterEvent* evt) override;
        void dragMoveEvent(QDragMoveEvent* evt) override;
        void dropEvent(QDropEvent* evt) override;
        void showEvent(QShowEvent* evt) override;
        void keyPressEvent(QKeyEvent* evt) override;

    private:
        void _OnFirstShowed();

    private:
        MScene* _scene;

        bool _firstShowed = true;
    };
} // namespace xStudio
