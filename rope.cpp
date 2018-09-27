#include "rope.hpp"
#pragma mark - constructors/destructors

RString::RString() { reset(); }
RString::RString(const char * s) { copy_str(s); }
RString::RString(const RString & old) { copy_str(old); }
RString::~RString() { reset(); }

RString::RString(RString && other) NOEXCEPT {
    reset();
    _str = other._str_;
    _str_len = other.str_len;
    other._str_ = nullptr;
    other.str_len = 0;
    other.reset();
    return;
}
#pragma mark - private methods

void RString::reset() {
    reset_split_array();
    if(_str_){
        delete [] _str_;
        _str_ = nullptr;
        str_len = 0;
    }
}

void RString::reset_split_array() const {
    if(split_count){
        while(split_count){
            split_array[--split_count].reset();
        }
        split_array.reset();
        split_count = 0;
    }
}