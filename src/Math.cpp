#include "Math.h"

float Math::toDegree(float radian)
{
	return radian*(180/pi());
}

float Math::toRadian(float degree)
{
	return degree*(pi()/180);
}

float Math::pi()
{
	return 4.0*atan(1.0);
}

pair<float, float> Math::toSlopeIntercept(sf::Vector2f direction, sf::Vector2f origin)
{
	//y=mx+b
	float m=direction.x/direction.y;
	float b=origin.y-m*origin.x;
	return pair<float, float>(m, b);
}

float Math::length(sf::Vector2f vector)
{
	return sqrt(vector.x*vector.x+vector.y*vector.y);
}

sf::Vector2f Math::normalize(sf::Vector2f vector)
{
	float divisor=length(vector);
	vector.x/=divisor;
	vector.y/=divisor;
	return vector;
}

float Math::dot(sf::Vector2f first, sf::Vector2f second)
{
	return first.x*second.x+first.y*second.y;
}

float Math::angle(sf::Vector2f first, sf::Vector2f second)
{
	return toDegree(acos(dot(first, second)));
}

sf::Vector2f Math::rotate(sf::Vector2f vector, float angle)
{
	angle=toRadian(angle);
	sf::Vector2f res;
	res.x=vector.x*cos(angle)+vector.y*-sin(angle);
	res.y=vector.x*sin(angle)+vector.y*cos(angle);
	return res;
}

sf::Vector2f Math::orthogonal(sf::Vector2f vector)
{
	sf::Vector2f res;
	if(vector.x==0 && vector.y==0)
	{
		
	}
	else
	{
		res.x=-vector.y;
		res.y=vector.x;
	}
	/*else if(vector.x==0)
	{
		res.y=1;
	}
	else if(vector.y==0)
	{
		res.x=1;
	}
	else
	{
		res.x=1;
		res.y=vector.x/-vector.y;
		res=normalize(res);
	}*/
	return res;
}

sf::Vector2f Math::reflect(sf::Vector2f first, sf::Vector2f second)
{
	//Not useful in case both first and second are parallel
	sf::Vector2f normal=orthogonal(second);
	//cout << second.x << " " << second.y << " " << normal.x << " " << normal.y << endl;
	sf::Vector2f res=(first-2*(dot(first, normal))*normal);
	//cout << first.x << " " << first.y << " " << second.x << " " << second.y << " " << res.x << " " << res.y << endl;
	return res;
}

bool Math::lineOverlapsRect(pair<sf::Vector2f, sf::Vector2f> line, sf::FloatRect rect, sf::Vector2f &intersectionPoint)
{
	pair<sf::Vector2f, sf::Vector2f> edge;
	pair<float, float> t;

	//Redundance
	//Test with top edge
	edge.first.x=rect.left;
	edge.first.y=rect.top;
	edge.second.x=rect.left+rect.width;
	edge.second.y=rect.top;
	
	t=lineIntersection(line, edge, true);

	if(tCheck(t))
	{
		return true;
	}
	//cout << "Top edge " << t.first << " " << t.second << endl;
	
	//Test with bottom edge
	edge.first.x=rect.left;
	edge.first.y=rect.top+rect.height;
	edge.second.x=rect.left+rect.width;
	edge.second.y=rect.top+rect.height;
	
	t=lineIntersection(line, edge, true);
	
	if(tCheck(t))
	{
		return true;
	}
	//cout << "Bottom edge " << t.first << " " << t.second << endl;
	
	//Test with left edge
	edge.first.x=rect.left;
	edge.first.y=rect.top;
	edge.second.x=rect.left;
	edge.second.y=rect.top+rect.height;
	
	t=lineIntersection(line, edge, false);
	
	if(tCheck(t))
	{
		return true;
	}
	//cout << "Left edge " << t.first << " " << t.second << endl;
	
	//Test with right edge
	edge.first.x=rect.left+rect.width;
	edge.first.y=rect.top;
	edge.second.x=rect.left+rect.width;
	edge.second.y=rect.top+rect.height;
	
	t=lineIntersection(line, edge, false);
	
	if(tCheck(t))
	{
		return true;
	}
	
	return false;
	//cout << "Right edge " << t.first << " " << t.second << endl;
}

pair<float, float> Math::lineIntersection(pair<sf::Vector2f, sf::Vector2f> line, pair<sf::Vector2f, sf::Vector2f> edge, bool horizontal)
{
	//Implementation of (1-tLine)*lineStart+tLine*lineEnd=(1-tEdge)*edgeStart+tEdge*edgeEnd
	pair<float, float> t;
	if(horizontal)
	{
		t.first=(edge.first.y-line.first.y)/(line.second.y-line.first.y);
		t.second=(line.first.x-edge.first.x+t.first*(line.second.x-line.first.x))/(edge.second.x-edge.first.x);
	}
	else
	{
		t.first=(edge.first.x-line.first.x)/(line.second.x-line.first.x);
		t.second=(line.first.y-edge.first.y+t.first*(line.second.y-line.first.y))/(edge.second.y-edge.first.y);
	}
	return t;
}

bool Math::tCheck(pair<float, float> t)
{
	return (t.first>=0 && t.first<=1 && t.second>=0 && t.second<=1);
}

sf::Vector2f Math::slopeInterceptIntersection(pair<float, float> first, pair<float, float> second)
{
	sf::Vector2f res;
	res.x=(second.second-first.second)/(first.first-second.first);
	res.y=first.first*res.x+first.second;
	return res;
}