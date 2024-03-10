#include <new>
#include <type_traits>

#include <impl-private.hpp>
#include <impl.hpp>

namespace impl
{

template<typename T>
using impl_t = std::conditional_t<std::is_const_v<std::remove_pointer_t<T>>,
                                  impl_private const,
                                  impl_private>*;

#define IMPL std::launder(reinterpret_cast<impl_t<decltype(this)>>(buffer))

impl::impl()
{
  (void)new (buffer) impl_private(1);
}

impl::~impl()
{
  IMPL->~impl_private();
}

int impl::add(int x) const
{
  return IMPL->add(x);
}

}  // namespace impl
