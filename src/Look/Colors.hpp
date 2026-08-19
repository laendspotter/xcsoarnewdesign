// SPDX-License-Identifier: GPL-2.0-or-later
// Copyright The XCSoar Project

#pragma once

#include "ui/canvas/Color.hpp"

#include <cstddef>
#include <iterator>

#ifdef XCSOAR_TESTING
static constexpr Color COLOR_XCSOAR_DEFAULT_LIGHT = Color(0xed, 0x90, 0x90);
static constexpr Color COLOR_XCSOAR_DEFAULT = Color(0xd0, 0x17, 0x17);
static constexpr Color COLOR_XCSOAR_DEFAULT_DARK = Color(0x5d, 0x0a, 0x0a);
#else
static constexpr Color COLOR_XCSOAR_DEFAULT_LIGHT = Color(0xaa, 0xc9, 0xe4);
static constexpr Color COLOR_XCSOAR_DEFAULT = Color(0x3f, 0x76, 0xa8);
static constexpr Color COLOR_XCSOAR_DEFAULT_DARK = Color(0x00, 0x31, 0x5e);
#endif

/**
 * The active accent ("brand") color, used throughout the UI for
 * buttons, selection/focus highlights, dialog accents and InfoBox
 * accents.  This is what most code should keep using the
 * `COLOR_XCSOAR*` names for.
 *
 * Unlike the other colors in this header, these are *not*
 * `constexpr`: they are plain `inline` (C++17) globals so that every
 * translation unit shares one instance, and their value is set at
 * runtime by ApplyAccentColorPreset() from Look::InitialiseConfigured(),
 * according to the user's UISettings::accent_color choice.  They must
 * not be used in a constexpr/compile-time context.
 *
 * They default to the classic XCSoar color (red in testing builds)
 * so that code running before the user's settings are loaded (e.g.
 * the startup splash / progress window) still gets a sensible color.
 */
inline Color COLOR_XCSOAR_LIGHT = COLOR_XCSOAR_DEFAULT_LIGHT;
inline Color COLOR_XCSOAR = COLOR_XCSOAR_DEFAULT;
inline Color COLOR_XCSOAR_DARK = COLOR_XCSOAR_DEFAULT_DARK;

/**
 * One entry of the curated "modern" accent color palette the user
 * can choose from in the Appearance settings.  Index corresponds to
 * UISettings::AccentColor.
 */
struct AccentColorPreset {
  Color light, base, dark;
};

/**
 * Curated accent color presets, matching UISettings::AccentColor
 * 1:1 by array index.
 */
static constexpr AccentColorPreset ACCENT_COLOR_PRESETS[] = {
  /* XCSOAR: the classic brand color (default) */
  { COLOR_XCSOAR_DEFAULT_LIGHT, COLOR_XCSOAR_DEFAULT, COLOR_XCSOAR_DEFAULT_DARK },
  /* BLUE */
  { Color(0xa9, 0xd2, 0xf7), Color(0x1f, 0x6f, 0xeb), Color(0x0b, 0x2e, 0x66) },
  /* TEAL */
  { Color(0x9d, 0xe6, 0xdc), Color(0x0f, 0x9d, 0x8f), Color(0x06, 0x4a, 0x43) },
  /* GREEN */
  { Color(0xb2, 0xe6, 0xb2), Color(0x2e, 0xa0, 0x4a), Color(0x14, 0x4a, 0x21) },
  /* PURPLE */
  { Color(0xd3, 0xc3, 0xf0), Color(0x7c, 0x4d, 0xd9), Color(0x37, 0x1f, 0x66) },
  /* ORANGE */
  { Color(0xff, 0xd4, 0xa9), Color(0xe6, 0x7e, 0x22), Color(0x66, 0x38, 0x0a) },
  /* RED */
  { Color(0xf5, 0xb1, 0xae), Color(0xd6, 0x39, 0x2e), Color(0x5c, 0x14, 0x11) },
};

/**
 * Apply one of the #ACCENT_COLOR_PRESETS to the mutable
 * `COLOR_XCSOAR*` globals.  Called once from
 * Look::InitialiseConfigured().
 */
inline void
ApplyAccentColorPreset(std::size_t index) noexcept
{
  if (index >= std::size(ACCENT_COLOR_PRESETS))
    index = 0;

  const auto &preset = ACCENT_COLOR_PRESETS[index];
  COLOR_XCSOAR_LIGHT = preset.light;
  COLOR_XCSOAR = preset.base;
  COLOR_XCSOAR_DARK = preset.dark;
}

