// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreGameStateBase.h"

void AScoreGameStateBase::AddScore(int32 Value)
{
	Score += Value;
}

int32 AScoreGameStateBase::GetScore()
{
	return Score;
}

void AScoreGameStateBase::ResetScore()
{
	Score = 0;
}
