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
	TENTACULE_PIRATE					UMETA(DisplayName = "Tentacule/Pirate"),
	MODERNHIPSTER_PHOTOSHOP             UMETA(DisplayName = "Modern Hipster/Photoshopped Proof"),
	BARNEYBETTYHILL_AMNESIA             UMETA(DisplayName = "Barney & Betty Hill/Forced Amnesia"),
	COWKIDNAPPING_IMPORTEXPORT          UMETA(DisplayName = "Cow Kidnapping/Import Export"),
	ANONYMOUS_FIREWALL                  UMETA(DisplayName = "Anonymous/Firewall"),
	WHITELADY_GHOSTBUSTERS              UMETA(DisplayName = "White Lady/Ghostbusters"),
	IARULESWORLD_COMPUTERVIRUS          UMETA(DisplayName = "IARulesWorld/Computer Virus"),
	ROBOTARMY_SOLDIERARMY		        UMETA(DisplayName = "RobotArmy/Soldier"),
	PROPAGANDA_WHISTLEBLOWER            UMETA(DisplayName = "Propaganda/Whistleblower"),
	SERBIANDANCINGLADY_POLICEROADBLOCK  UMETA(DisplayName = "Serbian Dancing Lady/Police Roadblock"),
	WELLTOHELL_MENINBLACK               UMETA(DisplayName = "Well to Hell/Men in Black"),
	KAPPA_CRYPTOZOOLOGIST               UMETA(DisplayName = "Kappa/Cryptozoologist"),
	ILLUMINATI_VATICANARCHIVES          UMETA(DisplayName = "Illuminati/Vatican Archives"),
	PYRAMIDES_EGYPTE					UMETA(DisplayName = "LandPyramideEgypte"),
	PYRAMIDES_AZTEQUE					UMETA(DisplayName = "LandPyramideAzteque"),
	PYRAMIDES_ANTARCTIQUE				UMETA(DisplayName = "LandPyramideAntarctique"),
	ZONE_TEST_MILITAIRE					UMETA(DisplayName = "LandZoneTestMilitaire"),
	LABO_TRANSHUMANISTE					UMETA(DisplayName = "LandLaboTransHumaniste"),
	CENTRE_VACCINATION					UMETA(DisplayName = "LandCentreVaccination"),
	FORET_HANTEE						UMETA(DisplayName = "LandForetHantee"),
	ATLANTIDE							UMETA(DisplayName = "LandAtlantide"),
	MONTAGNE_CARPATES					UMETA(DisplayName = "LandMontagneCarpates"),
	DATA_CENTER							UMETA(DisplayName = "LandDataCenter"),
	CERN								UMETA(DisplayName = "LandCern"),
	MATRIX								UMETA(DisplayName = "LandMatrix"),
	SIEGE_ONU							UMETA(DisplayName = "LandSiegeONU"),
	PENTAGONE							UMETA(DisplayName = "LandPentagone"),
	ZONE_51								UMETA(DisplayName = "LandZone51"),
	SANCTUAIRE_DESACRALISE				UMETA(DisplayName = "LandSanctuaireDesacralise"),
	ALUNISSAGE							UMETA(DisplayName = "LandAlunissage"),
	TERRE_PLATE							UMETA(DisplayName = "LandTerrePlate")
};