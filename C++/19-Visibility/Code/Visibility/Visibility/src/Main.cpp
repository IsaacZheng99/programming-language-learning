#include <iostream>


// 2.1 private
class PrivateEntity
{
private:
	int x, y;
};

//class Player1 : public PrivateEntity
//{
//public:
//	Player1()
//	{
//		x = 0;  // Wrong! Compiling error.
//	}
//};

// 2.2 protected
class ProtectedEntity
{
protected:
	int x, y;
};

class Player2 : public ProtectedEntity
{
public:
	Player2()
	{
		x = 0;
	}
};

// 2.3 public
class PublicEntity
{
public:
	int x, y;
};

class Player3 : public PublicEntity
{
public:
	Player3()
	{
		x = 0;
	}
};

// 3.1 private inheritance
class Player4 : private PublicEntity
{
public:
	Player4()
	{
		x = 0;
	}
};

//class SubPlayer4 : public Player4
//{
//public:
//	SubPlayer4()
//	{
//		x = 0;  // Wrong! Compiling error.
//	}
//};

// 3.2 protected inheritance
class Player5 : protected PublicEntity
{
public:
	Player5()
	{
		x = 0;
	}
};

class SubPlayer5 : public PublicEntity
{
public:
	SubPlayer5()
	{
		x = 0;
	}
};

// 4.1 friend function
class FriendFunctionEntity
{
private:
	int x, y;

	friend void PrintFriendFunctionEntity(FriendFunctionEntity* e);
};

void PrintFriendFunctionEntity(FriendFunctionEntity* e)
{
	std::cout << e->x << ", " << e->y << std::endl;
}

// 4.2 friend class
class FriendClassEntity
{
private:
	int x, y;

	friend class Friend;
};

class Friend
{
public:
	void PrintFriendClassEntity(FriendClassEntity* e)
	{
		std::cout << e->x << ", " << e->y << std::endl;
	}
};


int main()
{
	// 3.1 private inheritance
	//Player4 p4;
	//std::cout << p4.x << std::endl;  // Wrong! Compiling error.
	//Player4 p5;
	//std::cout << p5.x << std::endl;  // Wrong! Compiling error.

	// 4.1 friend function
	FriendFunctionEntity* friendFunctionEntity = new FriendFunctionEntity();
	PrintFriendFunctionEntity(friendFunctionEntity);

	// 4.2 friend class
	FriendClassEntity* friendClassEntity = new FriendClassEntity();
	Friend friendClass;
	friendClass.PrintFriendClassEntity(friendClassEntity);
}
