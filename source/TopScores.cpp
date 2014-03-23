#include "TopScores.h"


TopScores::TopScores(void)
{
	randomVariable = 5;
}


TopScores::~TopScores(void)
{
}

PlayerScore TopScores::GetNameScorePair(int index)
{
	return m_PlayerScores[index];
}

void TopScores::SetNameScorePair(PlayerScore playerScore, int index)
{
	m_PlayerScores[index] = playerScore;
}

void TopScores::SetRandomVariable()
{
	randomVariable = 7;
}