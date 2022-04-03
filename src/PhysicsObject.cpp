#include "../include/PhysicsObject.h"
#include <iostream>
#include <math.h>
//Constructors / Destructors



PhysicsObject::PhysicsObject(float radius, float gravitationalAcceleration, float mass)
{

	this->mass = mass;
	this->G = gravitationalAcceleration;
	this->setColor(color);
	this->setRadius(radius);



	this->lineVectorG[0].color = sf::Color(255 ,0 ,0 ,255);
	this->lineVectorG[1].color = sf::Color(255, 0, 0, 255);

	this->lineVectorZP[0].color = sf::Color(0, 255, 0, 255);
	this->lineVectorZP[1].color = sf::Color(0, 255, 0, 255);

	this->lineVectorR[0].color = sf::Color(0, 0, 255, 255);
	this->lineVectorR[1].color = sf::Color(0, 0, 255, 255);

	this->connectionTofixPoint[0].color = sf::Color(255, 255, 255, 255);
	this->connectionTofixPoint[1].color = sf::Color(255, 255, 255, 255);

	this->connectionTofixPoint[0].position = sf::Vector2f(fixPoint.x,fixPoint.y);

}


PhysicsObject::~PhysicsObject()
{
	
}



//functions

void PhysicsObject::renderObject(sf::RenderWindow* window)
{
	//Connection
	window->draw(connectionTofixPoint, 2, sf::Lines);

	//Object
	window->draw(this->object);

	//Forces
	window->draw(lineVectorG, 2, sf::Lines);
	window->draw(lineVectorZP, 2, sf::Lines);
	window->draw(lineVectorR, 2, sf::Lines);
}

void PhysicsObject::updatePendulum()
{

	//sets the lenght of the object back to its original lenght to avoid simulation errors

	//lenght = sqrt(pow((this->fixPoint.x - (this->Position.x + this->radius)), 2) + pow(abs(this->fixPoint.y - (this->Position.y + this->radius)), 2));
	//calculate angle
	this->alpha = atan((this->fixPoint.x - (this->Position.x  + this->radius)) / abs(this->fixPoint.y - (this->Position.y + this->radius)));
	//calc Energy
	this->height = (this->lenght * (1 - cos(this->alpha)));

	this->Epot = height * this->G;

	this->Ekin = this->Emax - this->Epot;
	Emax -= 0.05f;
	if (Emax <= 0) {
		Emax = 0;
	}
	std::cout << Epot + Ekin << ", DIR:" << (alpha/abs(alpha)) << "\n";

	if (lround(initialHeight*10) == lround(height*10)) {
		Velocity.x = 0;
		Velocity.y = 0;
		
;	}
	//this->VelocityAmount = pow(sqrt(pow(this->Velocity.x, 2) + pow(this->Velocity.y, 2)), 2);	


	this->VelocityAmount = 2 * this->Ekin;

	this->R = this->G * cos(this->alpha);
	this->F = -this->G * cos(this->alpha) * 0.05f;
	this->ZP = VelocityAmount /this->lenght;
	this->setAcceleration( sin(this->alpha) * (R + ZP), -cos(this->alpha) * (abs(R) + abs(ZP)));



	//update line Positions
	this->lineVectorG[0].position = sf::Vector2f(this->Position.x + this->radius + 15, this->Position.y + this->radius + this->G*1000);
	this->lineVectorZP[0].position = sf::Vector2f(this->Position.x + this->radius + sin(this->alpha) * ZP * 1000 + 25, this->Position.y + this->radius - cos(this->alpha) * abs(ZP) * 1000);
	this->lineVectorR[0].position = sf::Vector2f(this->Position.x + this->radius + sin(this->alpha) * R * 1000 + 15, this->Position.y + this->radius -cos(this->alpha) * abs(R * 1000));
	
	this->lineVectorG[1].position = sf::Vector2f(this->Position.x + this->radius + 15, this->Position.y + this->radius);
	this->lineVectorZP[1].position = sf::Vector2f(this->Position.x + this->radius + 25, this->Position.y + this->radius);
	this->lineVectorR[1].position = sf::Vector2f(this->Position.x + this->radius + 15, this->Position.y + this->radius);

	//update Line Position of Connection to FixPoint
	this->connectionTofixPoint[1].position = sf::Vector2f(this->Position.x + this->radius, this->Position.y + this->radius);

}




void PhysicsObject::updateObject()
{
	this->updatePendulum();
	this->Velocity.y += this->G;
	this->Velocity.x += this->Acceleration.x;
	this->Velocity.y += this->Acceleration.y;
	this->Position.x = this->fixPoint.x - this->radius + (sin(alpha) * -this->lenght) + this->Velocity.x;
	this->Position.y = this->fixPoint.y - this->radius + (cos(abs(alpha)) * this->lenght) + this->Velocity.y;
	this->object.setPosition(Position.x, Position.y);
	//std::cout << sqrt(pow((this->fixPoint.x - (this->Position.x + this->radius)), 2) + pow(abs(this->fixPoint.y - (this->Position.y + this->radius)), 2)) << "\n";

}


//set

void PhysicsObject::setRadius(float radius)
{
	this->object.setRadius(radius);
	this->radius = radius;
}

void PhysicsObject::setPosition(float x, float y)
{
	this->Position.x = x;
	this->Position.y = y;
	this->startingPosition.x = x;
	this->startingPosition.y = y;
	this->lenght = sqrt(pow((this->fixPoint.x - (this->Position.x + this->radius)), 2) + pow(abs(this->fixPoint.y - (this->Position.y + this->radius)), 2));
	this->alpha = atan(abs(this->fixPoint.x - (this->Position.x + this->radius)) / abs(this->fixPoint.y - (this->Position.y + this->radius)));

	this->initialHeight = (this->lenght * (1 - cos(this->alpha)));
	this->Emax = this->initialHeight * this->G;
	this->object.setPosition(this->Position);

}

void PhysicsObject::setVelocity(float x, float y)
{
	this->Velocity.x = x;
	this->Velocity.y = y;
}

void PhysicsObject::setAcceleration(float x, float y)
{
	this->Acceleration.x = x;
	this->Acceleration.y = y;
}


void PhysicsObject::addAcceleration(float x, float y)
{
	this->Acceleration.x += x;
	this->Acceleration.y += y;
}

void PhysicsObject::setColor(sf::Color color)
{
	this->color = color;
	this->object.setFillColor(color);

}



//get


float PhysicsObject::getRadius()
{
	return this->radius;
}

sf::Vector2f PhysicsObject::getPosition()
{
	return this->Position;
}

sf::Vector2f PhysicsObject::getVelocity()
{
	return this->Velocity;
}

sf::Vector2f PhysicsObject::getAcceleration()
{
	return this->Acceleration;
}

sf::Color PhysicsObject::getColor()
{
	return this->color;
}



