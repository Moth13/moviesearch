/*
 * MSMainwindow.h
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#ifndef MSMAINWINDOW_H
#define MSMAINWINDOW_H

#include <QtGui>
#include <QtNetwork>

namespace Ui
{
    class MSMainWindow;
}

namespace Data
{
    class MSData;
    class MSMovieSearchResult;
    class MSMovieInfo;
}

namespace Tools
{
    class MSSearchEngine;
}

namespace UI
{
    class MSTabInfo;

    /*! \class Describing main UI */
    class MSMainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        /*! Constructor */
        explicit MSMainWindow( QWidget *_pParent = NULL );
        /*! Destructor */
        virtual ~MSMainWindow();

    private:
        Ui::MSMainWindow *              m_pUI;
        QList< MSTabInfo* >             m_lpTabsInfo;               ///< Opened tabs

        Tools::MSSearchEngine*          m_xpCurrentSearchEngine;    ///< Current search engine
        QList< Data::MSData* >          m_lpDataSearchResult;       ///< Search result

        uint                            m_uiLastQueryID;

        //------------------------------------------------------//
        // Tools
        /*! \brief UI to search engine*/
        void connectToSearchEngine( Tools::MSSearchEngine* _pSearchEngine = NULL );
        //------------------------------------------------------//

    private slots:
        //------------------------------------------------------//
        // Search engine slot
        /*! sigMoviesFromTitleFound handler slot */
        void onMoviesFromTitleFound( uint _uiQueryID, QList< Data::MSMovieSearchResult* > _lpResults );
        /*! sigMoviesFromTitleFound handler slot */
        void onMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie );
        //------------------------------------------------------//

        //------------------------------------------------------//
        // UI slot
        void on_SearchFor_TextEdit_returnPressed();

        void on_lTabInfo_Widget_tabCloseRequested(int index);

        void on_actionClose_triggered();

        void on_actionAbout_MovieSearch_triggered();

        void on_History_View_itemDoubleClicked(QListWidgetItem *item);
        //------------------------------------------------------//
    };
}

#endif // MSMAINWINDOW_H
