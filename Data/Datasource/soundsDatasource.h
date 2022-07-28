#ifndef SOUNDSDATASOURCE_H
#define SOUNDSDATASOURCE_H
#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#define CAB_NUMBER_1 QUrl("qrc:/sounds/UI/sound/voices/1.mp3")
#define CAB_NUMBER_2 QUrl("qrc:/sounds/UI/sound/voices/2.mp3")
#define CAB_NUMBER_3 QUrl("qrc:/sounds/UI/sound/voices/3.mp3")
#define CAB_NUMBER_4 QUrl("qrc:/sounds/UI/sound/voices/4.mp3")
#define CAB_NUMBER_5 QUrl("qrc:/sounds/UI/sound/voices/5.mp3")
#define CAB_NUMBER_6 QUrl("qrc:/sounds/UI/sound/voices/6.mp3")
#define ASSIGN_BAT_TIMEOUT QUrl("qrc:/sounds/UI/sound/voices/bat-assign-timeout.mp3")
#define RETURN QUrl ("qrc:/sounds/UI/sound/voices/bat-assign-timeout.mp3")
#define OPEN_DOOR QUrl("qrc:/sounds/UI/sound/voices/open-door.mp3")
#define BAT_RUN_OUT QUrl("qrc:/sounds/UI/sound/voices/bat-run-out.mp3")
#define THANK_YOU_USING_SERVICE QUrl("qrc:/sounds/UI/sound/voices/thank-for-sevice.mp3")
#define BP_VIEW QUrl("qrc:/sounds/UI/sound/voices/bpview.mp3")
#define CHECKING_BAT QUrl("qrc:/sounds/UI/sound/voices/checking-battery.mp3")
#define CLOSE_DOOR QUrl("qrc:/sounds/UI/sound/voices/close-door.mp3")
#define CONTINUE QUrl("qrc:/sounds/UI/sound/voices/continue.mp3")
#define LOGIN_VIEW QUrl("qrc:/sounds/UI/sound/voices/login-view.mp3")
#define PUT_BAT_IN_CAB QUrl("qrc:/sounds/UI/sound/voices/put-pin-into-cab.mp3")
#define SUCCESS_SWAP_RECEIVE QUrl("qrc:/sounds/UI/sound/voices/suceess-swap-recervie-pin-number.mp3")
#define USER_VIEW QUrl("qrc:/sounds/UI/sound/voices/userview.mp3")
#define WRONG_PASS QUrl("qrc:/sounds/UI/sound/voices/wrong-pass.mp3")
const QList<QUrl> cabNumberSound = {CAB_NUMBER_1, CAB_NUMBER_2, CAB_NUMBER_3, CAB_NUMBER_4, CAB_NUMBER_5, CAB_NUMBER_6};
#endif // SOUNDSDATASOURCE_H
