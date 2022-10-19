#pragma once
class Counter
{
	const unsigned int ownedBy;
	const unsigned int id;

public:
	
	Counter(unsigned int ownedBy,unsigned int id):
		ownedBy(ownedBy),
		id(id)
	{}
	unsigned int getId() { return id; }
};

