/*****************************************************************/ /**
 * \file   BaseCommand.h
 * \brief  ָ��ִ�������
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
         * ִ��ָ������룩.
         *
         * \param commandDesc   ָ������
         * \param undoRedoState ָ���Ƿ��ڳ�����������״̬
         */
        virtual void Execute(CommandDesc*         commandDesc,
                             CommandUndoRedoState undoRedoState = CommandUndoRedoState_Normal) const
        {
        }
    };
} // namespace xStudio
