/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IRenderTarget
*/

#ifndef PAML_IRENDERTARGET_HPP_
    #define PAML_IRENDERTARGET_HPP_

    #include "../System/INonCopyable.hpp"
    #include "../System/IVector2.hpp"
    #include "../System/Type.hpp"

    #include "../Graphics/IDrawable.hpp"

namespace paml {

    class IRenderTarget : public INonCopyable {

        public:

            virtual ~IRenderTarget() = default;

            virtual IVector2<float> mapPixelToCoords (const IVector2<uint32_t> &point) const = 0;
    };

} // namespace paml

#endif /* !PAML_IRENDERTARGET_HPP_ */