/**
 * Dark mode color palette.
 *
 * Slightly flattened (lower-contrast) gradient and refined neutral
 * greys for a cleaner, more modern dark theme.
 */
static constexpr Color COLOR_DARK_THEME_BACKGROUND =
  Color(0x0e, 0x14, 0x1a);
static constexpr Color COLOR_DARK_THEME_CAPTION =
  Color(0x12, 0x12, 0x12);
static constexpr Color COLOR_DARK_THEME_CAPTION_INACTIVE =
  Color(0x30, 0x30, 0x30);
static constexpr Color COLOR_DARK_THEME_LIST =
  Color(0x24, 0x27, 0x2b);
static constexpr Color COLOR_DARK_THEME_LIST_SELECTED =
  Color(0x34, 0x38, 0x3d);
static constexpr Color COLOR_DARK_THEME_BUTTON =
  Color(0x20, 0x26, 0x2d);
static constexpr Color COLOR_DARK_THEME_GRADIENT_TOP =
  Color(0x16, 0x1c, 0x22);

/**
 * Light mode dialog background colors.
 *
 * Modernised to a clean, neutral off-white/grey instead of the
 * previous warm parchment tint, with a flatter (lower-contrast)
 * top-to-bottom gradient for a less dated look.
 */
static constexpr Color COLOR_DIALOG_BACKGROUND =
  Color(0xf1, 0xf2, 0xf4);
static constexpr Color COLOR_DIALOG_GRADIENT_TOP =
  Color(0xf8, 0xf9, 0xfa);

/**
 * Admonition colors for Markdown rendering.
 */
static constexpr Color COLOR_ADMONITION_IMPORTANT =
  Color(0xd0, 0x6b, 0x00);
static constexpr Color COLOR_ADMONITION_IMPORTANT_DARK =
  Color(0xff, 0xa0, 0x30);
static constexpr Color COLOR_ADMONITION_TIP =
  Color(0x00, 0x80, 0x00);

/**
 * A muted green readable on light backgrounds.
 * Standard COLOR_GREEN (0,255,0) is too bright on white.
 */
static constexpr Color COLOR_LIGHT_GREEN = Color(0x00, 0xc0, 0x00);

/**
 * Airspace warning list / map-item status badge colours.
 */
static constexpr Color COLOR_AIRSPACE_WARNING_INSIDE =
  Color(254, 50, 50);
static constexpr Color COLOR_AIRSPACE_WARNING_NEAR =
  Color(254, 254, 50);
static constexpr Color COLOR_AIRSPACE_WARNING_INSIDE_ACK =
  Color(254, 100, 100);
static constexpr Color COLOR_AIRSPACE_WARNING_NEAR_ACK =
  Color(254, 254, 100);

/**
 * XCTherm overlay palette.
 */
static constexpr Color COLOR_XCTHERM_BLUE = Color(0x00, 0x00, 0xc8);
static constexpr Color COLOR_XCTHERM_BRIGHT_CYAN = Color(0x00, 0xd0, 0xff);
static constexpr Color COLOR_XCTHERM_SKY_BLUE = Color(0x60, 0xe0, 0xff);
static constexpr Color COLOR_XCTHERM_LIGHT_BLUE = Color(0xa0, 0xe8, 0xff);
static constexpr Color COLOR_XCTHERM_PALE_BLUE = Color(0xc8, 0xf0, 0xff);
static constexpr Color COLOR_XCTHERM_CREAM = Color(0xf0, 0xf0, 0xc0);
static constexpr Color COLOR_XCTHERM_YELLOW = Color(0xff, 0xff, 0x00);
static constexpr Color COLOR_XCTHERM_GOLD = Color(0xff, 0xd0, 0x00);
static constexpr Color COLOR_XCTHERM_ORANGE = Color(0xff, 0xa0, 0x00);
static constexpr Color COLOR_XCTHERM_RED_ORANGE = Color(0xff, 0x40, 0x00);
static constexpr Color COLOR_XCTHERM_RED = Color(0xff, 0x00, 0x00);
static constexpr Color COLOR_XCTHERM_PURPLE = Color(0xa0, 0x20, 0xf0);

static constexpr uint8_t ALPHA_OVERLAY = 0xA0;
