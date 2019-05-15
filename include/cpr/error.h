#ifndef CPR_ERROR_H
#define CPR_ERROR_H

#include <cstdint>
#include <string>
#include <system_error>

#include "cpr/cprtypes.h"
#include "cpr/defines.h"

namespace cpr {

enum class ErrorCode {
    OK = 0,
    CONNECTION_FAILURE,
    EMPTY_RESPONSE,
    HOST_RESOLUTION_FAILURE,
    INTERNAL_ERROR,
    INVALID_URL_FORMAT,
    NETWORK_RECEIVE_ERROR,
    NETWORK_SEND_FAILURE,
    OPERATION_TIMEDOUT,
    PROXY_RESOLUTION_FAILURE,
    SSL_CONNECT_ERROR,
    SSL_LOCAL_CERTIFICATE_ERROR,
    SSL_REMOTE_CERTIFICATE_ERROR,
    SSL_CACERT_ERROR,
    GENERIC_SSL_ERROR,
    UNSUPPORTED_PROTOCOL,
    UNKNOWN_ERROR = 1000,
};

class Error {
  public:
    Error() : code{ErrorCode::OK} {}

    template <typename TextType>
    Error(const std::int32_t& curl_code, TextType&& p_error_message)
            : code{getErrorCodeForCurlError(curl_code)}, message{CPR_FWD(p_error_message)} {}

    explicit operator bool() const {
        return code != ErrorCode::OK;
    }

    ErrorCode code;
    std::string message;

  private:
    static ErrorCode getErrorCodeForCurlError(std::int32_t curl_code);
};


} // namespace cpr

namespace std {
template <>
struct is_error_code_enum<cpr::ErrorCode> : std::true_type {};
} // namespace std

namespace detail {
class ErrorCode_category : public std::error_category {
  public:
    virtual const char* name() const noexcept override final;
    virtual std::string message(int c) const override final;
    virtual std::error_condition default_error_condition(int c) const noexcept override final;
};
} // namespace detail

namespace cpr {
#define ERRORCODE_API_DECL extern inline
ERRORCODE_API_DECL const detail::ErrorCode_category& ErrorCode_category() {
    static detail::ErrorCode_category c;
    return c;
}

inline std::error_code make_error_code(cpr::ErrorCode e) {
    return {static_cast<int>(e), ErrorCode_category()};
}

} // namespace cpr

#endif
