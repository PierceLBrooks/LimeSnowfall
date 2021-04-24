
// Author: Pierce Brooks

#ifndef LS_OWNABLE_HPP
#define LS_OWNABLE_HPP

namespace LS
{
    template <typename T>
    class Ownable
    {
        public:
            Ownable() {};
            virtual ~Ownable() {};
            virtual T getOwner() const = 0;
    };
}

#endif // LS_OWNABLE_HPP

