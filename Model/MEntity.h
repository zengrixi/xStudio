/*****************************************************************/ /**
 * \file   MEntity.h
 * \brief  场景实体对象基类
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once
#include "MObject.h"

#include <osg/AutoTransform>
#include <osg/LOD>
#include <osg/Node>

namespace xStudio
{
    class MEntity : public MObject
    {
        Q_OBJECT

    public:
        MEntity(MObject* parent);
        ~MEntity();

        osg::Group* GetRender();

        bool FillWithFile(const QString& file);

        void SetPosition(const QVector3D& pos, bool emitPropertyChanged = false);

        void SetRotate(const QVector3D& rot, bool emitPropertyChanged = false);

        void SetScale(const QVector3D& scale, bool emitPropertyChanged = false);

        void     SetId(uint64_t id);
        uint64_t GetId() const;

    private:
        osg::ref_ptr<osg::Group>           _entityRoot;
        osg::ref_ptr<osg::LOD>             _entityLOD;
        osg::ref_ptr<osg::AutoTransform> _transform;

        uint64_t _id;
    };
} // namespace xStudio
