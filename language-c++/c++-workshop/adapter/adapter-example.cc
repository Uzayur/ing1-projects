#include "adapt-legacy-rectangle.hh"
#include "legacy-rectangle.hh"

int main()
{
    LegacyRectangle adaptee = LegacyRectangle(5, 2, 8, 6);
    AdaptLegacyRectangle adapter = AdaptLegacyRectangle(adaptee);
    adapter.print();
}
