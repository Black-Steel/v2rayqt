#ifndef CONFIG_CONSTEXPR_H
#define CONFIG_CONSTEXPR_H

#include "os_define.h"

constexpr char DEFAULT_CONFIG_TEMPLATE_DIR[] =  "$HOME/v2rayqt_config/template";
constexpr char DEFAULT_CONFIG_SUBSCRIPTION_DIR[] =  "$HOME/v2rayqt_config/subscription";
constexpr char DEFAULT_GUI_CONFIG_FILENAME[] =  "$HOME/v2rayqt_config/gui_config.json";
constexpr char DEFAULT_V2RAY_EXEC_CONFIG_FILENAME[] =  "$HOME/v2rayqt_config/v2ray_exec_config.json";

#if defined(OS_WINDOWS)
constexpr char DEFAULT_V2RAY_DIR[] = "$HOME/v2rayqt_config/v2ray_core";
constexpr char DEFAULT_V2RAY_EXEC[] = "$HOME/v2rayqt_config/v2ray_core/v2ray.exe";
#elif defined(OS_LINUX)
constexpr char DEFAULT_V2RAY_DIR[] = "$HOME/v2rayqt_config/v2ray_core";
constexpr char DEFAULT_V2RAY_EXEC[] = "$HOME/v2rayqt_config/v2ray_core/v2ray";
#endif


#endif // CONFIG_CONSTEXPR_H
