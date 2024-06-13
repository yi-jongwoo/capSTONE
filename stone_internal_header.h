#ifndef STONE_INTERNAL_H
#define STONE_INTERNAL_H

#include <vector>
#include <utility>
#include <string>
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/ref.hpp>

#include <boost/graph/make_biconnected_planar.hpp>
#include <boost/graph/make_maximal_planar.hpp>
#include <boost/graph/planar_face_traversal.hpp>

#include <boost/graph/planar_canonical_ordering.hpp>
#include <boost/graph/is_straight_line_drawing.hpp>
#include <boost/graph/chrobak_payne_drawing.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

#define NOTHING -1
#define IMPOSSIBLE -2
#define weight first
#define link second

//impl in stone_utility.cpp
bool is_cross(ll a,ll b,ll c,ll d,ll e,ll f,ll g,ll h);
ll cactus_objective(int n,vector<pair<int,int>>&edges,
  int* x,int* y,int u,vector<pair<int,int>>& adj);
ll planar_objective(int n,vector<pair<int,int>>&edges,
  int* x,int* y,int u,vector<pair<int,int>>& adj);
ll general_objective(int n,vector<pair<int,int>>&edges,
  int* x,int* y,int u,vector<pair<int,int>>& adj);

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

//impl in weighted_optimize.cpp
void weighted_embad_cactus(int n,vector<int>* grr,int w,int h,int* x,int* y);
void weighted_embad_planar(int n,vector<int>* grr,int w,int h,int* x,int* y);
void weighted_embad_general(int n,vector<int>* grr,int w,int h,int* x,int* y);

//impl in weighted_visualization.cpp
void weighted_make_svg_undirected(string filename,int w,int h,int n,vector<pair<int,int>>* arr,int* x,int* y);
void weighted_make_svg(string filename,int w,int h,int n,vector<pair<int,int>>* arr,int* x,int* y);

struct coord_t
{
  std::size_t x;
  std::size_t y;
};
struct face_counter : public boost::planar_face_traversal_visitor
{
  face_counter() : count(0) {}
  void begin_face() { ++count; }
  int count;
};

#endif
