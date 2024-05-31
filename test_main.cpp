#include <bits/stdc++.h>
using namespace std;

#include "stone_yame.h"

vector<int> arr[1000];

int main(){
	for(int i=0;i<20;i++)
		for(int j=0;j<5;j++)
			arr[j+5*i].push_back((j+1)%5+5*i);
	for(int i=0;i<4;i++)
		for(int j=0;j<5;j++)
			arr[5*j+25*i].push_back((j+1)%5*5+25*i);
	arr[0].push_back(25);
	arr[0].push_back(50);
	arr[0].push_back(75);
	arr[50].push_back(75);
	graph_visualization(100,arr,"out.html",814,814);
}