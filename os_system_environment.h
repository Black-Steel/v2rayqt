#ifndef OS_SYSTEM_ENVIRONMENT_H
#define OS_SYSTEM_ENVIRONMENT_H

//#define _CRT_NONSTDC_DEPRECATE
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <memory>
#include <malloc.h>

namespace os_system_environment
{
    std::string get_env(const std::string &key);
    void delete_env(const std::string &key);
    void set_env(const std::string &key, const std::string &value);
};

#endif // OS_SYSTEM_ENVIRONMENT_H
