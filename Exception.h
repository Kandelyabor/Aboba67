#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class BookstoreException : public std::exception {
private:
    std::string m_errorMsg;
public:
    explicit BookstoreException(const std::string& msg);
    const char* what() const noexcept override;
};

#endif // EXCEPTION_H
