#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);

   // connect(ui->pushButton,&QPushButton::clicked, this , &MainForm::iamclicked);
}

MainForm::~MainForm()
{
    delete ui;
}

//void MainForm::iamclicked()
//{
   // ui->textEdit_2->setText(ui->textEdit->toPlainText());
//}


