/*  LOOT

    A load order optimisation tool for Oblivion, Skyrim, Fallout 3 and
    Fallout: New Vegas.

    Copyright (C) 2018    WrinklyNinja

    This file is part of LOOT.

    LOOT is free software: you can redistribute
    it and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    LOOT is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LOOT.  If not, see
    <https://www.gnu.org/licenses/>.
    */

#include "plugin_sorting_data.h"

namespace loot {
PluginSortingData::PluginSortingData(const Plugin& plugin,
                                     const PluginMetadata&& metadata) :
    plugin_(plugin),
    PluginMetadata(metadata) {}

std::string PluginSortingData::GetName() const { return plugin_.GetName(); }

bool PluginSortingData::IsMaster() const {
  return plugin_.IsMaster() || (plugin_.IsLightMaster() &&
                                !boost::iends_with(plugin_.GetName(), ".esp"));
}

bool PluginSortingData::LoadsArchive() const { return plugin_.LoadsArchive(); }

std::vector<std::string> PluginSortingData::GetMasters() const {
  return plugin_.GetMasters();
}

size_t PluginSortingData::NumOverrideFormIDs() const {
  return plugin_.NumOverrideFormIDs();
}

bool PluginSortingData::DoFormIDsOverlap(
    const PluginSortingData& plugin) const {
  return plugin_.DoFormIDsOverlap(plugin.plugin_);
}

std::unordered_set<std::string> PluginSortingData::GetAfterGroupPlugins() const {
  return afterGroupPlugins_;
}

void PluginSortingData::SetAfterGroupPlugins(std::unordered_set<std::string> plugins) {
  afterGroupPlugins_ = plugins;
}
}