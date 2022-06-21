/*****************************************************************//**
 * \file   qtfilemanager.h
 * \brief  文件属性控件 manager
 * 
 * \author zengrixi
 * \date   June 2022
 *********************************************************************/
#pragma once

#include <QMap>

#include <View/qtpropertybrowser/qtpropertybrowser.h>

class QtFilePropertyManager : public QtAbstractPropertyManager
{
    Q_OBJECT

public:
    QtFilePropertyManager(QObject* parent = 0);
    ~QtFilePropertyManager();

    QString value(const QtProperty* property) const;
    QString filter(const QtProperty* property) const;

public Q_SLOTS:
    void setValue(QtProperty* property, const QString& val);
    void setFilter(QtProperty* property, const QString& fil);

Q_SIGNALS:
    void valueChanged(QtProperty* property, const QString& val);
    void filterChanged(QtProperty* property, const QString& fil);

protected:
    QString valueText(const QtProperty* property) const { return value(property); }
    void    initializeProperty(QtProperty* property) { _theValues[property] = Data(); }
    void    uninitializeProperty(QtProperty* property) { _theValues.remove(property); }

private:
    struct Data
    {
        QString value;
        QString filter;
    };
    QMap<const QtProperty*, Data> _theValues;
};
