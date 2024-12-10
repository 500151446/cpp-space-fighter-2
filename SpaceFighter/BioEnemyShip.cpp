
#include "BioEnemyShip.h"
#include "Level.h"


BioEnemyShip::BioEnemyShip()
{
	SetSpeed(150);
	SetMaxHitPoints(1);
	SetCollisionRadius(20);
	m_scoreValue = 100;
}


void BioEnemyShip::Update(const GameTime& gameTime)
{
	if (IsActive())
	{
		double actualTotalTime = gameTime.GetTotalTime() - GetCurrentLevel()->GetPausedTime();
		float x = sin(actualTotalTime * Math::PI + GetIndex());
		x *= GetSpeed() * gameTime.GetElapsedTime() * 1.4f;
		TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());

		if (!IsOnScreen()) Deactivate();
	}

	EnemyShip::Update(gameTime);
}


void BioEnemyShip::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive())
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}
