#include <impl-private.hpp>

static char info[] = {'I',
                      'N',
                      'F',
                      'O',
                      ':',
                      's',
                      't',
                      'o',
                      'r',
                      'a',
                      'g',
                      'e',
                      '[',
                      '0' + ((sizeof(impl::impl_private) / 10000) % 10),
                      '0' + ((sizeof(impl::impl_private) / 1000) % 10),
                      '0' + ((sizeof(impl::impl_private) / 100) % 10),
                      '0' + ((sizeof(impl::impl_private) / 10) % 10),
                      '0' + (sizeof(impl::impl_private) % 10),
                      ':',
                      '0' + ((alignof(impl::impl_private) / 10000) % 10),
                      '0' + ((alignof(impl::impl_private) / 1000) % 10),
                      '0' + ((alignof(impl::impl_private) / 100) % 10),
                      '0' + ((alignof(impl::impl_private) / 10) % 10),
                      '0' + (alignof(impl::impl_private) % 10),
                      ']',
                      '\0'};

int main(int argc, char* argv[])
{
  int require = 0;
  require += info[argc];
  (void)argv;
  return require;
}
