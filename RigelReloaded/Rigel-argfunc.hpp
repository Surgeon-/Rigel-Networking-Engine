#pragma once

#include "Rigel-argrecv.hpp"
#include "Rigel-node.hpp"
#include "Rigel-types.hpp"

#include <type_traits>

namespace RIGELNETW_CONFIG_NS_NAME {
    
    #define ns RIGELNETW_CONFIG_NS_NAME
    #define cmptype(t1, t2) (std::is_same<t1, t2>::value)

    // Number / String argument fetch:
    template<class TypeToRet>
    TypeToRet arg(const Node *node, size_t argument_index) {
        
        static_assert( (RIGELNETW_ENUMERATE_TYPE(TypeToRet) > 0) || cmptype(TypeToRet, ns::Lpcstr)
                     , "The rn::arg(Node*, size_t) function can't return the specified value (See Rigel-types.hpp for supported types)."
                     ) ;

        const ArgRecv &ar = node->argrecv_vec[argument_index];

        // Integral types:
        if (cmptype(TypeToRet, ns::Int8  )) return (TypeToRet)(ar.number.d_int8  );

        if (cmptype(TypeToRet, ns::Uint8 )) return (TypeToRet)(ar.number.d_uint8 );

        if (cmptype(TypeToRet, ns::Int16 )) return (TypeToRet)(ar.number.d_int16 );

        if (cmptype(TypeToRet, ns::Uint16)) return (TypeToRet)(ar.number.d_uint16);

        if (cmptype(TypeToRet, ns::Int32 )) return (TypeToRet)(ar.number.d_int32 );

        if (cmptype(TypeToRet, ns::Uint32)) return (TypeToRet)(ar.number.d_uint32);

        if (cmptype(TypeToRet, ns::Int64 )) return (TypeToRet)(ar.number.d_int64 );

        if (cmptype(TypeToRet, ns::Uint64)) return (TypeToRet)(ar.number.d_uint64);

        // Floating point types:
        if (cmptype(TypeToRet, ns::Float )) return *reinterpret_cast<const TypeToRet*>(&( ar.number.d_float  ));

        if (cmptype(TypeToRet, ns::Double)) return *reinterpret_cast<const TypeToRet*>(&( ar.number.d_double ));

        // String:
        if (cmptype(TypeToRet, ns::Lpcstr)) return (TypeToRet)reinterpret_cast<uintptr_t>( ar.string.c_str() );

        // Else (Won't ever happen - it just surpresses warnings):
        return TypeToRet(0);

        // Note: This function is full of casts which would normally be very unsafe and a bad practice.
        // However, here they only serve the purpose of surpressing warnings and errors and they don't
        // actually do anything since they always cast from and to the same type.

        }

    // Packet (reference) argument fetch:
    inline
    rn::Packet & pkt(Node *node) {
        
        /*static_assert( cmptype(TypeToRet, ns::Packet)
                     , "The single-argument overload of rn::arg<>(Node*) function can only be used to return a reference to rn::Packet type."
                     ) ;*/

        return node->user_packet;

        }

    #undef cmptype
    #undef ns

    }