// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetControllerBase.generated.h"



/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class QUESTSYSTEM_API UWidgetControllerBase : public UObject
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	virtual void BindCallbacksToDependencies();
	
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();
};
