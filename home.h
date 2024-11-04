#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <selectpage.h>
#include <opedb.h>
#include <itemform.h>

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

    void receiveNameInfo(const QString &name);
    void receiveNationInfo(const QString &nation);
    void receiveAreaInfo(const QString &area);

private:
    Ui::home *ui;
    selectPage *sp = new selectPage;
};
#endif // HOME_H
