#include <hyprland/src/plugins/PluginAPI.hpp>
#include <cstdlib>

inline HANDLE PHANDLE = nullptr;
// Do NOT change this function.
APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}
APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    const std::string HASH = __hyprland_api_get_hash();

    // ALWAYS add this to your plugins. It will prevent random crashes coming from
    // mismatched header versions.
    if (HASH != GIT_COMMIT_HASH) {
        HyprlandAPI::addNotification(PHANDLE, "[MyPlugin] Mismatched headers! Can't proceed.",
                                     CColor{1.0, 0.2, 0.2, 1.0}, 5000);
        throw std::runtime_error("[MyPlugin] Version mismatch");
    }

    return {"wallpaper switcher", "plugin to change my wallpapers", "polyface", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() {
    const std::string random = "$(find /home/polyface/Pictures/wallpapers | shuff -n 1)";
    int ret_hyprlock = system("magick convert [random] /home/polyface/.config/background.png");
    if (ret_hyprlock != 0) {
        HyprlandAPI::addNotification(PHANDLE, "error setting the wallpaper of hyprlock", CColor{1.0, 0.2, 0.2, 1.0}, 5000);
    }
    int ret_grub = system("magick convert [random] /boot/grub/themes/Nyarch-theme/background.png");
    if (ret_hyprlock != 0) {
            HyprlandAPI::addNotification(PHANDLE, "error setting the wallpaper of hyprlock", CColor{1.0, 0.2, 0.2, 1.0}, 5000);
        }
}
