#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <QListWidgetItem>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

#include "LoggingCategories.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->seasonButton->setEnabled(false);
    ui->clothesButton->setEnabled(false);
    ui->typeOfClothesButton->setEnabled(false);
    ui->materialButton->setEnabled(false);
    ui->mainColorButton->setEnabled(false);
    ui->supColorButton->setEnabled(false);
    ui->setPrintButton->setEnabled(false);
    ui->countButton->setEnabled(false);
    ui->productionButton->setEnabled(false);
    ui->endButton->setEnabled(false);

    qInfo(logDebug()) << "Программа запущена";

    instructions.append(QPair<QString, QString>("Начало технологии", ""));
    instructions.append(QPair<QString, QString>("Сезон одежды: ", ""));
    instructions.append(QPair<QString, QString>("Вид одежды: ", ""));
    instructions.append(QPair<QString, QString>("Фасон: ", ""));
    instructions.append(QPair<QString, QString>("Материал: ", ""));
    instructions.append(QPair<QString, QString>("Основной цвет: ", ""));
    instructions.append(QPair<QString, QString>("Дополнительный цвет: ", ""));
    instructions.append(QPair<QString, QString>("Рисунок: ", ""));
    instructions.append(QPair<QString, QString>("Количество: ", ""));
    instructions.append(QPair<QString, QString>("Пуск в производство", ""));
    instructions.append(QPair<QString, QString>("Конец технологии", ""));

    typClo = "изделий";

    seasonCheck = false;
    typeCheck = false;
    fashionCheck = false;
    materialCheck = false;
    mainColCheck = false;
    supColCheck = false;
    picCheck = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    qInfo(logDebug()) << "Программа прекратила работу";
}


void MainWindow::on_beginButton_clicked()
{
    order.append(0);

    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);
    QLabel *label = new QLabel("Начало технологии");
    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();
    layout->addWidget(label);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);
    ui->beginButton->setEnabled(false);

    ui->seasonButton->setEnabled(true);
    ui->mainColorButton->setEnabled(true);
    ui->setPrintButton->setEnabled(true);
    ui->countButton->setEnabled(true);
    ui->productionButton->setEnabled(true);
    ui->endButton->setEnabled(true);

    qInfo(logDebug()) << "Ввод инструкции Начало технологии";
}


void MainWindow::on_seasonButton_clicked()
{
    order.append(1);

    QComboBox *seasons = new QComboBox();
    seasons->addItem("Лето");
    seasons->addItem("Зима");
    seasons->addItem("Демисезон");
    seasons->setCurrentIndex(-1);

    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);

    QLabel *label = new QLabel("Сезон одежды ");

    qInfo(logDebug()) << "Ввод инструкции Сезон одежды";

    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();

    connect( seasons, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentTextChanged),[=]{
    season = seasons->currentText();
    instructions[1].second = season;
    qInfo(logInfo()) << "Инструкция - " + label->text() + seasons->currentText();
    seasons->setDisabled(true);
    ui->clothesButton->setEnabled(true);

    seasonCheck = true;
    });

    layout->addWidget(label);
    layout->addWidget(seasons);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);

    ui->seasonButton->setEnabled(false);

}


void MainWindow::on_clothesButton_clicked()
{
    order.append(2);

    QComboBox *clothes = new QComboBox();
    if(season == "Лето") {
        clothes->addItem("Футболка");
        clothes->addItem("Шорты");
        timeOfYear = "летней";
    }
    else if (season == "Зима") {
        clothes->addItem("Перчатки");
        clothes->addItem("Шапка");
        timeOfYear = "зимней";
    }
    else if (season == "Демисезон") {
        clothes->addItem("Куртка");
        clothes->addItem("Брюки");
        timeOfYear = "межсезонной";
    }
    clothes->setCurrentIndex(-1);

    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);

    QLabel *label = new QLabel("Вид " + timeOfYear + " одежды ");

    qInfo(logDebug()) << "Ввод инструкции Вид одежды ";

    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();

    connect( clothes, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentTextChanged),[=]{
    typeClothes = clothes->currentText();
    instructions[2].second = typeClothes;
    qInfo(logInfo()) << "Инструкция - " + label->text() + clothes->currentText();
    clothes->setDisabled(true);
    ui->typeOfClothesButton->setEnabled(true);
    ui->materialButton->setEnabled(true);

    typeCheck = true;
    });

    layout->addWidget(label);
    layout->addWidget(clothes);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);

    ui->clothesButton->setEnabled(false);
}


