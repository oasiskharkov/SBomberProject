#pragma once

#include <vector>

class DynamicObject;
class GameObject;
class Plane;

class Command 
{
public:
	virtual ~Command() {}
	virtual void Execute() = 0;
};

class DeleteDynamicObjectCommand : public Command
{
public:
	DeleteDynamicObjectCommand(std::vector<DynamicObject*>& dObjects, DynamicObject* dObject);
	void Execute() override;
private:
	std::vector<DynamicObject*>& dynamicObjects;
	DynamicObject* dynamicObject;
};

class DeleteStaticObjectCommand : public Command
{
public:
	DeleteStaticObjectCommand(std::vector<GameObject*>& gObjects, GameObject* gObject);
	void Execute() override;
private:
	std::vector<GameObject*>& gameObjects;
	GameObject* gameObject;
};

class DropBombCommand : public Command
{
public:
	DropBombCommand(std::vector<DynamicObject*>& dObjects, const Plane* plane, uint16_t& bombsNumber, int16_t& score);
	void Execute() override;
private:
	std::vector<DynamicObject*>& dynamicObjects;
	const Plane* plane;
	uint16_t& bombsNumber;
	int16_t& score;
};