#ifndef HOME_H
#define HOME_H

#include <QWidget>

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

private:
    Ui::home *ui;
};
#endif // HOME_H
