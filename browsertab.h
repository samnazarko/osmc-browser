#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include <QWidget>
#include <QTabWidget>
#include <QUrl>

namespace Ui {
class BrowserTab;
}

class BrowserTab : public QWidget
{
    Q_OBJECT

public:
    static QString INITIAL_TITLE;
    explicit BrowserTab(QWidget *parent = 0);
    ~BrowserTab();

private:
    Ui::BrowserTab *ui;
    QTabWidget* tabWidget;
    QStringList* urlList;
    int currentUrlIndex = -1;
    bool isLoading = false;

private slots:
    void createAndSwitchTab();
    void removeTab();
    void evaluteUrlField();
    void goBack();
    void goForward();
    void evaluateClickedLink(QUrl url);
    void onLoadStarted();
    void onLoadProgress(int progress);
    void onLoadFinished(bool success);
    void setTitle(QString title);
};
#endif // BROWSERTAB_H
