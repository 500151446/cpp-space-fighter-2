
#include "Ship.h"
#include "Level.h"


Ship::Ship()
{
	SetPosition(0, 0);
	SetCollisionRadius(10);

	Initialize();
}

void Ship::Update(const GameTime& gameTime)
{
	for (const auto& pair : m_attachments)
	{
		pair.second->Update(gameTime);
	}

	GameObject::Update(gameTime);
}

void Ship::Hit(const float damage)
{
	if (m_isInvulnurable) return;

	m_hitPoints -= damage;
	if (m_hitPoints > 0) return;

	// Xana - Original add score was here, it was moved to EnemyShip.cpp

	GameObject::Deactivate();
	GetCurrentLevel()->SpawnExplosion(this);
}

IAttachment* Ship::GetAttachment(const std::string& key)
{
	m_attachmentIt = m_attachments.find(key);
	if (m_attachmentIt == m_attachments.end()) return nullptr;
	return m_attachmentIt->second;
}

IAttachment* Ship::GetAttachment(const int index)
{
	if (index < m_attachments.size())
	{
		m_attachmentIt = m_attachments.begin();
		std::advance(m_attachmentIt, index);
		return m_attachmentIt->second;
	}

	return nullptr;
}

void Ship::Initialize()
{
	m_hitPoints = m_maxHitPoints;
}

void Ship::FireWeapons(TriggerType triggerType)
{
	//m_weaponIt = m_weapons.begin();
	//for (; m_weaponIt != m_weapons.end(); m_weaponIt++)
	//{
	//	(*m_weaponIt)->Fire(type);
	//}

	m_attachmentIt = m_attachments.begin();
	for (; m_attachmentIt != m_attachments.end(); m_attachmentIt++)
	{
		if (m_attachmentIt->second->GetAttachmentType() != "Weapon") continue;
		((Weapon *)(m_attachmentIt->second))->Fire(triggerType);
	}
}

//void Ship::AttachWeapon(Weapon* pWeapon, Vector2 position)
//{
//	AttachItem(pWeapon, position);
//	m_weapons.push_back(pWeapon);
//}

void Ship::AttachItem(IAttachment* item, Vector2 position)
{
	item->AttachTo(this, position);
	m_attachments[item->GetKey()] = item;
}