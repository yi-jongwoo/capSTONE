#include "graph_visualization.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::string;
using std::ofstream;
using std::vector;

void make_svg_undirected(string filename,int w,int h,int n,vector<int>* arr,int* x,int* y){
	ofstream fout(filename);
	fout<<"<html><body>\n";
	
	fout<<"<svg width=\""<<w<<"\" height=\""<<h<<"\">\n";
	
	for(int i=0;i<n;i++)for(int j:arr[i])
		fout<<"<line x1=\""<<x[i]<<"\" y1=\""<<y[i]
			<<"\" x2=\""<<x[j]<<"\" y2=\""<<y[j]
			<<"\" style=\"stroke:red;stroke-width:2\" />\n";
	
	for(int i=0;i<n;i++)
		fout<<"<circle cx=\""<<x[i]<<"\" cy=\""<<y[i]
			<<"\" r=\"4\" fill=\"blue\" />\n";
	for(int i=0;i<n;i++)
		fout<<"<text x=\""<<x[i]+2<<"\" y=\""<<y[i]
			<<"\" fill=\"black\">"<<i<<"</text>\n";
	fout<<"</svg></body></html>";
}
void make_svg(string filename,int w,int h,int n,vector<int>* arr,int* x,int* y){
	ofstream fout(filename);
	fout<<"<html><body>\n";
	
	fout<<"<svg width=\""<<w<<"\" height=\""<<h<<"\">\n";
	
	fout<<"<defs><marker id='head' orient=\"auto\"markerWidth='3' markerHeight='4'\
refX='0.1' refY='2'><path d='M0,0 V4 L2,2 Z' fill=\"black\"/></marker></defs>\n";

	for(int i=0;i<n;i++)for(int j:arr[i])
		fout<<"<path id='arrow-line' marker-end='url(#head)' stroke-width='4' \
fill='none' stroke='black' d='M"<<x[i]<<","<<y[i]<<", "<<x[j]<<" "<<y[j]<<",120'/>\n";
	for(int i=0;i<n;i++)
		fout<<"<circle cx=\""<<x[i]<<"\" cy=\""<<y[i]
			<<"\" r=\"4\" fill=\"blue\" />\n";
	for(int i=0;i<n;i++)
		fout<<"<text x=\""<<x[i]+2<<"\" y=\""<<y[i]
			<<"\" fill=\"black\">"<<i<<"</text>\n";
	fout<<"</svg></body></html>";
}
