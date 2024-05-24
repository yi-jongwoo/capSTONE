#include <bits/stdc++.h>
using namespace std;

#include "stone_yame.h"

vector<int> arr[1000];

int main(){
	arr[0].push_back(1);
	arr[1].push_back(2);
	arr[2].push_back(3);
	arr[3].push_back(4);
	arr[4].push_back(5);
	arr[3].push_back(6);
	
	arr[7].push_back(8);
	arr[7].push_back(9);
	arr[9].push_back(10);
	arr[9].push_back(11);
	arr[9].push_back(12);
	arr[8].push_back(13);
	arr[8].push_back(10);
	arr[8].push_back(14);
	
	graph_visualization(15,arr,"out.html",814,814);
}