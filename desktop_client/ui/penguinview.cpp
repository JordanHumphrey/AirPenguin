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

#include <QString>
#include <QFile>
#include <QUrl>
#include <QDesktopServices>
#include <QWidget>
#include "vlc/args.h"
#include <iostream>
#include <string>
#include <QFontDatabase>
#include <QNetworkInterface>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QFile>
#include <QDockWidget>

#include "ui/penguinview.h"
#include "ui_penguinview.h"
#include "player/localplayer.h"
#include "player/castplayer.h"
#include "vlc/networkmanager.h"
#include "vlc/mediaplayer.h"
#include "qtinterface/error.h"

PenguinView::PenguinView(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::PenguinView)
        {

            this->setAttribute(Qt::WA_TranslucentBackground);
            _trayIcon = new QSystemTrayIcon(this);
            _trayIcon->setIcon(QIcon(":/PengTray.png"));
            _trayIcon->show();
            connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconClicked()));

            _ui->setupUi(this);
            this->updateDeviceList();

            /*to make sure load is the first window*/
            _ui->stackedWidgetVeiwWindow->setCurrentIndex(0);

            /* messing around with fonts*/
            QFontDatabase fontDatabase;
            int loaded = fontDatabase.addApplicationFont(":/fonts/Audiowide-Regular.ttf");
            if (loaded < 0)
                {
                    qDebug() << "could not load AudioWide";
                }
            QFont audioWide = fontDatabase.font("Audiowide-Regular", "normal", 11);
            QFont audioWideLarge = fontDatabase.font("Audiowide-Regular", "normal", 15);

            setAcceptDrops(true);
            _ui->lineEditOpenFile->setAcceptDrops(false);
            _ui->lineEditStream->setAcceptDrops(true);
            _movie = new QMovie(":/penguinLight.gif");
            connect(_movie, SIGNAL(frameChanged(int)), this, SLOT(set_button_icon(int)));
            this->update();
        }

PenguinView::~PenguinView()
    {

    }

void PenguinView::on_pushButtonLoad_clicked()
    {
        _ui->stackedWidgetVeiwWindow->setCurrentIndex(0);
        this->updateDeviceList();
    }

void PenguinView::on_pushButtonCast_clicked()
    {

        QString         execution;
        t_AirPenguin    selectedDevice;

        /* If file not loaded, do not start player */
        if (_filePath.isEmpty())
            {
                QtError err("No file selected for streaming",this);
                return;
            }

        if (_ui->listWidgetDeviceList->selectedItems().isEmpty())
            {
                QtError err("No pi selected or available",this);
                return;
            }

        selectedDevice = NetworkManager::getInstance().getDeviceFromName(_ui->listWidgetDeviceList->currentItem()->text().toStdString());
        NetworkManager::getInstance().connectToAP(selectedDevice.ip);
        _castArgs = new VlcArgs(QString::fromStdString(selectedDevice.ip), clientIp(), "5554", "peng.sdp", "--network-caching=40--file-caching=0--sout-keep");
        _playerWidget = new CastPlayer(_filePath, _castArgs, _autoPlay);
        this->addDockWidget(Qt::RightDockWidgetArea, (QDockWidget *)_playerWidget);
        connect(_playerWidget, SIGNAL(playerClosed()), this, SLOT(playerDeleted()));
        _playerWidget->show();
        _movie->start();
    }

void PenguinView::on_playLocalButton_clicked()
    {

        /* Check for current player object (QWidget) */
        if (_playerWidget != Q_NULLPTR)
            {
                return;
            }

        /* ensure file is selected */
        if (_filePath.isEmpty())
            {
                QtError err("No file selected",this);
                return;
            }
        _localArgs = new VlcArgs();
        _playerWidget = new LocalPlayer(_filePath, _localArgs, _autoPlay, false);
        _playerWidget->show();
        connect(_playerWidget, SIGNAL(playerClosed()), this, SLOT(playerDeleted()));
    }

void PenguinView::on_pushButtonAbout_clicked()
    {
        _ui->stackedWidgetVeiwWindow->setCurrentIndex(2);
    }

void PenguinView::on_pushButtonBrowse_clicked()
    {

        /* Check for current player object (QWidget) */
        if (_playerWidget != Q_NULLPTR)
        {
            return;
        }

        _filePath = QFileDialog::getOpenFileName(this, tr("Open media"), "",
                                             tr("Video (*.mp4, *.wmv, *.mov) ;; "
                                                "Audio (*.mp3, *.aac, *.ogg, *.wav) ;; "
                                                "All Files (*.*)"));
        //make sure filepath holds string
        if(_filePath.isEmpty())
            {
                return;
            }

        //text field load into lineEdit
        QFileInfo file(_filePath);
        _ui->lineEditOpenFile->setText(file.baseName());
    }


