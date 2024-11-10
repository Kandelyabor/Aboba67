#include "Exception.h"

BookstoreException::BookstoreException(const std::string& msg) 
    : m_errorMsg("ОШИБКА: " + msg) {}

const char* BookstoreException::what() const noexcept {
    return m_errorMsg.c_str();
}
