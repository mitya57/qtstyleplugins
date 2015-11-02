/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qgtk3theme.h"
#include "qgtk3dialoghelpers.h"
#include <QVariant>

#undef signals
#include <gtk/gtk.h>

QT_BEGIN_NAMESPACE

const char *QGtk3Theme::name = "gtk3";

static QString gtkSetting(const gchar *propertyName)
{
    GtkSettings *settings = gtk_settings_get_default();
    gchararray value;
    g_object_get(settings, propertyName, &value, NULL);
    QString str = QString::fromUtf8(value);
    g_free(value);
    return str;
}

QGtk3Theme::QGtk3Theme()
{
    gtk_init(0, 0);
}

QVariant QGtk3Theme::themeHint(QPlatformTheme::ThemeHint hint) const
{
    switch (hint) {
    case QPlatformTheme::StyleNames:
        return QStringList() << QStringLiteral("gtk3") << QStringLiteral("fusion");
    case QPlatformTheme::SystemIconThemeName:
        return gtkSetting("gtk-icon-theme-name");
    case QPlatformTheme::SystemIconFallbackThemeName:
        return gtkSetting("gtk-fallback-icon-theme");
    default:
        return QGnomeTheme::themeHint(hint);
    }
}

bool QGtk3Theme::usePlatformNativeDialog(DialogType type) const
{
    switch (type) {
    case ColorDialog:
        return true;
    case FileDialog:
        return true;
    case FontDialog:
        return true;
    default:
        return false;
    }
}

QPlatformDialogHelper *QGtk3Theme::createPlatformDialogHelper(DialogType type) const
{
    switch (type) {
    case ColorDialog:
        return new QGtk3ColorDialogHelper;
    case FileDialog:
        return new QGtk3FileDialogHelper;
    case FontDialog:
        return new QGtk3FontDialogHelper;
    default:
        return 0;
    }
}

QT_END_NAMESPACE
