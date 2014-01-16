/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGTK3DIALOGHELPERS_H
#define QGTK3DIALOGHELPERS_H

#include <QtCore/qscopedpointer.h>
#include <qpa/qplatformdialoghelper.h>

typedef struct _GtkDialog GtkDialog;
typedef struct _GtkFileFilter GtkFileFilter;

QT_BEGIN_NAMESPACE

class QGtk3Dialog;

class QGtk3ColorDialogHelper : public QPlatformColorDialogHelper
{
    Q_OBJECT

public:
    QGtk3ColorDialogHelper();
    ~QGtk3ColorDialogHelper();

    bool show(Qt::WindowFlags flags, Qt::WindowModality modality, QWindow *parent);
    void exec();
    void hide();

    void setCurrentColor(const QColor &color);
    QColor currentColor() const;

private Q_SLOTS:
    void onAccepted();

private:
    static void onColorChanged(QGtk3ColorDialogHelper *helper);
    void applyOptions();

    QScopedPointer<QGtk3Dialog> d;
};

class QGtk3FileDialogHelper : public QPlatformFileDialogHelper
{
    Q_OBJECT

public:
    QGtk3FileDialogHelper();
    ~QGtk3FileDialogHelper();

    bool show(Qt::WindowFlags flags, Qt::WindowModality modality, QWindow *parent);
    void exec();
    void hide();

    bool defaultNameFilterDisables() const;
    void setDirectory(const QUrl &directory) Q_DECL_OVERRIDE;
    QUrl directory() const Q_DECL_OVERRIDE;
    void selectFile(const QUrl &filename) Q_DECL_OVERRIDE;
    QList<QUrl> selectedFiles() const Q_DECL_OVERRIDE;
    void setFilter();
    void selectNameFilter(const QString &filter);
    QString selectedNameFilter() const;

private Q_SLOTS:
    void onAccepted();

private:
    static void onSelectionChanged(GtkDialog *dialog, QGtk3FileDialogHelper *helper);
    static void onCurrentFolderChanged(QGtk3FileDialogHelper *helper);
    void applyOptions();
    void setNameFilters(const QStringList &filters);

    QUrl _dir;
    QList<QUrl> _selection;
    QHash<QString, GtkFileFilter*> _filters;
    QHash<GtkFileFilter*, QString> _filterNames;
    QScopedPointer<QGtk3Dialog> d;
};

class QGtk3FontDialogHelper : public QPlatformFontDialogHelper
{
    Q_OBJECT

public:
    QGtk3FontDialogHelper();
    ~QGtk3FontDialogHelper();

    bool show(Qt::WindowFlags flags, Qt::WindowModality modality, QWindow *parent);
    void exec();
    void hide();

    void setCurrentFont(const QFont &font);
    QFont currentFont() const;

private Q_SLOTS:
    void onAccepted();

private:
    void applyOptions();

    QScopedPointer<QGtk3Dialog> d;
};

QT_END_NAMESPACE

#endif // QGTK3DIALOGHELPERS_H
