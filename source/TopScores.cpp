#include "TopScores.h"


TopScores::TopScores(void)
{
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
