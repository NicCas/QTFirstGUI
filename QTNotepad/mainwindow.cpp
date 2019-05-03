#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); // Set as central widgit
}

MainWindow::~MainWindow()
{
    delete ui;
}

// New
// The barebones of this was auto filled from the user interface is "go to slot"
void MainWindow::on_actionNew_triggered()
{
    // Want to clear screen
    currentFile.clear();
    // Want to create a new text window
    // New string
    // Set text to string
    ui->textEdit->setText(QString());
}

// Open
// The barebones of this was auto filled from the user interface
void MainWindow::on_actionOpen_triggered()
{
    // want to open file
    QString fileName =QFileDialog::getOpenFileName(this, "Open the File");
    QFile file(fileName);

    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning (this, "warning", "Can NOT deal with this file: ", file.errorString());

    }
    setWindowTitle (fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

// Save
void MainWindow::on_actionSave_triggered()
{
    QString fileName =QFileDialog::getSaveFileName(this, "Save the File");

    //Create object to hold file
    QFile file(fileName);

    //Open file, notify if problem
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning (this, "warning", "Can NOT save  this file: ", file.errorString());

    }

    // Store current file
    currentFile = fileName;

    // Set window title to name of this file
    setWindowTitle (fileName);

    //when writting to out we are actually writting to file in line 79
    QTextStream out(&file);

    // Copy text into textedit widgit, convert to plain text
    QString text = ui->textEdit -> toPlainText();

    // Write file name then close file
    out << text;
    file.close();

}

// End/exit
void MainWindow::on_actionEnd_triggered()
{
    QApplication::quit();
}

// Copy
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

// Paste
void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

// Undo
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

// Redo
void MainWindow::on_actionRedo_triggered()
{
     ui->textEdit->redo();
}
