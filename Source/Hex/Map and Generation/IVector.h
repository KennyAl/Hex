// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


/** A Vector 3 with integer precision, full support for assignment and comparisons */
class IVector3
{
public:

	int32 X;
	int32 Y;
	int32 Z;

	IVector3()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	IVector3(int32 Int)
	{
		X = Int;
		Y = Int;
		Z = Int;
	}

	IVector3(int32 _X, int32 _Y, int32 _Z)
	{
		X = _X;
		Y = _Y;
		Z = _Z;
	}

	IVector3(IVector3* _Coord)
	{
		X = _Coord->X;
		Y = _Coord->Y;
		Z = _Coord->Z;
	}

	/*IVector3(IVector2* Vec)
	{
		X = Vec->X;
		Y = Vec->Y;
		Z = 0;
	}*/

	/*void Set(int32 _X, int32 _Y, int32 _Z)
	{
		X = _X;
		Y = _Y;
		Z = _Z;
	}*/

	/*void Set(int32 Int)
	{
		X = Int;
		Y = Int;
		Z = Int;
	}*/

	/*void Set(MapCoord Coord)
	{
		X = Coord.X;
		Y = Coord.Y;
		Z = Coord.Z;
	}*/

	inline IVector3& IVector3::operator=(const IVector3& Other)
	{
		this->X = Other.X;
		this->Y = Other.Y;
		this->Z = Other.Z;

		return *this;
	}

	inline IVector3 IVector3::operator+(const IVector3 Coord)
	{
		return IVector3(X + Coord.X, Y + Coord.Y, Z + Coord.Z);
	}

	inline IVector3 IVector3::operator+(const int32 Int)
	{
		return IVector3(X + Int, Y + Int, Z + Int);
	}

	inline IVector3 IVector3::operator-(const IVector3 Coord)
	{
		return IVector3(X - Coord.X, Y - Coord.Y, Z - Coord.Z);
	}

	inline IVector3 IVector3::operator-(const int32 Int)
	{
		return IVector3(X - Int, Y - Int, Z - Int);
	}

	inline IVector3 IVector3::operator*(const IVector3 Coord)
	{
		return IVector3(X * Coord.X, Y * Coord.Y, Z * Coord.Z);
	}

	inline IVector3 IVector3::operator*(const int32 Int)
	{
		return IVector3(X * Int, Y * Int, Z * Int);
	}

	inline bool IVector3::operator==(const IVector3 Coord)
	{
		return X == Coord.X && Y == Coord.Y && Z == Coord.Z;
	}

	inline bool IVector3::operator<(const IVector3 Coord)
	{
		return X < Coord.X && Y < Coord.Y && Z < Coord.Z;
	}

	inline bool IVector3::operator<=(const IVector3 Coord)
	{
		return X <= Coord.X && Y <= Coord.Y && Z <= Coord.Z;
	}

	inline bool IVector3::operator>(const IVector3 Coord)
	{
		return X > Coord.X && Y > Coord.Y && Z > Coord.Z;
	}

	inline bool IVector3::operator>=(const IVector3 Coord)
	{
		return X >= Coord.X && Y >= Coord.Y && Z >= Coord.Z;
	}

	inline bool IVector3::operator!=(const IVector3 Coord)
	{
		return X != Coord.X || Y != Coord.Y || Z != Coord.Z;
	}

};


/** A Vector 3 with integer precision, full support for assignment and comparisons */
class IVector2
{
public:

	int32 X;
	int32 Y;

	IVector2()
	{
		X = 0;
		Y = 0;
	}

	IVector2(int32 Int)
	{
		X = Int;
		Y = Int;
	}

	IVector2(int32 _X, int32 _Y)
	{
		X = _X;
		Y = _Y;
	}

	IVector2(IVector2* _Coord)
	{
		X = _Coord->X;
		Y = _Coord->Y;
	}

	/*IVector2(IVector3* Vec)
	{
		X = Vec->X;
		Y = Vec->Y;
	}*/

	/*void Set(int32 _X, int32 _Y, int32 _Z)
	{
	X = _X;
	Y = _Y;
	Z = _Z;
	}*/

	/*void Set(int32 Int)
	{
	X = Int;
	Y = Int;
	Z = Int;
	}*/

	/*void Set(MapCoord Coord)
	{
	X = Coord.X;
	Y = Coord.Y;
	Z = Coord.Z;
	}*/

	inline IVector2& IVector2::operator=(const IVector2& Other)
	{
		this->X = Other.X;
		this->Y = Other.Y;

		return *this;
	}

	inline IVector2 IVector2::operator+(const IVector2 Coord)
	{
		return IVector2(X + Coord.X, Y + Coord.Y);
	}

	inline IVector2 IVector2::operator+(const int32 Int)
	{
		return IVector2(X + Int, Y + Int);
	}

	inline IVector2 IVector2::operator-(const IVector2 Coord)
	{
		return IVector2(X - Coord.X, Y - Coord.Y);
	}

	inline IVector2 IVector2::operator-(const int32 Int)
	{
		return IVector2(X - Int, Y - Int);
	}

	inline IVector2 IVector2::operator*(const IVector2 Coord)
	{
		return IVector2(X * Coord.X, Y * Coord.Y);
	}

	inline IVector2 IVector2::operator*(const int32 Int)
	{
		return IVector2(X * Int, Y * Int);
	}

	inline bool IVector2::operator==(const IVector2 Coord)
	{
		return X == Coord.X && Y == Coord.Y;
	}

	inline bool IVector2::operator<(const IVector2 Coord)
	{
		return X < Coord.X && Y < Coord.Y;
	}

	inline bool IVector2::operator<=(const IVector2 Coord)
	{
		return X <= Coord.X && Y <= Coord.Y;
	}

	inline bool IVector2::operator>(const IVector2 Coord)
	{
		return X > Coord.X && Y > Coord.Y;
	}

	inline bool IVector2::operator>=(const IVector2 Coord)
	{
		return X >= Coord.X && Y >= Coord.Y;
	}

	inline bool IVector2::operator!=(const IVector2 Coord)
	{
		return X != Coord.X || Y != Coord.Y;
	}

};