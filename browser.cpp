/*
 * (c) 2014-205 Sam Nazarko
 * email@samnazarko.co.uk
 */

#include "browser.h"
#include "ui_browser.h"
#include <QDebug>

browser::browser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::browser)
{
    ui->setupUi(this);
    connect(ui->urlBar, SIGNAL(returnPressed()), this, SLOT(handleUrl()));
}

browser::~browser()
{
    delete ui;
}

void browser::handleUrl()
{
    qDebug() << ui->urlBar->text();
    if (ui->tabWidget->currentIndex() == 0)
    {
        qDebug() << "tab1 is active!";
        ui->webView1->load(QUrl(ui->urlBar->text()));
    } else
    {
        qDebug() << "tab2 is active";
        ui->webView2->load(QUrl(ui->urlBar->text()));
    }
}
