#include "Board.h"
#include "Vertex.h"
#include "macros.h"
#include "Rectangle.h"
#include "Window.h"

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

Window::Window(const Rectangle& outer, const Rectangle& inner)
{
	m_center_outer = outer.getCenter();// center outer
	m_center_inner = inner.getCenter();// center inner
	
	if (m_center_outer.m_col != m_center_inner.m_col   //if not OK
		|| m_center_outer.m_row != m_center_inner.m_row
	    || outer.getBottomLeft().isToTheRightOf(inner.getBottomLeft())
		|| inner.getBottomLeft().isToTheRightOf(outer.getTopRight())
		|| inner.getTopRight().isHigherThan(outer.getTopRight())
		|| inner.getTopRight().isToTheRightOf(outer.getTopRight()))
	{	
		m_bottomLeft_outer = setBottomLeft_default();//reset
		m_topRight_outer = setTopRight_default();//reset
		m_bottomLeft_inner = setBottomLeft_default();// reset
		m_topRight_inner = setTopRight_default();// reset
	
		getVerticalThickness();// get the vertical thickness between
		getHorizontalThickness();//get the horizontal thickness between
		getHeight();// get height of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get perimeter of the rectangle
		getCenter(); //get center of the rectangles
	}
	else
	{// if Ok
		m_bottomLeft_outer = outer.getBottomLeft();// update member
		m_topRight_outer = outer.getTopRight();// update member
		m_bottomLeft_inner = inner.getBottomLeft();// update member
		m_topRight_inner = inner.getTopRight();// update member
		getVerticalThickness();// get the vertical thickness between
		getHorizontalThickness();//get the horizontal thickness between
		getHeight();// get height of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get perimeter of the rectangle
		getCenter();//get center of the rectangles
	}
}
//------------------------------------------------------
Window::Window(const Rectangle& outer, double verticalThickness,
            	double horizontalThickness)
{
	if (getVerticalThickness() > ( getHeight() / 2)
		|| getHorizontalThickness() > (getWidth() / 2))
	{
		m_bottomLeft_outer = setBottomLeft_default();
		m_topRight_outer = getTopRight();
		m_bottomLeft_inner = setBottomLeft_default();
		m_topRight_inner = getTopRight();
		getVerticalThickness();// get the vertical thickness between
		getHorizontalThickness();//get the horizontal thickness between
		getHeight();// get height of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get perimeter of the rectangle
		getCenter();//get center of the rectangles
	}
	else
	{
		m_bottomLeft_outer = outer.getBottomLeft();// update member
		m_topRight_outer = outer.getTopRight();// update member
		verticalThickness = getVerticalThickness();// get the vertical thickness between
		horizontalThickness = getHorizontalThickness(); //get the horizontal thickness between
		getHeight();// get height of the rectangle
		getArea();// get area of the rectangle
		getPerimeter();// get perimeter of the rectangle
		getCenter();//get center of the rectangles
	}
}
//---------------------------------------------------
Vertex Window::getBottomLeft() const
{ // get bottom left vertex
	return m_bottomLeft_outer;
}
//----------------------------------------------
Vertex Window::getTopRight() const
{// get top right vertex
	return m_topRight_inner;
}
//---------------------------------------------------
Vertex Window::setBottomLeft_default() const
{// set bottom left default
	Vertex bLeft;
	bLeft.m_col = 20;
	bLeft.m_row = 10;
	return bLeft;
}
//--------------------------------
Vertex Window::setTopRight_default() const
{   // set top right default
	Vertex topR;
	topR.m_col = 30;
	topR.m_row = 20;
	return topR;
}
//------------------------------------------------------
double Window::getVerticalThickness()const
{// get the vertical thickness between
	return (abs(m_bottomLeft_outer.m_row - m_bottomLeft_inner.m_row) *2);
}
//-------------------------------------------------------------
double Window::getHorizontalThickness()const
{//get the horizontal thickness between
	return (abs(m_topRight_outer.m_col - m_topRight_inner.m_col) *2);
}
//-----------------------------------------------------------------
double Window::getHeight()const // get height of the rectangle
{
	return (abs(m_topRight_outer.m_row - m_bottomLeft_outer.m_row));
}
//--------------------------------------------------------------------
double Window::getHeigh_inner()const // get height inner of the rectangle
{
	return (abs(m_topRight_inner.m_row - m_bottomLeft_inner.m_row));
}
//---------------------------------------------------------------
double Window::getWidth()const // get width outer
{
	return (abs(m_topRight_outer.m_col - m_bottomLeft_outer.m_col));
}
//----------------------------------------------------------
double Window::getWidth_inner()const // get width inner of the rectangle
{
	return (abs(m_topRight_inner.m_col - m_bottomLeft_inner.m_col));
}
//----------------------------------------------------------
double  Window::getArea() const // get area of the rectangle
{
	return (getHeight() * getWidth());
}
//------------------------------------------------------------
double Window::getPerimeter()const // get perimeter of the rectangle
{
	return ( 2 * (getHeight() + getWidth()));
}
//------------------------------------------------------------
Vertex Window::getCenter()const // get Center of the rectangle
{
	return (Vertex(m_bottomLeft_outer.m_col - (getWidth() / 2),
		m_bottomLeft_outer.m_row - (getHeight() / 2)));
}
//----------------------------------------------------------
Vertex Window::getCenter_inner()const//get center of inner the rectangle
{
	return (Vertex(m_bottomLeft_inner.m_col - (getWidth_inner() / 2),
		m_bottomLeft_inner.m_row - (getHeigh_inner() / 2)));
}
//--------------------------------------------------------
void Window::draw(Board& board) const// draw the rectangles
{
	Vertex bottomRight_out, topLeft_out,
		   bottomRight_in, topLeft_in;
	bottomRight_out.m_col = m_bottomLeft_outer.m_col + getWidth();
	bottomRight_in.m_col = m_bottomLeft_inner.m_col + getWidth_inner();

	bottomRight_out.m_row = m_bottomLeft_outer.m_row;
	bottomRight_in.m_row = m_bottomLeft_inner.m_row;

	topLeft_out.m_col = m_bottomLeft_outer.m_col;
	topLeft_in.m_col = m_bottomLeft_inner.m_col;

	topLeft_out.m_row = m_bottomLeft_outer.m_row + getHeight();
	topLeft_in.m_row = m_bottomLeft_inner.m_row + getHeigh_inner();

	board.drawLine(m_bottomLeft_outer, topLeft_out);
	board.drawLine(m_bottomLeft_inner, topLeft_in);

	board.drawLine(m_topRight_outer, bottomRight_out);
	board.drawLine(m_topRight_inner, bottomRight_in);

	board.drawLine(m_topRight_outer, topLeft_out);
	board.drawLine(m_topRight_inner, topLeft_in);

	board.drawLine(m_bottomLeft_outer, bottomRight_out);
	board.drawLine(m_bottomLeft_inner, bottomRight_in);
}
//----------------------------------------------------------
Rectangle Window::getBoundingRectangle()const
{// return bounded rectangles
	return Rectangle(m_bottomLeft_outer, m_topRight_outer);
}
//------------------------------------------------
bool Window::scale(double factor)
{ // scaling retangles * factor
	if (factor < 0)
		return false;
	Vertex bLeft_out, tRight_out,
		   bLeft_in, tRight_in ;
	Vertex center = getCenter();
	bLeft_out.m_col = (m_bottomLeft_outer.m_col - center.m_col) * factor 
		               + m_bottomLeft_outer.m_col;
	bLeft_in.m_col = (m_bottomLeft_inner.m_col - center.m_col) * factor
	                	+ m_bottomLeft_inner.m_col;

	bLeft_out.m_row = (m_bottomLeft_outer.m_row - center.m_row) * factor 
		               + m_bottomLeft_outer.m_row;
	bLeft_in.m_row = (m_bottomLeft_inner.m_row - center.m_row) * factor
	                	+ m_bottomLeft_inner.m_row;

	tRight_out.m_col = (m_topRight_outer.m_col - center.m_col) * factor
		                + m_topRight_outer.m_col;
	tRight_in.m_col = (m_topRight_inner.m_col - center.m_col) * factor
	                	+ m_topRight_inner.m_col;

	tRight_out.m_row = (m_topRight_outer.m_row - center.m_row) * factor 
		                 + m_topRight_outer.m_row;
	tRight_in.m_row = (m_topRight_inner.m_row - center.m_row) * factor
	             	    + m_topRight_inner.m_row;

	if ((!bLeft_out.isValid() || !tRight_out.isValid())
		|| (!bLeft_in.isValid() || !tRight_in.isValid()))
		return false;

	m_bottomLeft_outer = bLeft_out;
	m_bottomLeft_inner = bLeft_in;
	m_topRight_outer = tRight_out;
	m_topRight_inner = tRight_in;
	return true;
}

