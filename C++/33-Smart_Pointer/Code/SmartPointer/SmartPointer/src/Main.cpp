#include <iostream>


// 2. std::unique_ptr<>
// 2.1 scoped pointer
class Entity
{
private:
	int x, y;
public:
	Entity()
	{
		std::cout << "Created Entity!" << std::endl;
	}

	Entity(int x, int y)
		: x(x), y(y)
	{
		std::cout << "Created Entity!" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print()
	{
		std::cout << x << ", " << y << std::endl;
	}
};


int main()
{
	// 2. std::unique_ptr<>
	// 2.1 scoped pointer
	{
		std::unique_ptr<Entity> e1(new Entity(1, 2));
		e1->Print();
		std::unique_ptr<Entity> e2(new Entity());
		e2->Print();
		std::unique_ptr<Entity> e3 = std::make_unique<Entity>(1, 2);
		e3->Print();
		std::unique_ptr<Entity> e4 = std::make_unique<Entity>();
		e4->Print();
	}

	// 2.2 can't copy
	{
		std::unique_ptr<Entity> e1 = std::make_unique<Entity>(1, 2);
		//std::unique_ptr<Entity> e2 = e1;  // Wrong! error C2280: 'std::unique_ptr<Entity,std::default_delete<Entity>>::unique_ptr(const std::unique_ptr<Entity,std::default_delete<Entity>> &)': attempting to reference a deleted function
	}

	// 3. std::shared_ptr<>
	// 3.3 control block
	{
		std::shared_ptr<Entity> e1(new Entity());
		std::shared_ptr<Entity> e2 = std::make_shared<Entity>();  // more efficient
	}

	// 3.4 use std::shared_ptr<> inside the scope
	{
		std::shared_ptr<Entity> e1 = std::make_shared<Entity>();
		std::shared_ptr<Entity> e2 = e1;
	}
	std::cout << "Destroyed has been printed!" << std::endl;

	// 3.5 use std::shared_ptr<> outside the scope
	{
		std::shared_ptr<Entity> e0;
		{
			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
			e0 = sharedEntity;
			sharedEntity->Print();
		}
		std::cout << "Destroyed hasn't been printed!" << std::endl;
	}

	// 4. std::weak_ptr<>
	// 4.2 when to use it
	{
		std::weak_ptr<Entity> e0;
		{
			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
			e0 = sharedEntity;
			//e0->Print();  // Wrong! error C2819: type 'std::weak_ptr<_Ty>' does not have an overloaded member 'operator ->'
			// error C2039: 'Print': is not a member of 'std::weak_ptr<_Ty>'
		}
		std::cout << "Destroyed has been printed!" << std::endl;
	}
}
