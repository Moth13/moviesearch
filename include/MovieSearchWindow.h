#ifndef MOVIESEARCHWINDOW_H
#define MOVIESEARCHWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>

class MovieSearchWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MovieSearchWindow(QWidget *parent = 0);

        ~MovieSearchWindow();

    signals :
        void requestLaunch( const QString& _strRequest );
        void selectionDone( const QString& _strSelection );

    public slots:
        void screenSearchResult( const QStringList & _lResults );

    private:
      QPushButton *                   m_pLaunchSearchButton;    //<
      QLabel *                        m_pSearchText;            //<
      QTextEdit *                     m_pSearchEdit;            //<
      QListWidget *                   m_pSearchResultList;      //<

    private slots :
        void launchButtonPressed();

};

#endif // MOVIESEARCHWINDOW_H
