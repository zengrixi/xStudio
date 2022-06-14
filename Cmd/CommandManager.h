/*****************************************************************/ /**
 * \file   CommandManager.h
 * \brief  ���������
 * 
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <QObject.h>
#include <QMap>

#include <Util/Singleton.h>

#include "BaseCommand.h"
#include "CommandDesc.h"

namespace xStudio
{
    struct DelayDispatchCommand
    {
        CommandDesc* cmdDesc;
        bool         supportUndoRedo;
        float        delayTime;
    };

    class CommandManager
        : public QObject
        , Singleton<CommandManager>
    {
        Q_OBJECT

    public:
        void Initialzie();

        /**
         * ע��ָ��.
         * 
         * \param cmdDesc   ָ����������
         * \param cmd       ָ��ִ�ж���
         */
        void RegisterCommand(CommandDesc* cmdDesc, BaseCommand* cmd);

        /**
         * ����ָ��.
         * 
         * \param cmdDesc           ָ������ָ�루��ָ���ⲿ����Ҫ�ͷţ�ֻ��Ҫ������ָ��ϵͳ������ָ����������ڣ�
         * \param supportUndoRedo   �Ƿ���Ҫ֧�ֳ������������������ָ���֧�ֳ���������������Ҳ���ܳ�����������
         * \param delayTime         �ӳٶ����뷢�ͣ����Ϊ0��������ִ��
         */
        void SendCommand(CommandDesc* cmdDesc, bool supportUndoRedo = true, float delayTime = 0.f);

        /**
         * �����ϴ�ִ�е�ָ��.
         * 
         * \param windowName    ָ��ִ�����ĸ���������
         */
        void Undo(const QString& windowName);

        /**
         * �����ϴ�ִ�е�ָ��.
         * 
         * \param windowName    ָ��ִ�����ĸ���������
         */
        void Redo(const QString& windowName);

    signals:
        void DispatchCommandWithDesc(CommandDesc* commandDesc);

    private:
        //ָ�����ֺ�ָ��ִ�ж����
        QMap<QString, BaseCommand*> _cmdNameToCmd;
        //ָ�����ֺ�ָ�����������
        QMap<QString, CommandDesc*> _cmdNameToCmdDesc;

        QList<DelayDispatchCommand*> _delayDispatchCommandSet;
    };
}; // namespace xStudio
