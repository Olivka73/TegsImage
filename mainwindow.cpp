#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_load_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_load_triggered() //+
{
    ui->currenttegs->clear();
    thistegs.clear();
    NameImage = QFileDialog::getOpenFileName(this, "Выбор изображения", "C:/Olivka/pics");

    QImage Image;
    Image.load(NameImage);
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->addPixmap(QPixmap::fromImage(Image));
    ui->graphicsView->setScene(scene);

        QString teg;
        for(int i = 0; i < NameImage.size(); i++)
            if(NameImage[i] == '[')
                for(int j = i+1; NameImage[j] != ']'; j++)
                {
                    if(NameImage[j] == ',')
                    {
                        if(teg.size() > 1)
                            thistegs.push_back(teg);

                        teg.clear();
                    }
                    else teg += NameImage[j];
                }
        if(teg.size()>0)
            thistegs.push_back(teg);

        ui->currenttegs->addItems(thistegs);
        ui->statusbar->showMessage(NameImage);
}


void MainWindow::on_currenttegs_currentTextChanged(const QString &currentText)//+
{
    current = currentText;
}


void MainWindow::on_lineEdit_editingFinished() // +
{
    QString text = ui->lineEdit->text();
    if(!text.isEmpty())
    {
        thistegs.push_back(text);
        ui->lineEdit->clear();
        ui->currenttegs->clear();
        ui->currenttegs->addItems(thistegs);
        ui->statusbar->showMessage("Тег добавлен");
    }
}


void MainWindow::on_savechange_clicked() // +
{
    QMessageBox::StandardButton ans = QMessageBox::question(this, "Сохранение", "Хотите сохранить изменения? \n Файл будет переименован",
                                                            QMessageBox::Yes | QMessageBox::No);

    if(ans == QMessageBox::Yes)
    {
        QString newname, tegs = "[", png = ".", gnp;

        for(int i = NameImage.size()-1; NameImage[i] != '.'; i--)
            gnp += NameImage[i];

        for(int i = gnp.size()-1; i >= 0; i--)
            png += gnp[i];

        if(NameImage.indexOf('[') == -1)
        {
            newname = NameImage;
            newname.resize(newname.size()-png.size());
        }
        else newname = NameImage.left(NameImage.indexOf('['));

        if(thistegs.size() > 0)
        {
            for(auto &p : thistegs)
                if(p.size() > 0)
                {
                    tegs += p;
                    tegs += ',';
                }

            tegs.resize(tegs.size()-1);
            tegs += ']';
            newname += tegs;
        }
        newname += png;

        QFile::rename(NameImage, newname);

        ui->statusbar->showMessage(newname);
        NameImage = newname;
    }
}

void MainWindow::on_deletetegs_clicked() // +
{
    ui->currenttegs->clear();
    thistegs.clear();
}

void MainWindow::on_deleteimage_triggered() // +
{
    QMessageBox::StandardButton ans = QMessageBox::question(this, "Удаление изображения", "Вы действительно хотите удалить это изображение?",
                                                                QMessageBox::Yes | QMessageBox::No);

    if(ans == QMessageBox::Yes)
    {
        QFile::remove(NameImage);
        ui->graphicsView->setScene(NULL);
        ui->statusbar->showMessage("Изображение удалено");
        ui->currenttegs->clear();
        thistegs.clear();
    }
}

void MainWindow::on_delThisTeg_clicked()//+
{
    thistegs.removeAt(thistegs.indexOf(current, 0));
    ui->currenttegs->clear();
    ui->currenttegs->addItems(thistegs);
    ui->statusbar->showMessage("Тег удален");
}

