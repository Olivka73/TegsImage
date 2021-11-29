#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QVector>
#include <QGraphicsScene>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString NameImage;
    QStringList thistegs;
    QString current;

private slots:
    void on_load_triggered();

    void on_currenttegs_currentTextChanged(const QString &currentText);

    void on_lineEdit_editingFinished();

    void on_savechange_clicked();

    void on_deletetegs_clicked();

    void on_deleteimage_triggered();

    void on_delThisTeg_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
