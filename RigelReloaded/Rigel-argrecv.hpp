#pragma once

#include "Rigel-config.hpp"

#include "Rigel-types.hpp"

#include <string>

namespace RIGELNETW_CONFIG_NS_NAME {
    
    // Argument receiver helper struct

    #define ns RIGELNETW_CONFIG_NS_NAME

    struct ArgRecv {
        
        union Data {
            
            ns::Int8    d_int8;
            ns::Uint8   d_uint8;
            ns::Int16   d_int16;
            ns::Uint16  d_uint16;
            ns::Int32   d_int32; 
            ns::Uint32  d_uint32;
            ns::Int64   d_int64;
            ns::Uint64  d_uint64;
            ns::Float   d_float;
            ns::Double  d_double;

            };

        Data number;

        std::string string;

        };

    #undef ns

    }