/*****************************************************************/ /**
 * \file   MObject.h
 * \brief  所有Model对象的基类，Object对象的属性支持修改和撤销以及重做
 * 
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <QObject>

namespace xStudio
{
    class MObject : public QObject
    {
        Q_OBJECT

    public:
        MObject(MObject* parent);

        void Ref();
        void UnRef();
        
        void Destroy();

    private:
        std::atomic<uint32_t> _refCount = 0;
    };
}; // namespace xStudio
