#include "CharacterBuilder.h"


CharacterBuilder::CharacterBuilder(int characterIndex)
	:m_CharacterIndex(characterIndex), m_IsGold(false), m_IsSilver(false)
{
}


CharacterBuilder::~CharacterBuilder(void)
{
}

bool CharacterBuilder::IsGold() const
{
	return m_IsGold;
}

bool CharacterBuilder::IsSilver() const
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

int CharacterBuilder::GetCharacterIndex() const
{
	return m_CharacterIndex;
}