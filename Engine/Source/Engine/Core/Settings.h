#pragma once

namespace Settings {
    const char* const resourcesConfigFile = "Resources.cfg";

#ifdef _DEBUG
    const char* const pluginsConfigFile = "Plugins_d.cfg";
#else
    const char* const pluginsConfigFile = "Plugins.cfg";
#endif

    const char* const configFile = "SolidBlack.cfg";

    const char* const ogreLogFile = "Logs/Ogre.log";
    const char* const myGuiLogFile = "Logs/MyGui.log";

    const char* const ambientLightMaterial = "DeferredShading/AmbientLight";
}