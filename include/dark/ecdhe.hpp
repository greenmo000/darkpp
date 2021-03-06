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

#ifndef DARK_ECDHE_HPP
#define DARK_ECDHE_HPP

#include <cstdint>
#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#include <dark/ecdhe.h>
}
#endif // __cplusplus

namespace dark {

    /**
     * Implements Elliptic Curve Diffie–Hellman Exchange.
     */
    class ecdhe
    {
        public:
        
            /**
             * Constructor
             */
            ecdhe();
        
            /**
             * Destructor
             */
            ~ecdhe();
        
            /**
             * Returns the public key generating if needed.
             */
            const std::string & public_key();
        
            /**
             * Derives a secret key from the remote peer's public key.
             * @param peer_public_key The remote peer's public key.
             */
            std::vector<std::uint8_t> derive_secret_key(
                const std::string & peer_public_key
            );

            /**
             * Gets the EC_DHE.
             */
            EC_DHE * get_EC_DHE();
        
            /**
             * Runs test case.
             */
            static int run_test();
        
            /**
             * Signs
             * @param buf The buffer.
             * @param len The length.
             * @param signature The signature.
             */
            bool sign(
                const std::uint8_t * buf, const std::size_t & len,
                std::vector<std::uint8_t> & signature
            );

            /**
             * Verifies
             * @param buf The buffer.
             * @param len The length.
             * @param public_key The public key.
             * @param signature The signature.
             */
            static bool verify(
                const std::uint8_t * buf, const std::size_t & len,
                const std::vector<std::uint8_t> & public_key,
                const std::vector<std::uint8_t> & signature
            );

        private:
        
            /**
             * The EC_DHE.
             */
            EC_DHE * m_ecdhe;
        
            /**
             * The public key.
             */
            std::string m_public_key;
        
        protected:
        
            // ...
    };
} // namespace dark

#endif // DARK_ECDHE_HPP
