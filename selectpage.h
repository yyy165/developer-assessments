#ifndef SELECTPAGE_H
#define SELECTPAGE_H

#include <QWidget>

namespace Ui {
class selectPage;
}

class selectPage : public QWidget
{
    Q_OBJECT

public:
    explicit selectPage(QWidget *parent = nullptr);
    ~selectPage();

signals:
    void nameInfoReady(const QString &name);

private slots:
    void on_clearBt_clicked();

    void on_selectBt_clicked();

private:
    Ui::selectPage *ui;
};

#endif // SELECTPAGE_H
