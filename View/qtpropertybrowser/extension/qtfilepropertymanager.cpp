#include "qtfilepropertymanager.h"

/**
 * file manager.
 *
 * \param parent
 */
QtFilePropertyManager::QtFilePropertyManager(QObject* parent)
    : QtAbstractPropertyManager(parent)
{
}

QtFilePropertyManager::~QtFilePropertyManager() { }

QString QtFilePropertyManager::value(const QtProperty* property) const
{
    if (!_theValues.contains(property))
    {
        return QString();
    }
    return _theValues[property].value;
}

QString QtFilePropertyManager::filter(const QtProperty* property) const
{
    if (!_theValues.contains(property))
    {
        return QString();
    }
    return _theValues[property].filter;
}

void QtFilePropertyManager::setValue(QtProperty* property, const QString& val)
{
    if (!_theValues.contains(property))
    {
        return;
    }

    Data data = _theValues[property];
    if (data.value == val)
    {
        return;
    }
    data.value           = val;
    _theValues[property] = data;

    emit propertyChanged(property);
    emit valueChanged(property, data.value);
}

void QtFilePropertyManager::setFilter(QtProperty* property, const QString& fil)
{
    if (!_theValues.contains(property))
    {
        return;
    }

    Data data = _theValues[property];
    if (data.filter == fil)
    {
        return;
    }
    data.filter          = fil;
    _theValues[property] = data;

    emit propertyChanged(property);
    emit filterChanged(property, data.filter);
}