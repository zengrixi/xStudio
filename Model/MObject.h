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

        void AddChild(MObject* child);
        void RemoveChild(MObject* child);

        void AddParent(MObject* parent);
        void RemoveParent(MObject* parent);

        bool IsChildOf(MObject* parent);

        void Destroy();

    protected:
        /**
         * 当属性发生改变时调用.
         *
         * \param propertyName      属性名称
         * \param needSaveToFile    是否需要保存
         */
        virtual void OnPropertyChanged(const QString& propertyName, bool needSaveToFile = true);

        /**
         * 当子对象的属性发生改变时调用.
         *
         * \param child             子对象
         * \param propertyName      属性名称
         * \param needSaveToFile    是否需要保存
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
