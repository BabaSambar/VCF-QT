#include "vcf.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VCF w;
    w.show();
    return a.exec();

}
