#pragma once
#include "PlayerScore.h"
class TopScores
{
public:
	TopScores(void);
	~TopScores(void);
	PlayerScore GetNameScorePair(int index);
	void SetNameScorePair(PlayerScore playerScore, int index);
	void SetRandomVariable();
private:
	PlayerScore m_PlayerScores[5];
	int randomVariable;
};

