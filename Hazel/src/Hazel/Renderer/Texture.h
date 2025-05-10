//
// Created by tanhao on 2025/5/9.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "Hazel/Core/Core.h"

namespace Hazel
{
    class HAZEL_API Texture {


    public:
        virtual ~Texture() = default;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot) const = 0;

    };

    class HAZEL_API Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string path);
    };





}
#endif //TEXTURE_H