void MainWindow::on_typeOfClothesButton_clicked()
{
    order.append(3);

    fashionCheck = false;

    QComboBox *fashion = new QComboBox();
    if(typeClothes == "Футболка") {
        fashion->addItem("Классическая");
        fashion->addItem("Поло");
        fashion->addItem("Лонгслив");
        typClo = "футболок";
    }
    else if (typeClothes == "Шорты") {
        fashion->addItem("Бермуды");
        fashion->addItem("Боксеры");
        typClo = "шорт";
    }
    else if (typeClothes == "Шапка") {
        fashion->addItem("Классическая");
        fashion->addItem("Ушанка");
        typClo = "шапок";
    }
    else if (typeClothes == "Перчатки") {
        fashion->addItem("Классические");
        fashion->addItem("Укороченные");
        typClo = "перчаток";
    }
    else if (typeClothes == "Куртка") {
        fashion->addItem("Ветровка");
        fashion->addItem("Бомбер");
        fashion->addItem("Анорак");
        typClo = "курток";
    }
    else if (typeClothes == "Брюки") {
        fashion->addItem("Классические");
        fashion->addItem("Джоггеры");
        typClo = "брюк";
    }

    fashion->setCurrentIndex(-1);

    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);

    QLabel *label = new QLabel("Тип фасона " + typClo);
    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();

    qInfo(logDebug()) << "Ввод инструкции Тип фасона вида одежды ";

    connect( fashion, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentTextChanged),[=]{
    typeOfFashion = fashion->currentText();
    instructions[3].second = typeOfFashion;
    qInfo(logInfo()) << "Инструкция - " + label->text() + fashion->currentText();
    fashion->setDisabled(true);

    fashionCheck = true;
    });

    layout->addWidget(label);
    layout->addWidget(fashion);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);

    ui->typeOfClothesButton->setEnabled(false);
}


void MainWindow::on_materialButton_clicked()
{
    order.append(4);

    QComboBox *material = new QComboBox();
    if(typeClothes == "Футболка") {
        material->addItem("Хлопок");
        material->addItem("Лён");
        material->addItem("Полиэстер");
        typClo = "футболок";
    }
    else if (typeClothes == "Шорты") {
        material->addItem("Хлопок");
        material->addItem("Лён");
        material->addItem("Полиэстер");
        typClo = "шорт";
    }
    else if (typeClothes == "Шапка") {
        material->addItem("Шерсть");
        material->addItem("Акрил");
        material->addItem("Полиэстер");
        typClo = "шапок";
    }
    else if (typeClothes == "Перчатки") {
        material->addItem("Шерсть");
        material->addItem("Акрил");
        material->addItem("Замша");
        typClo = "перчаток";
    }
    else if (typeClothes == "Куртка") {
        material->addItem("Хлопок");
        material->addItem("Полиэстер");
        material->addItem("Полиамид");
        typClo = "курток";
    }
    else if (typeClothes == "Брюки") {
        material->addItem("Хлопок");
        material->addItem("Лён");
        material->addItem("Вискоза");
        material->addItem("Полиэстер");
        typClo = "брюк";
    }

    material->setCurrentIndex(-1);

    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);

    QLabel *label = new QLabel("Материал для " + typClo);
    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();

    qInfo(logDebug()) << "Ввод инструкции Вид материала ";

    connect( material, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentTextChanged),[=]{
    typeMaterial = material->currentText();
    instructions[4].second = typeMaterial;
    qInfo(logInfo()) << "Инструкция - " + label->text() + material->currentText();
    material->setDisabled(true);

    materialCheck = true;
    });

    layout->addWidget(label);
    layout->addWidget(material);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);

    ui->materialButton->setEnabled(false);
}


void MainWindow::on_mainColorButton_clicked()
{
    order.append(5);

    QPushButton *button = new QPushButton();
    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);


    QLabel *label = new QLabel("Основной цвет изделия ");
    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();

    qInfo(logDebug()) << "Ввод инструкции Выбрать основной цвет изделия";

    connect( button, static_cast<void(QPushButton::*)(bool)>(&QPushButton::clicked),[=]{
    mainColor = QColorDialog::getColor(QColor(Qt::white), this);
    instructions[5].second = mainColor.name();
    qInfo(logInfo()) << "Инструкция - " + label->text() + mainColor.name();
    button->setStyleSheet("background-color: " + mainColor.name());

    mainColCheck = true;
    });

    layout->addWidget(label);
    layout->addWidget(button);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);

    ui->mainColorButton->setEnabled(false);
}


