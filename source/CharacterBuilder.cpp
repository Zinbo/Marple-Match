#include "CharacterBuilder.h"


CharacterBuilder::CharacterBuilder(int characterIndex)
	:m_CharacterIndex(characterIndex), m_IsGold(false), m_IsSilver(false)
{
}


CharacterBuilder::~CharacterBuilder(void)
{
}

bool CharacterBuilder::IsGold()
{
	return m_IsGold;
}

bool CharacterBuilder::IsSilver()
{
	return m_IsSilver;
}

void CharacterBuilder::SetGold(bool isGold)
{
	m_IsGold = isGold;
}

void CharacterBuilder::SetSilver(bool isSilver)
{
	m_IsSilver = isSilver;
}

int CharacterBuilder::GetCharacterIndex()
{
	return m_CharacterIndex;
}