#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QPrintDialog>
#include <QPrinter>
#include <QIcon>
#include <QFont>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QCoreApplication::setApplicationName( QString("My Application") );
//    setWindowTitle( QCoreApplication::applicationName() );
    setWindowTitle("Zer0nepad");
    setWindowIcon(QIcon(":/rec/mainwindowIcon/icons8-notepad-85.png"));
    this->setCentralWidget(ui->textEdit);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    FilePath = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open a new fie", "C:\\Users\\tejarat pooya\\Pictures\\Desktop\\UNI\\AP");
    QFile file(file_name);
    FilePath = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox message;
        message.warning(this, "Error", "Can not Open the file");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void MainWindow::on_actionSaeve_triggered()
{
    QFile file(FilePath);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox message;
        message.warning(this, "Error", "Can not Open the file");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_2_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save a fie");
    QFile file(file_name);
    FilePath = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox message;
        message.warning(this, "Error", "Can not Open the file");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
        ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
        ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
        ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
        ui->textEdit->undo();
}


void MainWindow::on_actionAbout_triggered()
{
    QString about_text;
    about_text = "Author : Zer0ne\n";
    about_text+= "Date : 6/14/2022\n";
    about_text+= "Information : Writing by Qt c++ in Qt creator\n";
    QMessageBox::about(this, "About", about_text);
}


void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->textEdit->setCurrentFont(font);
    }
    else
    {
        return;
    }
}


void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
    else
    {
        return;
    }
}


void MainWindow::on_actionNotepad_bacckground_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if(color.isValid())
    {
        QPalette p = ui->textEdit->palette();
        p.setColor(QPalette::Active, QPalette::Base, color);
        ui->textEdit->setPalette(p);
    }
}


void MainWindow::on_actionBackground_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if(color.isValid())
    {
        ui->textEdit->setTextBackgroundColor(color);
    }
    else
    {
        return;
    }
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Desierd Printer name");
    QPrintDialog dialog(&printer, this);
    if(dialog.exec() == QDialog::Rejected)
        return;
    ui->textEdit->print(&printer);
}

