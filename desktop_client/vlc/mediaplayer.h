/* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
 * Modified from 02.2017-05.2017 by AirPenguin team (joistjn@san.rr.com)
 * This file is part of AirPenguin.
 *
    AirPenguin is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AirPenguin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AirPenguin.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QtCore/QObject>
#include <QWidget>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtGui/qwindowdefs.h>
#include <QMouseEvent>
#include <QEvent>

#include "vlc/vlc.h"
#include "qtinterface/videoframe.h"
#include "vlc/vlcinstance.h"
#include "vlc/media.h"
#include "vlc/mediaplayer.h"
#include "vlc/audio.h"

#include "vlc/state.h"

class VlcAudio;
class VlcMedia;

class VlcMediaPlayer : public QObject
{
    Q_OBJECT

public:
    /* VlcMediaPlayer constructor */
    explicit VlcMediaPlayer(VlcInstance *instance);

    /* VlcMediaPlayer destructor */
    ~VlcMediaPlayer();

    /* Returns libvlc media player object */
    libvlc_media_player_t *libMedia_p() const;

    /* Returns libvlc instance */
    libvlc_instance_t *libInst_t() const;

    /* Return VlcInstance */
    VlcInstance *vlcInstance() const;

    /* Returns libvlc audio manager object */
    VlcAudio *audio() const;

    /* Returns current media */
    VlcMedia *currentMedia() const;

    /* Open media file or stream (needs to be playable) */
    void openAndPlay(VlcMedia *media);

    /* Open media file or stream but do not auto-play */
    void openOnly(VlcMedia *media);

    /* Open url for playback */
    void openUrl(QString url);

    /* Set video widget (for rendering) to play inside Qt interface */
    void setVideoWidget(QtVideoFrame *widget);

    /*** ACCESSORS ***/
    float position() const;

    /* Get current video widget */
    QtVideoFrame *videoWidget() const;

    /* Get current media state */
    Vlc::State state() const;

public slots:
    /* Set media position */
    void setPosition(float pos);

    /* Play media if possible */
    void play();

    /* Pause media if possible */
    void pause();

    /* Resume media playback if possible */
    void resume();

    /* Stop media if possible */
    void stop();

private:

     libvlc_media_player_t *_libvlcMediaPlayer;
     VlcInstance           *_vlcInstance;

     //QWidget *_videoWidget;
     QtVideoFrame  *_videoWidget;

     /* Window id */
     WId _currentWId;

     VlcAudio       *_audio;
     VlcMedia       *_media;

};

#endif // MEDIAPLAYER_H
