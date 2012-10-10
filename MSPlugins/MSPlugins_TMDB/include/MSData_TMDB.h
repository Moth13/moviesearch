#ifndef MSDATA_TMDB_H
#define MSDATA_TMDB_H

#include <MSDataMovie.h>
#include <MSDataPerson.h>

namespace Data
{
    class MSDataImage_TMDB : public MSDataImage
    {
            Q_OBJECT

            Q_PROPERTY(QString file_path READ getImageFile WRITE setImageFile)
            Q_PROPERTY(QString iso_639_1 READ getIso WRITE setIso)
            Q_PROPERTY(float aspect_ratio READ getAspectRatio WRITE setAspectRatio)
            Q_PROPERTY(int height READ getHeight WRITE setHeight)
            Q_PROPERTY(int width READ getWidth WRITE setWidth)

        public:
            explicit MSDataImage_TMDB( QObject* parent = NULL ) : MSDataImage( parent ){ m_strClassName = "MSDataImage_TMDB"; }
            ~MSDataImage_TMDB(){}
    };

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

    class MSMovieCast_TMDB : public MSMovieCast
    {
            Q_OBJECT

            Q_PROPERTY(QString character READ getCharacterName WRITE setCharacterName)
            Q_PROPERTY(QString name READ getActorName WRITE setActorName)
            Q_PROPERTY(QString profile_path READ getActorImage WRITE setActorImage)
            Q_PROPERTY(int id READ getActorID WRITE setActorID)
            Q_PROPERTY(int order READ getCastPos WRITE setCastPos)

        public:
            explicit MSMovieCast_TMDB( QObject* parent = NULL ) : MSMovieCast( parent ){ m_strClassName = "MSMovieCast_TMDB"; }
            ~MSMovieCast_TMDB(){}
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

    class MSPersonCredits_TMDB : public MSPersonCredits
    {
            Q_OBJECT

            Q_PROPERTY(QString character READ getCharacterName WRITE setCharacterName)
            Q_PROPERTY(QString original_title READ getMovieOriTitle WRITE setMovieOriTitle)
            Q_PROPERTY(QString poster_path READ getMoviePosterPath WRITE setMovePosterPath)
            Q_PROPERTY(QString title READ getMovieTitle WRITE setMovieTitle)
            Q_PROPERTY(QDate release_date READ getMovieReleaseDate WRITE setMovieReleaseDate)
            Q_PROPERTY(int id READ getMovieID WRITE setMovieID)

        public:
            explicit MSPersonCredits_TMDB( QObject* parent = NULL ) : MSPersonCredits( parent ){ m_strClassName = "MSPersonCredits_TMDB"; }
            ~MSPersonCredits_TMDB(){}
    };
}

#endif // MSDATA_TMDB_H
