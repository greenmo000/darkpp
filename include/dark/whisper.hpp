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

#ifndef DARK_WHISPER_HPP
#define DARK_WHISPER_HPP

#include <ctime>
#include <map>
#include <mutex>
#include <string>

#include <dark/ecdhe.hpp>

namespace dark {

    class whisper
    {
        public:
        
            /**
             * Constructor
             */
            whisper();
        
            /**
             * The singleton accessor.
             */
            static whisper & instance();
        
            /**
             * The ecdhe.
             */
            ecdhe & get_ecdhe();
        
            /**
             * The ecdhe shared secrets (mapped to public key).
             */
            std::map<std::string,
                std::pair<std::time_t, std::vector<std::uint8_t> > >
                & ecdhe_shared_secrets()
            ;
        
        private:
        
            /**
             * The ecdhe.
             */
            ecdhe m_ecdhe;
        
            /**
             * The ecdhe shared secrets (mapped to public key).
             */
            std::map<std::string,
                std::pair<std::time_t, std::vector<std::uint8_t> > >
                m_ecdhe_shared_secrets
            ;
        
        protected:
        
            // ...
    };
}

#endif // DARK_WHISPER_HPP
