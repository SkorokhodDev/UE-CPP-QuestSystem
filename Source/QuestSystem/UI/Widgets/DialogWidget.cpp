// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DialogWidget.h"


void UDialogWidget::Speak_Implementation(const FText& Text)
{
}

void UDialogWidget::Reply_Implementation(const TArray<FText>& Texts)
{

}

void UDialogWidget::OnExit_Implementation()
{
}

void UDialogWidget::SetDialogState_Implementation(EDialogState InDialogState)
{
	DialogState = InDialogState;
}