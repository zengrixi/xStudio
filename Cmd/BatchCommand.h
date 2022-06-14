/*****************************************************************//**
 * \file   BatchCommand.h
 * \brief  ����ִ�ж������Command�Ĳ���
 * 
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include "BaseCommand.h"

namespace xStudio
{
    class BatchCommand : public BaseCommand
    {
    public:
        /**
         * ִ��ָ������룩.
         * 
         * \param commandDesc   ָ������
         * \param undoRedoState ָ���Ƿ��ڳ�����������״̬
         */
        void Execute(CommandDesc*         commandDesc,
                     CommandUndoRedoState undoRedoState = CommandUndoRedoState_Normal) const override;
    };
} // namespace xStudio
