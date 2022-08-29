#pragma once

#include "structure/ExpansionPosition.h"

/**
 * Interface-marker for expanded DSCs.
 *
 * @author AlexeyVorobyev
 */
class PossibleExpansion
{
public:

	PossibleExpansion()
	{

	}

	~PossibleExpansion()
	{

	}

	ExpansionPosition getExpansion()
	{
		return exp;
	}

protected:

	ExpansionPosition exp;
};