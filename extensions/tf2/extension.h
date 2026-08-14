/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Team Fortress 2 Extension
 * Copyright (C) 2004-2015 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#ifndef _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
#define _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_

/**
 * @file extension.h
 * @brief Sample extension code header.
 */

#include "smsdk_ext.h"
#include <IBinTools.h>
#include <server_class.h>
#include <igameevents.h>

namespace SourceMod {
	class ISDKTools;
}

/**
 * @brief Sample implementation of the SDK Extension.
 * Note: Uncomment one of the pre-defined virtual functions in order to use it.
 */
class TF2Tools : 
	public SDKExtension,
	public ICommandTargetProcessor,
	public IConCommandBaseAccessor,
	public IGameEventListener2,
	public IPluginsListener
{
public: //SDKExtension
	/**
	 * @brief This is called after the initial loading sequence has been processed.
	 *
	 * @param error		Error message buffer.
	 * @param maxlength	Size of error message buffer.
	 * @param late		Whether or not the module was loaded after map load.
	 * @return			True to succeed loading, false to fail.
	 */
	virtual bool SDK_OnLoad(char *error, size_t maxlength, bool late);
	
	/**
	 * @brief This is called right before the extension is unloaded.
	 */
	virtual void SDK_OnUnload();

	/**
	 * @brief This is called once all known extensions have been loaded.
	 * Note: It is is a good idea to add natives here, if any are provided.
	 */
	virtual void SDK_OnAllLoaded();

	/**
	 * @brief this is called when Core wants to know if your extension is working.
	 *
	 * @param error		Error message buffer.
	 * @param maxlength	Size of error message buffer.
	 * @return			True if working, false otherwise.
	 */
	virtual bool QueryRunning(char *error, size_t maxlength);

	void NotifyInterfaceDrop(SMInterface *pInterface);
	bool QueryInterfaceDrop(SMInterface *pInterface);

	const char *GetExtensionVerString();
	const char *GetExtensionDateString();
public: //ICommandTargetProcessor
	bool ProcessCommandTarget(cmd_target_info_t *info);
public: //IConCommandBaseAccessor
	bool RegisterConCommandBase(ConCommandBase *pVar);
public: //IGameEventManager
	IGameEventManager2 *m_GameEventManager;
	void FireGameEvent( IGameEvent *event );
public: //IPluginsListener
	void OnPluginLoaded(IPlugin *plugin);
	void OnPluginUnloaded(IPlugin *plugin);
public:
#if defined SMEXT_CONF_METAMOD
	/**
	 * @brief Called when Metamod is attached, before the extension version is called.
	 *
	 * @param error			Error buffer.
	 * @param maxlength		Maximum size of error buffer.
	 * @param late			Whether or not Metamod considers this a late load.
	 * @return				True to succeed, false to fail.
	 */
	virtual bool SDK_OnMetamodLoad(ISmmAPI *ismm, char *error, size_t maxlength, bool late);
#endif
private:
	bool m_CritDetoursEnabled;
	bool m_CondChecksEnabled;
	bool m_RulesDetoursEnabled;
	bool m_TeleportDetourEnabled;
};

enum TFClassType
{
	TFClass_Unknown = 0,
	TFClass_Scout,
	TFClass_Sniper,
	TFClass_Soldier,
	TFClass_DemoMan,
	TFClass_Medic,
	TFClass_Heavy,
	TFClass_Pyro,
	TFClass_Spy,
	TFClass_Engineer
};

TFClassType ClassnameToType(const char *classname);

extern IBinTools *g_pBinTools;
extern ISDKTools *g_pSDKTools;
extern IGameConfig *g_pGameConf;
extern sm_sendprop_info_t *playerSharedOffset;

extern CGlobalVars *gpGlobals;

void OnServerActivate(edict_t *pEdictList, int edictCount, int clientMax);

int FindResourceEntity();
int FindEntityByNetClass(int start, const char *classname);

extern int g_resourceEntity;

