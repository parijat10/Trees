// Build and Search  - Vantage Point trees

// Based on "Data Structures and Algorithms for Nearest Neighbor Search" by Peter N. Yianilos


//PD
#include<bits/stdc++.h>
#define pb push_back
#define SZ(a) (int)(a.size())
#define sortarr(a) sort(a.begin(),a.end()) 
#define sortrev(a) sort(a.rbegin(),a.rend())
#define mp make_pair
#define fi(i,a,b) for(i=a;i<b;i++)
#define X first
#define Y second
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <queue>
#include <limits>

using namespace std;

typedef long long LL;
typedef vector<int> VI;
LL modpow(LL a, LL p, LL mod)
{LL ret = 1;while(p){if(p&1)ret = (ret*a)%mod;a=(a*a)%mod;p/=2;}return ret;}

LL power(LL a, LL p)
{LL ret = 1;while(p){if(p&1)ret = (ret*a);a=(a*a);p/=2;}return ret;}
/*int p[1000011];
VI prms;
void sieve(int n)
{int i,j;prms.pb(2);;fi(i,3,n){if(!i%2||!p[i])continue;prms.pb(i);for(j=2*i;j<n;j+=i)p[j]=1;}}*/

//to be declared by the user according to the data set

struct points
{
    vector<int> data;
};




class VPtree
{
    vector<points> _points;

    vector<points> NN;
    vector<double> dist;
    double _tau;

    double distance(points a, points b)
    {
        double ret;
        for(int i=0;i<a.data.size();i++)
        {
            ret+=pow((a.data[i] - b.data[i]),2);
        }
        return sqrt(ret);
    }

                
    struct Node
    {
        int index;
        double threshold;
        Node* left;
        Node* right;

        Node() : index(0), threshold(0.0), left(0), right(0) {}
        ~Node()
        {   delete left;
            delete right;
        }
    };

    Node* root;

    //to be called from main()
    Node* createtree(vector<points> items )
    {
        delete root;
        _points=items;
        return build(0,_points.size());
    }


    struct DistanceComparator
    {
        points item;
        double distance(points a, points b)
        {
            double ret;
            for(int i=0;i<a.data.size();i++)
            {
                ret+=pow((a.data[i] - b.data[i]),2);
            }
            return sqrt(ret);
        }


        DistanceComparator( points item ) : item(item) {}
        bool operator()(points a, points b) {
            return (distance( item, a ) < distance( item, b ));
        }
    };




    Node* build(int lower, int upper)
    {
        if ( upper == lower ) {
            return NULL;
        }

        Node* node = new Node();
        node->index = lower;

        if ( upper - lower > 1 ) {

            // choose an arbitrary point and move it to the start
            int i = (int)((double)rand() / RAND_MAX * (upper - lower - 1) ) + lower;
            std::swap( _points[lower], _points[i] );

            int median = ( upper + lower ) / 2;


            //DistanceComparator* dist= new DistanceComparator(_points[lower]);

            
            // partitian around the median distance
            std::nth_element(_points.begin() + lower + 1, _points.begin() + median,_points.begin() + upper, DistanceComparator(_points[lower]));

            // set threshold as median
            node->threshold = distance( _points[lower], _points[median] );

            node->index = lower;
            node->left = build( lower + 1, median );
            node->right = build( median, upper );
        }

        return node;
    }


    struct HeapItem {
        HeapItem( int index, double dist) :
            index(index), dist(dist) {}
        int index;
        double dist;
        bool operator<( const HeapItem& o ) const {
            return dist < o.dist;   
        }
    };

    // to be called from main()
    void search(points target, int k)
    {
        NN.clear();
        dist.clear();
        //search(root, );

        std::priority_queue<HeapItem> heap;

        _tau = DBL_MAX;
        search( root, target, k, heap );



        while( !heap.empty() ) {
            NN.push_back( _points[heap.top().index] );
            dist.push_back( heap.top().dist );
            heap.pop();
        }

        





    }


    void search( Node* node, points target, int k,
            std::priority_queue<HeapItem> heap )
    {
        if ( node == NULL ) return;

        double dist = distance( _points[node->index], target );


        if ( dist < _tau ) {
            if ( heap.size() == k ) heap.pop();
            heap.push( HeapItem(node->index, dist) );
            if ( heap.size() == k ) _tau = heap.top().dist;
        }

        if ( node->left == NULL && node->right == NULL ) {
            return;
        }

        if ( dist < node->threshold ) {
            if ( dist - _tau <= node->threshold ) {
                search( node->left, target, k, heap );
            }

            if ( dist + _tau >= node->threshold ) {
                search( node->right, target, k, heap );
            }

        } else {
            if ( dist + _tau >= node->threshold ) {
                search( node->right, target, k, heap );
            }

            if ( dist - _tau <= node->threshold ) {
                search( node->left, target, k, heap );
            }
        }
    }


};





int main()
{
    // create a tree of class Vptree
    vector<points> data;        
    //store the dataset in variable data.
    
    //call createtree(data) to build the tree.

    // call search(points target, int k) for knn of query point target.

    // access the knn points from 'NN' and distances from 'dist' of class Vptree.
   
    
    return 0;
}

