#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class PhysicsObject
{
private:

	//Variables
	sf::CircleShape object;

	float mass;
	float G;
	sf::Vector2f Acceleration;
	sf::Vector2f Velocity;
	sf::Vector2f Position;
	sf::Color color;
	float radius;


	//Pendulum
	void updatePendulum();
	const sf::Vector2i fixPoint = sf::Vector2i(720, 0);
	float alpha;
	sf::Vertex lineVectorG[2];
	sf::Vertex lineVectorZP[2];
	sf::Vertex lineVectorR[2];

	sf::VertexArray lineVectorGArrow;
	sf::VertexArray lineVectorZPArrow;
	sf::VertexArray lineVectorRArrow;
	sf::Vertex connectionTofixPoint[2];
	float lenght;
	float height;
	float initialHeight;
	//void updateLenght();
	float VelocityAmount; // Amount of Velocity
	float F; // acceleration friction 
	float R; // acceleration radial
	float ZP; // acceleration zentripetal

	//Energy
	float Emax;
	float Ekin;
	float Epot;

	sf::Vector2f startingPosition;



public:
	//Constructors / Destructors
	PhysicsObject(float radius, float gravitationalAcceleration, float mass);
	virtual ~PhysicsObject();



	//functions
	void renderObject(sf::RenderWindow* window);
	void updateObject();
	
	//get
	float getRadius();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getAcceleration();
	sf::Color getColor();

	//set
	void setRadius(float radius);
	void setPosition(float x, float y);
	void setVelocity(float x, float y);
	void setAcceleration(float x, float y);
	void addAcceleration(float x, float y);
	void setColor(sf::Color color);

	
	


};

