#pragma once
/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "guiinfo/GUIInfoProvider.h"

#include <atomic>

#include "XBDateTime.h"

namespace GUIINFO
{

class GUIInfo;

class CPlayerGUIInfo : public CGUIInfoProvider
{
public:
  CPlayerGUIInfo() : m_AfterSeekTimeout(0), m_seekOffset(0), m_playerShowTime(false), m_playerShowInfo(false) {}
  ~CPlayerGUIInfo() override = default;

  // GUIINFO::IGUIInfoProvider implementation
  bool InitCurrentItem(CFileItem *item) override;
  bool GetLabel(std::string& value, const CFileItem *item, const GUIInfo &info, std::string *fallback) const override;
  bool GetInt(int& value, const CGUIListItem *item, const GUIInfo &info) const override;
  bool GetBool(bool& value, const CGUIListItem *item, const GUIInfo &info) const override;

  bool GetDisplayAfterSeek() const;
  void SetDisplayAfterSeek(unsigned int timeOut = 2500, int seekOffset = 0);
  void SetShowTime(bool showtime) { m_playerShowTime = showtime; };
  void SetShowInfo(bool showinfo);
  bool GetShowInfo() const { return m_playerShowInfo; }
  bool ToggleShowInfo();

private:
  unsigned int m_AfterSeekTimeout;
  mutable int m_seekOffset;
  std::atomic_bool m_playerShowTime;
  std::atomic_bool m_playerShowInfo;

  int GetTotalPlayTime() const;
  int GetPlayTime() const;
  int GetPlayTimeRemaining() const;
  float GetSeekPercent() const;

  std::string GetCurrentPlayTime(TIME_FORMAT format) const;
  std::string GetCurrentPlayTimeRemaining(TIME_FORMAT format) const;
  std::string GetDuration(TIME_FORMAT format) const;
  std::string GetCurrentSeekTime(TIME_FORMAT format) const;
  std::string GetSeekTime(TIME_FORMAT format) const;
};

} // namespace GUIINFO
