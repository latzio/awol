#ifndef AwolLog_h
#define AwolLog_h

// WIN32 Support
#ifdef WIN32
#define __PRETTY_FUNCTION__ __FUNCDNAME__
#endif

namespace Awol {

    #define TRACE fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);

}

#endif
