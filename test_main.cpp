

#include "stone_yame.h"

#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int>> arr[1000];

int main(){
	for(int i=1;i<20;i++){
		arr[i].emplace_back(rand()%200,rand()%i);
	}
	weighted_graph_visualization(20,arr,"out.html",1000,1000);
}