void MainWindow::on_supColorButton_clicked()
{
    order.append(6);

    QPushButton *button = new QPushButton();
    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);


    QLabel *label = new QLabel("Цвет рисунка ");
    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();

    qInfo(logDebug()) << "Ввод инструкции Выбрать цвет рисунка";

    connect( button, static_cast<void(QPushButton::*)(bool)>(&QPushButton::clicked),[=]{
    supColor = QColorDialog::getColor(QColor(Qt::white), this);
    instructions[6].second = supColor.name();
    qInfo(logInfo()) << "Инструкция - " + label->text() + supColor.name();
    button->setStyleSheet("background-color: " + supColor.name());

    supColCheck = true;
    });

    layout->addWidget(label);
    layout->addWidget(button);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);

    ui->supColorButton->setEnabled(false);
}


void MainWindow::on_setPrintButton_clicked()
{
    order.append(7);

    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);
    QLabel *label = new QLabel("Рисунок на изделии ");
    QPushButton *button = new QPushButton();

    qInfo(logDebug()) << "Ввод инструкции Выбрать рисунок на изделии";

    connect( button, static_cast<void(QPushButton::*)(bool)>(&QPushButton::clicked),[=]{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Изображения(*.png *.jpg *.jpeg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть изображение"),
                                                    "C:/Users/user/Documents/TailorCode/img",
                                                    tr("Файлы изображений(*.png *.jpg *.jpeg)"));
    if(!filename.isEmpty())
    {
        QPixmap Pixmap(filename);
        QIcon buttonIcon(Pixmap);
        button->setIcon(buttonIcon);
        button->setIconSize(QSize(75, 75));
        button->setFixedSize(QSize(75, 75));
        qInfo(logInfo()) << "Инструкция - " + label->text() + filename;
        picture = filename;
        instructions[7].second = filename;
        picCheck = true;
    }
    });

    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();

    layout->addWidget(label);
    layout->addWidget(button);
    widget->setLayout(layout);
    item->setSizeHint(QSize(100, 100));
    ui->codeListWidget->setItemWidget(item, widget);
    ui->setPrintButton->setEnabled(false);

    ui->supColorButton->setEnabled(true);
}


void MainWindow::on_countButton_clicked()
{
    order.append(8);

    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);
    QLabel *label = new QLabel("Количество производимых изделий ");
    QLabel *label1 = new QLabel("шт.");

    QSpinBox *spinBox = new QSpinBox();
    spinBox->setMinimum(1);
    spinBox->setMaximum(999);
    spinBox->setValue(0);
    spinBox->clear();

    countCheck = false;

    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();

    qInfo(logDebug()) << "Ввод инструкции Количество производимых изделий";

    connect( spinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=]{
    count = spinBox->text();
    instructions[8].second = count;
    qInfo(logInfo()) << label->text() + count;

    countCheck = true;
    });

    layout->addWidget(label);
    layout->addWidget(spinBox);
    layout->addWidget(label1);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);

    ui->countButton->setEnabled(false);
}


