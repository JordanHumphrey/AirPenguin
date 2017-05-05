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

#ifndef PENGUINVIEW_H
#define PENGUINVIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QFileDialog>
#include <QTimer>
#include <QSharedPointer>
#include <QMovie>
#include <QFontDatabase>
#include <QSystemTrayIcon>

#include "qtinterface/error.h"
#include "vlc/args.h"
#include "vlc/mediaplayer.h"
#include "vlc/media.h"
#include "vlc/vlcinstance.h"

namespace Ui {
class PenguinView;
}

class PenguinView : public QMainWindow
{
    Q_OBJECT

public:
    explicit PenguinView(QWidget *parent = 0);
    ~PenguinView();

signals:
    void changeStackedWidgetIndex(int);



public slots:

    void playerDeleted();

private slots:
   void on_pushButtonLoad_clicked();

   void on_pushButtonCast_clicked();

   void on_playLocalButton_clicked();

   void on_pushButtonAbout_clicked();

   void on_pushButtonBrowse_clicked();

   void on_lineEditStream_returnPressed();

   void on_actionLight_Theme_triggered();

   void on_actionContact_triggered();

   void on_actionDark_Theme_triggered();

   void on_actionOn_triggered();

   void set_button_icon(int frame);

   void dragEnterEvent(QDragEnterEvent *E);

   void dropEvent(QDropEvent *E);

   void paintEvent(QPaintEvent *event);

   void on_AutoLaunchOn_triggered();

   void trayIconClicked();

   QString clientIp();

private:

    Ui::PenguinView         *_ui;

    QString                  _filePath;
    QSystemTrayIcon          *_trayIcon;

    VlcArgs                 *_castArgs;
    VlcArgs                 *_localArgs;

    QMovie                  *_movie;

    QWidget                 *_playerWidget = Q_NULLPTR;

    bool                     _autoPlay = false;
    bool                     _autoLaunch = false;

    bool updateDeviceList();
};

#endif // PENGUINVIEW_H
