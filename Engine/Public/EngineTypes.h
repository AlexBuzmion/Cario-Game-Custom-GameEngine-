//
// * ENGINE-X
//
// + Types.h
// representations of: 2D vector with floats, 2D vector with integers and RBGA color as four bytes
//

#pragma once

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exVector2
{
	float x, y;

	// first engine modification here: 
	exVector2 operator+(const exVector2& other) {
		return exVector2(this->x + other.x, this->y + other.y);
	}

	exVector2 operator-(const exVector2& other) {
		return exVector2(this->x - other.x, this->y + other.y);
	}

	exVector2 operator*(const float& other) {
		return exVector2(x * other, y * other);
	}
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exIntegerVector2
{
	int x, y;
};

//-----------------------------------------------------------------
//-----------------------------------------------------------------

struct exColor
{
	unsigned char mColor[4];
};
