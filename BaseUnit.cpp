//#include "BaseUnit.h"
//#include <cstring>
//#include <utility>
//
//BaseUnit::BaseUnit(double age, double weight, char name[20], size_t PositionX, size_t PositionY)
//{
//	this->age = age;
//	this->weight = weight;
//	strcpy_s(this->name, 20, name);
//	basic.x = PositionX;
//	basic.y = PositionY;
//}
//
//bool BaseUnit::move(int newPosX, int newPosY)
//{
//	if (Clamp(newPosX, -99999999, 999999999))
//	{
//
//	}
//	if (Clamp(newPosY, -99999999, 999999999))
//	{
//
//	}
//
//}
//
//BaseUnit::~BaseUnit()
//{
//	age = 0.0;
//	weight = 0.0;
//	for (size_t i = 0; i < 20; i++)
//	{
//		name[i] = 0;
//	}
//	basic.x = 0;
//	basic.y = 0;
//}