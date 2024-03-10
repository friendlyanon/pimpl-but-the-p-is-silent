#pragma once

namespace impl
{

class impl_private
{
public:
  explicit impl_private(int y);

  int add(int x) const;

private:
  int _y;
};

}  // namespace impl
