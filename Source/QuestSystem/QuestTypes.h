// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestTypes.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	Location     UMETA(DisplayName = "Reach Location"),
	Kill         UMETA(DisplayName = "Kill Target"),
	Interact     UMETA(DisplayName = "Interact with Object"),
	Collect      UMETA(DisplayName = "Collect Items")
};


USTRUCT(BlueprintType)
struct FObjectiveDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ObjectiveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Multiline = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObjectiveType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOptional;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin="0"))
	int32 BonusXP;
};


USTRUCT(BlueprintType)
struct FStageDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText StageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjectiveDetails> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int32 XPReward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int32> ItemRewards; // item name && amount

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0"))
	int32 CurrencyReward;
};

USTRUCT(BlueprintType)
struct FQuestDetails : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LogDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TrackingDescription;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMainQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAutoAccept;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStageDetails> Stages;
};



/**
 * 
 */
class QUESTSYSTEM_API QuestTypes
{
public:
	QuestTypes();
	~QuestTypes();
};
