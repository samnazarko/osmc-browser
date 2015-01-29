/*
 * (c) 2014-205 Sam Nazarko
 * email@samnazarko.co.uk
 */

#include "browser.h"
#include "ui_browser.h"

browser::browser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::browser)
{
    ui->setupUi(this);
}

browser::~browser()
{
    delete ui;
}
