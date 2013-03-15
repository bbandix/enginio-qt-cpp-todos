#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class EnginioClient;
class EnginioError;
class EnginioObjectModel;
class EnginioOperation;
class QLineEdit;
class QListView;
class QStatusBar;
class QToolButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);

private slots:
    void operationFinished();
    void operationError(EnginioError *error);
    void queryTodos();
    void createNewTodo();
    void toggleCompleted(const QModelIndex &index);
    void showContextMenu(const QPoint&);
    void deleteTodo(const QModelIndex &index);

private:
    QLineEdit *m_newTodoInput;
    QToolButton *m_newTodoButton;
    QListView *m_objectList;
    QStatusBar *m_statusBar;
    EnginioClient *m_client;
    EnginioObjectModel *m_objectModel;
    QList<EnginioOperation*> m_operations;
};

#endif // MAINWINDOW_H
