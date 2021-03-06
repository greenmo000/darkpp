/*
 * Copyright (c) 2013-2015 John Connor (BM-NC49AxAjcqVcF5jNPu85Rb8MJ2d9JqZt)
 *
 * This file is part of Dark++.
 *
 * Dark++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>

#include <dark/crypto.hpp>

using namespace dark;

std::string crypto::base64_encode(
    const char * buf, const std::size_t & len
    )
{
    static const char b64_forward_table[65] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
        "0123456789+/"
    ;
    std::string bindata(buf, len);

    if (
        bindata.size() > (
        std::numeric_limits<std::string::size_type>::max() / 4u) * 3u
        )
    {
        throw std::runtime_error(
            "String is too large for base64 encoding."
        );
    }

    const std::size_t binlen = bindata.size();
    
    /**
     * Pad the end with '='.
     */
    std::string ret((((binlen + 2) / 3) * 4), '=');
    
    std::size_t outpos = 0;
    int bits_collected = 0;
    unsigned int accumulator = 0;
    
    const std::string::const_iterator binend = bindata.end();

    for (
        std::string::const_iterator i = bindata.begin();
        i != binend; ++i
        )
    {
        accumulator = (accumulator << 8) | (*i & 0xffu);
        bits_collected += 8;
        
        while (bits_collected >= 6)
        {
            bits_collected -= 6;
            ret[outpos++] = b64_forward_table[
                (accumulator >> bits_collected) & 0x3fu
            ];
        }
    }
   
    if (bits_collected > 0)
    {
        assert(bits_collected < 6);
        accumulator <<= 6 - bits_collected;
        ret[outpos++] = b64_forward_table[accumulator & 0x3fu];
    }
   
    assert(outpos >= (ret.size() - 2));
    assert(outpos <= ret.size());
    
    return ret;
}

std::string crypto::base64_decode(
    const char * buf, const std::size_t & len
    )
{
    static const char b64_reverse_table[128] =
    {
       64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
       64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
       64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
       52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
       64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
       15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
       64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
       41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
    };

    std::string ascdata(buf, len);
    
    std::string ret;
    int bits_collected = 0;
    unsigned int accumulator = 0;

    for (
        std::string::const_iterator i = ascdata.begin();
        i != ascdata.end(); ++i
        )
    {
        const int c = *i;
        
        /**
         * Skip whitespace and padding.
         */
        if (isspace(c) || c == '=')
        {
            continue;
        }
        
        if ((c > 127) || (c < 0) || (b64_reverse_table[c] > 63))
        {
            throw std::runtime_error("Illegal characters");
        }
        
        accumulator = (accumulator << 6) | b64_reverse_table[c];
        
        bits_collected += 6;
        
        if (bits_collected >= 8)
        {
            bits_collected -= 8;
            
            ret += (char)((accumulator >> bits_collected) & 0xffu);
        }
    }
   
    return ret;
}
