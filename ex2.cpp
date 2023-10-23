#include <iostream>

int main ( )
{
	int a = 5, b = 7, c = 9;
	int *p1, *p2;
	p1 = &a;
	p2 = &c;
	std::cout << a << " " << b << " " << c << std::endl;
	*p1 = ( *p2 )++;
	std::cout << a << " " << b << " " << c << std::endl;
	p1 = p2;
	p2 = &b;
	*p1 -= *p2;
	std::cout << a << " " << b << " " << c << std::endl;
	++( *p2 );
	std::cout << a << " " << b << " " << c << std::endl;
	*p1 *= *p2;
	std::cout << a << " " << b << " " << c << std::endl;
	a = ( ++( *p2 ) ) * *p1;
	std::cout << a << " " << b << " " << c << std::endl;
	p1 = &a;
	std::cout << a << " " << b << " " << c << std::endl;
	*p2 = *p1 /= *p2 ;
	std::cout << a << " " << b << " " << c << std::endl;
	return 0;
}
