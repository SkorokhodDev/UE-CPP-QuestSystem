// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetControllers/WidgetControllerBase.h"
#include "QuestMenuWidgetControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewQuestWasAdded, AQuestBase*, QuestActor);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class QUESTSYSTEM_API UQuestMenuWidgetControllerBase : public UWidgetControllerBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnNewQuestWasAdded NewQuestWasAddedDelegate;

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
};
