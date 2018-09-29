#ifndef ROPE_LIBRARY_H
#define ROPE_LIBRARY_H


#ifdef MSC_VER
#define CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4068) //disable pragrma warnings
#include <cstdarg>
int vasprintf(char **ret, const char  *format, va_list ap);
#else
#define NOEXCEPT noexcept
#endif

#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cctype>
#include <memory>

#define RString_VERSION 1
#define RString_MAX_LEN 65535
#define RString_MAX_SPLIT 1023

class RString {
    typedef std::shared_ptr<RString> _rsp;
    typedef std::unique_ptr<_rsp[]> split_ptr;
    char *_str_ = nullptr;
    size_t str_len = 0;
    mutable split_ptr split_array;
    mutable size_t split_count = 0;
    virtual void reset_split_array() const = 0;
    virtual void append_split_array(const RString & s) const = 0;

public:
    typedef split_ptr;
   static const char * version() { return reinterpret_cast<const char *>(RString_VERSION); }
   RString();
   RString(const char * s);
   RString(const RString &);
   RString(RString &&) NOEXCEPT;
   ~RString();

   //methods used to manage data
   const char *  copy_str(const char *);
   const char *  c_str() const;
   const char * alloc_str(size_t s);
   void reset();
   void swap(RString & b);

   //util methods

   const char & back() const;
   const char & front() const;
   bool have_value() const;
   size_t length() const {return str_len;}
   size_t size() const {return str_len;}//dont ask me why this is the same, you'll see later!
   RString & format(const char * format, ...);
   RString & trim();
   RString & lower() const;
   RString & upper() const;
   //operators
   bool operator = (const RString &) const;
   bool operator == (const RString &) const;
   bool operator != (const RString &) const;
   bool operator > (const RString &) const;
   bool operator < (const RString &) const;
   bool operator >= (const RString &) const;
   bool operator <= (const RString &) const;
   const char operator[] (const int) const;
   RString & operator = (const char * other);
   RString & operator += (const char *);
   RString & operator += (const RString *);
   operator const char * () const;

   //find, replace and that shit
   long int char_find(const char & match) const;
   long find(const RString & match) const;
   const RString & replace(const RString & match, const RString & replace);
   const RString & char_repl(const char & match, const char & replace);
   RString & substring(size_t start, size_t length);

   //split methods
   const split_ptr & split(const char * match) const;
   const split_ptr & split(const char match) const;
   const split_ptr & split(const char * match, int split_size) const;
};

#endif
