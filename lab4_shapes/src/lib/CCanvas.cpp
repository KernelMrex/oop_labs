#include "CCanvas.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

static sf::Color MapColor(uint32_t color);

CCanvas::CCanvas(sf::RenderWindow& window)
	: m_window(window)
{
}

void CCanvas::DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor)
{
	auto color = MapColor(lineColor);

	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(from.x, from.y), color),
		sf::Vertex(sf::Vector2f(to.x, to.y), color)
	};

	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::DrawPolygon(const std::vector<CPoint>& points, uint32_t lineColor)
{
	sf::ConvexShape convex;

	convex.setFillColor(sf::Color::Transparent);
	convex.setOutlineThickness(1);
	convex.setOutlineColor(MapColor(lineColor));

	convex.setPointCount(points.size());
	for (int i = 0; i < points.size(); i++)
	{
		convex.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}

	m_window.draw(convex);
}

void CCanvas::FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor)
{
	sf::ConvexShape convex;

	convex.setFillColor(MapColor(fillColor));
	convex.setOutlineThickness(1);
	convex.setOutlineColor(sf::Color::Transparent);

	convex.setPointCount(points.size());
	for (int i = 0; i < points.size(); i++)
	{
		convex.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}

	m_window.draw(convex);
}

void CCanvas::DrawCircle(const CPoint& center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle;
	circle.setRadius(radius - 1);
	circle.setPosition(sf::Vector2f(center.x - radius, center.y - radius));
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(MapColor(lineColor));
	circle.setOutlineThickness(1);
	m_window.draw(circle);
}

void CCanvas::FillCircle(const CPoint& center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle(64);
	circle.setRadius(radius - 1);
	circle.setPosition(sf::Vector2f(center.x - radius, center.y - radius));
	circle.setFillColor(MapColor(fillColor));
	circle.setOutlineColor(sf::Color::Transparent);
	m_window.draw(circle);
}

static sf::Color MapColor(uint32_t color)
{
	return {
		static_cast<sf::Uint8>((color & 0xff0000) >> (2 * 8)),
		static_cast<sf::Uint8>((color & 0x00ff00) >> (1 * 8)),
		static_cast<sf::Uint8>(color & 0x0000ff)
	};
}