void PenguinView::on_lineEditStream_returnPressed()
    {

        /* Check for current player object (QWidget) */
        if (_playerWidget != Q_NULLPTR)
        {
            return;
        }

        QString url = _ui->lineEditStream->text();

        //if no url entered, do nothing
        if (url.isEmpty())
            {
                QtError err("No url entered",this);
                return;
            }
        _localArgs = new VlcArgs();
        _playerWidget = new LocalPlayer(url, _localArgs, _autoPlay, true);
        _playerWidget->show();
        connect(_playerWidget, SIGNAL(playerClosed()), this, SLOT(playerDeleted()));
    }

bool PenguinView::updateDeviceList()
    {
        std::list<t_AirPenguin> airPenguinList;
        NetworkManager::getInstance().fillAirPenguinList();
        airPenguinList = NetworkManager::getInstance().getAirPenguinList();
        _ui->listWidgetDeviceList->clear();
        for (std::list<t_AirPenguin>::iterator it = airPenguinList.begin(); it != airPenguinList.end(); ++it)
            {
                std::cout << "-----> " << it->name << " - " << it->ip << std::endl;
                _ui->listWidgetDeviceList->addItem(QString::fromLocal8Bit(it->name.c_str()));
            }
        return (true);
    }

void PenguinView::on_actionLight_Theme_triggered()
    {
        qApp->setStyleSheet("");
        _ui->pushButtonLoad->setIcon(QIcon(":/raspberryPiLight.png"));
        _ui->pushButtonCast->setIcon(QIcon(":/penguinLight.gif"));
        _ui->pushButtonAbout->setIcon(QIcon(":/aboutLight.png"));
    }

void PenguinView::on_actionDark_Theme_triggered()
    {
        QFile darkTheme(":/QTDark.css");
        darkTheme.open(QFile::ReadOnly);
        QString darkSS = QLatin1String(darkTheme.readAll());
        qApp->setStyleSheet(darkSS);
        _ui->pushButtonLoad->setIcon(QIcon(":/raspberryPiDark.png"));
        _ui->pushButtonCast->setIcon(QIcon(":/penguinDark.gif"));
        _ui->pushButtonAbout->setIcon(QIcon(":/aboutDark.png"));
    }

void PenguinView::on_actionContact_triggered()
    {
        _ui->stackedWidgetVeiwWindow->setCurrentIndex(1);
    }

void PenguinView::on_actionOn_triggered()
    {
        if(_autoPlay)
            {
                _autoPlay = false;
            }
        else
            {
                 _autoPlay = true;
            }
    }

void PenguinView::set_button_icon(int frame)
    {
        _ui->pushButtonCast->setIcon(QIcon(_movie->currentPixmap()));
    }

void PenguinView::playerDeleted()
    {
        _playerWidget = Q_NULLPTR;
        _filePath = "";
        _ui->lineEditOpenFile->clear();
        _ui->lineEditStream->clear();
        _movie->stop();
    }

void PenguinView::dragEnterEvent(QDragEnterEvent *E)
    {
        if (E->mimeData()->hasUrls())
            {
                E->acceptProposedAction();
            }
    }


void PenguinView::dropEvent(QDropEvent *E)
{
    foreach (const QUrl &url, E->mimeData()->urls())
       {
           QString path = url.toLocalFile();
           _filePath = path;

           QFileInfo file(_filePath);
           _ui->lineEditOpenFile->setText(file.baseName());
           if(_autoLaunch)
               {
                   on_playLocalButton_clicked();
               }
       }
}


void PenguinView::on_AutoLaunchOn_triggered()
{
    if(_autoLaunch)
        {
            _autoLaunch = false;
        }
    else
        {
            _autoLaunch = true;
        }
}

QString PenguinView::clientIp()
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol&&address != QHostAddress(QHostAddress::LocalHost))
        {
            return address.toString();
        }
    }

    QtError err("Client Ip not obtained, recast stream", 0);
    return "";
}

/* Background coloring */
void PenguinView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(250,250,250,240));
    painter.drawRect(0,0,width(),height());
}

void PenguinView::trayIconClicked()
{
    if((this->isMinimized()))
        this->showMaximized();
    else
        this->showMinimized();
}
