//
// Created by ice_city on 1/26/17.
#include "mainwindow.h"
#include "lexer.hpp"
#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    textEdit = new QTextEdit;
    QVBoxLayout *v_layout = new QVBoxLayout;
    lexer_button = new QPushButton("词法分析");
    paraser_button = new QPushButton("语法分析");
    v_layout->addWidget(lexer_button);
    v_layout->addWidget(paraser_button);
    QHBoxLayout *h_layout = new QHBoxLayout;
    h_layout->addWidget(textEdit);
    h_layout->addLayout(v_layout);
    main_widget = new QWidget;
    main_widget->setLayout(h_layout);
    setCentralWidget(main_widget);
    textEdit->setAcceptDrops(false);
    setAcceptDrops(true);
    QObject::connect(lexer_button, &QPushButton::clicked, this, &MainWindow::show_lexer_result);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
    {
        return;
    }

    QString file_name = urls.first().toLocalFile();
    if (file_name.isEmpty())
    {
        return;
    }

    if (read_file(file_name))
    {
        qDebug() << "read_file success!";
    }
}

bool MainWindow::read_file(const QString &file_name)
{
    bool result = false;
    QFile file(file_name);
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly))
    {
        content = in.readAll();
        result = true;
    }
    textEdit->setText(content);
    return result;
}

void MainWindow::show_lexer_result()
{
    std::istringstream ss(content.toStdString());
    read_source(ss);
    token current_token("null","null",1);
    while (current_token.id != -1)
    {
        current_token = get_next_token();
        lexer_result += QString::fromStdString(current_token.to_string());
    }
    textEdit->setText(lexer_result);
}

