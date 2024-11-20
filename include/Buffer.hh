#ifndef _TINYMUDUO_BUFFER_H
#define _TINYMUDUO_BUFFER_H

#include <vector>
#include <string>
#include <algorithm>

class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    explicit Buffer(size_t initialSize = kInitialSize);
    ~Buffer();

    size_t readableBytes() const {return writerIndex_ - readerIndex_; }
    size_t writableBytes() const {return buffer_.size() - writerIndex_; }
    size_t prependableBytes() const { return readerIndex_; }
    const char* peek() const { return begin() + readerIndex_; }
    
    void retrieve(size_t len);
    void retrieveAll();
    std::string retrieveAllAsString();
    std::string retrieveAsString(size_t len);

    void ensureWritableBytes(size_t len);

    void append(const char *data, size_t len);

    char* beginWrite() { return begin() + writerIndex_; }
    const char* beginWrite() const { return begin() + writerIndex_; }

    ssize_t readFd(int fd, int *saveErrno);
private:
    char* begin() { return &*buffer_.begin(); }
    const char* begin() const { return &*buffer_.begin(); }

    void makeSpace(size_t len);

    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
};



#endif
