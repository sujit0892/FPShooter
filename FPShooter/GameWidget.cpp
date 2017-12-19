// Fill out your copyright notice in the Description page of Project Settings.

#include "GameWidget.h"

void UGameWidget::Load()
{
	const FName TextBlockName = FName(TEXT("ScoreTextBlock"));

	if (ScoreText == nullptr)
	{
		ScoreText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}

void UGameWidget::setScore(int Score)
{
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("Score : ")) + FString::FromInt(Score)));
	}
}

void UGameWidget::OnGameOver(int Score)
{
	if (ScoreText != nullptr)
	{
		ScoreText->SetText(FText::FromString(FString(TEXT("Game Over!\n"))+FString(TEXT("Score : ")) + FString::FromInt(Score)+ FString(TEXT("\nPress R to restart"))));
	}
}

