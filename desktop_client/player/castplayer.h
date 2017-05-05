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

#ifndef CASTPLAYER_H
#define CASTPLAYER_H

#include <QWidget>
#include <QDockWidget>
#include <QMainWindow>
#include <QPainter>

#include "vlc/args.h"
#include "vlc/mediaplayer.h"
#include "qtinterface/volumeslider.h"
#include "qtinterface/scrubber.h"
#include "qtinterface/playbutton.h"
#include "qtinterface/stopbutton.h"

class QWidget;
class VlcArgs;
class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class CastPlayer : public QDockWidget
{
    Q_OBJECT

public:

    explicit CastPlayer(QString filePath, VlcArgs *args, bool autoPlay, QWidget *parent = 0);

    ~CastPlayer();

signals:

    void playerClosed();

private:

    void initQtPlayer(VlcArgs *args);

    void paintEvent(QPaintEvent *event);

    VlcInstance         *_instance;
    VlcMedia            *_media;
    VlcMediaPlayer      *_player;
    QString              _filePath;
    QWidget             *_layout;
    //QtPositionScrubber  *_posScrubber;
    QtPlayButton        *_playButton;
    QtStopButton        *_stopButton;

    QtVideoFrame        *_videoFrame;

    bool                 _autoPlay;
};


#endif // CASTPLAYER_H
