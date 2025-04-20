OldaleTown_Mart_MapScripts::
	.byte 0

OldaleTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_ExpandedItems
	pokemart OldaleTown_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart_Basic:
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_HP_IV_VITAMIN
	.2byte ITEM_ATKUP_IV_VITAMIN
	.2byte ITEM_ATKDWN_IV_VITAMIN
	.2byte  ITEM_DEF_IV_VITAMIN 
    .2byte  ITEM_SPATK_IV_VITAMIN 
    .2byte  ITEM_SPDEF_IV_VITAMIN 
    .2byte  ITEM_SPDUP_IV_VITAMIN 
    .2byte  ITEM_SPDDWN_IT_VITAMIN 
	pokemartlistend

OldaleTown_Mart_ExpandedItems::
	pokemart OldaleTown_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
OldaleTown_Mart_Pokemart_Expanded:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	pokemartlistend

BP_Mart_EventScript_ClerkWelcome::
	msgbox BP_Mart_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special ShowBattlePointsWindow
	return

BP_Mart_EventScript_ClerkGoodbye::
	msgbox BP_Mart_Text_ThankYouVisitWithPoints, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

BP_Mart_EventScript_TryPurchasePrize::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_ExchangeServiceCorner_EventScript_TryGiveItem
	msgbox BP_Mart_Text_DontHaveEnoughPoints, MSGBOX_DEFAULT
	goto BP_Mart_EventScript_ChooseTM
	end

BP_Mart_EventScript_TryGiveItem::
	checkitemspace VAR_0x8009
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ExchangeServiceCorner_EventScript_BagFull
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	additem VAR_0x8009
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BP_Mart_Text_HereIsYourPrize, MSGBOX_DEFAULT
	goto BP_Mart_EventScript_ChooseTM
	end

BP_Mart_EventScript_BagFull::
	msgbox BP_Mart_Text_DontHaveSpaceToHoldIt, MSGBOX_DEFAULT
	special CloseBattlePointsWindow
	release
	end

BP_Mart_EventScript_TMClerk::
	lock
	faceplayer
	setvar VAR_TEMP_2, BP_MART_TM_CLERK
	call BP_Mart_EventScript_ClerkWelcome
	goto BP_Mart_EventScript_ChooseTM
	end

BP_Mart_EventScript_ChooseTM::
	setvar VAR_0x8004, SCROLL_MULTI_BP_TMS
	special ShowFrontierExchangeCornerItemIconWindow
	special ShowScrollableMultichoice
	waitstate
	special CloseFrontierExchangeCornerItemIconWindow
	switch VAR_RESULT
	case 0, BP_Mart_EventScript_RainDance
	case 1, BP_Mart_EventScript_SunnyDay
	case 2, BP_Mart_EventScript_ClerkGoodbye
	case MULTI_B_PRESSED, BP_Mart_EventScript_ClerkGoodbye
	end

BP_Mart_EventScript_RainDance::
	msgbox BP_Mart_Text_ConfirmRainDance, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BP_Mart_EventScript_ChooseTM
	setvar VAR_0x8008, 2
	setvar VAR_0x8009, ITEM_TM_RAIN_DANCE
	goto BP_Mart_EventScript_TryPurchasePrize
	end

BP_Mart_EventScript_SunnyDay::
	msgbox BP_Mart_Text_ConfirmSunnyDay, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BP_Mart_EventScript_ChooseTM
	setvar VAR_0x8008, 2
	setvar VAR_0x8009, ITEM_TM_SUNNY_DAY
	goto BP_Mart_EventScript_TryPurchasePrize
	end
	
OldaleTown_Mart_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_PokeBallsInStock
	msgbox OldaleTown_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_PokeBallsInStock::
	msgbox OldaleTown_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
	release
	end

OldaleTown_Mart_EventScript_Boy::
	msgbox OldaleTown_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
	end

OldaleTown_Mart_Text_PokeBallsAreSoldOut:
	.string "The clerk says they're all sold out.\n"
	.string "I can't buy any POKé BALLS.$"

OldaleTown_Mart_Text_ImGoingToBuyPokeBalls:
	.string "I'm going to buy a bunch of POKé BALLS\n"
	.string "and catch a bunch of POKéMON!$"

OldaleTown_Mart_Text_RestoreHPWithPotion:
	.string "If a POKéMON gets hurt and loses its HP\n"
	.string "and faints, it won't be able to battle.\p"
	.string "To prevent your POKéMON from fainting,\n"
	.string "restore its HP with a POTION.$"

BP_Mart_Text_WelcomePleaseChoosePrize:
	.string "Hello, this is the Battle Leauge\n"
	.string "Reward Program.\p"
	.string "We exchange the Battle Points you\n"
	.string "have collected for lovely prizes.\p"
	.string "Please choose a prize from this list.$"

BP_Mart_Text_ThankYouVisitWithPoints:
	.string "Thank you very much.\p"
	.string "Please visit us when you have\n"
	.string "saved up Battle Points.$"

BP_Mart_Text_ConfirmRainDance:
	.string "You've chosen Rain Dance.\n"
	.string "Is that correct?$"

BP_Mart_Text_ConfirmSunnyDay:
	.string "You've chosen Sunny Day.\n"
	.string "Is that correct?$"

BP_Mart_Text_DontHaveEnoughPoints:
	.string "I'm so sorry…\n"
	.string "You don't have enough Battle Points…$"

BP_Mart_Text_DontHaveSpaceToHoldIt:
	.string "I'm so sorry…\n"
	.string "You don't have space to hold it…$"

BP_Mart_Text_HereIsYourPrize:
	.string "Here is your prize!$"
