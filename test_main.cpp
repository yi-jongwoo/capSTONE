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
	graph_visualization(6,arr,"out.html",814,814);
}