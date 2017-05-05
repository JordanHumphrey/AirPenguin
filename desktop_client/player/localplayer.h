/*This file is part of AirPenguin.

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

#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMainWindow>
#include <QMouseEvent>

#include "vlc/args.h"
#include "vlc/mediaplayer.h"
#include "qtinterface/volumeslider.h"
#include "qtinterface/scrubber.h"
#include "qtinterface/playbutton.h"
#include "qtinterface/stopbutton.h"
#include "qtinterface/mutebutton.h"
#include "qtinterface/fullscreenbutton.h"
#include "qtinterface/videoframe.h"

class QWidget;
class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class LocalPlayer : public QWidget
{
    Q_OBJECT

public:

    explicit LocalPlayer(QString &filePath, VlcArgs *args, bool autoPlay, bool stream, QWidget *parent = 0);

    ~LocalPlayer();

signals:

    void playerClosed();

public slots:

   void toggleFullscreen();

private:

    void initQtPlayer();

    VlcInstance         *_instance;
    VlcMedia            *_media;
    VlcMediaPlayer      *_player;
    QString              _filePath;

    VlcArgs             *_args;
    QtVolumeSlider      *_volSlider;
    QtPositionScrubber  *_posScrubber;
    QtPlayButton        *_playButton;
    QtStopButton        *_stopButton;
    QtMuteButton        *_muteButton;
    QtFullscreenButton  *_fsButton;

    QtVideoFrame        *_videoFrame;

    bool                 _autoPlay;
    bool                 _stream;

    };

#endif // PLAYER_H
