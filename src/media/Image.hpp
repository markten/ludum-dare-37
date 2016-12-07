#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include "Media_Object.hpp"

#include <string>

namespace Media
{


    class Image : public Media_Object
    {
        public:
            Image();
            ~Image();

            bool load(const std::string& fileName) override;

    };
}

#endif // IMAGE_HPP_INCLUDED
