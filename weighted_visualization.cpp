#include "stone_internal_header.h"

void weighted_make_svg_undirected(string filename,int w,int h,int n,vector<pair<int,int>>* arr,int* x,int* y){
    ofstream fout(filename);
    fout<<"<html><body>\n";
    fout<<"<svg width=\""<<w<<"\" height=\""<<h<<"\">\n";
    
    for(int i=0;i<n;i++)for(pair<int,int> p:arr[i]){
        int j=p.second;
        fout<<"<line x1=\""<<x[i]<<"\" y1=\""<<y[i]
            <<"\" x2=\""<<x[j]<<"\" y2=\""<<y[j]
            <<"\" style=\"stroke:red;stroke-width:2\" />\n";
    }
    
    for(int i=0;i<n;i++)for(pair<int,int> p:arr[i]){
        int c=p.first;
        int j=p.second;
        fout<<"<circle cx=\""<<(double)(x[i]+x[j])/2<<"\" cy=\""<<(double)(y[i]+y[j])/2
            <<"\" r=\"12\" fill=\"white\" />\n";
    }
    
    for(int i=0;i<n;i++)
        fout<<"<circle cx=\""<<x[i]<<"\" cy=\""<<y[i]
            <<"\" r=\"4\" fill=\"blue\" />\n";
    for(int i=0;i<n;i++)
        fout<<"<text x=\""<<x[i]+2<<"\" y=\""<<y[i]
            <<"\" fill=\"white\" stroke=\"red\" font-weight=\"bold\">"<<i<<"</text>\n";

    for(int i=0;i<n;i++)for(pair<int,int> p:arr[i]){
        int c=p.first;
        int j=p.second;

        fout<<"<text x=\""<<(double)(x[i]+x[j])/2<<"\" y=\""<<(double)(y[i]+y[j])/2
            <<"\" fill=\"black\" text-anchor=\"middle\" dominant-baseline=\"middle\" font-size=\"12\" font-weight=\"bold\" >"<<c<<"</text>\n";
    }


    fout<<"</svg></body></html>";
}
void weighted_make_svg(string filename,int w,int h,int n,vector<pair<int,int>>* arr,int* x,int* y){
    ofstream fout(filename);
    fout<<"<html><body>\n";
    fout<<"<svg width=\""<<w<<"\" height=\""<<h<<"\">\n";
    
    
    fout<<"<defs><marker id='head' orient=\"auto\"markerWidth='1.5' markerHeight='6'\
refX='3' refY='2' viewBox=\"0 0 2 1\"><path d='M0,0 V4 L2,2 Z' fill=\"black\"/></marker></defs>\n";

    for(int i=0;i<n;i++)for(pair<int,int> p:arr[i]){
        int j=p.second;
            fout<<"<path id='arrow-line' marker-end='url(#head)' stroke-width='4' \
fill='none' stroke='#404040' d='M"<<x[i]<<","<<y[i]<<", "<<x[j]<<" "<<y[j]<<",120'/>\n";
    }
    
    for(int i=0;i<n;i++)
        fout<<"<circle cx=\""<<x[i]<<"\" cy=\""<<y[i]
            <<"\" r=\"4\" fill=\"blue\" />\n";
    for(int i=0;i<n;i++)
        fout<<"<text x=\""<<x[i]+2<<"\" y=\""<<y[i]
            <<"\" fill=\"white\" font-size=\"24\" stroke=\"red\" font-weight=\"bold\">"<<i<<"</text>\n";

    for(int i=0;i<n;i++)for(pair<int,int> p:arr[i]){
        int c=p.first;
        int j=p.second;
        fout<<"<circle cx=\""<<(double)(x[i]+x[j])/2<<"\" cy=\""<<(double)(y[i]+y[j])/2
            <<"\" r=\"12\" fill=\"white\" />\n";

        fout<<"<text x=\""<<(double)(x[i]+x[j])/2<<"\" y=\""<<(double)(y[i]+y[j])/2
            <<"\" fill=\"black\" text-anchor=\"middle\" dominant-baseline=\"middle\" font-size=\"12\" font-weight=\"bold\" >"<<c<<"</text>\n";
    }


    fout<<"</svg></body></html>";
}
