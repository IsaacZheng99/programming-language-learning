#include <iostream>


// 3. some examples
// 3.1 implicit cast
class Entity {};

class Player : public Entity {};

class Enemy : public Entity {};


// 3.3 dynamic_cast<> with virtual function
class Entity2
{
private:
	virtual void Print() {}
};

class Player2 : public Entity2 {};

class Enemy2 : public Entity2 {};


int main()
{
	// 3. some examples
	// 3.1 implicit cast
	Player* p1 = new Player();
	Entity* e1 = p1;  // implicit cast
	//Player* p2 = e1;  // Wrong! error C2440: 'initializing': cannot convert from 'Entity *' to 'Player *'

	// 3.2 dynamic_cast<> without virtual function
	Player* p3 = new Player();
	Entity* e2 = p3;
	// we need to add a "virtual function" in the "Entity" class to indicate it is a polymorphic type
	//Player* p4 = dynamic_cast<Player*>(e2);  // Wrong! error C2683: 'dynamic_cast': 'Entity' is not a polymorphic type

	// 3.3 dynamic_cast<> with virtual function
	Player2* player = new Player2();
	Entity2* actualPlayer = player;
	Entity2* actualEnemy = new Enemy2();

	Player2* player2 = dynamic_cast<Player2*>(actualPlayer);
	if (player2)
		std::cout << "player2 is Player2" << std::endl;
	Player2* player3 = dynamic_cast<Player2*>(actualEnemy);
	if (player3 == nullptr)
		std::cout << "player3 is not Player2" << std::endl;
}
