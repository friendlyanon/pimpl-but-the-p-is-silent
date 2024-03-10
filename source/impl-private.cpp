#include <impl-private.hpp>

namespace impl
{

impl_private::impl_private(int y)
    : _y(y)
{
}

int impl_private::add(int x) const
{
  return x + _y;
}

}  // namespace impl