enum TFCond
{
	TF_COND_INVALID                          = -1,
	TF_COND_AIMING                           = 0, // Sniper aiming, Heavy minigun.
	TF_COND_ZOOMED                           = 1,
	TF_COND_DISGUISING                       = 2,
	TF_COND_DISGUISED                        = 3,
	TF_COND_STEALTHED                        = 4, // Spy specific
	TF_COND_INVULNERABLE                     = 5,
	TF_COND_TELEPORTED                       = 6,
	TF_COND_TAUNTING                         = 7,
	TF_COND_INVULNERABLE_WEARINGOFF          = 8,
	TF_COND_STEALTHED_BLINK                  = 9,
	TF_COND_SELECTED_TO_TELEPORT             = 10,
	TF_COND_CRITBOOSTED                      = 11, // DO NOT RE-USE THIS -- THIS IS FOR KRITZKRIEG AND REVENGE CRITS ONLY
	TF_COND_TMPDAMAGEBONUS                   = 12,
	TF_COND_FEIGN_DEATH                      = 13,
	TF_COND_PHASE                            = 14,
	TF_COND_STUNNED                          = 15, // Any type of stun. Check iStunFlags for more info.
	TF_COND_OFFENSEBUFF                      = 16,
	TF_COND_SHIELD_CHARGE                    = 17,
	TF_COND_DEMO_BUFF                        = 18,
	TF_COND_ENERGY_BUFF                      = 19,
	TF_COND_RADIUSHEAL                       = 20,
	TF_COND_HEALTH_BUFF                      = 21,
	TF_COND_BURNING                          = 22,
	TF_COND_HEALTH_OVERHEALED                = 23,
	TF_COND_URINE                            = 24,
	TF_COND_BLEEDING                         = 25,
	TF_COND_DEFENSEBUFF                      = 26, // 35% defense! No crit damage.
	TF_COND_REGENONDAMAGEBUFF                = 27,
	TF_COND_MARKEDFORDEATH                   = 28,
	TF_COND_NOHEALINGDAMAGEBUFF              = 29,
	TF_COND_SPEED_BOOST                      = 30, // = 30
	TF_COND_CRITBOOSTED_PUMPKIN              = 31, // Brandon hates bits
	TF_COND_CRITBOOSTED_USER_BUFF            = 32,
	TF_COND_CRITBOOSTED_DEMO_CHARGE          = 33,
	TF_COND_CRITBOOSTED_FIRST_BLOOD          = 34, // arena mode first blood
	TF_COND_CRITBOOSTED_BONUS_TIME           = 35,
	TF_COND_CRITBOOSTED_CTF_CAPTURE          = 36,
	TF_COND_CRITBOOSTED_ON_KILL              = 37, // KGB, etc.
	TF_COND_DEFENSEBUFF_NO_CRIT_BLOCK        = 38, // 35% defense! Still damaged by crits.
	TF_COND_CRITBOOSTED_RAGE_BUFF            = 39,
	TF_COND_DEFENSEBUFF_HIGH                 = 40, // =40 75% defense! Still damaged by crits.
	TF_COND_DISGUISE_WEARINGOFF              = 41, // Applied for half-second post-disguise
	TF_COND_MARKEDFORDEATH_SILENT            = 42, // Sans sound
	TF_COND_DISGUISED_AS_DISPENSER           = 43,
	TF_COND_INVULNERABLE_HIDE_UNLESS_DAMAGED = 44,
	TF_COND_RADIUSHEAL_ON_DAMAGE             = 45,
	TF_COND_CRITBOOSTED_CARD_EFFECT          = 46,
	TF_COND_INVULNERABLE_CARD_EFFECT         = 47,
	TF_COND_STEALTHED_USER_BUFF              = 48, // Any class can have this
	TF_COND_STEALTHED_USER_BUFF_FADING       = 49,
	TF_COND_PREVENT_DEATH                    = 50, // =50
	TF_COND_HALLOWEEN_TINY                   = 51,
	TF_COND_HALLOWEEN_GHOST_MODE             = 52,
	TF_COND_MINICRITBOOSTED_ON_KILL          = 53,
	TF_COND_OBSCURED_SMOKE                   = 54,
	TF_COND_BLASTJUMPING                     = 55,
	TF_COND_MELEE_ONLY                       = 56, // =56 melee only
	TF_COND_FREEZE_INPUT                     = 57, // =57 freezes player input
	TF_COND_AFTERBURN_IMMUNE                 = 58,
	TF_COND_SWIMMING_NO_EFFECTS              = 59, // =59_DNOC_FT
	TF_COND_KNOCKED_INTO_AIR                 = 60, // =60
	TF_COND_HEALING_DEBUFF                   = 61,
	// Players who lose their footing have lessened friction and don't re-stick to the ground unless they're below a
	// tf_movement_lost_footing_restick speed
	TF_COND_LOST_FOOTING                     = 62,
	// When in the air, slide up/along surfaces with momentum as if caught up in a... blast of air of some sort.
	// Reduces air control as well.  See tf_movement_aircurrent convars.  Removed upon touching ground.
	TF_COND_AIR_CURRENT                      = 63,

	TF_COND_LAST
};

