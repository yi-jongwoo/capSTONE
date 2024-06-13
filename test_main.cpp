#include <bits/stdc++.h>
using namespace std;

#include "stone_yame.h"

vector<pair<int,int>> arr[1000];

int main(){
	for(int i=0;i<20;i++)
		for(int j=0;j<5;j++)
			arr[j+5*i].emplace_back(rand()%200,(j+1)%5+5*i);
	for(int i=0;i<4;i++)
		for(int j=0;j<5;j++)
			arr[5*j+25*i].emplace_back(rand()%200,(j+1)%5*5+25*i);
	arr[0].emplace_back(rand()%200,25);
	arr[0].emplace_back(rand()%200,50);
	arr[0].emplace_back(rand()%200,75);
	arr[50].emplace_back(rand()%200,75);
	weighted_graph_visualization(100,arr,"out.html",1000,1000);
}
