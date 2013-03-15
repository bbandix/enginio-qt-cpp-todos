#ifndef TODOITEMDELEGATE_H
#define TODOITEMDELEGATE_H

#include <QStyledItemDelegate>

class TodoItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TodoItemDelegate(QObject *parent = 0);
    void paint(QPainter * painter,
               const QStyleOptionViewItem & option,
               const QModelIndex & index) const;
};

#endif // TODOITEMDELEGATE_H
