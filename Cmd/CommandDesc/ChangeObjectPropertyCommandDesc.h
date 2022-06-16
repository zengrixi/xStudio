/*****************************************************************/ /**
 * \file   ChangeObjectPropertyCommandDesc.h
 * \brief  object���Ըı�ָ������
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include "CommandDesc.h"

#include <Cmd/CommandManager.h>
#include <QVariant>

namespace xStudio
{
    class ChangeObjectPropertyCommandDesc : public CommandDesc
    {
    public:
        /**
         * Object���Ըı��������캯��.
         *
         * \param target            MObject����
         * \param propertyName      ��������
         * \param newValue          ��ֵ
         * \param oldValue          ��ֵ
         * \param option            ��ѡ����
         */
        ChangeObjectPropertyCommandDesc(MObject*                 target,
                                        const QString&           propertyName,
                                        const QVariant&          newValue,
                                        const QVariant&          oldValue,
                                        const CommandDescOption& option = CommandDescOption());

        ChangeObjectPropertyCommandDesc();
        ~ChangeObjectPropertyCommandDesc();

        static QString CommandName() { return "ChangeObjectPropertyCommand"; }

        QString GetCommandName() const override { return CommandName(); }

        CommandDesc* CreateSameTypeCommandDesc() const override;

        bool CombinedWith(CommandDesc* lastCmdDesc) override;

        bool HasModifiedTarget(MObject* target) const override;

    private:
        MObject* _ptarget;
        QString  _propertyName;
        QVariant _newValue;
        QVariant _oldValue;

        friend class ChangeObjectPropertyCommand;
    };

    class ChangeObjectListPropertyCommandDesc : public CommandDesc
    {
    public:
        ChangeObjectListPropertyCommandDesc(MObject*                 target,
                                            const QString&           propertyName,
                                            ListOperateEnum          operate,
                                            int                      index,
                                            int                      cnt,
                                            const QVariant&          newValue,
                                            const QVariant&          oldValue,
                                            const CommandDescOption& option = CommandDescOption());

        ChangeObjectListPropertyCommandDesc() { }
        ~ChangeObjectListPropertyCommandDesc() { }

        static QString CommandName() { return "ChangeObjectListPropertyCommand"; }

        QString GetCommandName() const override { return CommandName(); }

        CommandDesc* CreateSameTypeCommandDesc() const override;

        bool HasModifiedTarget(MObject* target) const override;

    private:
        MObject*        _ptarget;
        QString         _propertyName;
        ListOperateEnum _operate;
        int             _index;
        int             _cnt;
        QVariant        _newValue;
        QVariant        _oldValue;

        friend class ChangeObjectListPropertyCommand;
    };
} // namespace xStudio
