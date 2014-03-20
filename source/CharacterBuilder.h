#pragma once
class CharacterBuilder
{
public:
	CharacterBuilder(int characterIndex);
	~CharacterBuilder(void);
	bool IsGold();
	bool IsSilver();
	int GetCharacterIndex();
	void SetGold(bool isGold);
	void SetSilver(bool isSilver);
private:
	int m_CharacterIndex;
	bool m_IsGold;
	bool m_IsSilver;
};

