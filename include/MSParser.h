/*
 * MSParser.h
 *
 * Author(s):
 * - Jeremie GUERINEL
 *
 * Created 2012-9-17
 */

#ifndef MSPARSER_H
#define MSPARSER_H

#include <QtCore>

class MSMovieInfo;

class MSParser
{
    public :
        QHash< int, QString > parseContentToResultList( const QByteArray& _rstrContent );
        MSMovieInfo* parseContentToMovie( const QByteArray& _rstrContent );

        MSParser();
        ~MSParser();
};

#endif // MSPARSER_H
