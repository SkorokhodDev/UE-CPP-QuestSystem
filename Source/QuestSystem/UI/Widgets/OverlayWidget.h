// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/MyUserWidget.h"
#include "OverlayWidget.generated.h"

/**
 * 
 */
UCLASS(abstract)
class QUESTSYSTEM_API UOverlayWidget : public UMyUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ToggleQuestMenu();
};
