/*****************************************************************/ /**
 * \file   CommandManager.h
 * \brief  命令管理器
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
         * 注册指令.
         * 
         * \param cmdDesc   指令描述对象
         * \param cmd       指令执行对象
         */
        void RegisterCommand(CommandDesc* cmdDesc, BaseCommand* cmd);

        /**
         * 发送指令.
         * 
         * \param cmdDesc           指令描述指针（该指针外部不需要释放，只需要创建，指令系统会管理该指针的生命周期）
         * \param supportUndoRedo   是否需要支持撤销和重做操作（如果指令本身不支持撤销和重做方法，也不能撤销和重做）
         * \param delayTime         延迟多少秒发送，如果为0，则立即执行
         */
        void SendCommand(CommandDesc* cmdDesc, bool supportUndoRedo = true, float delayTime = 0.f);

        /**
         * 撤销上次执行的指令.
         * 
         * \param windowName    指令执行在哪个窗口名称
         */
        void Undo(const QString& windowName);

        /**
         * 重做上次执行的指令.
         * 
         * \param windowName    指令执行在哪个窗口名称
         */
        void Redo(const QString& windowName);

    signals:
        void DispatchCommandWithDesc(CommandDesc* commandDesc);

    private:
        //指令名字和指令执行对象表
        QMap<QString, BaseCommand*> _cmdNameToCmd;
        //指令名字和指令描述对象表
        QMap<QString, CommandDesc*> _cmdNameToCmdDesc;

        QList<DelayDispatchCommand*> _delayDispatchCommandSet;
    };
}; // namespace xStudio
