/*****************************************************************/ /**
 * \file   BaseCommand.h
 * \brief  指令执行类基类
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <Cmd/CommandDesc/CommandDesc.h>

namespace xStudio
{
    enum CommandUndoRedoState
    {
        CommandUndoRedoState_Normal,
        CommandUndoRedoState_Undo,
        CommandUndoRedoState_Redo
    };

    class BaseCommand
    {
    public:
        BaseCommand();
        ~BaseCommand();

        /**
         * 执行指令（可重入）.
         *
         * \param commandDesc   指令描述
         * \param undoRedoState 指令是否处于撤销或者重做状态
         */
        virtual void Execute(CommandDesc*         commandDesc,
                             CommandUndoRedoState undoRedoState = CommandUndoRedoState_Normal) const
        {
        }
    };
} // namespace xStudio
