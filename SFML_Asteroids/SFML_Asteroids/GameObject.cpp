#include "GameObject.h"
#include <iostream>

GameObject::GameObject(std::string TexturePath, const sf::Vector2f& Position) :
	m_Position(Position),
	m_Velocity(sf::Vector2f(0.0f, 0.0f)),
	m_Accel(sf::Vector2f(0.0f, 0.0f)),
	m_Angle(0.0f),
	m_CollisionRadius(0.0f),
	m_Destroyed(false)
{
	// Load the Texture and Assign the Sprite
	if (TexturePath != "")
	{
		m_Texture = TextureHolder::GetTexture(TexturePath); // Use the Container to Load Texture
		m_Sprite.setTexture(m_Texture);
		m_Sprite.setOrigin(m_Sprite.getTextureRect().width * 0.5f, m_Sprite.getTextureRect().height * 0.5f);
		// ^ Set Origin to the Center of the Sprite
	}
}

void GameObject::Update(sf::RenderWindow* Window, float DeltaTime)
{
	float s_DecelScalar = 0.5f; // Rate of Deceleration
	m_Velocity += m_Accel * DeltaTime;

	LimitVelocity(DeltaTime);
	ApplyDrag(DeltaTime);

	/*
	Velocity, scaled by DeltaTime, is used to Manipulate the Position
	*/
	m_Position += m_Velocity * DeltaTime;

	/*
	Make sure nothing goes off screen to infinity
	*/
	if (m_Position.x < 0) // Left
	{
		m_Position.x = Window->getSize().x;
		WentOffEdgeOfScreen(false);
	}
	else if (m_Position.x > Window->getSize().x) // Right
	{
		m_Position.x = 0;
		WentOffEdgeOfScreen(false);
	}

	if (m_Position.y < 0) // Top
	{
		m_Position.y = Window->getSize().y;
		WentOffEdgeOfScreen(true);
	}
	else if (m_Position.y > Window->getSize().y) // Bottom
	{
		m_Position.y = 0;
		WentOffEdgeOfScreen(true);
	}

	// Rotate and then Manipulate Position
	m_Sprite.setRotation(m_Angle);
	m_Sprite.setPosition(m_Position);
}

void GameObject::Draw(sf::RenderWindow* Window)
{
	Window->draw(m_Sprite);
}

void GameObject::LimitVelocity(float DeltaTime)
{
	// Calculate the Magnitude of the Velocity Vector
	float s_Speed = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);

	if (s_Speed <= 0.1f)
	{
		return;
	}

	// Normalize the Velocity Vector
	sf::Vector2f s_NormalizedVelocity = sf::Vector2f(m_Velocity.x / s_Speed, m_Velocity.y / s_Speed);

	if (s_Speed > 500)
	{
		s_Speed = 500;
		// Limit the Speed
	}

	m_Velocity.x = s_NormalizedVelocity.x * s_Speed;
	m_Velocity.y = s_NormalizedVelocity.y * s_Speed;
}

void GameObject::ApplyDrag(float DeltaTime)
{
	// If you're not trying to move the Sprite
	if (m_Accel.x == 0.0f && m_Accel.y == 0.0f)
	{
		float s_DragAmount = DeltaTime * 0.9f; 
		m_Velocity.x -= s_DragAmount * m_Velocity.x;
		m_Velocity.y -= s_DragAmount * m_Velocity.y;
	}
}

bool GameObject::IsColliding(GameObject* Other)
{
	/*
	If the Object calling the "IsColliding()" Function
	Is not the Same as the Other "GameObject"
	AND
	if the Object calling the "IsColliding()" Function
	IS NOT Destroyed
	OR if the Other "GameObject" IS Destroyed
	*/
	if (this != Other && !IsDestroyed()
		|| Other->IsDestroyed())
	{
		sf::Vector2f s_VectorToOther;
		s_VectorToOther = Other->GetPosition() - this->GetPosition();

		// Calculate the Magnitude of the s_VectorToOther Vector
		float s_Distance = std::sqrt(s_VectorToOther.x * s_VectorToOther.x + s_VectorToOther.y * s_VectorToOther.y);

		/*
		If the Distance Between the Two Objects
		is Less Than Both of the Objects
		Collision Radius
		*/
		if (s_Distance < m_CollisionRadius + Other->m_CollisionRadius)
		{
			return true;
		}
	}

	return false;
}

void GameObject::Destroy()
{
	m_Destroyed = true;
}

bool GameObject::IsDestroyed()
{
	return m_Destroyed;
}

void GameObject::SetOwner(PlayState* Owner)
{
	m_Owner = Owner;
}

void GameObject::SetAngle(float Angle)
{
	m_Angle = Angle;
}

float GameObject::GetAngle()
{
	return m_Angle;
}

void GameObject::SetPosition(const sf::Vector2f& Position)
{
	m_Position = Position;
}

void GameObject::SetAccel(float Amount)
{
	if (Amount > 0.0f)
	{
		/*
		SFML Calculates in Radians
		Convert the Current Angle to Radians
		*/
		float s_RotationInRadians = DEG_TO_RAD * m_Angle;

		m_Accel = sf::Vector2f(Amount * std::sin(s_RotationInRadians), -Amount * cos(s_RotationInRadians));
	}
	else
	{
		m_Accel = sf::Vector2f(0.0f, 0.0f);
	}
}

void GameObject::SetVelocity(float Amount)
{
	if (Amount > 0.0f)
	{
		/*
		SFML Calculates in Radians
		Convert the Current Angle to Radians
		*/
		float s_RotationInRadians = DEG_TO_RAD * m_Angle;

		m_Velocity = sf::Vector2f(Amount * std::sin(s_RotationInRadians), -Amount * cos(s_RotationInRadians));
	}
	else
	{
		m_Velocity = sf::Vector2f(0.0f, 0.0f);
	}
}