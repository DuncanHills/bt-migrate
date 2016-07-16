// bt-migrate, torrent state migration tool
// Copyright (C) 2014 Mike Gelfand <mikedld@mikedld.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <json/value.h>

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <string>

namespace boost { namespace filesystem { class path; } }

class IStructuredDataCodec;

class TorrentInfo
{
public:
    TorrentInfo();
    TorrentInfo(Json::Value const& torrent);

    void Encode(std::ostream& stream, IStructuredDataCodec const& codec) const;

    std::string const& GetInfoHash() const;
    std::uint64_t GetTotalSize() const;
    std::uint32_t GetPieceSize() const;
    std::string GetName() const;
    boost::filesystem::path GetFilePath(std::size_t fileIndex) const;

    static TorrentInfo Decode(std::istream& stream, IStructuredDataCodec const& codec);

private:
    Json::Value m_torrent;
    std::string m_infoHash;
};
