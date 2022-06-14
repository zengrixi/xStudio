#include "MObject.h"

namespace xStudio
{
    MObject::MObject(MObject* parent)
    {
    }

    void MObject::Ref()
    {
        ++_refCount;
    }

    void MObject::UnRef()
    {
        uint32_t newRef     = --_refCount;
        bool     needDelete = (newRef == 0);

        if (needDelete)
        {
            Destroy();
        }
    }

    void MObject::Destroy()
    {
        delete this;
    }
}; // namespace xStudio
