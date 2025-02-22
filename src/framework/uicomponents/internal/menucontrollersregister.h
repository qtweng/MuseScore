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
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================
#ifndef MU_UICOMPONENTS_MENUCONTROLLERSREGISTER_H
#define MU_UICOMPONENTS_MENUCONTROLLERSREGISTER_H

#include "imenucontrollersregister.h"

namespace mu::uicomponents {
class MenuControllersRegister : public IMenuControllersRegister
{
public:
    void registerController(MenuType menuType, IMenuControllerPtr controller) override;
    IMenuControllerPtr controller(MenuType menuType) const override;
    IMenuControllerPtrList controllers() const override;

private:
    std::map<MenuType, IMenuControllerPtr> m_controllers;
};
}

#endif // MU_UICOMPONENTS_MENUCONTROLLERSREGISTER_H
