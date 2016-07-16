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

#include "Util.h"

#include "Exception.h"
#include "Throw.h"

#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/uuid/sha1.hpp>

#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <iomanip>
#include <sstream>

namespace fs = boost::filesystem;

namespace Util
{

long long StringToInt(std::string const& text)
{
    errno = 0;
    long long const result = std::strtoll(text.c_str(), NULL, 10);
    if (result == 0 && errno != 0)
    {
        Throw<Exception>() << "Unable to convert \"" << text << "\" to integer";
    }

    return result;
}

fs::path GetPath(std::string const& nativePath)
{
    if (nativePath.size() >= 3 && std::isalpha(nativePath[0]) && nativePath[1] == ':' &&
        (nativePath[2] == '/' || nativePath[2] == '\\'))
    {
        // Looks like Windows path
        return boost::algorithm::replace_all_copy(nativePath, "\\", "/");
    }

    return nativePath;
}

std::string CalculateSha1(std::string const& data)
{
    boost::uuids::detail::sha1 sha;
    sha.process_bytes(data.c_str(), data.size());
    unsigned int result[5];
    sha.get_digest(result);

    std::ostringstream stream;
    for (std::size_t i = 0; i < sizeof(result) / sizeof(*result); ++i)
    {
        stream << std::hex << std::setw(8) << std::setfill('0') << result[i];
    }

    return stream.str();
}

std::string BinaryToHex(std::string const& data)
{
    static char const* const HexAlphabet = "0123456789abcdef";

    std::string result;

    for (char const c : data)
    {
        result += HexAlphabet[(c >> 4) & 0x0f];
        result += HexAlphabet[c & 0x0f];
    }

    return result;
}

} // namespace Util
