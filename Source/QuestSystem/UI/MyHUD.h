// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UOverlayWidget;
class UOverlayWidgetController;
class UQuestMenuWidgetControllerBase;
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	

protected:
	UPROPERTY()
	TObjectPtr<UOverlayWidget> OverlayWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UOverlayWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UQuestMenuWidgetControllerBase> QuestMenuWidgetController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UQuestMenuWidgetControllerBase> QuestMenuWidgetControllerClass;

	void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ToggleQuestMenu();


	UFUNCTION(BlueprintCallable)
	UOverlayWidgetController* GetOverlayWidgetController();
	UFUNCTION(BlueprintCallable)
	UQuestMenuWidgetControllerBase* GetQuestMenuWidgetController();
};
