// A1_Paper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

typedef struct papertag {
	float l;
	float w;
	int c;
};


int main()
{
	int n(0);
	
	std::cin >> n;
	//init a vector of papers.
	std::vector<papertag> sheets;
	
	for(int i = 0; i < n; i++){}
    return 0;
}

