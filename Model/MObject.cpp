#include "MObject.h"
#include <Cmd/CommandManager.h>

#include <QMetaMethod>

namespace xStudio
{
    MObject::MObject(MObject* parent)
    {
        if (parent)
            AddParent(parent);
    }

    void MObject::Ref() { ++_refCount; }

    void MObject::UnRef()
    {
        auto newRef     = --_refCount;
        auto needDelete = (newRef == 0);

        if (needDelete)
        {
            Destroy();
        }
    }

    void MObject::AddChild(MObject* child)
    {
        if (child)
            child->AddParent(this);
    }

    void MObject::RemoveChild(MObject* child)
    {
        if (child)
        {
            child->RemoveParent(this);
        }
    }

    void MObject::AddParent(MObject* parent)
    {
        if (parent && _parentList.indexOf(parent) == -1)
        {
            Ref();
            _parentList.push_back(parent);
            parent->_childList.push_back(this);
        }
    }

    void MObject::RemoveParent(MObject* parent)
    {
        auto index = _parentList.indexOf(parent);
        if (index >= 0)
        {
            UnRef();
            _parentList.removeAt(index);
            parent->_childList.removeOne(this);
        }
    }

    bool MObject::IsChildOf(MObject* parent)
    {
        if (_parentList.contains(parent))
            return true;
        else
        {
            for (auto& eachParent : _parentList)
            {
                if (eachParent->IsChildOf(parent))
                    return true;
            }
            return false;
        }
    }

    void MObject::Destroy()
    {
        emit BeforeDestroy();

        for (auto& child : _childList)
        {
            child->RemoveParent(this);
        }
        delete this;
    }

    void MObject::OnPropertyChanged(const QString& propertyName, bool needSaveToFile)
    {
        emit PropertyChanged(propertyName, needSaveToFile);

        for (auto& parent : _parentList)
        {
            parent->OnChildPropertyChanged(this, propertyName, needSaveToFile);
        }
    }

    void MObject::OnChildPropertyChanged(MObject* child, const QString& propertyName, bool needSaveToFile)
    {
        static const auto childPropertyChanged = QMetaMethod::fromSignal(&MObject::ChildPropertyChanged);
        if (isSignalConnected(childPropertyChanged))
            emit ChildPropertyChanged(child, propertyName, needSaveToFile);

        for (auto& parent : _parentList)
        {
            parent->OnChildPropertyChanged(child, propertyName, needSaveToFile);
        }
    }
}; // namespace xStudio