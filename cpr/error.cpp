#include "cpr/error.h"
#include <string>

#include <curl/curl.h>

namespace cpr {

ErrorCode Error::getErrorCodeForCurlError(std::int32_t curl_code) {
    switch (curl_code) {
        case CURLE_OK:
            return ErrorCode::OK;
        case CURLE_UNSUPPORTED_PROTOCOL:
            return ErrorCode::UNSUPPORTED_PROTOCOL;
        case CURLE_URL_MALFORMAT:
            return ErrorCode::INVALID_URL_FORMAT;
        case CURLE_COULDNT_RESOLVE_PROXY:
            return ErrorCode::PROXY_RESOLUTION_FAILURE;
        case CURLE_COULDNT_RESOLVE_HOST:
            return ErrorCode::HOST_RESOLUTION_FAILURE;
        case CURLE_COULDNT_CONNECT:
            return ErrorCode::CONNECTION_FAILURE;
        case CURLE_OPERATION_TIMEDOUT:
            return ErrorCode::OPERATION_TIMEDOUT;
        case CURLE_SSL_CONNECT_ERROR:
            return ErrorCode::SSL_CONNECT_ERROR;
        case CURLE_PEER_FAILED_VERIFICATION:
            return ErrorCode::SSL_REMOTE_CERTIFICATE_ERROR;
        case CURLE_GOT_NOTHING:
            return ErrorCode::EMPTY_RESPONSE;
        case CURLE_SSL_ENGINE_NOTFOUND:
            return ErrorCode::GENERIC_SSL_ERROR;
        case CURLE_SSL_ENGINE_SETFAILED:
            return ErrorCode::GENERIC_SSL_ERROR;
        case CURLE_SEND_ERROR:
            return ErrorCode::NETWORK_SEND_FAILURE;
        case CURLE_RECV_ERROR:
            return ErrorCode::NETWORK_RECEIVE_ERROR;
        case CURLE_SSL_CERTPROBLEM:
            return ErrorCode::SSL_LOCAL_CERTIFICATE_ERROR;
        case CURLE_SSL_CIPHER:
            return ErrorCode::GENERIC_SSL_ERROR;
        case CURLE_SSL_CACERT:
            return ErrorCode::SSL_CACERT_ERROR;
        case CURLE_USE_SSL_FAILED:
            return ErrorCode::GENERIC_SSL_ERROR;
        case CURLE_SSL_ENGINE_INITFAILED:
            return ErrorCode::GENERIC_SSL_ERROR;
        case CURLE_SSL_CACERT_BADFILE:
            return ErrorCode::SSL_CACERT_ERROR;
        case CURLE_SSL_SHUTDOWN_FAILED:
            return ErrorCode::GENERIC_SSL_ERROR;
        case CURLE_SSL_CRL_BADFILE:
            return ErrorCode::SSL_CACERT_ERROR;
        case CURLE_SSL_ISSUER_ERROR:
            return ErrorCode::SSL_CACERT_ERROR;
        case CURLE_TOO_MANY_REDIRECTS:
            return ErrorCode::OK;
        default:
            return ErrorCode::INTERNAL_ERROR;
    }
}

} // namespace cpr

namespace detail {
const char* ErrorCode_category::name() const noexcept {
    return "cprErrorCode";
}

std::string ErrorCode_category::message(int c) const {
    switch (static_cast<cpr::ErrorCode>(c)) {
        case cpr::ErrorCode::CONNECTION_FAILURE:
            return "connection failure";
        case cpr::ErrorCode::EMPTY_RESPONSE:
            return "empty response";
        case cpr::ErrorCode::HOST_RESOLUTION_FAILURE:
            return "host resolution failure";
        case cpr::ErrorCode::INTERNAL_ERROR:
            return "internal error";
        case cpr::ErrorCode::INVALID_URL_FORMAT:
            return "invalid url format";
        case cpr::ErrorCode::NETWORK_RECEIVE_ERROR:
            return "network receive error";
        case cpr::ErrorCode::NETWORK_SEND_FAILURE:
            return "network send failure";
        case cpr::ErrorCode::OPERATION_TIMEDOUT:
            return "operation timeout";
        case cpr::ErrorCode::PROXY_RESOLUTION_FAILURE:
            return "proxy resolution failure";
        case cpr::ErrorCode::SSL_CONNECT_ERROR:
            return "ssl connect error";
        case cpr::ErrorCode::SSL_LOCAL_CERTIFICATE_ERROR:
            return "ssl local certificate error";
        case cpr::ErrorCode::SSL_REMOTE_CERTIFICATE_ERROR:
            return "ssl remote certificate error";
        case cpr::ErrorCode::SSL_CACERT_ERROR:
            return "ssl cacert error";
        case cpr::ErrorCode::GENERIC_SSL_ERROR:
            return "generic ssl error";
        case cpr::ErrorCode::UNSUPPORTED_PROTOCOL:
            return "unsupported protocol";
        case cpr::ErrorCode::UNKNOWN_ERROR:
        default:
            return "unknown error";
    }
}

std::error_condition ErrorCode_category::default_error_condition(int c) const noexcept {
    switch (static_cast<cpr::ErrorCode>(c)) {
        case cpr::ErrorCode::CONNECTION_FAILURE:
            return std::errc::not_connected;
        case cpr::ErrorCode::EMPTY_RESPONSE:
            return std::errc::no_message;
        case cpr::ErrorCode::HOST_RESOLUTION_FAILURE:
            return std::errc::bad_address;
        case cpr::ErrorCode::INTERNAL_ERROR:
            return std::errc::state_not_recoverable;
        case cpr::ErrorCode::INVALID_URL_FORMAT:
            return std::errc::bad_address;
        case cpr::ErrorCode::NETWORK_RECEIVE_ERROR:
            return std::errc::bad_message;
        case cpr::ErrorCode::NETWORK_SEND_FAILURE:
            return std::errc::bad_message;
        case cpr::ErrorCode::OPERATION_TIMEDOUT:
            return std::errc::timed_out;
        case cpr::ErrorCode::PROXY_RESOLUTION_FAILURE:
            return std::errc::bad_address;
        case cpr::ErrorCode::SSL_CONNECT_ERROR:
            return std::errc::not_connected;
        case cpr::ErrorCode::SSL_LOCAL_CERTIFICATE_ERROR:
            return std::errc::invalid_argument;
        case cpr::ErrorCode::SSL_REMOTE_CERTIFICATE_ERROR:
            return std::errc::invalid_argument;
        case cpr::ErrorCode::SSL_CACERT_ERROR:
            return std::errc::invalid_argument;
        case cpr::ErrorCode::GENERIC_SSL_ERROR:
            return std::errc::invalid_argument;
        case cpr::ErrorCode::UNSUPPORTED_PROTOCOL:
            return std::errc::protocol_not_supported;
        case cpr::ErrorCode::UNKNOWN_ERROR:
        default:
            return std::errc::state_not_recoverable;
    }
}
} // namespace detail
