// A1_Paper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

typedef struct papertag {
	float area;
	float l;
	float w;
	int c;
}paper;


int main()
{
	int n(0);
	std::string strline;
	std::size_t t(0), pos(0);
	std::cin >> n;
	paper p;
	float WIDTH_A_2(0.0), LEN_A_2(0.0), EXP(0.0), BASE(0.0), tape_len(0.0);
	EXP = 1.25f;
	BASE = 2.0F;
	//init a vector of papers.
	std::vector<papertag> sheets;
	std::vector<int> res;

	//init paper structure
	::memset(&p, 0, sizeof(paper));
	//calculate width and length of A2 paper as base size to measure A3, A4, .... PAPER SIZES
	//ALL THE CALCULATIONS ARE IN FLOAT!
	WIDTH_A_2 = pow(BASE, EXP);
	WIDTH_A_2 = 1 / WIDTH_A_2;
	
	//ALL THE CALCULATIONS ARE IN FLOAT
	EXP = 0.75f;
	LEN_A_2 = pow(BASE, EXP);
	LEN_A_2 = 1 / LEN_A_2;

	//construct and init an A1-SIZE paper; we need to calculate its area to compare with the area of smaller
	//size of papers like A2_SIZE AND ... then when we reach to a point that we made an A1_SIZE paper we
	//are done!
	paper P_A_1; ::memset(&P_A_1, 0, sizeof(paper));
	//this is originated from algorithm of this program
	P_A_1.area = 0.0; P_A_1.l = 2 * WIDTH_A_2; P_A_1.w = LEN_A_2;
	//calculate area of the A1_SIZE paper
	P_A_1.area = P_A_1.l * P_A_1.w;

	printf("WIDTH_A_ONE: %f\n", WIDTH_A_2);
	printf("LEN_A_ONE: %f\n", LEN_A_2);
	//rest cin \n character from input buffer so getline to work
	std::cin.ignore();
	std::getline(std::cin, strline);
	t = strline.find_first_of(' ');

	do {
		p.c = std::atoi( strline.substr(pos, t-pos).c_str());
		sheets.push_back(p);
		pos = t;
		t = strline.find_first_of(' ', t+1);
	} while (t != std::string::npos);
	p.c = std::atoi(strline.substr(pos, t+1 - pos).c_str());
	sheets.push_back(p);

	sheets[0].l = LEN_A_2; sheets[0].w = WIDTH_A_2; 
	//calculate area for A2_SIZE papare
	sheets[0].area = sheets[0].l * sheets[0].w;

	for(std::size_t i = 0; i <sheets.size()-1; i++){
		sheets[i + 1].l = sheets[i].w; //length of A3 is equal to width of A2
		sheets[i + 1].w = sheets[i].l / 2; // width of A3 is equal to 1/2 length of A2
		//calculate the area of this type of paper
		sheets[i + 1].area = sheets[i + 1].l * sheets[i + 1].w;
	}

	/*
						calculate the least amount of tape needed to join all 
						the smaller papers of sizes(A2-A4) to make an A1 paper.
	*/
	int c(0), c1(0);
	float tot_area(0.0);

	for (std::size_t i = 0; i < sheets.size(); i++) {
		tot_area += sheets[i].area * sheets[i].c;
		if ( tot_area < P_A_1.area ) {
			res.push_back(sheets[i].c);
		}
		else {//seems that at this stage we are almost done lets caculate the tape_len
			float a(0.0);
			c1 = sheets[i].c;
			//subtract the extra area, we should add area gradually
			tot_area -= sheets[i].area * sheets[i].c;
			do {
				tot_area += sheets[i].area;
				//add the long side of paper to tape_len
				c++; if (c % 2 == 0) a += 0.5;
			} while (tot_area != P_A_1.area); //check whether we made a A1_SIZE paper?
			
			//add the count of paapers to the res vector.
			res.push_back(c / 2); res[i - 1] = a;
		}
	}
	 //calculate the least amount of tape used to join the papers together to make an A1-SIZE paper.
	for (std::size_t i = 0; i < res.size(); i++)
		tape_len += res[i] * sheets[i].l;
	
	printf("%f\n", tape_len);

    return 0;
}

