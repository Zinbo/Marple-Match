#pragma once
#include "PlayerScore.h"
class TopScores
{
public:
	TopScores(void) {};
	~TopScores(void) {};
	PlayerScore GetNameScorePair(int index) const;
	void SetNameScorePair(const PlayerScore playerScore, int index);
	void SetRandomVariable();
private:
	PlayerScore m_PlayerScores[5];
};

