/*
 * This file Copyright (C) 2009-2015 Mnemosyne LLC
 *
 * It may be used under the GNU GPL versions 2 or 3
 * or any future license endorsed by Mnemosyne LLC.
 *
 */

#pragma once

#include <memory>

#include <QFileSystemWatcher>
#include <QObject>
#include <QSet>
#include <QString>

class TorrentModel;

class WatchDir : public QObject
{
    Q_OBJECT

public:
    WatchDir(TorrentModel const&);

    void setPath(QString const& path, bool is_enabled);

signals:
    void torrentFileAdded(QString const& filename);

private:
    enum
    {
        OK,
        DUPLICATE,
        ERROR
    };

private:
    int metainfoTest(QString const& filename) const;

private slots:
    void watcherActivated(QString const& path);
    void onTimeout();

    void rescanAllWatchedDirectories();

private:
    TorrentModel const& model_;

    QSet<QString> watch_dir_files_;
    std::unique_ptr<QFileSystemWatcher> watcher_;
};
