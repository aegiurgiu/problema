#include <iostream>
#include <fstream>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

struct booked{
    float in,sf; ///i used a structure for each person for read the range for each meeting
};

int n,meet=0,nr=0;
float minutes;
booked v[100],c1,c2;

void read(int &n,booked v[])
{
    int i;
    f>>n; ///numbers of meetings for calendar1
    for (i=1; i<=n; i++)
        f>>v[i].in>>v[i].sf;

    f>>minutes; ///meeting time minutes
    f>>c1.in>>c1.sf; ///min and max range for the firs person
    f>>c2.in>>c2.sf; ///min and max range for the second person

     if ((c2.in>=c1.in) && (c2.in<=c1.sf) && (c2.sf<=c1.sf)) ///check if the people have a common range for meeting
        {
            g<<"People can meet!"<<endl; ///print a message if people have a common range for meeting
            meet=1;
        }
}

void sorting(int n,booked v[])
{
  booked aux;
  int i,j;       ///to solve the problem i used the greedy method
  for (i=1; i<n; i++)
  for (j=i+1; j<=n; j++)
    {
        if(v[i].in>v[j].in)
            aux=v[i], v[i]=v[j], v[j]=aux;
        if(v[i].in==v[j].in && v[i].sf>v[j].sf)
            aux=v[i],v[i]=v[j],v[j]=aux;
    }
}

void result(int n, booked v[])
{
    float min_in,min_sf;
    for (int i=1; i<n; i++)
    {
         min_sf=v[i].sf;
         min_in=v[i+1].in;
         if ((min_sf+(minutes/100)<=min_in) )  //(min_sf+(minutes/100))-(int)(min_sf+(minutes/100))>=6)
            {
                nr++;
                g<<v[i].sf<<" "<<v[i+1].in<<endl;
            }
    }
       min_sf=v[n].sf;
     if (min_sf+(minutes/100)<=c2.sf || min_sf+(minutes/100)<=c1.sf)
        {
            if(c1.sf<=c2.sf)
                {
                    g<<v[n].sf<<" "<<c1.sf<<endl;
                    nr++;
                }
            else
                {
                    g<<v[n].sf<<" "<<c2.sf<<endl;
                    nr++;
                }
        }
}
int main()
{
    read(n,v);
    sorting(n,v);
    result(n,v);
    if(meet==0 && nr==0)
    {
        g<<"People cannot meet!"<<endl;
        return 0;
    }
    f.close();
    g.close();
    return 0;
}
