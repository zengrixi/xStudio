#include "MEntity.h"

#include <osg/MatrixTransform>
#include <osgDB/ReadFile>

namespace xStudio
{
    MEntity::MEntity(MObject* parent)
        : MObject(parent)
    {
        _transform  = new osg::MatrixTransform();
        _entityRoot = new osg::Group();
    }

    MEntity::~MEntity() { }

    osg::Group* MEntity::GetRender() { return _entityRoot.get(); }

    bool MEntity::FillWithFile(const QString& file)
    {
        auto node = osgDB::readNodeFile(file.toStdString());

        if (!node)
            return false;

        _transform->addChild(node);

        _entityRoot->addChild(_transform);

        return true;
    }

    void MEntity::SetPosition(const QVector3D& pos, bool emitPropertyChanged) { }

    void MEntity::SetRotate(const QVector3D& rot, bool emitPropertyChanged) { }

    void MEntity::SetScale(const QVector3D& scale, bool emitPropertyChanged) { }

    void MEntity::SetId(uint64_t id)
    {
        if (id != _id)
            _id = id;
    }

    uint64_t MEntity::GetId() const { return _id; }
} // namespace xStudio