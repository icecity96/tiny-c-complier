//
// Created by ice_city on 1/26/17.
//

#ifndef CH03_MAINWINDOW_H
#define CH03_MAINWINDOW_H

#include <QWidget>
#include <QtGui>
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void show_lexer_result();
private:
    QTextEdit   *textEdit;
    QWidget     *main_widget;
    QPushButton *lexer_button;
    QPushButton *paraser_button;
    QString lexer_result;
    QString content;
    bool read_file(const QString &file_name);
};
#endif //CH03_MAINWINDOW_H
