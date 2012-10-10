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
    class MSPersonSearchResult;
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
            QCompleter*                     m_pCompleter;
            QStandardItemModel*             m_pCompleterModel;
            QList< MSTabInfo* >             m_lpTabsInfo;               ///< Opened tabs

            Tools::MSSearchEngine*          m_xpCurrentSearchEngine;    ///< Current search engine
            QMap< QString, Data::MSData* >  m_mDataSearchResult;       ///< Search result
            QMap< uint, QStandardItem* >    m_mQueryImage;

            uint                            m_uiLastQueryID;

            //------------------------------------------------------//
            // Tools
            /*! \brief UI to search engine*/
            void connectToSearchEngine( Tools::MSSearchEngine* _pSearchEngine = NULL );

            void cleanResults();
            //------------------------------------------------------//

        private slots:
            //------------------------------------------------------//
            // Search engine slot
            /*! sigMoviesFromTitleFound handler slot */
            void onMoviesFromTitleFound( uint _uiQueryID, QList< Data::MSMovieSearchResult* > _lpResults );
            /*! sigPersonsFromNameFound handler slot */
            void onPersonsFromNameFound( uint _uiQueryID, QList< Data::MSPersonSearchResult* > _lpResults );

            /*! sigImageFound handler slot */
            void onImageFound( uint _uiQueryID, QPixmap* _pPixmap );
            //------------------------------------------------------//

            //------------------------------------------------------//
            // UI slot
            void on_SearchFor_TextEdit_returnPressed();
            void on_lTabInfo_Widget_tabCloseRequested(int index);
            void on_actionClose_triggered();
            void on_actionAbout_MovieSearch_triggered();
            void on_SearchFor_TextEdit_textEdited(const QString &arg1);
            void on_SearchEngine_Combox_activated(int index);
            //------------------------------------------------------//
    };
}

#endif // MSMAINWINDOW_H
