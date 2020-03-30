#include<stdio.h>
#include<vector>
#include<cmath>
#include<iostream>
#include<fstream>
using namespace std;



/*
vector< vector<double> > input={{7,40},{7,90},{96,51},{58,92},{100,17}
,{19,30},{96,84},{65,79},{42,93},{12,22},{28,36},{6,70},{3,94},
{61,44},{94,61},{72,69},{5,80},{87,87},{6,45},{82,72},{31,78}
,{88,47},{53,63},{48,69},{46,17},{34,28},{40,51},{39,21}
,{60,46},{10,81}};
*/

vector< vector<double> > input;




    vector<int> output;
    double x_max;
    double x_min;
    double y_max;
    double y_min;
    int x_maxindexup=0,x_maxindexdown=0,x_minindexup=0,x_minindexdown=0;
    int y_maxindexleft=0,y_maxindexright=0,y_minindexleft=0,y_minindexright=0;


void findboundary();//查找最原始的边界多边形
void recur(double x1,double y1,double x2,double y2,bool n);//输入直线方程及y=kx+b的系数k和b，以及标识符n
double cal_distance(double k,double b,double x,double y);
int main()
{
    vector<double> m;
    double d;

    ifstream in("data.txt");
    while(in>>d)
        m.push_back(d);



    for(int i=0;i<=m.size()-1;i+=2)
    {
        input.push_back({m[i],m[i+1]});
    }

   /* for(auto c:input)
    {
        for(auto k:c)
            cout<<k<<" ";
        cout << endl;
    }*/

    x_max=input[0][0];
    x_min=input[0][0];
    y_max=input[0][1];
    y_min=input[0][1];



    findboundary();

    if(y_maxindexleft==x_minindexup)
        output.push_back(y_maxindexleft);
    else
        {
            output.push_back(x_minindexup);
            recur(input[x_minindexup][0],input[x_minindexup][1],
                  input[y_maxindexleft][0],input[y_maxindexleft][1],true);
            output.push_back(y_maxindexleft);
        }


    if((y_maxindexright==x_maxindexup)&&(y_maxindexright!=output.back()))
        output.push_back(y_maxindexright);
    else
    {
        if(y_maxindexright!=output.back())
            output.push_back(y_maxindexright);
        recur(input[y_maxindexright][0],input[y_maxindexright][1],input[x_maxindexup][0],input[x_maxindexup][1],true);
        if(x_maxindexup!=output.back())
            output.push_back(x_maxindexup);
    }


    if((y_minindexright==x_maxindexdown)&&(y_minindexright!=output.back()))
        output.push_back(y_minindexright);
    else
    {
        if(x_maxindexdown!=output.back())
            output.push_back(x_maxindexdown);
        recur(input[x_maxindexdown][0],input[x_maxindexdown][1],input[y_minindexright][0],input[y_minindexright][1],false);
        if(y_minindexright!=output.back())
            output.push_back(y_minindexright);
    }


    if((y_minindexleft==x_minindexdown)&&(y_minindexleft!=output.back()))
        output.push_back(y_minindexleft);

    else
    {
        if(y_minindexleft!=output.back())
            output.push_back(y_minindexleft);
        recur(input[y_minindexleft][0],input[y_minindexleft][1],input[x_minindexdown][0],input[x_minindexdown][1],false);
        if(x_minindexdown!=output.back())
            output.push_back(x_minindexdown);
    }
    if(output.back()!=output.front())
        output.push_back(output.front());
    for(auto k:output)
        cout << input[k][0]<<" ";
    cout<<endl;
    for(auto k:output)
        cout<<input[k][1] << " ";
    return 0;



}

void findboundary()
{
for(int i=1;i<=input.size()-1;++i)
    {

        //寻找横坐标最大的点
        if(input[i][0]>x_max)
        {
            x_max=input[i][0];
            x_maxindexup=i;
            x_maxindexdown=i;
        }
        if(input[i][0]==x_max)
        {
            x_maxindexup=input[i][1]>input[x_maxindexup][1]?i:x_maxindexup;
            x_maxindexdown=input[i][1]<input[x_maxindexdown][1]?i:x_maxindexdown;
        }
        //寻找横坐标最小的点
        if(input[i][0]<x_min)
        {
            x_min=input[i][0];
            x_minindexup=i;
            x_minindexdown=i;
        }
        if(input[i][0]==x_min)
        {
            x_minindexup=input[i][1]>input[x_minindexup][1]?i:x_minindexup;
            x_minindexdown=input[i][1]<input[x_minindexdown][1]?i:x_minindexdown;
        }
        //寻找纵坐标最大的点
        if(input[i][1]>y_max)
        {
            y_max=input[i][1];
            y_maxindexleft=i;
            y_maxindexright=i;
        }
        if(input[i][1]==y_max)
        {
            y_maxindexleft=input[i][0]<input[y_maxindexleft][0]?i:y_maxindexleft;
            y_maxindexright=input[i][0]>input[y_maxindexright][0]?i:y_maxindexright;
        }
        //寻找纵坐标最小的点
        if(input[i][1]<y_min)
        {
            y_min=input[i][1];
            y_minindexleft=i;
            y_minindexright=i;
        }
        if(input[i][1]==y_min)
        {
            y_minindexleft=input[i][0]<input[y_minindexleft][0]?i:y_minindexleft;
            y_minindexright=input[i][0]>input[y_minindexright][0]?i:y_minindexright;
        }
    }
}

void recur(double x1,double y1,double x2,double y2,bool n)
{
    //cout <<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
    double k=(y2-y1)/(x2-x1);
    double b=y1-x1*(y2-y1)/(x2-x1);
    double distance = 0.0;
    double maxdistance = 0.0;
    vector<int> nextrecur;

    for(int i=0;i<=input.size()-1;++i)
    {

        if(fabs(input[i][1]-(k*input[i][0]+b))<=0.00000001)

            continue;
        if((input[i][1]>k*input[i][0]+b)==n)
        {
            distance=cal_distance(k,b,input[i][0],input[i][1]);
            if(fabs(distance-maxdistance)<=0.00000001)
            {
                nextrecur.push_back(i);
                continue;
            }
            if(distance>maxdistance)
            {
                maxdistance = distance;
                nextrecur.clear();
                nextrecur.push_back(i);
            }

        }
    }
    if(nextrecur.size()==0)
        return;
    /*if(nextrecur.size()==1)
    {
        recur(x1,y1,input[nextrecur[0]][0],input[nextrecur[0]][1]           );
        recur(x2,y2,input[nextrecur[0]][0],input[nextrecur[0]][1]           );
    }*/
    int next2x1y1index=nextrecur[0],far2x1y1index=nextrecur[0];
    for(int j=1;j<nextrecur.size();++j)
    {
        if(fabs(input[nextrecur[j]][0]-x1)<fabs(input[next2x1y1index][0]-x1))
        {
            next2x1y1index=nextrecur[j];
        }

        if(fabs(input[nextrecur[j]][0]-x1)>fabs(input[far2x1y1index][0]-x1))
        {
            far2x1y1index=nextrecur[j];
        }
    }
    recur(x1,y1,input[next2x1y1index][0],input[next2x1y1index][1] ,n     );
    output.push_back(next2x1y1index);
    if(next2x1y1index!=far2x1y1index)
        output.push_back(far2x1y1index);
    recur(input[far2x1y1index][0],input[far2x1y1index][1]  ,x2,y2,n      );

    return;

}

double cal_distance(double k,double b,double x,double y)
{
    return fabs(k*x-y+b)/sqrt(k*k+1);
}
