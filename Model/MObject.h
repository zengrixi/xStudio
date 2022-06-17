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

        void AddChild(MObject* child);
        void RemoveChild(MObject* child);

        void AddParent(MObject* parent);
        void RemoveParent(MObject* parent);

        bool IsChildOf(MObject* parent);

        void Destroy();

    protected:
        /**
         * �����Է����ı�ʱ����.
         *
         * \param propertyName      ��������
         * \param needSaveToFile    �Ƿ���Ҫ����
         */
        virtual void OnPropertyChanged(const QString& propertyName, bool needSaveToFile = true);

        /**
         * ���Ӷ�������Է����ı�ʱ����.
         *
         * \param child             �Ӷ���
         * \param propertyName      ��������
         * \param needSaveToFile    �Ƿ���Ҫ����
         */
        virtual void OnChildPropertyChanged(MObject* child, const QString& propertyName, bool needSaveToFile = true);

    signals:
        void PropertyChanged(const QString& propertyName, bool needSaveToFile);
        void ChildPropertyChanged(MObject* child, const QString& propertyName, bool needSaveToFile);
        void BeforeDestroy();

    private:
        std::atomic<uint32_t> _refCount = 0;

        QList<MObject*> _parentList;
        QList<MObject*> _childList;

        friend class CommandDesc;
        friend class BatchCommand;
    };
}; // namespace xStudio
