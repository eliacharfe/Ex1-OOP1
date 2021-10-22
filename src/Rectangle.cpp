#include "Board.h"
#include "Vertex.h"
#include "macros.h"
#include "Rectangle.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)//c-tor
{ 
	if ((!bottomLeft.isValid() || !topRight.isValid())
		|| (!topRight.isHigherThan(bottomLeft))
		|| (!topRight.isToTheRightOf(bottomLeft))) // if not OK
	{
		m_bottomLeft = setBottomLeft_default(); //reset data vertex left
		m_topRight = setTopRight_default();// reset data vertex right
		getHeight();// get height of the rectangle
		getWidth();// get the width of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get the perimeter  of the rectangle
		getCenter();
	}
	else
	{ //if OK
	    m_bottomLeft = bottomLeft;
		m_topRight = topRight;
		getHeight();// get height of the rectangle
		getWidth();// get the width of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get the perimeter  of the rectangle
		getCenter();
	}
}
//-----------------------------------------------------------
Rectangle::Rectangle(const Vertex vertices[2])//c-tor
{
	Vertex bottomLeft;
	Vertex topRight;
	if (!vertices[0].isValid() || !vertices[1].isValid()
		|| !vertices[1].isHigherThan(vertices[0])
		|| !vertices[1].isToTheRightOf(vertices[0]))// if not OK
	{
		m_bottomLeft = setBottomLeft_default();
		m_topRight = setTopRight_default();
		getHeight();// get height of the rectangle
		getWidth();// get the width of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get the perimeter  of the rectangle
		getCenter();
	}
	else
	{//if OK
		m_bottomLeft = vertices[0];
		m_topRight = vertices[1];
		getHeight();// get height of the rectangle
		getWidth();// get the width of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get the perimeter  of the rectangle
		getCenter();
	}
}
//---------------------------------------------------------
Rectangle::Rectangle(double x0, double y0, double x1, double y1) //c-tor
{
	m_bottomLeft.m_col = x0; m_bottomLeft.m_row = y0;
	m_topRight.m_col = x1; m_topRight.m_row = y1;

	if ((!m_bottomLeft.isValid() || !m_topRight.isValid())
		|| (!m_topRight.isHigherThan(m_bottomLeft))
		|| (!m_topRight.isToTheRightOf(m_bottomLeft)))
	{
		m_bottomLeft = setBottomLeft_default();
		m_topRight = setTopRight_default();
		getHeight();// get height of the rectangle
		getWidth();// get the width of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get the perimeter  of the rectangle
		getCenter();
	}
	else
	{//if OK
		getHeight();// get height of the rectangle
		getWidth();// get the width of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get the perimeter  of the rectangle
		getCenter();
	}
}
//-----------------------------------------------------------
Rectangle::Rectangle(const Vertex& center, double width, double height)
{
	m_bottomLeft.m_col = m_center.m_col - (getWidth() / 2); //x0
	m_bottomLeft.m_row = m_center.m_row - (getHeight() / 2); //y0
	m_topRight.m_col = m_center.m_col + (getHeight() / 2); //x1
	m_topRight.m_row = m_center.m_row + (getWidth() / 2); //y1

	if ((!m_bottomLeft.isValid() || !m_topRight.isValid())
		|| (!m_topRight.isHigherThan(m_bottomLeft))
		|| (!m_topRight.isToTheRightOf(m_bottomLeft)))
	{
		m_bottomLeft = setBottomLeft_default();
		m_topRight = setTopRight_default();
		getHeight();// get height of the rectangle
		getWidth();// get width of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get the perimeter  of the rectangle
		getCenter();
	}
	else
	{//if OK
		getHeight();// get height of the rectangle
		getWidth();// get width of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get the perimeter  of the rectangle
		getCenter();
	}
}
//------------------------------------
Vertex Rectangle::getBottomLeft() const
{ // return left bottom
	return m_bottomLeft;
}
//----------------------------------------------
Vertex Rectangle::getTopRight() const
{ //return top right
	return m_topRight;
}
//---------------------------------------------------
Vertex Rectangle::setBottomLeft_default() const
{// set bottom left default
	Vertex bLeft;
	   bLeft.m_col = 20;
	   bLeft.m_row = 10;
	return bLeft;
}
//--------------------------------
Vertex Rectangle::setTopRight_default() const
{   // set top right default
	Vertex topR;
		topR.m_col = 30;
		topR.m_row = 20;
	return topR;
}
//------------------------------------------------------
double Rectangle::getHeight()const // get height of the rectangle
{
	return (abs(m_topRight.m_row - m_bottomLeft.m_row));
}
//-------------------------------------------------------------
double Rectangle::getWidth()const // get width of the rectangle
{
	return (abs(m_topRight.m_col - m_bottomLeft.m_col));
}
//----------------------------------------------------------
double Rectangle::getArea()const //get Area of the rectangle
{
	return (getHeight() * getWidth());
}
//--------------------------------------------------------
double Rectangle::getPerimeter()const // get Perimeter of the rectangle
{
	return (2 * (getHeight() + getWidth()));
}
//------------------------------------------------------------
Vertex Rectangle::getCenter()const // get Center of the rectangle
{
	Vertex center;
	center.m_col = (m_bottomLeft.m_col + m_topRight.m_col) / 2;
	center.m_row = (m_bottomLeft.m_row + m_topRight.m_row) / 2;
	return center; // (x1 +x2)/2 ,(y1 + y2)/2
}
//-----------------------------------------------------------
void Rectangle::draw(Board& board) const// draw the rectangle
{
	Vertex bottomRight, topLeft;
	bottomRight.m_col = m_bottomLeft.m_col + getWidth();
	bottomRight.m_row = m_bottomLeft.m_row;
	topLeft.m_col = m_bottomLeft.m_col;
	topLeft.m_row = m_bottomLeft.m_row + getHeight();

	board.drawLine(m_bottomLeft, topLeft);
	board.drawLine(m_topRight, bottomRight);
	board.drawLine(m_topRight, topLeft);
	board.drawLine(m_bottomLeft, bottomRight);
}
//----------------------------------------------------------
Rectangle Rectangle::getBoundingRectangle()const
{ // return rectangle
	return Rectangle(m_bottomLeft, m_topRight);
}
//------------------------------------------------
bool Rectangle::scale(double factor) // scaling the retangle * factor
{ 
	if (factor < 0)
		return false;
	Vertex bLeft, tRight;
	Vertex center = getCenter();
	bLeft.m_col = (m_bottomLeft.m_col - center.m_col) * factor + m_bottomLeft.m_col;
	bLeft.m_row = (m_bottomLeft.m_row - center.m_row) * factor + m_bottomLeft.m_row;
	tRight.m_col = (m_topRight.m_col - center.m_col) * factor + m_topRight.m_col;
	tRight.m_row = (m_topRight.m_row - center.m_row) * factor + m_topRight.m_row;

	if ((!bLeft.isValid() || !tRight.isValid()))
		return false;

	m_bottomLeft = bLeft;
	m_topRight = tRight;
	return true;
}
