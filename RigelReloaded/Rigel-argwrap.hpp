#pragma once

#include "Rigel-config.hpp"

#include <SFML\Config.hpp>

#include <type_traits>

namespace RIGELNETW_CONFIG_NS_NAME {
    
    // Wrapper class for function arguments to send to remote handlers.

    template<class TypeToSend>
    class ArgWrap {

        static_assert( std::is_same< TypeToSend, sf::Int8   >::value ||
                       std::is_same< TypeToSend, sf::Uint8  >::value ||
                       std::is_same< TypeToSend, sf::Int16  >::value ||
                       std::is_same< TypeToSend, sf::Uint16 >::value ||
                       std::is_same< TypeToSend, sf::Int32  >::value ||
                       std::is_same< TypeToSend, sf::Uint32 >::value ||
                       std::is_same< TypeToSend, sf::Int64  >::value ||
                       std::is_same< TypeToSend, sf::Uint64 >::value ||
                       std::is_same< TypeToSend, float      >::value ||
                       std::is_same< TypeToSend, double     >::value ,

                       "Rigel Networking doesn't support this type for sending (see Rigel-types.hpp)." );

        // const char * Handled separately...

        private:

            union Data {
                
                TypeToSend  num;
                const char *str;

                };

            Data data;

            bool is_string_;

        public:

            // Construction:
            ArgWrap() = delete;

            // Copy:
            ArgWrap(const ArgWrap & other) = default;

            ArgWrap & operator=(const ArgWrap & other) = default;

            // Move:
            ArgWrap(ArgWrap && other) = default;

            ArgWrap & operator=(ArgWrap && other) = default;

            // Make new:
            ArgWrap(TypeToSend arg)
                : is_string_(false) {
                
                data.num = arg;

                }

            ArgWrap(const char *arg)
                : is_string_(true) {
                
                data.str = arg;
                
                }

            ArgWrap(const std::string &arg)
                : is_string_(true) {

                data.str = arg.c_str();

                }

            // Other methods:
            bool is_string() const { return is_string_; }

            TypeToSend  get_number() const { return data.num; }

            const char *get_string() const { return data.str; }

            void set_number(TypeToSend  num) { data.num = num; is_string_ = false; }

            void set_string(const char *str) { data.str = str; is_string_ = true;  }
        
        };

    }