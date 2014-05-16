#include "TopScores.h"

PlayerScore TopScores::GetNameScorePair(int index) const
{
	return m_PlayerScores[index];
}

void TopScores::SetNameScorePair(const PlayerScore playerScore, int index)
{
	m_PlayerScores[index] = playerScore;
}
