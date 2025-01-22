#include <iostream>
#include <vector>
#include <fstream>


// 3. simple usage of std::vector<>
struct Entity
{
	float x, y, z;
};

void Function(const std::vector<Entity>& entities)  // use reference to avoid copy
{

}

std::ostream& operator<<(std::ostream& stream, const Entity& entity)
{
	stream << entity.x << ", " << entity.y << ", " << entity.z;
	return stream;
}

// 4. optimization of using std::vector<>
struct Vertex
{
	float x, y, z;

	Vertex(float x, float y, float z)
		: x(x), y(y), z(z) {
	}

	Vertex(const Vertex& other)  // copy constructor
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Copied!" << std::endl;
	}
};


int main()
{
	// 3. simple usage of std::vector<>
	std::vector<Entity> entities;

	entities.push_back({ 1, 2, 3 });
	entities.push_back({ 4, 5, 6 });

	Function(entities);

	for (int i = 0; i < entities.size(); i++)
		std::cout << entities[i] << std::endl;

	for (Entity e : entities)
		std::cout << e << std::endl;

	for (const Entity& e : entities)
		std::cout << e << std::endl;

	entities.erase(entities.begin() + 1);

	entities.clear();
	std::cout << entities.size() << std::endl;

	// 4. optimization of using std::vector<>
	// 4.2 too many copies
	/*std::vector<Vertex> vertices;
	vertices.push_back({ 1, 2, 3 });
	vertices.push_back({ 4, 5, 6 });
	vertices.push_back({ 7, 8, 9 });*/

	// 4.3 reserve() at the beginning
	//std::vector<Vertex> vertices;
	//vertices.reserve(3);
	//vertices.push_back({ 1, 2, 3 });
	//vertices.push_back({ 4, 5, 6 });
	//vertices.push_back({ 7, 8, 9 });

	// 4.4 emplace_back() to construct the object in place in the memory of the std::vector<>
	std::vector<Vertex> vertices;
	vertices.reserve(3);
	vertices.emplace_back(1, 2, 3);
	vertices.emplace_back(4, 5, 6);
	vertices.emplace_back(7, 8, 9);
}
