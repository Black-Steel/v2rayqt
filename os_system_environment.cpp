#include "os_system_environment.h"


std::string os_system_environment::get_env(const std::string &key)
{
    const char *env_key = nullptr;
    const char *env_value = nullptr;
    env_key = key.c_str();
    env_value = getenv(env_key);
    return env_value;
}

void os_system_environment::set_env(const std::string &key, const std::string &value)
{
    std::string new_env_str = key + '=' + value;
    std::shared_ptr<char> p_strdup(strdup(new_env_str.c_str()));
    putenv(p_strdup.get());
}

void os_system_environment::delete_env(const std::string &key)
{
    std::shared_ptr<char> p_strdup(strdup(key.c_str()));
    putenv(p_strdup.get());
}