// translates live cond index into goldrush cond index
static TFCond g_aConditionMap[] =
{
	TF_COND_AIMING,
	TF_COND_ZOOMED,
	TF_COND_DISGUISING,
	TF_COND_DISGUISED,
	TF_COND_STEALTHED,
	TF_COND_INVULNERABLE,
	TF_COND_TELEPORTED,
	TF_COND_TAUNTING,
	TF_COND_INVULNERABLE_WEARINGOFF,
	TF_COND_STEALTHED_BLINK,
	TF_COND_SELECTED_TO_TELEPORT,
	TF_COND_CRITBOOSTED,
	TF_COND_TMPDAMAGEBONUS,
	TF_COND_FEIGN_DEATH,
	TF_COND_PHASE,
	TF_COND_STUNNED,
	TF_COND_OFFENSEBUFF,
	TF_COND_SHIELD_CHARGE,
	TF_COND_DEMO_BUFF,
	TF_COND_ENERGY_BUFF,
	TF_COND_RADIUSHEAL,
	TF_COND_HEALTH_BUFF,
	TF_COND_BURNING,
	TF_COND_HEALTH_OVERHEALED,
	TF_COND_URINE,
	TF_COND_BLEEDING,
	TF_COND_DEFENSEBUFF,
	TF_COND_INVALID, // TF_COND_MAD_MILK
	TF_COND_INVALID, // TF_COND_MEGAHEAL
	TF_COND_REGENONDAMAGEBUFF,
	TF_COND_MARKEDFORDEATH,
	TF_COND_NOHEALINGDAMAGEBUFF,
	TF_COND_SPEED_BOOST,
	TF_COND_CRITBOOSTED_PUMPKIN,
	TF_COND_CRITBOOSTED_USER_BUFF,
	TF_COND_CRITBOOSTED_DEMO_CHARGE,
	TF_COND_INVALID, // TF_COND_SODAPOPPER_HYPE
	TF_COND_CRITBOOSTED_FIRST_BLOOD,
	TF_COND_CRITBOOSTED_BONUS_TIME,
	TF_COND_CRITBOOSTED_CTF_CAPTURE,
	TF_COND_CRITBOOSTED_ON_KILL,
	TF_COND_INVALID, // TF_COND_CANNOT_SWITCH_FROM_MELEE
	TF_COND_DEFENSEBUFF_NO_CRIT_BLOCK,
	TF_COND_INVALID, // TF_COND_REPROGRAMMED
	TF_COND_CRITBOOSTED_RAGE_BUFF,
	TF_COND_DEFENSEBUFF_HIGH,
	TF_COND_INVALID, // TF_COND_SNIPERCHARGE_RAGE_BUFF
	TF_COND_DISGUISE_WEARINGOFF,
	TF_COND_MARKEDFORDEATH_SILENT,
	TF_COND_DISGUISED_AS_DISPENSER,
	TF_COND_INVALID, // TF_COND_SAPPED
	TF_COND_INVULNERABLE_HIDE_UNLESS_DAMAGED,
	TF_COND_INVALID, // TF_COND_INVULNERABLE_USER_BUFF
	TF_COND_INVALID, // TF_COND_HALLOWEEN_BOMB_HEAD
	TF_COND_INVALID, // TF_COND_HALLOWEEN_THRILLER
	TF_COND_RADIUSHEAL_ON_DAMAGE,
	TF_COND_CRITBOOSTED_CARD_EFFECT,
	TF_COND_INVULNERABLE_CARD_EFFECT,
	TF_COND_INVALID, // TF_COND_MEDIGUN_UBER_BULLET_RESIST
	TF_COND_INVALID, // TF_COND_MEDIGUN_UBER_BLAST_RESIST
	TF_COND_INVALID, // TF_COND_MEDIGUN_UBER_FIRE_RESIST
	TF_COND_INVALID, // TF_COND_MEDIGUN_SMALL_BULLET_RESIST
	TF_COND_INVALID, // TF_COND_MEDIGUN_SMALL_BLAST_RESIST
	TF_COND_INVALID, // TF_COND_MEDIGUN_SMALL_FIRE_RESIST
	TF_COND_STEALTHED_USER_BUFF,
	TF_COND_INVALID, // TF_COND_MEDIGUN_DEBUFF
	TF_COND_STEALTHED_USER_BUFF_FADING,
	TF_COND_INVALID, // TF_COND_BULLET_IMMUNE
	TF_COND_INVALID, // TF_COND_BLAST_IMMUNE
	TF_COND_INVALID, // TF_COND_FIRE_IMMUNE
	TF_COND_PREVENT_DEATH,
	TF_COND_INVALID, // TF_COND_MVM_BOT_STUN_RADIOWAVE
	TF_COND_INVALID, // TF_COND_HALLOWEEN_SPEED_BOOST
	TF_COND_INVALID, // TF_COND_HALLOWEEN_QUICK_HEAL
	TF_COND_INVALID, // TF_COND_HALLOWEEN_GIANT
	TF_COND_HALLOWEEN_TINY,
	TF_COND_INVALID, // TF_COND_HALLOWEEN_IN_HELL
	TF_COND_HALLOWEEN_GHOST_MODE,
	TF_COND_MINICRITBOOSTED_ON_KILL,
	TF_COND_OBSCURED_SMOKE,
	TF_COND_INVALID, // TF_COND_PARACHUTE_ACTIVE
	TF_COND_BLASTJUMPING,
	TF_COND_INVALID, // TF_COND_HALLOWEEN_KART
	TF_COND_INVALID, // TF_COND_HALLOWEEN_KART_DASH
	TF_COND_INVALID, // TF_COND_BALLOON_HEAD
	TF_COND_MELEE_ONLY,
	TF_COND_INVALID, // TF_COND_SWIMMING_CURSE
	TF_COND_FREEZE_INPUT,
	TF_COND_INVALID, // TF_COND_HALLOWEEN_KART_CAGE
	TF_COND_INVALID, // TF_COND_DONOTUSE_0
	TF_COND_INVALID, // TF_COND_RUNE_STRENGTH
	TF_COND_INVALID, // TF_COND_RUNE_HASTE
	TF_COND_INVALID, // TF_COND_RUNE_REGEN
	TF_COND_INVALID, // TF_COND_RUNE_RESIST
	TF_COND_INVALID, // TF_COND_RUNE_VAMPIRE
	TF_COND_INVALID, // TF_COND_RUNE_REFLECT
	TF_COND_INVALID, // TF_COND_RUNE_PRECISION
	TF_COND_INVALID, // TF_COND_RUNE_AGILITY
	TF_COND_INVALID, // TF_COND_GRAPPLINGHOOK
	TF_COND_INVALID, // TF_COND_GRAPPLINGHOOK_SAFEFALL
	TF_COND_INVALID, // TF_COND_GRAPPLINGHOOK_LATCHED
	TF_COND_INVALID, // TF_COND_GRAPPLINGHOOK_BLEEDING
	TF_COND_AFTERBURN_IMMUNE,
	TF_COND_INVALID, // TF_COND_RUNE_KNOCKOUT
	TF_COND_INVALID, // TF_COND_RUNE_IMBALANCE
	TF_COND_INVALID, // TF_COND_CRITBOOSTED_RUNE_TEMP
	TF_COND_INVALID, // TF_COND_PASSTIME_INTERCEPTION
	TF_COND_SWIMMING_NO_EFFECTS,
	TF_COND_INVALID, // TF_COND_PURGATORY
	TF_COND_INVALID, // TF_COND_RUNE_KING
	TF_COND_INVALID, // TF_COND_RUNE_PLAGUE
	TF_COND_INVALID, // TF_COND_RUNE_SUPERNOVA
	TF_COND_INVALID, // TF_COND_PLAGUE
	TF_COND_INVALID, // TF_COND_KING_BUFFED
	TF_COND_INVALID, // TF_COND_TEAM_GLOWS
	TF_COND_KNOCKED_INTO_AIR,
	TF_COND_INVALID, // TF_COND_COMPETITIVE_WINNER
	TF_COND_INVALID, // TF_COND_COMPETITIVE_LOSER
	TF_COND_HEALING_DEBUFF,
	TF_COND_INVALID, // TF_COND_PASSTIME_PENALTY_DEBUFF
	TF_COND_INVALID, // TF_COND_GRAPPLED_TO_PLAYER
	TF_COND_INVALID, // TF_COND_GRAPPLED_BY_PLAYER
	TF_COND_INVALID, // TF_COND_PARACHUTE_DEPLOYED
	TF_COND_INVALID, // TF_COND_GAS
	TF_COND_INVALID, // TF_COND_BURNING_PYRO
	TF_COND_INVALID, // TF_COND_ROCKETPACK
	TF_COND_LOST_FOOTING,
	TF_COND_AIR_CURRENT,
	TF_COND_INVALID, // TF_COND_HALLOWEEN_HELL_HEAL
	TF_COND_INVALID, // TF_COND_POWERUPMODE_DOMINANT
	TF_COND_INVALID, // TF_COND_IMMUNE_TO_PUSHBACK
};

int TranslateCondIndexToGR(int iCond);
int TranslateCondIndexToLive(int iCond);

#endif // _INCLUDE_SOURCEMOD_EXTENSION_PROPER_H_
