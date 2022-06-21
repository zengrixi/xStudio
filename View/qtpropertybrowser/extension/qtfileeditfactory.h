/*****************************************************************/ /**
 * \file   qtfileeditfactory.h
 * \brief  ÎÄ¼þÊôÐÔ factory
 *
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include "fileedit.h"
#include "qtfilepropertymanager.h"

class QtFileEditFactory : public QtAbstractEditorFactory<QtFilePropertyManager>
{
    Q_OBJECT
public:
    QtFileEditFactory(QObject* parent = nullptr);
    virtual ~QtFileEditFactory();

protected:
    void     connectPropertyManager(QtFilePropertyManager* manager);
    QWidget* createEditor(QtFilePropertyManager* manager, QtProperty* prop, QWidget* parent);
    void     disconnectPropertyManager(QtFilePropertyManager* manager);

private slots:
    void slotPropertyChanged(QtProperty* prop, const QString& value);
    void slotFilterChanged(QtProperty* prop, const QString& filter);
    void slotSetValue(const QString& value);
    void slotEditorDestroyed(QObject* object);

private:
    QMap<QtProperty*, QList<FileEdit*>> _theCreatedEditors;
    QMap<FileEdit*, QtProperty*>        _theEditorToProperty;
};
