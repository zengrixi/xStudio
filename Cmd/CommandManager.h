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
#include <QStack>

#include <Util/Singleton.h>

#include <Cmd/Command/BaseCommand.h>
#include <Cmd/CommandDesc/CommandDesc.h>

namespace xStudio
{
    enum ListOperateEnum
    {
        ListOperateEnum_Add,
        ListOperateEnum_Remove,
        ListOperateEnum_Update
    };

    struct DelayDispatchCommand
    {
        CommandDesc* cmdDesc;
        bool         supportUndoRedo;
        float        delayTime;
    };

    class CommandManager
        : public QObject
        , public Singleton<CommandManager>
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
         */
        void Undo();

        /**
         * 重做上次执行的指令.
         *
         */
        void Redo();

        void StartBatch();

        /**
         * 需要一起触发属性改变事件的属性名.
         *
         * \param batchedPropertyName
         * \param target
         */
        void StartBatch(const QString& batchedPropertyName, MObject* target);

        void EndBatch();

        bool HasBatch();

        void ChangeObjectProperty(MObject*        target,
                                  QString         propertyName,
                                  const QVariant& newValue,
                                  const QVariant& oldValue,
                                  bool            canBeCombined = false,
                                  QList<MObject*> refObjectList = QList<MObject*>(),
                                  CommandDesc*    accompanyCmd  = nullptr);

        void ChangeObjectListProperty(MObject*        target,
                                      const QString&  listName,
                                      ListOperateEnum operate,
                                      int             index,
                                      int             cnt,
                                      const QVariant& newValue,
                                      const QVariant& oldValue,
                                      bool            canBeCombined = false,
                                      QList<MObject*> refObjectList = QList<MObject*>(),
                                      CommandDesc*    accompanyCmd  = nullptr);

    private:
        void ExecuteCommand(CommandDesc* commandDesc, CommandUndoRedoState undoRedoState);

    signals:
        void DispatchCommandWithDesc(CommandDesc* commandDesc);

    private:
        //指令名字和指令执行对象表
        QMap<QString, BaseCommand*> _cmdNameToCmd;
        //指令名字和指令描述对象表
        QMap<QString, CommandDesc*> _cmdNameToCmdDesc;

        int                        _batchLevel = -1;
        QList<QList<CommandDesc*>> _batchCommands;

        QList<QList<QString>>  _batchedPropertyNames;
        QList<QList<MObject*>> _batchedPropertyTargets;

        QStack<CommandDesc*> _undoStack;
        QStack<CommandDesc*> _redoStack;

        uint64_t _lastStartBatchTime = 0;

        QList<DelayDispatchCommand*> _delayDispatchCommandSet;

        CommandDesc* _lastCombinedableCmd = nullptr;

        friend class BatchCommand;
        friend class CommandDesc;
    };
}; // namespace xStudio
