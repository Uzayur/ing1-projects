#pragma once

class LegacyRectangle
{
public:
    LegacyRectangle(int x1, int y1, int x2, int y2);
    unsigned compute_area() const;
    int x1_get() const;
    int x2_get() const;
    int y1_get() const;
    int y2_get() const;

private:
    int x1_;
    int y1_;
    int x2_;
    int y2_;
};
