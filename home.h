#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <selectpage.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class home;
}
QT_END_NAMESPACE

class home : public QWidget
{
    Q_OBJECT

public:
    home(QWidget *parent = nullptr);
    ~home();

private slots:
    void on_closeBT_clicked();

    void on_selectNameBT_clicked();

    void on_selectNationBT_clicked();

    void on_selectAreaBT_clicked();

private:
    Ui::home *ui;
    selectPage *sp = new selectPage;
};
#endif // HOME_H
