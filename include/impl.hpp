#pragma once

#include <impl-export.hpp>
#include <impl-private-storage.hpp>

namespace impl
{

class IMPL_EXPORT impl
{
public:
  impl();
  ~impl();

  int add(int x) const;

private:
  alignas(private_align) unsigned char buffer[private_size];
};

}  // namespace impl
