#include<unordered_map>
#include<vector>
#include<functional>
#include<cstdlib>


namespace he
{
    template<typename T>
    struct plane_position
    {
        T x, y;

        plane_position(T x, T y);
    };

    template<typename T>
    struct space_position
    {
        T x, y, z;

        space_position(T x, T y, T z);
    };
}

template<typename T>
inline T sign(T number);

inline unsigned int Z_to_N(int z);

inline int NxN_to_N(unsigned int x, unsigned int y);


/*
 * n(n+1) ~ n^2
 * ceil(sqrt(2*n+1)-0.5)
 *
 */
inline plane_position<unsigned int>
N_to_NxN(unsigned int x);

inline int ZxZ_to_N(int x, int y);


namespace std
{
    template<>
    struct hash<he::plane_position<int> >
    {
        public:
            size_t operator() (const he::plane_position<int>& pos) const
            {
                return ZxZ_to_N(pos.x, pos.y);
            }
    };
}


namespace he
{

    /* each event will have its own spatial_tracking tracker
     * (eg. click event callbacks will be on a different list
     * than hover) */
    template<typename P>
    class spatial_tracking
    {
        private:
            using vect_of_cbs = std::vector<std::function<void(P)> >;
            std::unordered_map<P, vect_of_cbs> callbacks;

            unsigned int lattice_spacing;

        public:
            spatial_tracking();
    };

}

template<typename T>
inline T sign(T number)
{
    return T(number >= 0) - T(number < 0);
}

inline unsigned int Z_to_N(int z)
{
    return 2*std::abs(z) + (sign<int>(z)-1)/2;
}

inline int NxN_to_N(unsigned int x, unsigned int y)
{
    return ((x+y+1)*(x+y))/2 + y;
}

inline int ZxZ_to_N(int x, int y)
{
    return NxN_to_N(Z_to_N(x), Z_to_N(y));
}
