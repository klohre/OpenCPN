/**************************************************************************
 *   Copyright (C) 2018 by David S. Register                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <https://www.gnu.org/licenses/>. *
 **************************************************************************/

/**
 * \file
 *
 * Implement color_handler.h -- global color handling by name.
 */

#include <wx/log.h>

#include "color_handler.h"
#include "model/gui_vars.h"
#include "model/ocpn_types.h"
#include "s52plib.h"

/**
 * \file
 *
 * Implement color_handler.h -- Global color handling by name.
 */

extern s52plib* ps52plib;  // In a library...
wxColorHashMap* pcurrent_user_color_hash;

wxColour GetGlobalColor(wxString colorName) {
  wxColour ret_color;

  //    Use the S52 Presentation library if present
  if (ps52plib) ret_color = ps52plib->getwxColour(colorName);
  if (!ret_color.Ok() && pcurrent_user_color_hash)
    ret_color = (*pcurrent_user_color_hash)[colorName];

  //    Default
  if (!ret_color.Ok()) {
    ret_color.Set(128, 128, 128);  // Simple Grey
    wxLogMessage("Warning: Color not found " + colorName);
    // Avoid duplicate warnings:
    if (pcurrent_user_color_hash)
      (*pcurrent_user_color_hash)[colorName] = ret_color;
  }
  return ret_color;
}

wxColour GetDialogColor(DialogColor color) {
  wxColour col = *wxRED;

  // Always use OpenCPN's own color scheme for consistent dark theme.
  // The color tables in user_colors.cpp define a cohesive dark palette
  // across DAY/DUSK/NIGHT modes.
  switch (color) {
    case DLG_BACKGROUND:
      col = GetGlobalColor("DILG0");
      break;
    case DLG_SELECTED_BACKGROUND:
      col = GetGlobalColor("DILG1");
      break;
    case DLG_UNSELECTED_BACKGROUND:
      col = GetGlobalColor("DILG0");
      break;
    case DLG_ACCENT:
    case DLG_SELECTED_ACCENT:
      col = GetGlobalColor("DILG3");
      break;
    case DLG_UNSELECTED_ACCENT:
      col = GetGlobalColor("DILG1");
      break;
    case DLG_TEXT:
      col = GetGlobalColor("DILG3");
      break;
    case DLG_HIGHLIGHT:
      col = GetGlobalColor("UINFB");  // Teal accent for highlights
      break;
  }
  return col;
}
