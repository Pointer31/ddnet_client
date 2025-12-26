#include "teeinfo.h"

#include <base/color.h>
#include <base/system.h>

class CStandardSkin
{
public:
	char m_aSkinName[MAX_SKIN_LENGTH];
	char m_aaSkinPartNames[protocol7::NUM_SKINPARTS][protocol7::MAX_SKIN_LENGTH];
	bool m_aUseCustomColors[protocol7::NUM_SKINPARTS];
	int m_aSkinPartColors[protocol7::NUM_SKINPARTS];
};

static constexpr CStandardSkin STANDARD_SKINS[] = {
	{"default", {"standard", "", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {1798004, 0, 0, 1799582, 1869630, 0}},
	{"bluekitty", {"kitty", "whisker", "", "standard", "standard", "negative"}, {true, true, false, true, true, true}, {8681144, -8229413, 0, 7885547, 8868585, 9043712}},
	{"bluestripe", {"standard", "stripes", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {10187898, 0, 0, 750848, 1944919, 0}},
	{"brownbear", {"bear", "bear", "hair", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {1082745, -15634776, 0, 1082745, 1147174, 0}},
	{"cammostripes", {"standard", "cammostripes", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {5334342, -14840320, 0, 750848, 1944919, 0}},
	{"cammo", {"standard", "cammo2", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {5334342, -11771603, 0, 750848, 1944919, 0}},
	{"limekitty", {"kitty", "whisker", "", "standard", "standard", "negative"}, {true, true, false, true, true, true}, {4612803, -12229920, 0, 3827951, 3827951, 8256000}},
	{"pinky", {"standard", "whisker", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {15911355, -801066, 0, 15043034, 15043034, 0}},
	{"redbopp", {"standard", "donny", "unibop", "standard", "standard", "standard"}, {true, true, true, true, true, false}, {16177260, -16590390, 16177260, 16177260, 7624169, 0}},
	{"redstripe", {"standard", "stripe", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {16307835, 0, 0, 184, 9765959, 0}},
	{"saddo", {"standard", "saddo", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {7171455, -9685436, 0, 3640746, 5792119, 0}},
	{"toptri", {"standard", "toptri", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {6119331, 0, 0, 3640746, 5792119, 0}},
	{"twinbop", {"standard", "duodonny", "twinbopp", "standard", "standard", "standard"}, {true, true, true, true, true, false}, {15310519, -1600806, 15310519, 15310519, 37600, 0}},
	{"twintri", {"standard", "twintri", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {3447932, -14098717, 0, 185, 9634888, 0}},
	{"warpaint", {"standard", "warpaint", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {1944919, 0, 0, 750337, 1944919, 0}},
	/* custom */
	{"nanami", {"raccoon", "mice", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {2686817, (int)4282737407, 0, 2686817, 3827951, 0}},
	{"mermydon", {"kitty", "sidemarks", "", "standard", "standard", "standard"}, {true, false, false, true, true, false}, {1769313, (int)4282737407, 0, 1769313, 3827951, 0}},
	{"greensward", {"greensward", "duodonny", "", "standard", "standard", "standard"}, {true, true, false, false, false, false}, {5635840, -11141356, 65408, 65408, 65408, 65408}},
	{"monkey", {"monkey", "monkey", "hair", "standard", "standard", "standard"}, {true, true, false, false, false, false}, {1421252, (int)4279665714, 2352795, 1659536, 1274287, 65408}},
	/* coala, but it was moved to the end to ensure coala_ skins look better*/
	{"coala", {"koala", "twinbelly", "", "standard", "standard", "standard"}, {true, true, false, true, true, false}, {184, -15397662, 0, 184, 9765959, 0}},
};

CTeeInfo::CTeeInfo(const char *pSkinName, int UseCustomColor, int ColorBody, int ColorFeet)
{
	str_copy(m_aSkinName, pSkinName);
	m_UseCustomColor = UseCustomColor;
	m_ColorBody = ColorBody;
	m_ColorFeet = ColorFeet;
}

CTeeInfo::CTeeInfo(const char *apSkinPartNames[protocol7::NUM_SKINPARTS], int aUseCustomColors[protocol7::NUM_SKINPARTS], int aSkinPartColors[protocol7::NUM_SKINPARTS])
{
	for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
	{
		str_copy(m_aaSkinPartNames[Part], apSkinPartNames[Part]);
		m_aUseCustomColors[Part] = aUseCustomColors[Part];
		m_aSkinPartColors[Part] = aSkinPartColors[Part];
	}
}

void CTeeInfo::ToSixup()
{
	// reset to default skin
	for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
	{
		str_copy(m_aaSkinPartNames[Part], STANDARD_SKINS[0].m_aaSkinPartNames[Part]);
		m_aUseCustomColors[Part] = STANDARD_SKINS[0].m_aUseCustomColors[Part];
		m_aSkinPartColors[Part] = STANDARD_SKINS[0].m_aSkinPartColors[Part];
	}

	// check for standard skin
	bool StandardSkinFound = false;
	for(const auto &StandardSkin : STANDARD_SKINS)
	{
		if(str_comp(m_aSkinName, StandardSkin.m_aSkinName) == 0)
		{
			for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
			{
				str_copy(m_aaSkinPartNames[Part], StandardSkin.m_aaSkinPartNames[Part]);
				m_aUseCustomColors[Part] = StandardSkin.m_aUseCustomColors[Part];
				m_aSkinPartColors[Part] = StandardSkin.m_aSkinPartColors[Part];
			}
			StandardSkinFound = true;
			break;
		}
	}

	if(str_comp_nocase(m_aSkinName, "1Hamster Ball Small2_KZ") == 0)
		{
			for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
				m_aSkinPartColors[Part] = 8180455;
			StandardSkinFound = true;
		}
	else if(str_comp_nocase(m_aSkinName, "1Hamster Ball Small1_KZ") == 0)
		{
			for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
				m_aSkinPartColors[Part] = 8126486;
			StandardSkinFound = true;
		}
	else if(str_comp_nocase(m_aSkinName, "AutismCreature") == 0)
		{
			for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
				m_aSkinPartColors[Part] = 1102591;
			StandardSkinFound = true;
		}
	else if(str_comp_nocase(m_aSkinName, "pointy_cactus") == 0)
		{
			for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
				m_aSkinPartColors[Part] = 3388754;
			m_aUseCustomColors[protocol7::SKINPART_DECORATION] = true;
			m_aSkinPartColors[protocol7::SKINPART_DECORATION] = 51002;
			str_copy(m_aaSkinPartNames[protocol7::SKINPART_DECORATION], "twinpen");
			m_aSkinPartColors[protocol7::SKINPART_FEET] = 3388686;
			StandardSkinFound = true;
		}
	
	if (!StandardSkinFound)
	{
		m_aUseCustomColors[1] = true;
		m_aSkinPartColors[1] = 1040187392;

		if(str_find(m_aSkinName, "jeet"))
		{
			for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
				m_aSkinPartColors[Part] = 10456660;
			m_aSkinPartColors[protocol7::SKINPART_FEET] = 1102591;
			StandardSkinFound = true;
		}
		else if(str_find(m_aSkinName, "greyfox"))
		{
			for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
				m_aSkinPartColors[Part] = 10420388;
			m_aSkinPartColors[protocol7::SKINPART_FEET] = 1048651;
			StandardSkinFound = true;
		}
		else if(str_find(m_aSkinName, "kintaro_2"))
		{
			for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
				m_aSkinPartColors[Part] = 1102591;
			m_aSkinPartColors[1] = 4278255360;
			m_aSkinPartColors[protocol7::SKINPART_FEET] = 8126486;
			StandardSkinFound = true;
		}

		// check for standard skin
		for(const auto &StandardSkin : STANDARD_SKINS)
		{
			if(str_find_nocase(m_aSkinName, StandardSkin.m_aSkinName))
			{
				for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
				{
					str_copy(m_aaSkinPartNames[Part], StandardSkin.m_aaSkinPartNames[Part]);
					m_aUseCustomColors[Part] = StandardSkin.m_aUseCustomColors[Part];
					m_aSkinPartColors[Part] = StandardSkin.m_aSkinPartColors[Part];
				}
				break;
			}
		}

		if (str_find_nocase(m_aSkinName, "kitty") || str_find_nocase(m_aSkinName, "nanami"))
		{
			str_copy(m_aaSkinPartNames[0], "kitty");
		}
		else if (str_find_nocase(m_aSkinName, "coala"))
		{
			str_copy(m_aaSkinPartNames[0], "koala");
		}
		else if (str_find_nocase(m_aSkinName, "fox"))
		{
			str_copy(m_aaSkinPartNames[0], "fox");
		}
		else if (str_find_nocase(m_aSkinName, "mouse") || str_find_nocase(m_aSkinName, "hammie"))
		{
			str_copy(m_aaSkinPartNames[0], "mouse");
		}
		else if (str_find_nocase(m_aSkinName, "bear"))
		{
			str_copy(m_aaSkinPartNames[0], "bear");
		}
		else if (str_find_nocase(m_aSkinName, "jeet") || str_find_nocase(m_aSkinName, "kintaro_2"))
		{
			str_copy(m_aaSkinPartNames[0], "force");
		}

		if (str_find_nocase(m_aSkinName, "cammostripes") || str_find_nocase(m_aSkinName, "kintaro_2"))
		{
			str_copy(m_aaSkinPartNames[1], "cammostripes");
		}
		else if (str_find_nocase(m_aSkinName, "saddo"))
		{
			str_copy(m_aaSkinPartNames[1], "saddo");
		}
	}

	if(m_UseCustomColor)
	{
		bool DarkMarking = m_aUseCustomColors[protocol7::SKINPART_MARKING];
		const int ColorBody = ColorHSLA(m_ColorBody).UnclampLighting(0.4f).Pack(ColorHSLA::DARKEST_LGT7);
		const int ColorMarking = DarkMarking ? 1241448448 : ColorHSLA(m_ColorBody).UnclampLighting(0.3f).Pack(0.0f, true);
		const int ColorFeet = ColorHSLA(m_ColorFeet).UnclampLighting(0.4f).Pack(ColorHSLA::DARKEST_LGT7);
		m_aUseCustomColors[protocol7::SKINPART_BODY] = true;
		m_aUseCustomColors[protocol7::SKINPART_MARKING] = true;
		m_aUseCustomColors[protocol7::SKINPART_DECORATION] = true;
		m_aUseCustomColors[protocol7::SKINPART_HANDS] = true;
		m_aUseCustomColors[protocol7::SKINPART_FEET] = true;
		m_aSkinPartColors[protocol7::SKINPART_BODY] = ColorBody;
		m_aSkinPartColors[protocol7::SKINPART_MARKING] = ColorMarking;
		m_aSkinPartColors[protocol7::SKINPART_DECORATION] = ColorBody;
		m_aSkinPartColors[protocol7::SKINPART_HANDS] = ColorBody;
		m_aSkinPartColors[protocol7::SKINPART_FEET] = ColorFeet;
	}
}

void CTeeInfo::FromSixup()
{
	// reset to default skin
	str_copy(m_aSkinName, "default");
	m_UseCustomColor = false;
	m_ColorBody = 0;
	m_ColorFeet = 0;

	// check for standard skin
	for(const auto &StandardSkin : STANDARD_SKINS)
	{
		bool Match = true;
		for(int Part = 0; Part < protocol7::NUM_SKINPARTS; Part++)
		{
			if(str_comp(m_aaSkinPartNames[Part], StandardSkin.m_aaSkinPartNames[Part]) != 0 ||
				m_aUseCustomColors[Part] != StandardSkin.m_aUseCustomColors[Part] ||
				(m_aUseCustomColors[Part] && m_aSkinPartColors[Part] != StandardSkin.m_aSkinPartColors[Part]))
			{
				Match = false;
				break;
			}
		}
		if(Match)
		{
			str_copy(m_aSkinName, StandardSkin.m_aSkinName);
			return;
		}
	}

	// find closest match
	int BestMatches = -1;
	const CStandardSkin *pBestSkin = &STANDARD_SKINS[0];
	for(const auto &StandardSkin : STANDARD_SKINS)
	{
		int Matches = 0;
		for(int Part = 0; Part <= protocol7::SKINPART_DECORATION; Part++) // not all parts are considered for comparison
		{
			if(str_comp(m_aaSkinPartNames[Part], StandardSkin.m_aaSkinPartNames[Part]) == 0)
			{
				Matches++;
			}
		}
		if(Matches > BestMatches)
		{
			BestMatches = Matches;
			pBestSkin = &StandardSkin;
		}
	}

	str_copy(m_aSkinName, pBestSkin->m_aSkinName);

	if(str_comp(m_aaSkinPartNames[0], "bat") == 0
	|| str_comp(m_aaSkinPartNames[0], "piglet")  == 0
	|| str_comp(m_aaSkinPartNames[0], "dog") == 0
	|| str_comp(m_aaSkinPartNames[0], "raccoon") == 0
	)
		str_copy(m_aSkinName, "bluekitty");

	if(str_comp(m_aaSkinPartNames[0], "fox") == 0
	)
		str_copy(m_aSkinName, "greyfox");

	if(str_comp(m_aaSkinPartNames[0], "mouse") == 0
	)
		str_copy(m_aSkinName, "mouse");

	if(str_comp(m_aaSkinPartNames[0], "hippo") == 0
	|| str_comp(m_aaSkinPartNames[0], "beaver") == 0
	)
		str_copy(m_aSkinName, "brownbear");

	m_UseCustomColor = true;
	m_ColorBody = ColorHSLA(m_aUseCustomColors[protocol7::SKINPART_BODY] ? m_aSkinPartColors[protocol7::SKINPART_BODY] : 255)
			      .UnclampLighting(ColorHSLA::DARKEST_LGT7)
			      .Pack(ColorHSLA::DARKEST_LGT);
	m_ColorFeet = ColorHSLA(m_aUseCustomColors[protocol7::SKINPART_FEET] ? m_aSkinPartColors[protocol7::SKINPART_FEET] : 255)
			      .UnclampLighting(ColorHSLA::DARKEST_LGT7)
			      .Pack(ColorHSLA::DARKEST_LGT);
}
