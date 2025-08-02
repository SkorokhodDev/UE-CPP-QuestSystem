// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeakFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplyFinished, int32, ReplyIndex);

UENUM(BlueprintType)
enum class EDialogState : uint8
{
	Speak = 0,
	Reply = 1,
};
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnExit OnExitDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSpeakFinished OnSpeakFinishedDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnReplyFinished OnReplyFinishedDelegate;

protected:
	UPROPERTY(BlueprintReadOnly)
	EDialogState DialogState;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetDialogState(EDialogState InDialogState);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Speak(const FText& Text);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reply(const TArray<FText>& Texts);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnExit();
};
