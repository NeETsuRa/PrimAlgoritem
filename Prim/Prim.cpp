// Prim.cpp : Defines the entry point for the console application.

/* Napišite program, ki poišèe minimalno vpeto drevo po Primovem postopku. V programu
   omogoèite, da boste lahko graf prebrali tudi iz datoteke. */

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CGraf
{
public:
	CGraf(int N);
	~CGraf(void);
	CGraf* Izpis(char* ime);
	void DodajPovezavo(int aI, int aJ, int aU);
	int OdstraniPovezavo(int aI, int aJ);
	bool JePovezava(int aI, int aJ);
	int VrniUtez(int aI, int aJ);
	vector<int> VrniSeznamSosedov(int aI);
	void IzpisMatrike();
	int Min1(int &aJ, int* aP);
	int Min(int &aJ);
	int Max(int &aJ);
	CGraf* MinVpetoDrevo();
	void IzpisPolja(int* aP);
	bool Polno(int* aP);
	bool JeVGrafu(int aI, int* aP);

	int stPovezav;
	int** graf;
};


CGraf::CGraf(int N)
{
	stPovezav = N;
	graf = new int*[stPovezav];
	for(int k = 0; k< stPovezav; k++){
		graf[k]= new int [stPovezav];
	}

	for (int i = 0; i <stPovezav; i++){
		for(int j = 0; j< stPovezav; j++){
			graf[i][j]= -1;
		}
	}
}

CGraf::~CGraf(void)
{
}

void CGraf::DodajPovezavo(int aI, int aJ, int aU)
{
	graf[aI][aJ] = aU;
	graf[aJ][aI] = aU;
}

int CGraf::OdstraniPovezavo(int aI, int aJ)
{
	int aU = graf[aI][aJ];
		graf[aI][aJ] = -1;
		graf[aJ][aI] = -1;
		return aU;
}

bool CGraf::JePovezava(int aI, int aJ)
{
	if(graf[aI][aJ] != -1)
		return true;
	else 
		return false;
}

int CGraf::VrniUtez(int aI, int aJ)
{
	if(graf[aI][aJ] != -1)
		return graf[aI][aJ];
	else
		return -1;
}

vector<int> CGraf:: VrniSeznamSosedov(int aI)
{
	vector<int> Sez;
	for(int i = 0; i< stPovezav; i++){
		if(graf[aI][i] != -1){
			Sez.push_back(i);
		}
	}
	return Sez;
}

void CGraf:: IzpisMatrike()
{
	cout << "(Utezena) matrika sosednosti: "<< endl;
	for(int i = 0; i< stPovezav; i++){
		for(int j = 0; j< stPovezav; j++){
			cout << graf[i][j] << "     ";
		}
		cout << endl;
	}
}

int CGraf:: Max(int &aJ)
{
	int aI = -1;
	int aM = VrniUtez(0,0);
	for(int i = 0; i< stPovezav; i++){
		for(int j = i+1; j < stPovezav; j++){
			if(aM < VrniUtez(i,j)){
				aM = VrniUtez(i,j);
				aI = i;
				aJ = j;
			}
		}
	}
	return aI;
}

int CGraf:: Min1(int &aJ, int* aP)
{
	int aK = Max(aJ);
	int aI = aK;
	int aMin = VrniUtez(aK, aJ);
	for(int i = 0; i< stPovezav; i++){
		for(int j = i+1; j <stPovezav; j++){
			if(JePovezava(i,j)&& aMin > VrniUtez(i,j)&&((JeVGrafu(i,aP) && !JeVGrafu(j,aP))|| (JeVGrafu(j,aP)) && !JeVGrafu(i,aP))){
				aI = i;
				aJ = j;
				aMin = VrniUtez(i,j);
			}
		}
	}
	return aI;
}

int CGraf:: Min(int &aJ)
{
	int aK = Max(aJ);
	int aI = aK;
	int aMin = VrniUtez(aK, aJ);
	for(int i = 0; i< stPovezav; i++){
		for(int j = i+1; j <stPovezav; j++){
			if(JePovezava(i,j)&& aMin > VrniUtez(i,j)){
				aI = i;
				aJ = j;
				aMin = VrniUtez(i,j);
			}
		}
	}
	return aI;
}

CGraf* CGraf:: MinVpetoDrevo()
{
	CGraf* aS = new CGraf(stPovezav);
	int* aP = new int[stPovezav];
	for(int i = 0; i< stPovezav; i++){
		aP[i] = -1;
	}
	int aR = -1;
	int aT = Min(aR);
	aP[aT] = 1;
	aP[aR] = 1;
	aS->DodajPovezavo(aR,aT, VrniUtez(aR,aT));
	int aU = OdstraniPovezavo(aR,aT);	
	cout <<"Dodam utez "<< aU <<endl;
	while(!Polno(aP)){
			int aR = -1;
			int aT = Min1(aR,aP); 
				aS->DodajPovezavo(aR,aT, VrniUtez(aR,aT));
				aU = OdstraniPovezavo(aR,aT);
				cout <<"Dodam utez "<< aU <<endl;
				aP[aT] = 1;
				aP[aR] = 1;
	}
	return aS;
}

bool CGraf::Polno(int* aP)
{
	for(int i = 0; i< stPovezav; i++){
		if(aP[i] != 1){
			return false;
		}
	}
	return true;
}

void CGraf:: IzpisPolja(int* aP)
{
	for(int i = 0; i< stPovezav; i++){
		cout << aP[i]<<" ";
	}
	cout << endl;
}

bool CGraf:: JeVGrafu(int aI, int* aP)
{
	if(aP[aI] == 1){
		return true;
	}else{
		return false;
	}
}

CGraf* Preberi(char* ime){
 ifstream dat(ime);
 if (dat.is_open()){
	 int aN;
	 dat>>aN;
	 CGraf * aG = new CGraf(aN);	
	if(dat.good()){
		while(!dat.eof()){
			int x;
			int y; 
			int z;
			dat>>x>>y>>z;
			aG->DodajPovezavo(x,y,z);
		}
	}
		dat.close();
		return aG;
 }
 else{	
	 cout<<"Napaka pri odpiranju datoteke!";
	 return NULL;
 }
}

int _tmain(int argc, _TCHAR* argv[])
{
	int aR = 0;
	CGraf* aS = Preberi("K.txt");
	aS->IzpisMatrike();
	CGraf* aT = aS->MinVpetoDrevo();
	aT->IzpisMatrike();

	cin.ignore();
	cin.get();
	return 0;
}

