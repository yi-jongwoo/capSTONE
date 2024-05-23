#include <bits/stdc++.h>
using namespace std;
#include "../boost_1_82_0/boost/graph/adjacency_list.hpp"
#include "../boost_1_82_0/boost/graph/boyer_myrvold_planar_test.hpp"

//impl in test_graph.cpp
bool is_tree(int n,vector<int>* arr);
bool is_cactus(int n,vector<int>* arr);
bool is_planar(int n,vector<int>* arr);

//impl in optimize.cpp
void embad_tree(int n,vector<int>* grr,int w,int h,int* x,int* y);
void embad_cactus(int n,vector<int>* grr,int w,int h,int* x,int* y);
void embad_planar(int n,vector<int>* grr,int w,int h,int* x,int* y);
void embad_general(int n,vector<int>* grr,int w,int h,int* x,int* y);

//impl in visualization.cpp
void make_svg_undirected(string filename,int w,int h,int n,vector<int>* arr,int* x,int* y);
void make_svg(string filename,int w,int h,int n,vector<int>* arr,int* x,int* y);
