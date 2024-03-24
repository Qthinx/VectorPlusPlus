//#pragma once
//#include <exception>
//
//
//struct Position2D
//{
//	size_t x;
//	size_t y;
//};
//class BaseUnit
//{
//private:
//	double age = 0.0;
//	double weight = 0.0;
//	char name[20] = "";
//	Position2D basic;
//public:
//	BaseUnit
//	(
//		double age,
//		double weight,
//		char name[20],
//		size_t PositionX,
//		size_t PositionY
//	);
//
//	int	Clamp(size_t val, size_t min, size_t max)
//	{
//		if (val >= min && val <= max)
//		{
//			return val;
//		}
//		else
//		{
//			throw std::exception("Incorrect value");
//		}
//	}
//	double get_age()
//	{
//		return age;
//	}
//
//	double get_weight()
//	{
//		return weight;
//	}
//
//	char get_name()
//	{
//		for (size_t i = 0; i < 20; i++)
//		{
//			return name[i];
//		}
//	}
//
//	int get_Xpos()
//	{
//		return basic.x;
//	}
//
//	int get_Ypos()
//	{
//		return basic.y;
//	}
//
//	bool move(int newPosX, int newPosY);
//	
//	virtual ~BaseUnit() = 0;
//
//};
//
