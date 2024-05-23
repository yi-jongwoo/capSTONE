#ifndef STONE_INTERNAL_H
#define STONE_INTERNAL_H

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

#define NOTHING -1
#define IMPOSSIBLE -2

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

#endif