#ifndef SOKETMAINWINDOW_H
#define SOKETMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SoketMainWindow; }
QT_END_NAMESPACE

class SoketMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SoketMainWindow(QWidget *parent = nullptr);
    ~SoketMainWindow();

private slots:
    void on_pbSend_clicked();
    void doParseRecv();
private:
    Ui::SoketMainWindow *ui;
};
#endif // SOKETMAINWINDOW_H
