#pragma once
#include "Board.h"
#include "Rectangle.h"

class Window
{
public:
	Window(const Rectangle & outer, const Rectangle& inner);
	Window(const Rectangle& outer, double verticalThickness, double horizontalThickness);

	Vertex getBottomLeft() const; // get bottom left vertex
	Vertex getTopRight()const;// get top right vertex

	double getVerticalThickness()const;// get the vertical thickness between
	double getHorizontalThickness()const;//get the horizontal thickness between

	double getHeight()const;// get height of the rectangle
	double getArea() const;// get area of the rectangle
	double getPerimeter() const;// get perimeter of the rectangle
	Vertex getCenter()const;// get center of the rectangles

	void draw(Board& board)const; // draw the rectangles
	Rectangle getBoundingRectangle()const;// return bounded rectangles
	bool scale(double factor);// scaling retangles * factor

private:
	Vertex m_bottomLeft_outer;
	Vertex m_topRight_outer;

	Vertex m_bottomLeft_inner;
	Vertex m_topRight_inner;

	Vertex m_center_outer;
	Vertex m_center_inner;

	Vertex setBottomLeft_default() const;  // default bottom left
	Vertex setTopRight_default() const;  // default top right

	double getWidth()const;// get width outer
	double getWidth_inner()const; // get width inner
	double getHeigh_inner()const;// get height inner
	Vertex getCenter_inner()const; // get center inner
};

