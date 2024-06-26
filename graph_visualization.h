#ifndef GRAPH_VISUALIZATION_H
#define GRAPH_VISUALIZATION_H

#include <vector>
#include <string>

void graph_visualization(int n,std::vector<int>* arr,std::string filename,int w,int h);
void weighted_graph_visualization(int n,std::vector<std::pair<int,int>>* arr,std::string filename,int w,int h);

#endif
