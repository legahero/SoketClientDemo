#include "soketmainwindow.h"
#include "ui_soketmainwindow.h"
#include <QTcpSocket>

QTcpSocket client;
SoketMainWindow::SoketMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SoketMainWindow)
{
    ui->setupUi(this);    
}

SoketMainWindow::~SoketMainWindow()
{
    client.disconnectFromHost();
    ui->teLog->append("---disconnect---");

    delete ui;
}


void SoketMainWindow::on_pbSend_clicked()
{
    if (client.state() != QAbstractSocket::ConnectedState) {
        ui->teLog->append("connect state:"+client.state());

        client.connectToHost(ui->leIP->text(),ui->lePort->text().toUInt());
        if (client.waitForConnected(30000))
        {
            ui->teLog->append("---connect---");
        }else
        {
            ui->teLog->append("connect time out");
        }
    }else
    {
        //取消异步收服务器数据
        disconnect(&client, SIGNAL(readyRead()), this, SLOT(doParseRecv()));
    }

    //阻塞式收发
    QString msg=ui->teSend->toPlainText();
    if(!msg.isEmpty())
    {
        msg+="\n";
        if(client.write(msg.toUtf8())>0)
        {
            ui->teLog->append("send: "+msg);
        }

        if(client.waitForReadyRead(15000))
        {
           //emit SockCondition("successful");
            QByteArray data=client.readAll();
            ui->teLog->append("read: "+QString(data));
        }
        else
        {
           //emit SockCondition("failed");
           //emit error(socket.error(),  socket.errorString());
           qDebug() <<"client.read fail, "<< client.errorString()<<",",client.error();
           ui->teLog->append("read err: "+client.errorString());
        }
    }

    //client.disconnectFromHost();

    //非阻塞，异步收服务器主动数据 数据
    connect(&client, SIGNAL(readyRead()), this, SLOT(doParseRecv()));

}

void SoketMainWindow::doParseRecv()
{
    while (client.bytesAvailable()) {

        QByteArray data = client.readAll();
        ui->teLog->append("recv:"+QString(data));
    }
}
