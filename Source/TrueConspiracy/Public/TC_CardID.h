// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ETC_CardID : uint8
{
	TESTATTACK_TESTDEFENSE = 0          UMETA(DisplayName = "TestAttack/TestDefense"),
	ROSEWELLCASE_SECRETOPERATION        UMETA(DisplayName = "Rosewell's Case/Secret Operation"),
	REPTILIAN_PRESIDENT                 UMETA(DisplayName = "Reptilian/President"),
	SHAREHOLDER                         UMETA(DisplayName = "Shareholder"),
	TVA                                 UMETA(DisplayName = "TVA"),
	SKINWALKER                          UMETA(DisplayName = "Skinwalker"),
	GIANT_SCIENTIFICPROOF               UMETA(DisplayName = "Giant/Scientific Proof"),
	LOCHNESS_HYDROBIOLOGIST             UMETA(DisplayName = "Loch Ness/Hydrobiologist"),
	YETI_MONSTERHUNTER                  UMETA(DisplayName = "Yeti/Monster Hunter"),
	KAPPACHIEF_YANAGITA                 UMETA(DisplayName = "Kappa (Chief)/Kunio Yanagita"),
	KRAKEN_PIRATECREW                   UMETA(DisplayName = "Kraken/Pirate Crew"),
	MODERNHIPSTER_PHOTOSHOP             UMETA(DisplayName = "Modern Hipster/Photoshopped Proof"),
	BARNEYBETTYHILL_AMNESIA             UMETA(DisplayName = "Barney & Betty Hill/Forced Amnesia"),
	COWKIDNAPPING_IMPORTEXPORT          UMETA(DisplayName = "Cow Kidnapping/Import Export"),
	ANONYMOUS_FIREWALL                  UMETA(DisplayName = "Anonymous/Firewall"),
	WHITELADY_GHOSTBUSTERS              UMETA(DisplayName = "White Lady/Ghostbusters"),
	IARULESWORLD_COMPUTERVIRUS          UMETA(DisplayName = "IARulesWorld/Computer Virus"),
	PROPAGANDA_WHISTLEBLOWER            UMETA(DisplayName = "Propaganda/Whistleblower"),
	SERBIANDANCINGLADY_POLICEROADBLOCK  UMETA(DisplayName = "Serbian Dancing Lady/Police Roadblock"),
	WELLTOHELL_MENINBLACK               UMETA(DisplayName = "Well to Hell/Men in Black"),
	KAPPA_CRYPTOZOOLOGIST               UMETA(DisplayName = "Kappa/Cryptozoologist"),
	ILLUMINATI_VATICANARCHIVES          UMETA(DisplayName = "Illuminati/Vatican Archives"),
};