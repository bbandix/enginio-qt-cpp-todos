#include "todoitemdelegate.h"
#include "enginiojsonobject.h"
#include "enginioobjectmodel.h"

#include <QDebug>
#include <QPainter>

TodoItemDelegate::TodoItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void TodoItemDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    painter->save();

    EnginioAbstractObject *abs = qvariant_cast<EnginioAbstractObject*>(
                index.data(Enginio::DataRole));
    EnginioJsonObject *json = static_cast<EnginioJsonObject*>(abs);

    QPalette::ColorGroup colorGroup = QPalette::Normal;
    if (json->value("completed").toBool())
        colorGroup = QPalette::Disabled;

    QPalette::ColorRole backgroundRole = QPalette::Base;
    if (option.state == QStyle::State_MouseOver)
        backgroundRole = QPalette::AlternateBase;

    painter->fillRect(option.rect, option.palette.brush(colorGroup,
                                                        backgroundRole));
    painter->setPen(option.palette.color(colorGroup, QPalette::WindowText));
    painter->drawText(option.rect, json->value("title").toString());

    painter->restore();
}
