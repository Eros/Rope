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

void RString::swap(RString & b) {
    std::swap(_str_, b._str_);
    std::swap(str_len, b.str_len);
}

const char * RString::c_str() const {
    return _str_;
}

const char * RString::copy_str(const char * s) {
    if(s){
        size_t len = strlen(s); //todo check why the strlen wont accept int for the max size comparison
        alloc_str(len);
        strncpy((char *) _str_, s, len);
    }
    return _str_;
}

void RString::append_split_array(const RString &s) const {
    if(split_count >= RString_MAX_LEN)
        return;
    if(!split_count){
        split_array.reset(new _rsp[RString_MAX_SPLIT]);
    }
    split_array[split_count] = std::make_shared<RString>(s);+
    ++split_count;
}

const char* RString::alloc_str(size_t s){
    if(_str_)
        reset();
    str_len = (s > RString_MAX_LEN) ? RString_MAX_LEN : s;
    return _str_;
}