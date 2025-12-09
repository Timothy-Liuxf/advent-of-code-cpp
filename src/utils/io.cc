#include "io.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>

#include <curl/curl.h>

#include <common/common.hpp>

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_BEGIN

using namespace std::literals::string_literals;

namespace {
std::once_flag curl_initialized = {};

class Curl {
public:
    Curl() : curl_(::curl_easy_init()) {
        if (this->curl_ == nullptr) [[unlikely]] {
            throw std::runtime_error("Failed to initialize CURL");
        }
    }

    [[nodiscard]] std::string GetContentsFromUrl(const std::string& url) {
        std::string read_buffer;

        ::curl_easy_setopt(curl_, ::CURLOPT_URL, url.c_str());
        ::curl_easy_setopt(curl_, ::CURLOPT_FOLLOWLOCATION, 1L);
        ::curl_easy_setopt(
            curl_, ::CURLOPT_WRITEFUNCTION,
            +[](char* ptr, [[maybe_unused]] size_t size, size_t nmemb, void* data) -> size_t {
                std::string& read_buffer = *reinterpret_cast<std::string*>(data);
                read_buffer.append(ptr, nmemb);
                return nmemb;
            });
        ::curl_easy_setopt(curl_, ::CURLOPT_WRITEDATA, &read_buffer);

        ::CURLcode res = ::curl_easy_perform(curl_);
        if (res != ::CURLE_OK) [[unlikely]] {
            throw std::runtime_error("CURL request failed: "s + std::string(::curl_easy_strerror(res)));
        }

        return read_buffer;
    }

    ~Curl() {
        if (curl_ != nullptr) [[unlikely]] {
            ::curl_easy_cleanup(curl_);
        }
    }

    [[nodiscard]] ::CURL* get() const {
        return curl_;
    }

private:
    ::CURL* curl_;
};
}  // namespace

[[nodiscard]] std::string GetContentsFromUrl(const std::string& url) {
    std::call_once(curl_initialized, []() {
        ::curl_global_init(CURL_GLOBAL_DEFAULT);
    });

    return Curl {}.GetContentsFromUrl(url);
}

[[nodiscard]] std::string GetContentsFromFile(const std::filesystem::path& path) {
    std::ifstream fin(path, std::ios::in);
    std::string   content;
    if (!fin) {
        throw std::runtime_error("Failed to open file: "s + path.string());
    }
    content = (std::ostringstream {} << fin.rdbuf()).str();
    fin.close();
    return content;
}

ADVENT_OF_CODE_CPP_UTILS_NAMESPACE_END
