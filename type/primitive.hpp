#pragma once
namespace fareloz
{
    namespace type
    {
        typedef unsigned char byte;

        template <typename CoordType>
        struct point { CoordType x; CoordType y; };

        template <typename MeasType>
        struct size { MeasType width; MeasType height; };
    }
}