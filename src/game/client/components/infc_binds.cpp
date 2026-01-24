#include "infc_binds.h"

#include <engine/shared/infclass.h>
#include <game/client/gameclient.h>

void CInfCBinds::OnConsoleInit()
{
	// bindings
	IConfigManager *pConfigManager = Kernel()->RequestInterface<IConfigManager>();
	if(pConfigManager)
		pConfigManager->RegisterCallback(ConfigSaveCallback, this);
	
	Console()->Register("infc_bind", "s[key] ?r[command]", CFGFLAG_CLIENT, ConBind, this, "Bind key to execute a command or view keybindings");
	Console()->Register("infc_binds", "?s[key]", CFGFLAG_CLIENT, ConBinds, this, "Print command executed by this keybindind or all binds");
	Console()->Register("infc_unbind", "s[key]", CFGFLAG_CLIENT, ConUnbind, this, "Unbind key");
	Console()->Register("infc_unbindall", "", CFGFLAG_CLIENT, ConUnbindAll, this, "Unbind all keys");

	// default bindings
	SetDefaults();
}

bool CInfCBinds::OnInput(const IInput::CEvent &Event)
{
	if(!GameClient()->m_GameInfo.m_InfClass)
		return false;

	return CBinds::OnInput(Event);
}

void CInfCBinds::ConfigSaveCallback(IConfigManager *pConfigManager, void *pUserData)
{
	CInfCBinds *pSelf = (CInfCBinds *)pUserData;

	pConfigManager->WriteLine("infc_unbindall", InfclassConfigDomainId());
	for(int Modifier = KeyModifier::NONE; Modifier < KeyModifier::COMBINATION_COUNT; Modifier++)
	{
		for(int Key = KEY_FIRST; Key < KEY_LAST; Key++)
		{
			if(!pSelf->m_aapKeyBindings[Modifier][Key])
				continue;

			char *pBuf = pSelf->GetKeyBindCommand(Modifier, Key);
			char pBuf2[128];
			str_format(pBuf2, sizeof(pBuf2), "infc_%s", pBuf); 
			pConfigManager->WriteLine(pBuf2, InfclassConfigDomainId());
			free(pBuf);
		}
	}
}

void CInfCBinds::SetDefaults()
{
	UnbindAll();
}
