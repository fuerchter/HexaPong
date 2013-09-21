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
	float dotResult=dot(first, second);
	if(dotResult>1.0)
	{
		dotResult=1.0;
	}
	if(dotResult<-1.0)
	{
		dotResult=-1.0;
	}
	return toDegree(acos(dotResult));
	//return toDegree(acos(dot(first, second)));
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

pair<float, float> Math::segmentDistances(pair<sf::Vector2f, sf::Vector2f> segment)
{
	return pair<float, float>(segment.first.x-segment.second.x, segment.first.y-segment.second.y);
}

float Math::segmentAngle(pair<sf::Vector2f, sf::Vector2f> first, pair<sf::Vector2f, sf::Vector2f> second)
{
	pair<float, float> firstDistances=segmentDistances(first);
	pair<float, float> secondDistances=segmentDistances(second);
	//absolute value?
	return firstDistances.first*secondDistances.second-firstDistances.second*secondDistances.first;
}

sf::Vector2f Math::segmentIntersection(pair<sf::Vector2f, sf::Vector2f> first, pair<sf::Vector2f, sf::Vector2f> second, float segmentAngle)
{
	sf::Vector2f res;
	
	//float denom=firstXDistance*secondYDistance-firstYDistance*secondXDistance;
	
	//redundance due to vector elements not accessible via [] operator
	float firstLeftDet=first.first.x*first.second.y-first.first.y*first.second.x;
	float secondLeftDet=second.first.x*second.second.y-second.first.y*second.second.x;
	
	pair<float, float> firstDistances=segmentDistances(first);
	pair<float, float> secondDistances=segmentDistances(second);
	
	if(segmentAngle!=0)
	{
		res.x=(firstLeftDet*secondDistances.first-secondLeftDet*firstDistances.first)/segmentAngle;
		res.y=(firstLeftDet*secondDistances.second-secondLeftDet*firstDistances.second)/segmentAngle;
	}
	//Test: is res on BOTH of the lines?
	return res;
}

bool Math::isPointOnSegment(sf::Vector2f point, pair<sf::Vector2f, sf::Vector2f> segment)
{
	//the segment is 90°
	if(segment.first.x==segment.second.x || segment.first.y==segment.second.y)
	{
		if(point==segment.first)
		{
			return true;
		}
		
		sf::Vector2f vector=segment.second-segment.first;
		float length=Math::length(vector);
		vector=Math::normalize(vector);
		
		sf::Vector2f firstToPoint=point-segment.first;
		float pointLength=Math::length(firstToPoint);
		firstToPoint=Math::normalize(firstToPoint);
		cout << "Lengths: " << pointLength << "<=" << length << " " << (pointLength<=length) << " Angle: " << Math::angle(firstToPoint, vector) << endl; 
		cout << "vector: " << vector.x << " " << vector.y << " firstToPoint: " << firstToPoint.x << " " << firstToPoint.y << endl;
		
		return pointLength<=length && Math::angle(firstToPoint, vector)==0;
	}
	else
	{
		return newTCheck(pair<float, float>(computeT(segment.first.x, segment.second.x, point.x), computeT(segment.first.y, segment.second.y, point.y)));
	}
}

float Math::computeT(float first, float second, float coordinate)
{
	float num=coordinate-first;
	float denom=second-first;
	float t=num/denom;
	cout.precision(10);
	cout << num << "/" << denom << "=" << t << endl;
	return t;
}

bool Math::newTCheck(pair<float, float> t)
{
	return t.first==t.second && t.first>=0 && t.first<=1;
}