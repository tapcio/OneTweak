#include "stdafx.h"
#include "PluginAPI_F4SE.h"

#include "Fallout4Host.h"

Fallout4Config::Fallout4Config()
{

}

Fallout4Config::~Fallout4Config()
{

}

void Fallout4Config::OnReadConfig(CSimpleIniA* ini)
{
	if (!ini) return;

	_MESSAGE(__FUNCTION__);

	ClassName = ini->GetValue("Fallout4", "ClassName", "Fallout4");
	WindowName = ini->GetValue("Fallout4", "WindowName", "Fallout4");
}

extern "C"
{
    bool __cdecl F4SEPlugin_Query(const F4SEInterface * fose, PluginInfo * info)
    {
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\f4se_OneTweak.log");

        _MESSAGE(__FUNCTION__);
        // populate info structure
        info->infoVersion =	PluginInfo::kInfoVersion;
        info->name =		"OneTweak";
        info->version =     VERSION_REVISION;

        if(fose->isEditor)
        {
            return false;
        }
        return true;
    }

    bool __cdecl F4SEPlugin_Load(const F4SEInterface * fose)
    {
        _MESSAGE(__FUNCTION__);

		g_Host.reset(new Fallout4Host(fose));

		return g_Host ? g_Host->Run() : 0;
    }
};