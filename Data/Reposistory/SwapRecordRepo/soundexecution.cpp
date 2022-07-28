#include "soundexecution.h"

SoundExecution::SoundExecution(QObject *parent) : QObject(parent)
{
    this->player = new QMediaPlayer();
    this->list = new QMediaPlaylist();
    this->player->setVolume(100);
}
void SoundExecution::play(const QList<QUrl> &list){
    if(getStatePlayer() == STATE_PLAYER_PLAYING) getPlayer()->stop();
    QList<QMediaContent> ls;
    for(int i =0; i < list.length();i++){
        ls<< list.at(i);
    }
    getList()->clear();
    getList()->addMedia(ls);
    getPlayer()->setPlaylist(getList());
    getPlayer()->play();
}
void SoundExecution::play(const QUrl& url){
    if(getStatePlayer() == STATE_PLAYER_PLAYING) getPlayer()->stop();
    getList()->clear();
    getList()->addMedia(url);
    getPlayer()->setPlaylist(getList());
    getPlayer()->play();
}
QMediaPlayer* SoundExecution::getPlayer(){
    return this->player;
}
QMediaPlaylist* SoundExecution::getList(){
    return this->list;
}
STATE_PLAYER SoundExecution::getStatePlayer() {
    if(getPlayer()->state() == QMediaPlayer::PlayingState)
        return STATE_PLAYER_PLAYING;
    else return STATE_PLAYER_DONE;
}
SoundExecution *SoundExecution::getSoundExecution(){
   static SoundExecution* self;
   if(self==nullptr){
       self=new SoundExecution;
   }
   return self;
}
