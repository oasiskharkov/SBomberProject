#pragma once

#include <vector>
#include <memory>

#include "DynamicObject.h"
#include "DestroyableGroundObject.h"

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
	DeleteDynamicObjectCommand(std::vector<std::shared_ptr<DynamicObject>>& dObjects, DynamicObject* dObject);
	void Execute() override;
private:
	std::vector<std::shared_ptr<DynamicObject>>& dynamicObjects;
	DynamicObject* dynamicObject;
};

class DeleteStaticObjectCommand : public Command
{
public:
	DeleteStaticObjectCommand(std::vector<std::shared_ptr<GameObject>>& gObjects, GameObject* gObject);
	void Execute() override;
private:
	std::vector<std::shared_ptr<GameObject>>& gameObjects;
	GameObject* gameObject;
};

class DropBombCommand : public Command
{
public:
	DropBombCommand(std::vector<std::shared_ptr<DynamicObject>>& dObjects, const std::vector<DestroyableGroundObject*>& dgos_, 
		const Plane* plane, uint16_t& bombsNumber, int16_t& score);
	void Execute() override;
private:
	std::vector<std::shared_ptr<DynamicObject>>& dynamicObjects;
	const std::vector<DestroyableGroundObject*>& dgos;
	const Plane* plane;
	uint16_t& bombsNumber;
	int16_t& score;
};