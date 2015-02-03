#include "browsertab.h"
#include "ui_browsertab.h"
#include <QTimer>
#include <QMessageBox>

#include <QDebug>


BrowserTab::BrowserTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BrowserTab)
{
    ui->setupUi(this);
    tabWidget = (QTabWidget*) parent;
    urlList = new QStringList;
    ui->progressbar->setMinimum(0);
    ui->progressbar->setMaximum(100);
    ui->progressbar->setValue(100);

    /* http://stackoverflow.com/questions/13327818/how-to-prevent-the-default-blue-border-being-drawn-on-qlineedit-focus */
    ui->urlInput->setAttribute(Qt::WA_MacShowFocusRect, 0);

    connect(ui->btnNewTab, SIGNAL(clicked()), this, SLOT(createAndSwitchTab()));
    connect(ui->btnRemoveTab, SIGNAL(clicked()), this, SLOT(removeTab()));
    connect(ui->urlInput, SIGNAL(returnPressed()), this, SLOT(evaluteUrlField()));
    connect(ui->btnBack, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(ui->btnForward, SIGNAL(clicked()), this, SLOT(goForward()));
    connect(ui->webView, SIGNAL(loadStarted()), this, SLOT(onLoadStarted()));
    connect(ui->webView, SIGNAL(loadProgress(int)), this, SLOT(onLoadProgress(int)));
    connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
    connect(ui->webView, SIGNAL(linkClicked(QUrl)), this, SLOT(evaluateClickedLink(QUrl)));
    connect(ui->webView, SIGNAL(titleChanged(QString)), this, SLOT(setTitle(QString)));

    /* make sure we get url-input focus. Required because just setFocus will not work
     * because the widget isn't fully constructed yet
     * see http://stackoverflow.com/questions/526761/set-qlineedit-focus-in-qt
     */
    QTimer::singleShot(0, ui->urlInput, SLOT(setFocus()));    
}

void BrowserTab::createAndSwitchTab()
{
    int newIndex = this->tabWidget->addTab(new BrowserTab(tabWidget), BrowserTab::INITIAL_TITLE);
    this->tabWidget->setCurrentIndex(newIndex);
}

void BrowserTab::removeTab()
{
    checkLoading();
    if (tabWidget->count() > 1)
    {
        this->tabWidget->removeTab(this->tabWidget->currentIndex());
        this->destroy();
    }
}

void BrowserTab::evaluteUrlField()
{
    checkLoading();
    currentUrlIndex++;
    QString url = ui->urlInput->text();
    if (url.startsWith("http") == false)
    {
        url = "http://" + url;
        ui->urlInput->setText(url);
    }
    urlList->append(url); /* FIXME we don't limit the number of stored URLs */
    ui->webView->load(url);
}

void BrowserTab::evaluateClickedLink(QUrl url)
{
    checkLoading();
    qDebug() << "clicked " << url.toString();
    urlList->append(url.toString());
    ui->urlInput->setText(url.toString());
    evaluteUrlField();
}

void BrowserTab::onLoadStarted()
{
    isLoading = true;
    ui->statusLabel->setText("Loading...");
    ui->progressbar->setValue(0);    
}

void BrowserTab::onLoadProgress(int progress)
{
    qDebug() << progress;
    ui->progressbar->setValue(progress);
}

void BrowserTab::onLoadFinished(bool success)
{
    ui->statusLabel->setText(success ? "Ready" : "Failed");
    ui->progressbar->setMaximum(1);
    ui->progressbar->setValue(1);

    if (success)
        setTitle(ui->webView->title());

    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    ui->webView->show();
    isLoading = false;
}

void BrowserTab::goBack()
{
    checkLoading();
    if (urlList->size() > 1 && currentUrlIndex > 0)
    {
        QString newUrl = urlList->at(++currentUrlIndex);
        qDebug() << "going back to URL " << newUrl;
        qDebug() << "URLs left befor the after the current one: " << (urlList->size() - currentUrlIndex);
        ui->urlInput->setText(newUrl);
        this->evaluteUrlField();
    }
}

void BrowserTab::goForward()
{
    if (urlList->size() > 1 && currentUrlIndex < (urlList->size() - 1)) {
        QString newUrl = urlList->at(--currentUrlIndex);
        qDebug() << "moving forwart to URL " << newUrl;
        qDebug() << "URLs left befor the current one: " << currentUrlIndex;
        ui->urlInput->setText(newUrl);
        this->evaluteUrlField();
    }
}

void BrowserTab::setTitle(QString title)
{
    tabWidget->setTabText(tabWidget->currentIndex(), title);
}

void BrowserTab::checkLoading()
{
    if (isLoading)
    {
        ui->webView->stop();
        isLoading = false;
    }
}

BrowserTab::~BrowserTab()
{
    delete ui;
}

QString BrowserTab::INITIAL_TITLE = QString("Welcome");
