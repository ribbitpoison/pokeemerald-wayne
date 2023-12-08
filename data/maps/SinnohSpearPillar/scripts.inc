SinnohSpearPillar_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SinnohSpearPillar_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SinnohSpearPillar_OnTransition
	.byte 0

SinnohSpearPillar_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, SinnohSpearPillar_EventScript_TryRemoveReshiram
	end

SinnohSpearPillar_EventScript_TryRemoveReshiram::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

SinnohSpearPillar_OnTransition:
	setflag FLAG_LANDMARK_SPEAR_PILLAR
	call_if_unset FLAG_DEFEATED_RESHIRAM, SinnohSpearPillar_EventScript_ShowReshiram
	end

SinnohSpearPillar_EventScript_ShowReshiram::
	clearflag FLAG_HIDE_RESHIRAM
	return

SinnohSpearPillar_EventScript_Reshiram::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RESHIRAM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_RESHIRAM, 70
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinnohSpearPillar_EventScript_DefeatedReshiram
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinnohSpearPillar_EventScript_RanFromReshiram
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinnohSpearPillar_EventScript_RanFromReshiram
	setflag FLAG_DEFEATED_RESHIRAM
	release
	end

SinnohSpearPillar_EventScript_DefeatedReshiram::
	setflag FLAG_DEFEATED_RESHIRAM
	goto Common_EventScript_RemoveStaticPokemon
	end

SinnohSpearPillar_EventScript_RanFromReshiram::
	setvar VAR_0x8004, SPECIES_RESHIRAM
	goto Common_EventScript_LegendaryFlewAway
	.string "Reshiram returned to it's original dimension...$"
	end
