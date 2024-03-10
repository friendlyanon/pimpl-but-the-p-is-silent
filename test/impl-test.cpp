#include <impl.hpp>

int main(int, char*[])
{
  auto instance = impl::impl();
  return instance.add(1) == 2 ? 0 : 1;
}
