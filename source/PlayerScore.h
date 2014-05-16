#pragma once
#include <string>

using namespace std;
class PlayerScore
{
public:
	PlayerScore(void);
	~PlayerScore(void);
	int GetScore() const;
	char* GetName();
	void SetScore(int score);
	void SetName(char playerName[]);
	void SetName(int score);
private:
	char m_PlayerName[6];
	int m_Score;
};

