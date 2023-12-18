#include "mywidget.h"
#include "ui_mywidget.h"
#include <QGridLayout>
#include <QString>
#include <QVector>
#include <QDebug>
#include "mydialog.h"

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ui->label,0,0,1,1);
    layout->addWidget(ui->lineEdit,0,1,1,1);
    layout->addWidget(ui->label_3,1,0,1,1);
    layout->addWidget(ui->lineEdit_3,1,1,1,1);
    layout->addWidget(ui->label_4,2,0,1,1);
    layout->addWidget(ui->lineEdit_4,2,1,1,1);
    layout->addWidget(ui->label_2,4,0,1,1);
    layout->addWidget(ui->lineEdit_2,4,1,1,1);
    layout->addWidget(ui->pushButton,5,0,1,2);
    layout->addWidget(ui->label_5,3,0,1,1);
    layout->addWidget(ui->lineEdit_5,3,1,1,1);
    layout->addWidget(ui->pushButton_2,6,0,1,2);

    setLayout(layout);

}

myWidget::~myWidget()
{
    delete ui;
}

void myWidget::on_pushButton_clicked()
{
     double amount = ui->lineEdit->text().toDouble();
     int specified_month = ui->lineEdit_5->text().toInt();
     int month=ui->lineEdit_3->text().toInt();
     double fake_rate = ui->lineEdit_4->text().toDouble()/1000;
     double interest = fake_rate*amount;
     QVector<double> rate_by_mon(month);
     QVector<double> principal(month);

     for (int i =0 ;i<month;i++) {
         principal[i]=amount-i*(amount/specified_month);
     }

     double average_rate=0;
     for (int i=0 ;i<month;i++) {
         rate_by_mon[i]=interest/(principal[i]);
         qDebug()<<"第"<<i+1<<"个月的利息和本金是："<<rate_by_mon[i]<<"  "<<principal[i]<<endl;
         average_rate+=rate_by_mon[i];

         qDebug()<<"第"<<i+1<<"个月的违约金是"<<principal[i]*0.03<<endl;
     }
     average_rate+=0.03;
     average_rate/=month;
     average_rate*=1000;
     ui->lineEdit_2->setText(QString::number(average_rate,'f',6));


}

void myWidget::on_pushButton_2_clicked()
{
    close();
    myDialog dialog;
    if(dialog.exec()==QDialog::Accepted){
        qDebug()<<"Accepted dialog"<<endl;
        show();
        qDebug()<<"show widgets"<<endl;
    }
}
