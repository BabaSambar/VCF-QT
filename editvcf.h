#ifndef EDITVCF_H
#define EDITVCF_H

#include <QDialog>

namespace Ui {
class editvcf;
}

class editvcf : public QDialog
{
    Q_OBJECT

public:
    explicit editvcf(QWidget *parent = nullptr);
    ~editvcf();

private:
    Ui::editvcf *ui;
};

#endif // EDITVCF_H
