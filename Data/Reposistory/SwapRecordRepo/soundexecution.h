#ifndef SOUNDEXECUTION_H
#define SOUNDEXECUTION_H
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QObject>
#include <QTimer>
#include <QList>
#include "Data/Datasource/soundsDatasource.h"
#include <QUrl>
typedef enum STATE_PLAYER{
    STATE_PLAYER_PLAYING,
    STATE_PLAYER_DONE
} STATE_PLAYER;

class SoundExecution : public QObject
{
    Q_OBJECT
private:
    STATE_PLAYER statePlayer;
    QMediaPlaylist* list;
    QMediaPlayer* player;

private:
    void stop();
    void pause();
    QMediaPlaylist* getList();

public:
    explicit SoundExecution(QObject *parent = nullptr);

    STATE_PLAYER getStatePlayer();
    static SoundExecution* getSoundExecution();
    void play(const QList<QUrl>& list);
    void play(const QUrl& url);
    QMediaPlayer* getPlayer();


};

#endif // SOUNDEXECUTION_H
