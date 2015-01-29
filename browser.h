/*
 * (c) 2014-205 Sam Nazarko
 * email@samnazarko.co.uk
 */

#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>

namespace Ui {
class browser;
}

class browser : public QMainWindow
{
    Q_OBJECT

public:
    explicit browser(QWidget *parent = 0);
    ~browser();

private:
    Ui::browser *ui;

private slots:
    void handleUrl();
};

#endif // BROWSER_H
