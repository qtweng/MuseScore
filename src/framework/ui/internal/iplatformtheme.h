//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2021 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#ifndef MU_UI_IPLATFORMTHEME_H
#define MU_UI_IPLATFORMTHEME_H

#include "modularity/imoduleexport.h"
#include "async/channel.h"

#include <QWidget>

namespace mu::ui {
class IPlatformTheme : MODULE_EXPORT_INTERFACE
{
    INTERFACE_ID(IPlatformTheme)

public:
    virtual ~IPlatformTheme() = default;

    virtual void startListening() = 0;
    virtual void stopListening() = 0;

    virtual bool isFollowSystemThemeAvailable() const = 0;

    virtual bool isDarkMode() const = 0;
    virtual async::Channel<bool> darkModeSwitched() const = 0;

    /// Performs platform-specific styling of the application.
    virtual void setAppThemeDark(bool isDark) = 0;

    /// Performs platform-specific styling of the window.
    virtual void applyPlatformStyle(QWidget* window) = 0;
};
}

#endif // MU_UI_IPLATFORMTHEME_H
