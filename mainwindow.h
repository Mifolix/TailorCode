#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString season;
    QString typeOfFashion;
    QString typeMaterial;
    QString typeClothes;
    QColor mainColor;
    QColor supColor;
    QString picture;
    QString count;

    QString timeOfYear;
    QString typClo;

    QVector<QPair<QString, QString>> instructions;
    QVector<int> order;

    bool seasonCheck, typeCheck, fashionCheck, materialCheck, mainColCheck, picCheck, supColCheck, countCheck;


private slots:
    void on_clothesButton_clicked();

    void on_materialButton_clicked();

    void on_mainColorButton_clicked();

    void on_supColorButton_clicked();

    void on_deleteMenu_triggered();

    void on_setPrintButton_clicked();

    void on_beginButton_clicked();

    void on_endButton_clicked();

    void on_countButton_clicked();

    void on_executeMenu_triggered();

    void on_seasonButton_clicked();

    void on_typeOfClothesButton_clicked();

    void on_productionButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
