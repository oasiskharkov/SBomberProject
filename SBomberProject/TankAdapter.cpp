#include "TankAdapter.h"

bool TankAdapter::isInside(double x1, double x2) const
{
   return adaptee.isInRange(x1, x2);
}

uint16_t TankAdapter::GetScore() const
{
   return adaptee.GetScore();
}

void TankAdapter::Draw() const
{
   adaptee.Paint();
}

void TankAdapter::SetPos(double nx, double ny)
{
   adaptee.SetPos(nx, ny);
}

double TankAdapter::GetY() const
{
   return adaptee.GetY();
}

double TankAdapter::GetX() const
{
   return adaptee.GetX();
}

void TankAdapter::SetWidth(uint16_t width)
{
   adaptee.SetWidth(width);
}

uint16_t TankAdapter::GetWidth() const
{
   return adaptee.GetWidth();
}

std::shared_ptr<DestroyableGroundObject> TankAdapter::Clone() const
{
   return nullptr;
}
