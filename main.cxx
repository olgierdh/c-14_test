#include <utility>

template < typename T, int N > struct tag
{
    constexpr friend auto loophole( tag< T, N > );
    constexpr friend int cloophole( tag< T, N > );
};

template < typename T, typename U, int N > struct fnc_def
{
    constexpr friend auto loophole( tag< T, N > )
    {
        return U{};
    }
    constexpr friend int cloophole( tag< T, N > )
    {
        return 0;
    }
};

template < typename T, int N > struct c_op
{
    template < typename U, typename = decltype( fnc_def< T, U, N >{}, tag< T, N >{} ) >
    operator U();
};

template < typename T > struct m_tag
{
    constexpr friend auto get_m( m_tag< T > );
};

template < typename T, typename N > struct map_impl
{
    constexpr friend auto get_m( m_tag< T > )
    {
        return N{};
    }
};

template < typename First, typename Second > struct m_pair
{
    using first_type  = First;
    using second_type = Second;
};

template < typename T, typename N, typename = decltype( map_impl< T, N >{} ) >
constexpr int register_type_f( m_tag< T > );

template < typename T, typename N >
using register_type = decltype( register_type_f< T, N >( m_tag< T >{} ),
                                register_type_f< N, T >( m_tag< N >{} ) );

template < typename... Ts > struct sequence
{
};

template < typename... P > struct make_map_impl
{
    using value_type =
        sequence< register_type< typename P::first_type, typename P::second_type >... >;
};

template < typename... Ts >
using register_types = typename make_map_impl< Ts... >::value_type;

struct foo
{
    int a;
    char b;
};

struct bar
{
};

int main( int argc, const char* argv[] )
{
#if 1
    using t0 = register_types< m_pair< foo, char >, m_pair< bar, int > >;

    using m_type  = decltype( get_m( m_tag< foo >{} ) );
    using m_type1 = decltype( get_m( m_tag< bar >{} ) );

    static_assert( std::is_same< m_type, char >::value, "" );
    static_assert( std::is_same< m_type1, int >::value, "" );
    static_assert( std::is_same< decltype( get_m( m_tag< int >{} ) ), bar >::value, "" );
    static_assert( std::is_same< decltype( get_m( m_tag< char >{} ) ), foo >::value, "" );

    using value_type = decltype( foo{c_op< foo, 0 >{}, c_op< foo, 1 >{}} );
    static_assert( std::is_same< decltype( loophole( tag< foo, 0 >{} ) ), int >::value,
                   "" );
#endif
    return 0;
}
