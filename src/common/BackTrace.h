#ifndef CEPH_BACKTRACE_H
#define CEPH_BACKTRACE_H

#include <iosfwd>
#ifdef HAVE_EXECINFO_H
#include <execinfo.h>
#endif
#include <stdlib.h>

namespace ceph {

struct BackTrace {
  const static int max = 100;

  int skip;
  void *array[max];
  size_t size;
  char **strings;

  BackTrace(int s) : skip(s) {
#ifdef HAVE_EXECINFO_H
    size = backtrace(array, max);
    strings = backtrace_symbols(array, size);
#else
    skip = 0;
    size = 0;
#endif
  }
  ~BackTrace() {
    free(strings);
  }

  BackTrace(const BackTrace& other);
  const BackTrace& operator=(const BackTrace& other);

  void print(std::ostream& out);
};

}

#endif
