/*
 * MSTabInfo.h
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#ifndef MSTABINFO_H
#define MSTABINFO_H

#include <QtCore>
#include <QtGui>

class MSImage;

namespace Ui
{
    class MSTabInfo;
}

namespace Tools
{
    class MSSearchEngine;
}

namespace Data
{
    class MSData;
    class MSDataImage;
    class MSMovieInfo;
    class MSMovieCast;
    class MSPersonInfo;
}

namespace UI
{
    class MSTabInfo : public QWidget
    {
            Q_OBJECT
        public:
            /*! Constructor */
            explicit MSTabInfo(QWidget *parent = 0);
            /*! Destructor */
            virtual ~MSTabInfo();

            //------------------------------------------------------//
            // Tools
            /*! \return true if has a data */
            bool hasData() const;
            /*! \return Current screen data */
            const Data::MSData& getCurrentData() const;
            /*! Set associate queryID */
            void setQueryID( uint _uiQueryID );
            /*! Set search engine */
            void setSearchEngine( Tools::MSSearchEngine* _xpSearchEngine = NULL );
            //------------------------------------------------------//

        private:
            //------------------------------------------------------//
            // Attributs
            Ui::MSTabInfo*              m_pUI;
            Data::MSData*               m_pData;
            Tools::MSSearchEngine*      m_xpSearchEngine;
            uint                        m_uiDataQueryID;
            uint                        m_uiCastQueryID;
            uint                        m_uiImagesQueryID;
            QList< Data::MSMovieCast* > m_lpMovieCast;
            QList< MSImage* >           m_lpImages;
            QMap< uint, MSImage* >      m_mQueryImage;
            QMap< uint, QTableWidgetItem* > m_mQueryIcon;
            //------------------------------------------------------//

            //------------------------------------------------------//
            // Tools
            void setContent( const Data::MSData& rMSData );
            //------------------------------------------------------//

        private slots :
            /*! sigMovieBasicInfoFound handler slot */
            void onMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie );
            /*! sigMovieCastFound handler slot */
            void onMovieCastFound( uint _uiQueryID, QList< Data::MSMovieCast* > _lpMovie );
            /*! sigPersonBasicInfoFound handler slot */
            void onPersonBasicInfoFound( uint _uiQueryID, Data::MSPersonInfo* _pPerson );
            /*! sigDataImagesFound handler slot */
            void onDataImagesFound( uint _uiQueryID, QList< Data::MSDataImage* > _lpDataImage );
            /*! sigImageFound handler slot */
            void onImageFound( uint _uiQueryID, QPixmap* _pPixmap );

            void on_listView_doubleClicked(const QModelIndex &index);
    };
}
#endif // MSTABINFO_H
