#ifndef TAPE_BASE_H
#define TAPE_BASE_H

#include <cstddef>

template<typename T>
class TapeBase{
public:
    TapeBase() : cur_{0}, len_{0} {}
    virtual ~TapeBase() = default;

    virtual size_t get_cur() const = 0;
    virtual size_t get_length() const = 0;
    virtual T read() const = 0;
    virtual void write(const T& data) = 0;

    virtual void shift_left() = 0;
    virtual void shift_right() = 0;
    virtual void wind_left(size_t len) = 0;
    virtual void wind_right(size_t len) = 0;
protected:
    size_t cur_,len_;
};

#endif