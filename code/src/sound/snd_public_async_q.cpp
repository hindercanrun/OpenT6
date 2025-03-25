#include "types.h"

/*
==============
SND_GetNewCommand
==============
*/
SndCommand *SND_GetNewCommand()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_CommandFreeBatch
==============
*/
void SND_CommandFreeBatch(SndCommand *start, SndCommand *end, int count)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_CommandPush
==============
*/
void SND_CommandPush(SndCommand *cmd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_CommandPeek
==============
*/
SndCommand *SND_CommandPeek()
{
	assert(g_snd.command_init);
	assert(g_snd.command_q_tail <1024);
	assert(g_snd.command_q_head <1024);

	if (!g_snd.command_q_tail == g_snd.command_q_head)
	{
		return g_snd.command_q[g_snd.command_q_tail];
	}

	return FALSE;
}

/*
==============
SND_CommandPop
==============
*/
void SND_CommandPop()
{
	assert(g_snd.command_init);
	assert(g_snd.command_q_tail < 1024);
	assert(g_snd.command_q_head < 1024);
	assert(g_snd.command_q_tail != g_snd.command_q_head);
	assert(g_snd.command_q[g_snd.command_q_tail]->type != SND_COMMAND_NOP);

	g_snd.command_q[g_snd.command_q_tail] = SND_COMMAND_NOP;
	g_snd.command_q_tail = (LOWORD(g_snd.command_q_tail) + 1) & 1023;
}

/*
==============
SND_CommandProcess
==============
*/
void SND_CommandProcess(const SndCommand *cmd)
{
	assert(g_snd.command_init);

	switch (cmd->type)
	{
	case SND_COMMAND_ALIAS_NAME:
		PIXBeginNamedEvent(-1, "SNDL_AliasName");
		SNDL_AliasName(cmd->context.alias_name.name, cmd->context.alias_name.id);
		break;
	case SND_COMMAND_PLAY:
		break;
	case SND_COMMAND_STOP_ALIAS:
		PIXBeginNamedEvent(-1, "SNDL_StopSoundAliasOnEnt");
		SNDL_StopSoundAliasOnEnt(cmd->context.stop_alias.ent, cmd->context.stop_alias.alias_name);
		break;
	case SND_COMMAND_STOP_ENT:
		PIXBeginNamedEvent(-1, "SNDL_StopSoundsOnEnt");
		SNDL_StopSoundsOnEnt(cmd->context.stop_alias.ent);
		break;
	case SND_COMMAND_CINEMATIC_START:
		PIXBeginNamedEvent(-1, "SNDL_NotifyCinematicStart");
		break;
	case SND_COMMAND_CINEMATIC_END:
		PIXBeginNamedEvent(-1, "SNDL_NotifyCinematicEnd");
		break;
	case SND_COMMAND_DISCONNECT_LISTENER:
		PIXBeginNamedEvent(-1, "SNDL_DisconnectListener");
		SNDL_DisconnectListener(cmd->context.disconnect_listener.listener);
		break;
	case SND_COMMAND_SET_LISTENER:
		PIXBeginNamedEvent(-1, "SNDL_SetListener");
		SNDL_SetListener(
			cmd->context.disconnect_listener.listener,
			cmd->context.set_listener.clientNum,
			cmd->context.set_listener.team,
			&cmd->context.set_listener.origin,
			cmd->context.set_listener.axis
		);
		break;
	case SND_COMMAND_STOP_SOUNDS:
		PIXBeginNamedEvent(-1, "SNDL_StopSounds");
		SNDL_StopSounds(cmd->context.stop_sounds.flags);
		break;
	case SND_COMMAND_FADE_IN:
		PIXBeginNamedEvent(-1, "SNDL_FadeIn");
		SNDL_FadeIn();
		break;
	case SND_COMMAND_FADE_OUT:
		PIXBeginNamedEvent(-1, "SNDL_FadeOut");
		SNDL_FadeOut();
		break;
	case SND_COMMAND_SET_ENVIRONMENT_EFFECTS:
		PIXBeginNamedEvent(-1, "SNDL_SetEnvironmentEffects");
		SNDL_SetEnvironmentEffects(
			cmd->context.stop_alias.ent.handle,
			cmd->context.stop_alias.alias_name,
			cmd->context.play.attenuation,
			cmd->context.set_listener.origin.x,
			cmd->context.play.notify
		);
		break;
	case SND_COMMAND_DEACTIVATE_ENVIRONMENT_EFFECTS:
		PIXBeginNamedEvent(-1, "SNDL_DeactivateEnvironmentEffects");
		SNDL_DeactivateEnvironmentEffects(cmd->context.stop_alias.ent.handle, cmd->context.play.fadeTimeMs);
		break;
	case SND_COMMAND_SET_PLAYBACK_ATTENUATION:
		PIXBeginNamedEvent(-1, "SNDL_SetPlaybackAttenuation");
		SNDL_SetPlaybackAttenuation(cmd->context.stop_alias.ent.handle, cmd->context.set_playback_attenuation.attenuation);
		break;
	case SND_COMMAND_SET_PLAYBACK_ATTENUATION_RATE:
		PIXBeginNamedEvent(-1, "SNDL_SetPlaybackAttenuationRate");
		SNDL_SetPlaybackAttenuationRate(
			cmd->context.stop_alias.ent.handle,
			cmd->context.set_playback_attenuation.attenuation
		);
		break;
	case SND_COMMAND_SET_PLAYBACK_PITCH:
		PIXBeginNamedEvent(-1, "SNDL_SetPlaybackPitch");
		SNDL_SetPlaybackPitch(cmd->context.stop_alias.ent.handle, cmd->context.set_playback_attenuation.attenuation);
		break;
	case SND_COMMAND_SET_PLAYBACK_PITCH_RATE:
		PIXBeginNamedEvent(-1, "SNDL_SetPlaybackPitchRate");
		SNDL_SetPlaybackPitchRate(cmd->context.stop_alias.ent.handle, cmd->context.set_playback_attenuation.attenuation);
		break;
	case SND_COMMAND_STOP_PLAYBACK:
		PIXBeginNamedEvent(-1, "SNDL_StopPlayback");
		SNDL_StopPlayback(cmd->context.stop_alias.ent.handle);
		break;
	case SND_COMMAND_SET_START_PAUSED:
		PIXBeginNamedEvent(-1, "SNDL_SetStartPaused");
		SNDL_SetStartPaused(cmd->context.stop_alias.ent.handle, cmd->context.play.fadeTimeMs != 0);
		break;
	case SND_COMMAND_DUCK:
		PIXBeginNamedEvent(-1, "SNDL_SetDuck");
		SNDL_SetDuck(cmd->context.duck.type, cmd->context.stop_alias.alias_name, cmd->context.play.attenuation);
		break;
	case SND_COMMAND_SET_ENT_STATE:
		PIXBeginNamedEvent(-1, "SNDL_SetEntState");
		SNDL_SetEntState(
			cmd->context.stop_alias.ent,
			&cmd->context.set_ent_state.origin,
			&cmd->context.set_ent_state.velocity,
			&cmd->context.set_listener.axis[0]
		);
		break;
	case SND_COMMAND_SET_GAME_STATE:
		PIXBeginNamedEvent(-1, "SNDL_SetGameState");
		SNDL_SetGameState(
			cmd->context.play.fadeTimeMs != NULL,
			cmd->context.play.alias != NULL,
			cmd->context.play.attenuation,
			cmd->context.set_game_state.cg_time,
			cmd->context.set_game_state.seed,
			cmd->context.play.position.x,
			cmd->context.play.position.y,
			cmd->context.play.position.z,
			cmd->context.play.direction.x,
			cmd->context.play.direction.y,
			cmd->context.set_game_state.masterPatch,
			cmd->context.set_game_state.hearingImpaired != NULL
		);
		break;
	case SND_COMMAND_STOP_LOOP_AT:
		PIXBeginNamedEvent(-1, "SNDL_StopLoopAt");
		SNDL_StopLoopAt(cmd->context.play.alias, &cmd->context.set_ent_state.origin);
		break;
	case SND_COMMAND_PLAY_LINE_AT:
		PIXBeginNamedEvent(-1, "SNDL_PlayLineAt");
		SNDL_PlayLineAt(cmd->context.play.alias, &cmd->context.set_ent_state.origin, &cmd->context.set_ent_state.velocity);
		break;
	case SND_COMMAND_STOP_LINE_AT:
		PIXBeginNamedEvent(-1, "SNDL_StopLineAt");
		SNDL_StopLineAt(cmd->context.play.alias, &cmd->context.set_ent_state.origin, &cmd->context.set_ent_state.velocity);
		break;
	case SND_COMMAND_GAME_RESET:
		PIXBeginNamedEvent(-1, "SNDL_GameReset");
		SNDL_GameReset();
		break;
	case SND_COMMAND_SET_CONTEXT:
		PIXBeginNamedEvent(-1, "SNDL_SetContext");
		SNDL_SetContext(cmd->context.play.alias, cmd->context.stop_alias.alias_name);
		break;
	case SND_COMMAND_SET_ENT_CONTEXT:
		PIXBeginNamedEvent(-1, "SNDL_SetEntContext");
		SNDL_SetEntContext(
			cmd->context.stop_alias.ent,
			cmd->context.stop_alias.alias_name,
			cmd->context.set_ent_context.value
		);
		break;
	case SND_COMMAND_SCRIPT_TIMESCALE:
		PIXBeginNamedEvent(-1, "SNDL_SetScriptTimescale");
		SNDL_SetScriptTimescale(cmd->context.notify_cinematic_start.volume);
		break;
	case SND_COMMAND_UPDATE_CG:
		PIXBeginNamedEvent(-1, "SNDL_UpdateLoopingSounds");
		SNDL_UpdateLoopingSounds();
		break;
	case SND_COMMAND_LOAD_BANK:
		PIXBeginNamedEvent(-1, "SNDL_AddBank");
		SNDL_AddBank(cmd->context.load_bank.bank);
		break;
	case SND_COMMAND_UNLOAD_BANK:
		PIXBeginNamedEvent(-1, "SNDL_RemoveBank");
		SNDL_RemoveBank(cmd->context.load_bank.bank);
		break;
	case SND_COMMAND_LOAD_PATCH:
		PIXBeginNamedEvent(-1, "SNDL_AddPatch");
		SNDL_AddPatch(cmd->context.load_patch.patch);
		break;
	case SND_COMMAND_UNLOAD_PATCH:
		PIXBeginNamedEvent(-1, "SNDL_RemovePatch");
		SNDL_RemovePatch(cmd->context.load_patch.patch);
		break;
	case SND_COMMAND_LOAD_GLOBALS:
		PIXBeginNamedEvent(-1, "SNDL_AddGlobals");
		SNDL_AddGlobals(cmd->context.load_globals.globals);
		break;
	case SND_COMMAND_UNLOAD_GLOBALS:
		PIXBeginNamedEvent(-1, "SNDL_RemoveGlobals");
		SNDL_RemoveGlobals(cmd->context.load_globals.globals);
		break;
	case SND_COMMAND_PRIME_ALIAS:
		PIXBeginNamedEvent(-1, "SNDL_PrimeAlias");
		BG_EvalVehicleName();
		break;
	case SND_COMMAND_RESTART_DRIVER:
		PIXBeginNamedEvent(-1, "SNDL_RestartDriver");
		SNDL_RestartDriver();
		break;
	case SND_COMMAND_SET_SIDE_CHAIN_DUCK:
		PIXBeginNamedEvent(-1, "SNDL_SetSideChainDuck");
		SNDL_SetSideChainDuck(cmd->context.stop_alias.alias_name);
		break;
	case SND_COMMAND_SET_MUSIC_STATE:
		PIXBeginNamedEvent(-1, "SNDL_SetMusicState");
		SNDL_SetMusicState(cmd->context.play.alias);
		break;
	case SND_COMMAND_PREFETCH_LOADED_ALIAS:
		PIXBeginNamedEvent(-1, "SNDL_PrefetchLoadedAlias");
		SNDL_PrefetchLoadedAlias(cmd->context.play.alias);
		break;
	case SND_COMMAND_SET_GLOBAL_FUTZ:
		PIXBeginNamedEvent(-1, "SNDL_SetGlobalFutz");
		SNDL_SetGlobalFutz(cmd->context.play.alias, cmd->context.setGlobalFutz.callLocation);
		break;
	case SND_COMMAND_SET_FRONTEND_MUSIC:
		PIXBeginNamedEvent(-1, "SNDL_SetFrontendMusic");
		SNDL_SetFrontendMusic(cmd->context.play.alias);
		break;
	case SND_COMMAND_SET_LOOP_STATE:
		PIXBeginNamedEvent(-1, "SNDL_SetLoopState");
		SNDL_SetLoopState(
			cmd->context.stop_alias.ent,
			cmd->context.stop_alias.alias_name,
			cmd->context.play.attenuation,
			cmd->context.set_listener.origin.x,
			cmd->context.set_listener.origin.y,
			cmd->context.play.position.x
		);
		break;
	case SND_COMMAND_PLAY_LOOPS:
		SNDL_PlayLoops(cmd->context.playLoops.count, &cmd->context);
		break;
	case SND_COMMAND_SHUTDOWN:
		SNDL_Shutdown();
		break;
	default:
		assertMsg(NULL, "(0)");
		break;
	}
}

/*
==============
SND_GetNewNotify
==============
*/
SndNotify *SND_GetNewNotify()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_NotifyFree
==============
*/
void SND_NotifyFree(SndNotify *p)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_NotifyProcess
==============
*/
void SND_NotifyProcess(const SndNotify *cmd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_NotifyPush
==============
*/
void SND_NotifyPush(SndNotify *cmd)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_NotifyPeek
==============
*/
SndNotify *SND_NotifyPeek()
{
	UNIMPLEMENTED(__FUNCTION__);
	return NULL;
}

/*
==============
SND_NotifyPop
==============
*/
void SND_NotifyPop()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_NotifyPump
==============
*/
void SND_NotifyPump()
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
SND_ShouldMuteAllSounds
==============
*/
bool SND_ShouldMuteAllSounds()
{
	return g_snd.muteAllSounds;
}

/*
==============
SND_CommandPump
==============
*/
int SND_CommandPump(SndCommand *a1)
{
	UNIMPLEMENTED(__FUNCTION__);
	return 0;
}

