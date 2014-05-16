#pragma once
class CharacterBuilder
{
public:
	CharacterBuilder(int characterIndex);
	~CharacterBuilder(void);
	bool IsGold() const;
	bool IsSilver() const;
	int GetCharacterIndex() const;
	void SetGold(bool isGold);
	void SetSilver(bool isSilver);
private:
	int m_CharacterIndex;
	bool m_IsGold;
	bool m_IsSilver;
};

