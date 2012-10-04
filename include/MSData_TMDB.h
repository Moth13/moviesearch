#ifndef MSDATA_TMDB_H
#define MSDATA_TMDB_H

#include <MSData.h>

namespace Data
{

    class MSMovieInfo_TMDB: public MSMovieInfo
    {
            Q_OBJECT

            Q_PROPERTY(QString title READ getTitle WRITE setTitle)
            Q_PROPERTY(QString original_title READ getOrignalTitle WRITE setOriTitle)
            Q_PROPERTY(QString tagline READ getTagline WRITE setTagline)
            Q_PROPERTY(QString overview READ getOverview WRITE setOverview)
            Q_PROPERTY(QUrl homepage READ getHomepage WRITE setHomepage)
            Q_PROPERTY(QDate release_date READ getReleaseDate WRITE setReleaseDate)
            Q_PROPERTY(float vote_average READ getVoteAverage WRITE setVoteAverage)
            Q_PROPERTY(int vote_count READ getVoteCount WRITE setVoteCount)
            Q_PROPERTY(QString poster_path READ getPosterPath WRITE setPosterPath)
            Q_PROPERTY(int imdb_id READ getImdbId WRITE setImdbId)
            Q_PROPERTY(int id READ getId WRITE setId)

        public :
            explicit MSMovieInfo_TMDB( QObject* parent = NULL ) : MSMovieInfo( parent ) { m_strClassName = "MSMovieInfo_TMDB"; }
            ~MSMovieInfo_TMDB(){}
    };

    class MSPersonInfo_TMDB : public MSPersonInfo
    {
            Q_OBJECT

            Q_PROPERTY(QString name READ getName WRITE setName)
            Q_PROPERTY(QUrl homepage READ getHomepage WRITE setHomepage)
            Q_PROPERTY(QDate birthday READ getBirthday WRITE setBirthday)
            Q_PROPERTY(QDate deathday READ getDeathday WRITE setDeathday)
            Q_PROPERTY(QString place_of_birth READ getPlaceOfBirth WRITE setPlaceOfBirth)
            Q_PROPERTY(QString profile_path READ getProfilePath WRITE setProfileImagePath)
            Q_PROPERTY(int id READ getId WRITE setId)

        public:
            explicit MSPersonInfo_TMDB( QObject* parent = NULL ) : MSPersonInfo( parent ){ m_strClassName = "MSPersonInfo_TMDB"; }
            ~MSPersonInfo_TMDB(){}
    };
}

#endif // MSDATA_TMDB_H
