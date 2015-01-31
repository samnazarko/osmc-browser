/*
 * (c) 2014-205 Sam Nazarko
 * email@samnazarko.co.uk
 */

#include "browser.h"
#include "ui_browser.h"
#include <QDebug>
#include <QPushButton>
#include <QRect>
#include <QWebView>
#include <QTabWidget>
#include "browsertab.h"

browser::browser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::browser)
{
    ui->setupUi(this);
    /* first, remove all tabs, coming from the ui designer. */
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    /* now add our initial tab */
    ui->tabWidget->addTab(new BrowserTab(ui->tabWidget), BrowserTab::INITIAL_TITLE);
}

browser::~browser()
{
    delete ui;
}
