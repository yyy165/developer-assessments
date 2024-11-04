#ifndef ITEMFORM_H
#define ITEMFORM_H

#include <QMainWindow>
#include <opedb.h>

namespace Ui {
class itemform;
}

class itemform : public QMainWindow
{
    Q_OBJECT

public:
    explicit itemform(QWidget *parent = nullptr);
    ~itemform();
    void setInfo(int id, dev info);
private:
    Ui::itemform *ui;
};

#endif // ITEMFORM_H
