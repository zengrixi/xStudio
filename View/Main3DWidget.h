#pragma once

#include "Base3DViewerWidget.h"

class Main3DWidget : public Base3DViewerWidget
{
public:
    Main3DWidget(QWidget* parent);
    ~Main3DWidget();

    osg::Group* GetRootNode() const;

    void AddNodeToRoot(const osg::ref_ptr<osg::Node>& node);
};
