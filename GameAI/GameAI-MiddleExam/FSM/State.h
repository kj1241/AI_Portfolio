#ifndef STATE_H
#define STATE_H


class Entity;

//Çàµ¿ 
class State
{
public:
	State();
	virtual ~State();
	virtual void Enter(Entity*) = 0;
	virtual void Execute(Entity*) = 0;
	virtual void Exit(Entity*) = 0;
};


#endif