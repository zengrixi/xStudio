#include "QtFileEditFactory.h"

QtFileEditFactory::QtFileEditFactory(QObject* parent)
    : QtAbstractEditorFactory<QtFilePropertyManager>(parent)
{
}

QtFileEditFactory::~QtFileEditFactory()
{
    auto editors = _theEditorToProperty.keys();

    QListIterator<FileEdit*> it(editors);
    while (it.hasNext())
        delete it.next();
}

void QtFileEditFactory::connectPropertyManager(QtFilePropertyManager* manager)
{
    connect(manager, &QtFilePropertyManager::valueChanged, this, &QtFileEditFactory::slotPropertyChanged);
    connect(manager, &QtFilePropertyManager::filterChanged, this, &QtFileEditFactory::slotFilterChanged);
}

QWidget* QtFileEditFactory::createEditor(QtFilePropertyManager* manager, QtProperty* prop, QWidget* parent)
{
    auto editor = new FileEdit(parent);
    editor->setFilePath(manager->value(prop));
    editor->setFilter(manager->filter(prop));
    _theCreatedEditors[prop].append(editor);
    _theEditorToProperty[editor] = prop;

    connect(editor, &FileEdit::filePathChanged, this, &QtFileEditFactory::slotSetValue);
    connect(editor, &FileEdit::destroyed, this, &QtFileEditFactory::slotEditorDestroyed);

    return editor;
}

void QtFileEditFactory::disconnectPropertyManager(QtFilePropertyManager* manager)
{
    disconnect(manager, &QtFilePropertyManager::valueChanged, this, &QtFileEditFactory::slotPropertyChanged);
    disconnect(manager, &QtFilePropertyManager::filterChanged, this, &QtFileEditFactory::slotFilterChanged);
}

void QtFileEditFactory::slotPropertyChanged(QtProperty* prop, const QString& value)
{
    if (!_theCreatedEditors.contains(prop))
        return;

    QList<FileEdit*>         editors = _theCreatedEditors[prop];
    QListIterator<FileEdit*> itEditor(editors);
    while (itEditor.hasNext())
        itEditor.next()->setFilePath(value);
}

void QtFileEditFactory::slotFilterChanged(QtProperty* prop, const QString& filter)
{
    if (!_theCreatedEditors.contains(prop))
        return;

    QList<FileEdit*>         editors = _theCreatedEditors[prop];
    QListIterator<FileEdit*> itEditor(editors);
    while (itEditor.hasNext())
        itEditor.next()->setFilter(filter);
}

void QtFileEditFactory::slotSetValue(const QString& value)
{
    auto object   = sender();
    auto itEditor = _theEditorToProperty.constBegin();
    while (itEditor != _theEditorToProperty.constEnd())
    {
        if (itEditor.key() == object)
        {
            auto prop    = itEditor.value();
            auto manager = propertyManager(prop);

            if (!manager)
                return;

            manager->setValue(prop, value);

            return;
        }
        itEditor++;
    }
}

void QtFileEditFactory::slotEditorDestroyed(QObject* object)
{
    auto itEditor = _theEditorToProperty.constBegin();
    while (itEditor != _theEditorToProperty.constEnd())
    {
        if (itEditor.key() == object)
        {
            auto editor = itEditor.key();
            auto prop   = itEditor.value();
            _theEditorToProperty.remove(editor);
            _theCreatedEditors[prop].removeAll(editor);
            if (_theCreatedEditors[prop].isEmpty())
                _theCreatedEditors.remove(prop);
            return;
        }
        itEditor++;
    }
}