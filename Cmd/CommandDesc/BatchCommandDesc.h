/*****************************************************************/ /**
 * \file   BatchCommandDesc.h
 * \brief  批处理指令描述
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include "CommandDesc.h"

namespace xStudio
{
    class BatchCommandDesc : public CommandDesc
    {
    public:
        BatchCommandDesc(const QList<CommandDesc*>& cmdList,
                         const QList<MObject*>&     batchedPropertyTargets,
                         const QList<QString>&      batchedPropertyNames,
                         const CommandDescOption&   option = CommandDescOption());

        BatchCommandDesc() { }
        ~BatchCommandDesc() { }

        static QString CommandName() { return "BatchCommand"; }

        QString GetCommandName() const override { return CommandName(); }

        virtual CommandDesc* CreateSameTypeCommandDesc() const;

        bool CombinedWith(CommandDesc* lastCmdDesc) override;

        bool HasModifiedTarget(MObject* target) const override;

    private:
        QList<QString>      _batchedPropertyNames;
        QList<MObject*>     _batchedPropertyTargets;
        QList<CommandDesc*> _cmdList;

        friend class BatchCommand;
    };
} // namespace xStudio
