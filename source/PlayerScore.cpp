#include "PlayerScore.h"


PlayerScore::PlayerScore(void)
	:m_Score(-1), m_PlayerName()
{
}


PlayerScore::~PlayerScore(void)
{
}

int PlayerScore::GetScore() const
{
	return m_Score;
}

char* PlayerScore::GetName()
{
	return m_PlayerName;
}

void PlayerScore::SetName(char playerName[])
{
	sprintf(m_PlayerName, playerName);
}

void PlayerScore::SetScore(int score)
{
	m_Score = score;
}
