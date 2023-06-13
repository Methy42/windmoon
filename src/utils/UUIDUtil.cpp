#include "utils/UUIDUtil.h"

#include <string>

#ifdef _WIN32
    #include <windows.h>
    #include <stdio.h>
    #include <Rpc.h>
#elif __linux__
    #include <uuid/uuid.h> // For Linux-based systems
#elif __APPLE__
    #include <CoreFoundation/CFUUID.h> // For macOS and iOS
#endif
std::string UUIDUtil::generateUUID()
{
    std::string uuid_str;

#ifdef _WIN32
    // Use CoCreateGuid to generate a GUID on Windows
    GUID guid;
    CoCreateGuid(&guid);
    char szGuid[39] = {0};
    sprintf_s(szGuid, 39, "%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", guid.Data1, guid.Data2, guid.Data3,
       guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    uuid_str = szGuid;
#elif __linux__
    // Use uuid_generate to generate a UUID on Linux
    uuid_t uuid;
    uuid_generate(uuid);
    char uuid_cstr[37];
    uuid_unparse_upper(uuid, uuid_cstr);
    uuid_str = uuid_cstr;
#elif __APPLE__
    // Use CFUUIDCreate to generate a UUID on macOS and iOS
    CFUUIDRef uuid = CFUUIDCreate(NULL);
    CFStringRef uuid_str_ref = CFUUIDCreateString(NULL, uuid);
    CFRelease(uuid);
    char uuid_cstr[37];
    CFStringGetCString(uuid_str_ref, uuid_cstr, 37, kCFStringEncodingASCII);
    CFRelease(uuid_str_ref);
    uuid_str = uuid_cstr;
#endif

    return uuid_str;
}
