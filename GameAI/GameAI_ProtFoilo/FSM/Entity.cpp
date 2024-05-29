#include "stdafx.h"

Entity::Entity():wID(0), wNextValueID(0), wHP(0), X(0),Y(0)
{
}

Entity::~Entity()
{
}

void Entity::SetID(WORD wID)
{
	this->wID = wID;
}

WORD Entity::GetHP()
{
	return wHP;
}

void Entity::SetHP(WORD wHP)
{
	this->wHP = wHP;
}

int Entity::GetX()
{
	return X;
}

void Entity::SetX(int x)
{
	this->X = x;
}

int Entity::GetY()
{
	return Y;
}

void Entity::SetY(int y)
{
	this->Y = y;
}
