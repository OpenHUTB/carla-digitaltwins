// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "Carla/Exception.h"

#include <Carla/disable-ue4-macros.h>
#include <boost/assert/source_location.hpp>
#include <Carla/enable-ue4-macros.h>
// =============================================================================
// -- Define boost::throw_exception --------------------------------------------
// =============================================================================

#ifdef BOOST_NO_EXCEPTIONS

namespace boost {

  void throw_exception(const std::exception &e) {
    carla::throw_exception(e);
  }

  void throw_exception(
      const std::exception &e,
      boost::source_location const & loc) {
    throw_exception(e);
  }

} // namespace boost

#endif // BOOST_NO_EXCEPTIONS

// =============================================================================
// -- Workaround for Boost.Asio bundled with rpclib ----------------------------
// =============================================================================

#ifdef ASIO_NO_EXCEPTIONS

#include <exception>
#include <system_error>
#include <typeinfo>

namespace clmdep_asio {
namespace detail {

  template <typename Exception>
  void throw_exception(const Exception& e) {
    carla::throw_exception(e);
  }

  template void throw_exception<std::bad_cast>(const std::bad_cast &);
  template void throw_exception<std::exception>(const std::exception &);
  template void throw_exception<std::system_error>(const std::system_error &);

} // namespace detail
} // namespace clmdep_asio

#endif // ASIO_NO_EXCEPTIONS
