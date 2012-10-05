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
#include <QMovie>

namespace Ui
{
    class MSTabInfo;
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
            //------------------------------------------------------//

        private:
            Ui::MSTabInfo*              m_pUI;
            Data::MSData*               m_pData;

            QMovie*                     m_pWaitingAnimation;

            //------------------------------------------------------//
            // Tools
            void setContent( const Data::MSData& rMSData );
            //------------------------------------------------------//

        private slots :
            /*! sigMoviesFromTitleFound handler slot */
            void onMovieBasicInfoFound( uint _uiQueryID, Data::MSMovieInfo* _pMovie );
    };
}
#endif // MSTABINFO_H
