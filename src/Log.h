#ifndef AwolLog_h
#define AwolLog_h

// WIN32 Support
#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCDNAME__
#endif

namespace Awol {

    #define TRACE fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);

}

#endif
