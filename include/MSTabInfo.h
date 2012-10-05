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
#include <QWidget>

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
    class MSMovieInfo;
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
            QMap< uint, MSImage* >      m_mQueryImage;
            //------------------------------------------------------//

            //------------------------------------------------------//
            // Tools
            void setContent( const Data::MSData& rMSData );
            //------------------------------------------------------//

        private slots :
            /*! sigMoviesFromTitleFound handler slot */
            void onMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie );
            /*! sigImageFound handler slot */
            void onImageFound( uint _uiQueryID, QPixmap* _pPixmap );
    };
}
#endif // MSTABINFO_H
