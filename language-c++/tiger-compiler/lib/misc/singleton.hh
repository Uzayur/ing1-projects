/**
 ** \file misc/singleton.hh
 ** \brief Generic singleton
 */

#pragma once

namespace misc
{
  template <typename T> class Singleton
  {
    // FIXME: Some code was deleted here.
  public:
    // Make it non-copyable
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    // Return the unique instance of this class
    static const T& instance()
    {
      static T instance;
      return instance; /* This seems familiar? */
    }

    Singleton() = default;
  };
} // namespace misc
