#ifndef CCANVAS_H
#define CCANVAS_H

#include "ICanvas.h"
#include <SFML/Graphics/RenderWindow.hpp>

class CCanvas : public ICanvas
{
public:
	explicit CCanvas(sf::RenderWindow& window);

	void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor) final;

	void DrawPolygon(const std::vector<CPoint>& points, uint32_t lineColor) final;

	void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) final;

	void DrawCircle(const CPoint& center, double radius, uint32_t lineColor) final;

	void FillCircle(const CPoint& center, double radius, uint32_t fillColor) final;

private:
	sf::RenderWindow& m_window;
};

#endif // CCANVAS_H
