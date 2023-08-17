#ifndef CREATEVCF_H
#define CREATEVCF_H
#include <qstringlist.h>
#include <QDialog>
#include <iostream>

namespace Ui {
class CreateVCF;
}

class CreateVCF : public QDialog
{
    Q_OBJECT

public:
    explicit CreateVCF(QWidget *parent = nullptr);
    ~CreateVCF();

private slots:
    void on_backButton_clicked();

    void on_addNumberButton_clicked();

    void on_numberEntry_textChanged();

    void on_saveButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::CreateVCF *ui;

    QString firstLetterToUpperCase(QString str);

    QString removeDoubleSpaces(QString name);

public:
    QStringList numberList = {};
    int counterNum = 0;
};

#endif // CREATEVCF_H