void MainWindow::on_productionButton_clicked()
{
    bool allCheck = (seasonCheck && typeCheck && fashionCheck && materialCheck && mainColCheck && picCheck &&
            supColCheck && countCheck) || (seasonCheck && typeCheck && fashionCheck && materialCheck &&
            mainColCheck && ui->setPrintButton->isEnabled() && countCheck);

    if (!seasonCheck) {
        QMessageBox::critical(this, "Внимание","Сезон одежды не выбран! Требуется выбор.");
        qCritical(logCritical()) << "Сообщение Сезон одежды не выбран";
    }
    if (!typeCheck) {
        QMessageBox::critical(this, "Внимание","Вид " + timeOfYear + " одежды не выбран! Требуется выбор.");
        qCritical(logCritical()) << "Сообщение Вид одежды не выбран";
    }
    if (!fashionCheck) {
        QMessageBox::critical(this, "Внимание","Тип фасона " + typClo + " не выбран! Требуется выбор.");
        qCritical(logCritical()) << "Сообщение Тип фасона не выбран";
    }
    if (!materialCheck) {
        QMessageBox::critical(this, "Внимание","Материал для " + typClo + " не выбран! Требуется выбор.");
        qCritical(logCritical()) << "Сообщение Материал не выбран";
    }
    if (!mainColCheck) {
        QMessageBox::critical(this, "Внимание","Основной цвет изделий не выбран! Требуется выбор.");
        qCritical(logCritical()) << "Сообщение Основной цвет не выбран";
    }
    if (!picCheck && !ui->setPrintButton->isEnabled()) {
        QMessageBox::critical(this, "Внимание","Рисунок не выбран! Требуется выбор.");
        qCritical(logCritical()) << "Сообщение Рисунок не выбран";
    }
    if (picCheck && !supColCheck) {
        QMessageBox::critical(this, "Внимание","Цвет рисунка не выбран. Требуется выбор.");
        qCritical(logCritical()) << "Сообщение Цвет рисунков не выбран";
    }
    if (!countCheck) {
        QMessageBox::critical(this, "Внимание","Количество производимых изделий не указано. Требуется ввести.");
        qCritical(logCritical()) << "Сообщение Количество производимых изделий не указано";
    }

    if (allCheck) {

    order.append(9);

        QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);
        QLabel *label = new QLabel("Запуск в производство");
        QHBoxLayout *layout = new QHBoxLayout();
        QWidget *widget = new QWidget();
        layout->addWidget(label);
        widget->setLayout(layout);
        item->setSizeHint(widget->sizeHint());
        ui->codeListWidget->setItemWidget(item, widget);

        ui->productionButton->setEnabled(false);

        ui->setPrintButton->setDisabled(true);

        ui->endButton->setEnabled(true);

        qInfo(logDebug()) << "Ввод инструкции Пуск в производство";
    }
}


void MainWindow::on_endButton_clicked()
{
    order.append(10);

    QListWidgetItem *item = new QListWidgetItem(ui->codeListWidget);
    QLabel *label = new QLabel("Конец технологии");
    QHBoxLayout *layout = new QHBoxLayout();
    QWidget *widget = new QWidget();
    layout->addWidget(label);
    widget->setLayout(layout);
    item->setSizeHint(widget->sizeHint());
    ui->codeListWidget->setItemWidget(item, widget);
    ui->endButton->setEnabled(false);

    ui->clothesButton->setEnabled(false);
    ui->countButton->setEnabled(false);
    ui->endButton->setEnabled(false);
    ui->mainColorButton->setEnabled(false);
    ui->materialButton->setEnabled(false);
    ui->supColorButton->setEnabled(false);
    ui->setPrintButton->setEnabled(false);
    ui->countButton->setEnabled(false);

    qInfo(logDebug()) << "Ввод инструкции Конец инструкций";
}


void MainWindow::on_deleteMenu_triggered()
{
    ui->codeListWidget->clear();

    qInfo(logDebug()) << "Исполнение функции Удалить всё";

    seasonCheck = false;
    typeCheck = false;
    fashionCheck = false;
    materialCheck = false;
    mainColCheck = false;
    supColCheck = false;
    picCheck = false;

    season = "";
    typeOfFashion = "";
    typeMaterial = "";
    typeClothes = "";
    mainColor = "";
    supColor = "";
    picture = "";
    count = "";

    timeOfYear = "";
    typClo = "";

    for (int i = 0; i < instructions.size(); i++) {
        instructions[i].second = "";
    }

    ui->beginButton->setEnabled(true);
    ui->clothesButton->setEnabled(false);
    ui->countButton->setEnabled(false);
    ui->mainColorButton->setEnabled(false);
    ui->materialButton->setEnabled(false);
    ui->supColorButton->setEnabled(false);
    ui->setPrintButton->setEnabled(false);
    ui->productionButton->setEnabled(false);
    ui->endButton->setEnabled(false);
    ui->typeOfClothesButton->setEnabled(false);

    order.clear();

    for (int i = 0; i < instructions.size(); i++) {
        instructions[i].second = "";
    }

    qInfo(logInfo()) << "Поле с инструкциями отчищено";
}


void MainWindow::on_executeMenu_triggered()
{
    qInfo(logDebug()) << "Исполнение функции Выполнить";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("Text Files(*.tcod)"));

    if(fileName != ""){
        QFile file(fileName);

        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this, tr("Error"), tr("Could not create file"));
            return;
        }
        QTextStream stream(&file);
        for(int i = 0; i < order.size(); i++){
            if ((order.at(i)) > 0 && (order.at(i)) < 9)
            stream << instructions[order.at(i)].first + instructions[order.at(i)].second << endl;
            else stream << instructions[order.at(i)].first << endl;
        }
    }
    qInfo(logInfo()) << "Выполнение совершено, файл с инструкциями " + fileName +" сохранён" ;
}

