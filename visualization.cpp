#include "stone_internal_header.h"

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
    
    fout<<"<defs><marker id='head' orient=\"auto\"markerWidth='1.5' markerHeight='6'\
refX='3' refY='2' viewBox=\"0 0 2 1\"><path d='M0,0 V4 L2,2 Z' fill=\"black\"/></marker></defs>\n";

    for(int i=0;i<n;i++)
        for(int j:arr[i])
            fout<<"<path id='arrow-line' marker-end='url(#head)' stroke-width='4' \
fill='none' stroke='#404040' d='M"<<x[i]<<","<<y[i]<<", "<<x[j]<<" "<<y[j]<<",120'/>\n";
    for(int i=0;i<n;i++)
        fout<<"<circle cx=\""<<x[i]<<"\" cy=\""<<y[i]
            <<"\" r=\"4\" fill=\"blue\" />\n";
    for(int i=0;i<n;i++)
        fout<<"<text x=\""<<x[i]+2<<"\" y=\""<<y[i]
            <<"\" fill=\"red\" font-weight=\"bold\">"<<i<<"</text>\n";
    fout<<"</svg></body></html>";
}
