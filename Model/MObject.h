/*****************************************************************/ /**
 * \file   MObject.h
 * \brief  ����Model����Ļ��࣬Object���������֧���޸ĺͳ����Լ�����
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
