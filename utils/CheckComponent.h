#include <typeinfo>

template<class T, class Cast>
bool isComponentCastable(T component)
{
	try
	{
		dynamic_cast<Cast>(component);
	}
	catch (std::bad_cast)
	{
		return false;
	}
	return true;
}