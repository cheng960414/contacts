#include "mywidget.h"
#include "ui_mywidget.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this); // 呼叫命名空間Ui內的MyWidget物件之成員函數
    ui->contactBook->setColumnCount(4);
        QStringList colTotal;
        colTotal << "學號" << "班級" << "姓名" << "電話";
        ui->contactBook->setHorizontalHeaderLabels(colTotal);
}
MyWidget::~MyWidget()
{
    delete ui;
}
void MyWidget::on_pushButton_clicked()
{
    {
        QTableWidgetItem *col1,*col2 ,*col3,*col4;
       col1 = new QTableWidgetItem(ui->lineEdit->text());
       col2 = new QTableWidgetItem(ui->lineEdit_2->text());
       col3 = new QTableWidgetItem(ui->lineEdit_3->text());
       col4 = new QTableWidgetItem(ui->lineEdit_4->text());
        int row = ui->contactBook->rowCount();
        qDebug() << row;
        ui->contactBook->insertRow(row);


        ui->contactBook->setItem(row, 0, col1);
        ui->contactBook->setItem(row, 1, col2);
        ui->contactBook->setItem(row, 2, col3);
        ui->contactBook->setItem(row, 3, col4);
    }
}
void MyWidget::CbWrite(QString fileName, QString str){
    QFile outFile(fileName);
    if(!outFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"Open File failed!";
        return;
    }
    QTextStream out(&outFile);
    out<<str;
    outFile.flush();
    outFile.close();
}


void MyWidget::on_pushButton_2_clicked()
{
    QString fileName;
    QString saveStr;
    fileName = QFileDialog::getSaveFileName(this,"匯出通訊錄",".","csv(*.csv);;text(*.txt)");
    for(int i=0;i<ui->contactBook->rowCount();i++)
     for(int j=0;j<ui->contactBook->columnCount();j++){
        saveStr+=ui->contactBook->item(i,j)->text()+",";
    }
    saveStr +="\n";
    CbWrite(fileName,saveStr);
}



void MyWidget::CbRead(QString fileName)
{
    QFile inFile(fileName);
    if(!inFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"Open File failed!";
        return;
    }
    QTextStream in(&inFile);
    ui->contactBook->setRowCount(0);
    while(!in.atEnd()){
        QString str = in.readLine();
        QStringList list = str.split(",");
        int row = ui->contactBook->rowCount();
        ui->contactBook->insertRow(row);
        for(int j=0; j<list.size(); j++){
            ui->contactBook->setItem(
                row,
                j,
                new QTableWidgetItem(list[j])
                );
        }
    }
}

void MyWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"匯入通訊錄",".","CSV (*.csv);;Text (*.txt)");
    if(fileName.isEmpty())
        return;
    CbRead(fileName);
}

