#include "mainwindow.h"
#include "todoitemdelegate.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QMenu>
#include <QStatusBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QMetaEnum>

#include "applicationconfig.h"
#include "enginioclient.h"
#include "enginioerror.h"
#include "enginiojsonobject.h"
#include "enginioobjectmodel.h"
#include "enginioobjectoperation.h"
#include "enginioqueryoperation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Enginio Todos"));

    m_client = new EnginioClient(Enginio::BACKEND_ID,
                                 Enginio::BACKEND_SECRET,
                                 this);
    m_client->setApiUrl(Enginio::BACKEND_API_URL);

    m_objectModel = new EnginioObjectModel(this);

    m_newTodoInput = new QLineEdit();
    connect(m_newTodoInput, SIGNAL(returnPressed()),
            this, SLOT(createNewTodo()));

    m_newTodoButton = new QToolButton();
    m_newTodoButton->setText("+");
    m_newTodoButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
    connect(m_newTodoButton, SIGNAL(clicked()), this, SLOT(createNewTodo()));

    m_objectList = new QListView;
    m_objectList->setModel(m_objectModel);
    m_objectList->setItemDelegate(new TodoItemDelegate(this));
    m_objectList->setContextMenuPolicy(Qt::CustomContextMenu);
    m_objectList->setSelectionMode(QAbstractItemView::NoSelection);
    m_objectList->setFocusPolicy(Qt::NoFocus);
    connect(m_objectList, SIGNAL(customContextMenuRequested(const QPoint&)),
            this, SLOT(showContextMenu(const QPoint&)));
    connect(m_objectList, SIGNAL(clicked(QModelIndex)),
            this, SLOT(toggleCompleted(QModelIndex)));

    m_statusBar = new QStatusBar;

    QFrame *frame = new QFrame;

    QVBoxLayout *windowLayout = new QVBoxLayout(frame);
    QHBoxLayout *newTodoLayout = new QHBoxLayout();
    newTodoLayout->addWidget(m_newTodoInput);
    newTodoLayout->addWidget(m_newTodoButton);
    windowLayout->addLayout(newTodoLayout);
    windowLayout->addWidget(m_objectList);
    windowLayout->addWidget(m_statusBar);
    setCentralWidget(frame);

    queryTodos();
}

void MainWindow::operationFinished()
{
    EnginioOperation *op = qobject_cast<EnginioOperation*>(sender());
    bool noError = op->error()->error() == EnginioError::NoError;

    if (m_operations.removeOne(op))
        delete op;

    if (noError)
        m_statusBar->showMessage("Done", 2000);
}

void MainWindow::operationError(EnginioError *error)
{
    QString errorValue;
        QMetaObject meta = QNetworkReply::staticMetaObject;
        for (int i=0; i < meta.enumeratorCount(); ++i) {
            QMetaEnum m = meta.enumerator(i);
            if (m.name() == QLatin1String("NetworkError")) {
                errorValue = QLatin1String(m.valueToKey(error->networkError()));
                break;
            }
        }

    QString message = error->errorString() + ", NetworkError:" + errorValue + ", HTTP:" + QString::number(error->httpCode());

    m_statusBar->showMessage(message);
}

void MainWindow::queryTodos()
{
    m_statusBar->showMessage("Fetching todos...");

    m_objectModel->clear();

    EnginioQueryOperation *op = new EnginioQueryOperation(m_client);
    m_operations.append(op);
    op->setModel(m_objectModel);
    op->setObjectType("objects.todos");
    connect(op, SIGNAL(finished()), this, SLOT(operationFinished()));
    connect(op, SIGNAL(error(EnginioError*)),
            this, SLOT(operationError(EnginioError*)));
    op->execute();
}

void MainWindow::createNewTodo()
{
    if (m_newTodoInput->text().isEmpty())
        return;

    EnginioJsonObject newTodo("objects.todos");
    newTodo.insert("title", m_newTodoInput->text());
    newTodo.insert("completed", false);

    m_statusBar->showMessage("Creating new todo...");

    EnginioObjectOperation *op = new EnginioObjectOperation(m_client);
    m_operations.append(op);
    connect(op, SIGNAL(finished()), this, SLOT(operationFinished()));
    connect(op, SIGNAL(error(EnginioError*)),
            this, SLOT(operationError(EnginioError*)));
    op->setModel(m_objectModel);
    op->create(newTodo);
    op->execute();

    m_newTodoInput->clear();
}

void MainWindow::toggleCompleted(const QModelIndex &index)
{
    EnginioJsonObject *obj = static_cast<EnginioJsonObject*>(
                m_objectModel->getObject(index));

    bool isCompleted = obj->value("completed").toBool();

    obj->insert("completed", !isCompleted);

    m_statusBar->showMessage("Updating state...");

    EnginioObjectOperation *op = new EnginioObjectOperation(m_client);
    m_operations.append(op);
    connect(op, SIGNAL(finished()), this, SLOT(operationFinished()));
    connect(op, SIGNAL(error(EnginioError*)),
            this, SLOT(operationError(EnginioError*)));
    op->setModel(m_objectModel);
    op->update(obj);
    op->execute();
}

void MainWindow::showContextMenu(const QPoint& point)
{
    QModelIndex index = m_objectList->indexAt(point);
    if (!index.isValid())
        return;

    QPoint globalPos = m_objectList->viewport()->mapToGlobal(point);

    QMenu contextMenu;
    contextMenu.addAction("Delete");
    contextMenu.addAction("Refresh");

    QAction *selectedAction = contextMenu.exec(globalPos);
    if (selectedAction) {
        if (selectedAction->text() == "Delete")
            deleteTodo(index);
        else if (selectedAction->text() == "Refresh")
            queryTodos();
    }
}

void MainWindow::deleteTodo(const QModelIndex &index)
{
    EnginioJsonObject *obj = static_cast<EnginioJsonObject*>(
                m_objectModel->getObject(index));

    m_statusBar->showMessage("Deleting todo...");

    EnginioObjectOperation *op = new EnginioObjectOperation(m_client);
    m_operations.append(op);
    connect(op, SIGNAL(finished()), this, SLOT(operationFinished()));
    connect(op, SIGNAL(error(EnginioError*)),
            this, SLOT(operationError(EnginioError*)));
    op->setModel(m_objectModel);
    op->remove(obj);
    op->execute();
}
