#include<iostream>
#include<stdlib.h>
#include <cstdlib>
#include<time.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
class Node {
public:
    int index;
    int y2;         //y coordinate of lower right corner
    Node* next;
};
Node* head=NULL;
Node* last=head;    // pointing to last node
//int mid,k=0;       //k is used for indexes of y2 coordinate
int compare(const void* a, const void* b)
{
const int* x = (int*) a;
const int* y = (int*) b;

if (*x > *y)
return 1;
else if (*x < *y)
return -1;

return 0;
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition1(int x1[][2], int low, int high)
{
    int pivot = x1[high][0]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (x1[j][0] < pivot)
        {
            i++; // increment index of smaller element
            swap(&x1[i][0], &x1[j][0]);
            swap(&x1[i][1], &x1[j][1]);

        }
    }
    swap(&x1[i + 1][1], &x1[high][1]);
    swap(&x1[i + 1][0], &x1[high][0]);

    return (i + 1);
}
void quickSort1(int x1[][2], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition1(x1, low, high);
        // Separately sort elements before
        // partition and after partition
        quickSort1(x1, low, pi - 1);
        quickSort1(x1, pi + 1, high);
    }
}
//int mc=1; //maxclique size initially
int intervalAlgo(int RectSort[][4],Node* head, int p,int x1[][2],int x2[][2],int *CR,int n,int mc){
    //cout<<"p="<<p<<endl;
    // int x2[p];
    // int x1[p];
    int CR1[n]; for(int i=0;i<n;i++) CR1[i]=0;
    //if(p==1) {CR1[head->index]=1;} //we write it here because if p==1 then condition if(mc<c)  will not true and noone will be in CR
    int c=0;
    int l=0;
    int k=0;
    int z;
    //static int mc=1; //maxclique size initially
    
    //int minn = 10; //set it to the maximum possible value
    //int maxx = -10;
    //cout<<"mc="<<mc<<endl;;
    Node* temp=head;
    for(int i=0;i<p;i++){
    x1[i][0]=RectSort[temp->index][0];//cout<<x1[i]<<" ";
    x1[i][1]=temp->index;
        x2[i][0]=RectSort[temp->index][2];//cout<<x2[i]<<endl;
        x2[i][1]=temp->index;
        //minn = min(minn,x1[i]);
        //maxx = max(maxx,x2[i]);
        temp=temp->next;
    }

    //qsort(x2,p,sizeof(int),compare);
     //qsort(x1,p,sizeof(int),compare);
    quickSort1(x1, 0, p - 1);
    quickSort1(x2, 0, p - 1);
     while(l<=p-1){
        //for(;x1[k]<x2[l],k<=p-1;c++,k++) cout<<k<<"alok"<<c<<endl;
        while(x1[k][0]<x2[l][0] && k<=p-1){
            z=x1[k][1];CR1[z]=1;k++;c++;
        }
        //if(k>p) c--;
     if(mc<c) {mc=c;for(int i=0;i<n;i++) CR[i]=CR1[i];}
    //  cout<<"CR = ";
    //  for(int i=0;i<n;i++) cout<<CR[i]<<" ";
    // cout<<endl;
     if(k>p-1) {
         //cout<<"mci1="<<mc<<" ";
         return mc;

     }

     while(x2[l][0]==x2[l+1][0] && l<p){c--; z=x2[l][1];CR1[z]=0;l++;}
     z=x2[l][1];CR1[z]=0;l++;c--;

     }
	

	/*int aux[maxx+2+abs(minn)]={0};
	int cur = 0,idx = 0;
	for(int i=0;i<p;i++)
	{
		aux[x1[i]+abs(minn)]+=1;
		aux[x2[i]+1+abs(minn)]-=1;
	}
	
	for(int i=0;i<maxx+1;i++)
	{
		cur+=aux[i];
		if(mc<cur)
		{
			IS5=mindeg(Rect,n);cout<<"By min deg Rect IS5="<<IS5<<endl;
    // Imc = cur;
			idx = i;
		}
	} */
//cout<<"mci2="<<mc<<" ";
return mc;
}
// deletenode(Node* head){}
Node* temp;
 Node* t;Node* u;
int maxclique(int RectSort[][4],int R[],int n,int *CR){
        static int i=0;                                      
        static int j=0;
        int mc=1;
        int s;
        int x1[n][2],x2[n][2];
        while(j<=n-1){
        //if(j>n-1||i>n-1) return mc;
        if(head==NULL) {head=new Node();last=head;last->index=j;last->y2=RectSort[j][3];j++;}
        while(j<n && RectSort[j][1]>R[i]){
            last->next=new Node();last=last->next;
            last->index=j;
            last->y2=RectSort[j][3];
            j++;
        }
        last->next=NULL;
        int p=0;
        for(temp=head;temp!=NULL;p++,temp=temp->next);
        //cout<<"p="<<p<<endl;
        
        if(head!=NULL){s=intervalAlgo(RectSort,head,p,x1,x2,CR,n,mc);}
        if(s>mc) mc=s;
        //cout<<"s="<<s<<" "<<"mc="<<mc<<endl;
        if(p>0){
        t=head;u=head;
        while(u!=NULL){//cout<<"y2="<<u->y2<<" p="<<p<<endl;
            if(p==1){               //only one node
                if(u->y2==R[i]){
                    delete head;
                    head=NULL;
                    last=NULL;
                    u=NULL;
                    t=NULL;
                }
            }
            else if(t==u){            // more than one node and check for 1 node
                if(u->y2==R[i]){
                    head=head->next;
                    delete u;
                    u=head;
                    t=head;
                }
                else {
                    u=t->next;
                }
            }
            else {
                if(u->y2==R[i]){
                    if(u==last) last=t;
                    t->next=u->next;
                    delete u;
                    u=t->next;
                }
                else {
                    t=t->next;
                    u=u->next;
                    
                }
            } 
        }
    }
        while(R[i]==R[i+1]) i++;
        i++;
	/*if(last==NULL)
	{
		head = NULL;
	}*/
       
       //int c = maxclique(RectSort,R,n);
       //if(c>mc) mc=c;
       //cout<<"R="<<endl;
       //for(int i=0;i<n;i++) cout<<R[i]<<endl;
        } 
       return mc;
  
}
void print(int n, int Rect[][4])
{int j,i;
  for (i=0;i<n;i++){
      j=0;
      while(j<4){
        if(Rect[i][j]<0)
        cout<<Rect[i][j]<<"   ";
        else  cout<<" "<<Rect[i][j]<<"   ";
        j++;
      }
      cout<<"\n";
    }
}
void RandRect(int n,int Rect[][4],int lower, int upper,int width, int height){ // width means in x coordinate and height means in y coordinate
  srand(time(0));
  int i;
  int w,h;
  for(i=0;i<n;i++){
        Rect[i][0]=(rand() % (upper - lower + 1)) + lower;
        Rect[i][1]=(rand() % (upper - lower + 1)) + lower;
        w=(rand() % (width - 1 + 1)) + 1;
        h=(rand() % (height - 1 + 1)) + 1;
        Rect[i][2]=Rect[i][0]+w;
        Rect[i][3]=Rect[i][1]-h;

        // if(i>0){                         // For removing confusing rectangles
        //   for(int j=0;j<i;j++){
        //     if(Rect[i][0]==Rect[j][2]){
        //       if((Rect[j][3]<=Rect[i][1] && Rect[i][1]<=Rect[j][1])||(Rect[j][3]<=Rect[i][3] && Rect[i][3]<=Rect[j][1])||(Rect[i][3]<=Rect[j][1] && Rect[j][1]<=Rect[i][1])||(Rect[i][3]<=Rect[j][3] && Rect[j][3]<=Rect[i][1])) {i--;}
        //     }
        //     else if(Rect[i][2]==Rect[j][0]){
        //       if((Rect[j][3]<=Rect[i][1] && Rect[i][1]<=Rect[j][1])||(Rect[j][3]<=Rect[i][3] && Rect[i][3]<=Rect[j][1])||(Rect[i][3]<=Rect[j][1] && Rect[j][1]<=Rect[i][1])||(Rect[i][3]<=Rect[j][3] && Rect[j][3]<=Rect[i][1])) {i--;}
        //     }
        //     else if(Rect[i][1]==Rect[j][3]){
        //       if((Rect[j][0]<=Rect[i][0] && Rect[i][0]<=Rect[j][2])||(Rect[j][0]<=Rect[i][2] && Rect[i][2]<=Rect[j][2])||(Rect[i][0]<=Rect[j][0] && Rect[j][0]<=Rect[i][2])||(Rect[i][0]<=Rect[j][2] && Rect[j][2]<=Rect[i][2])) {i--;}
        //     }
        //     else if(Rect[i][3]==Rect[j][1]){
        //        if((Rect[j][0]<=Rect[i][0] && Rect[i][0]<=Rect[j][2])||(Rect[j][0]<=Rect[i][2] && Rect[i][2]<=Rect[j][2])||(Rect[i][0]<=Rect[j][0] && Rect[j][0]<=Rect[i][2])||(Rect[i][0]<=Rect[j][2] && Rect[j][2]<=Rect[i][2])) {i--;}
        //     }
        //   }

        // }


  }
}

int partition (int RectSort[][4], int low, int high)
{
    int pivot = RectSort[high][1]; // pivot
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (RectSort[j][1] < pivot)
        {
            i++; // increment index of smaller element
            swap(&RectSort[i][1], &RectSort[j][1]);
            swap(&RectSort[i][0], &RectSort[j][0]);
            swap(&RectSort[i][2], &RectSort[j][2]);
            swap(&RectSort[i][3], &RectSort[j][3]);

        }
    }
    swap(&RectSort[i + 1][1], &RectSort[high][1]);
    swap(&RectSort[i + 1][0], &RectSort[high][0]);
    swap(&RectSort[i + 1][2], &RectSort[high][2]);
    swap(&RectSort[i + 1][3], &RectSort[high][3]);

    return (i + 1);
}
void quickSort(int RectSort[][4], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(RectSort, low, high);
        // Separately sort elements before
        // partition and after partition
        quickSort(RectSort, low, pi - 1);
        quickSort(RectSort, pi + 1, high);
    }
}

int mindeg1(int RectSort[][4],int n){
 int A[n][n];   //Adjacency matrix
 int deg[n],i,j;
    for(i=0;i<n;i++){
          A[i][i]=0;
        for(j=i+1;j<n;j++){
            if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
            else {
                 A[i][j]=1;
                 A[j][i]=1;
            }
        }
    }
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         cout<<A[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
     for(i=0;i<n;i++) deg[i]=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            deg[i]=deg[i]+A[i][j];
        }
    }
    cout<<endl;
    int min,IS=0,f=0,k,p=0,x=0;
        do{
            // for(i=0;i<n;i++) cout<<deg[i]<<" ";
            // cout<<endl;
    //for(i=0;i<n;i++) if(deg[i]deg[i]=0;
    // for(i=0;i<n;i++){
    //     if(deg[i]<0) continue;
    //     deg[i]=0;
    //     for(j=0;j<n;j++){
    //         deg[i]=deg[i]+A[i][j];
    //     }
    // } 
    //cout<<"degrees="<<endl;
    //for(i=0;i<n;i++) cout<<deg[i]<<" ";
      //cout<<endl;
           i=x;
           while(deg[i]<=-1 && i<n) {i++;}
           if(i==n) return IS;       // this function always return here so don't think about p
           x=i;
           min=deg[i];
           f=i;
           i++;
           for(;i<n;i++){
              if(deg[i]<=-1) continue;
              if(min>deg[i]){
                f=i;
                min=deg[i];
              }
           }
           IS++;
           deg[f]=-1;
        //    cout<<"Deleted rectangles="<<endl; 
        //    cout<<RectSort[f][0]<<" "<<RectSort[f][1]<<" "<<RectSort[f][2]<<" "<<RectSort[f][3]<<endl;
           for(j=x;j<n;j++){
                    if(A[f][j]==1){
                       deg[j]=-1;
                       for(k=x;k<n;k++){
                            if(A[k][j]==1 && deg[k]>0) deg[k]--;
                       }
                   }
                 
           }
           //for(j=0;j<n;j++) A[j][f]=0;
           p++;
           //cout<<"p="<<p<<endl;
        }while(p<n);
    return IS;  
}
int mindeg(int RectSort[][4],int n){
 int A[n][n];   //Adjacency matrix
 int deg[n],i,j;
    for(i=0;i<n;i++){
          A[i][i]=0;
        for(j=i+1;j<n;j++){
            if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
            else {
                 A[i][j]=1;
                 A[j][i]=1;
            }
        }
    }
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         cout<<A[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
     for(i=0;i<n;i++) deg[i]=0;
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         deg[i]=deg[i]+A[i][j];
    //     }
    // }
    //cout<<endl;
    int min,IS=0,f=0,k,p=0,x=0;
        do{
            // for(i=0;i<n;i++) cout<<deg[i]<<" ";
            // cout<<endl;
    //for(i=0;i<n;i++) if(deg[i]deg[i]=0;
    for(i=0;i<n;i++){
        if(deg[i]<0) continue;
        deg[i]=0;
        for(j=0;j<n;j++){
            deg[i]=deg[i]+A[i][j];
        }
    } 
    // cout<<"degrees="<<endl;
    // for(i=0;i<n;i++) cout<<deg[i]<<" ";
      //cout<<endl;
           i=x;
           while(deg[i]==-1 && i<n) {i++;}
           if(i==n) return IS;       // this function always return here so don't think about p
           x=i;
           min=deg[i];
           f=i;
           i++;
           for(;i<n;i++){
              if(deg[i]==-1) continue;
              if(min>deg[i]){
                f=i;
                min=deg[i];
              }
           }
           IS++;
           deg[f]=-1;
           //cout<<"selected rectangle in this pass="<<f+1<<endl;
           //cout<<"Deleted rectangles="<<endl; 
        //    cout<<RectSort[f][0]<<" "<<RectSort[f][1]<<" "<<RectSort[f][2]<<" "<<RectSort[f][3]<<endl;
        //cout<<"deleted rectangles= ";
           for(j=x;j<n;j++){
                    if(A[f][j]==1){
                        //cout<<j+1<<"  ";
                       deg[j]=-1;
                       for(k=x;k<n;k++){
                            A[k][j]=0;
                       }
                   }
                 
           }
           //cout<<endl;
           //cout<<endl;
           //for(j=0;j<n;j++) A[j][f]=0;
           p++;
           //cout<<"p="<<p<<endl;
        }while(p<n);
    return IS;  
}
int maxdeg(int RectSort[][4],int n){
 int A[n][n];   //Adjacency matrix
 int deg[n],i,j;
    for(i=0;i<n;i++){
          A[i][i]=0;
        for(j=i+1;j<n;j++){
            if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
            else {
                 A[i][j]=1;
                 A[j][i]=1;
            }
        }
    }
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         cout<<A[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    //for(i=0;i<n;i++) deg[i]=0;
    for(i=0;i<n;i++){
        deg[i]=0;
        for(j=0;j<n;j++){
            deg[i]=deg[i]+A[i][j];
        }
    }
    //cout<<endl;
    int max,IS=0,f=0,k,x=0;
        do{
            // for(i=0;i<n;i++) cout<<deg[i]<<" ";
            // cout<<endl;
           i=x;
           while(deg[i]<=0 && i<n) {i++;}
           if(i==n) {                              // this function always return here so don't think about 
              for(i=0;i<n;i++){
                  if(deg[i]==0) IS++;
              }
              return IS;
           }

           x=i;
           max=deg[i];
           f=i;
           i++;
           for(;i<n;i++){
              if(deg[i]<=0) continue;
              if(max<deg[i]){
                f=i;
                max=deg[i];
              }
           }
           deg[f]=-1;
           //cout<<"deleted rectangle in this pass="<<f+1<<endl; 
           for(j=x;j<n;j++){
                    if(A[f][j]==1){
                      deg[j]--;
                   }
                 
           }
           //for(j=0;j<n;j++) A[j][f]=0;
           //p++;
           //cout<<"p="<<p<<endl;
        }while(1);
    return IS;  
}
int mindegVector(int RectSort[][4], int n){
    int min=0,f,IS=0;
    vector<vector<int>> A;
    for (int i = 0; i < n; i++)
    {   vector<int>temp;
        for (int j = 0; j < n; j++)
        { if(i==j) {temp.push_back(0);}
          else if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {temp.push_back(0);}
            else {
                 temp.push_back(1);
            }  
        }
        A.push_back(temp);   
    }
    while(!A.empty()){
    vector<int> deg;
    int a;
    for(int i=0;i<A.size();i++){
        a=0;
        for(int j=0;j<A[i].size();j++){
            a=a+A[i][j];
        }
        deg.push_back(a);
    }
    f=0;
    min=deg[f];
    for(int i=1;i<deg.size();i++){
        if(min>deg[i]){
            min=deg[i];
            f=i;
        }
    }
    IS++;
    vector<int> del;
    del.push_back(f);
    for(int i=0;i<A.size();i++){
        if(A[f][i]==1){
            del.push_back(i);

        }
    }
    for(int i=0;i<del.size();i++){
        A.erase( A.begin() + del[i] );
        //std::for_each(A.begin(), A.end(), 
    //[&](std::vector<int>& row) {
        //row.erase(std::next(row.begin(), del[i]));
    //});
    //
    
  }
  for(int k=0;k<A.size();k++){
  	for(int j=0; j<del.size(); j++)
        	A[k].erase(A[k].begin()+del[j]);
    }
  }
  return IS;
}
int mindeg_minclique(int RectSort[][4],int n,int *CR){             // here don't try Rect from main because we need to pass this later for maxclique where we need RectSort       
int A[n][n],RectSort1[n][4],R[n];   //Adjacency matrix
 int deg[n],i,j;
    for(i=0;i<n;i++){
          A[i][i]=0;
        for(j=i+1;j<n;j++){
            if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
            else {
                 A[i][j]=1;
                 A[j][i]=1;
            }
        }
    }
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         cout<<A[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
     for(i=0;i<n;i++) deg[i]=0;
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         deg[i]=deg[i]+A[i][j];
    //     }
    // }
    //cout<<endl;
    int min,IS=0,f=0,k,p=0,x=0,ind[n],c[n],y;
        do{
            // for(i=0;i<n;i++) cout<<deg[i]<<" ";
            // cout<<endl;
    //for(i=0;i<n;i++) if(deg[i]deg[i]=0;
    for(i=0;i<n;i++){
        if(deg[i]<0) continue;
        deg[i]=0;
        for(j=0;j<n;j++){
            deg[i]=deg[i]+A[i][j];
        }
    } 
    // cout<<"degrees="<<endl;
    // for(i=0;i<n;i++) cout<<deg[i]<<" ";
      //cout<<endl;
           i=x;
           while(deg[i]<=-1 && i<n) {i++;}
           if(i==n) return IS;       // this function always return here so don't think about p
           x=i;
           min=deg[i];
           f=i;
           i++;
           for(;i<n;i++){
              if(deg[i]<=-1) continue;
              if(min>deg[i]){
                f=i;
                min=deg[i];
              }
    
           }
           if(min==0) {for(int i=0;i<n;i++) if(deg[i]==0) {IS++;deg[i]=-1;}}
        if(min>1){
           j=0;
           for(i=0;i<n;i++){
               if(min==deg[i]){
                   ind[j]=i;j++;
               }
           }
           k=0;
           while(k<j){
               y=0;
               for(i=0;i<n;i++){
                   if(ind[k]==i){
                       RectSort1[y][0]=RectSort[i][0];RectSort1[y][1]=RectSort[i][1];RectSort1[y][2]=RectSort[i][2];RectSort1[y][3]=RectSort[i][3];y++;
                   }
                   else{
                       if(A[ind[k]][i]==1){
                           RectSort1[y][0]=RectSort[i][0];RectSort1[y][1]=RectSort[i][1];RectSort1[y][2]=RectSort[i][2];RectSort1[y][3]=RectSort[i][3];y++;
                       }
                   }
               }
               for(i=0;i<y;i++) R[i]=RectSort1[i][3];
               qsort(R,n,sizeof(int),compare);
               for(int i=0,j=n-1;i<j;i++,j--){  //y2 in desc.
                     swap(&R[i],&R[j]);
                }
               c[k]=maxclique(RectSort1,R,y,CR);k++;
           }
           min=c[0];
           f=ind[0];
           for(i=1;i<j;i++){
               if(min>c[i]){
                   min=c[i];
                   f=ind[i];
               }
           }
        }  
    if(deg[f]>0){
           IS++;
           deg[f]=-1;
           //cout<<"selected rectangle in this pass="<<f+1<<endl;
        //    cout<<"Deleted rectangles="<<endl; 
        //    cout<<RectSort[f][0]<<" "<<RectSort[f][1]<<" "<<RectSort[f][2]<<" "<<RectSort[f][3]<<endl;
        //cout<<"deleted rectangles= ";
           for(j=x;j<n;j++){
                    if(A[f][j]==1){
                        //cout<<j+1<<"  ";
                       deg[j]=-1;
                       for(k=x;k<n;k++){
                            A[k][j]=0;
                       }
                   }
                 
           }
    }
        //    cout<<endl;
        //    cout<<endl;
           //for(j=0;j<n;j++) A[j][f]=0;
           p++;
      
    //cout<<"p="<<p<<endl;
        }while(p<n);
    return IS;  
}
int maxdeg_maxclique(int RectSort[][4],int n,int *CR){     // here don't try Rect from main because we need to pass this later for maxclique where we need RectSort
 int A[n][n],RectSort1[n][4],R[n];   //Adjacency matrix
 int deg[n],i,j;
    for(i=0;i<n;i++){
          A[i][i]=0;
        for(j=i+1;j<n;j++){
            if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
            else {
                 A[i][j]=1;
                 A[j][i]=1;
            }
        }
    }
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         cout<<A[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    //for(i=0;i<n;i++) deg[i]=0;
    for(i=0;i<n;i++){
        deg[i]=0;
        for(j=0;j<n;j++){
            deg[i]=deg[i]+A[i][j];
        }
    }
    //cout<<endl;
    int max,IS=0,f=0,k,x=0,ind[n],c[n],y;
        do{
            // for(i=0;i<n;i++) cout<<deg[i]<<" ";
            // cout<<endl;
           i=x;
           while(deg[i]<=0 && i<n) {i++;}
           if(i==n) {                              // this function always return here so don't think about 
              for(i=0;i<n;i++){
                  if(deg[i]==0) IS++;
              }
              return IS;
           }

           x=i;
           max=deg[i];
           f=i;
           i++;
           for(;i<n;i++){
              if(deg[i]<=0) continue;
              if(max<deg[i]){
                f=i;
                max=deg[i];
              }
           }
        if(max==0){for(int i=0;i<n;i++) {if(deg[i]==0) IS++;} return IS;}
        if(max>1){
           j=0;
           for(i=0;i<n;i++){
               if(max==deg[i]){
                   ind[j]=i;j++;
               }
           }
           k=0;
           while(k<j){
               y=0;
               for(i=0;i<n;i++){
                   if(ind[k]==i){
                       RectSort1[y][0]=RectSort[i][0];RectSort1[y][1]=RectSort[i][1];RectSort1[y][2]=RectSort[i][2];RectSort1[y][3]=RectSort[i][3];y++;
                   }
                   else{
                       if(A[ind[k]][i]==1){
                           RectSort1[y][0]=RectSort[i][0];RectSort1[y][1]=RectSort[i][1];RectSort1[y][2]=RectSort[i][2];RectSort1[y][3]=RectSort[i][3];y++;
                       }
                   }
               }
               for(i=0;i<y;i++) R[i]=RectSort1[i][3];
               qsort(R,n,sizeof(int),compare);
               for(int i=0,j=n-1;i<j;i++,j--){  //y2 in desc.
                     swap(&R[i],&R[j]);
                }
               c[k]=maxclique(RectSort1,R,y,CR);k++;
           }
           max=c[0];
           f=ind[0];
           for(i=1;i<j;i++){
               if(max<c[i]){
                   max=c[i];
                   f=ind[i];
               }
           }
        }
           deg[f]=-1;
           //cout<<"deleted rectangle in this pass="<<f+1<<endl; 
           for(j=x;j<n;j++){
                    if(A[f][j]==1){
                      deg[j]--;
                   }
                 
           }
           //for(j=0;j<n;j++) A[j][f]=0;
           //p++;
           //cout<<"p="<<p<<endl;
        }while(1);
    return IS;  
}
int minclique_mindeg(int RectSort[][4],int n,int *CR){             // here don't try Rect from main because we need to pass this later for maxclique where we need RectSort       
int A[n][n],RectSort1[n][4],R[n];   //Adjacency matrix
 int deg[n],i,j;
    for(i=0;i<n;i++){
          A[i][i]=0;
        for(j=i+1;j<n;j++){
            if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
            else {
                 A[i][j]=1;
                 A[j][i]=1;
            }
        }
    }
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         cout<<A[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    for(i=0;i<n;i++) deg[i]=0;
    // for(i=0;i<n;i++){
    //     for(j=0;j<n;j++){
    //         deg[i]=deg[i]+A[i][j];
    //     }
    // }
    //cout<<endl;
    int min,IS=0,f=0,k,p=0,x=0,ind[n],c[n],y,z,min1;
    int cv[n];     // cv is clique values
    //for(int i=0;i<n;i++) cv[i]=0;
            // for(i=0;i<n;i++) cout<<deg[i]<<" ";
            // cout<<endl;
    //for(i=0;i<n;i++) if(deg[i]deg[i]=0;
do{
    for(i=x;i<n;i++){
        if(deg[i]<0) continue;
        y=0;
        j=x;
        while(j<i){             // for correct positioning of i in RectSort1
            if(cv[j]!=-1 && A[i][j]==1) {
                deg[i]++;
                RectSort1[y][0]=RectSort[j][0];
                RectSort1[y][1]=RectSort[j][1];
                RectSort1[y][2]=RectSort[j][2];
                RectSort1[y][3]=RectSort[j][3];
                y++;j++;
            }
            else j++;
        }
        RectSort1[y][0]=RectSort[i][0];         //i==j
        RectSort1[y][1]=RectSort[i][1];
        RectSort1[y][2]=RectSort[i][2];
        RectSort1[y][3]=RectSort[i][3];
        y++;j++;
        while(j<n){
            if(cv[j]!=-1 && A[i][j]==1) {
                deg[i]++;
                RectSort1[y][0]=RectSort[j][0];
                RectSort1[y][1]=RectSort[j][1];
                RectSort1[y][2]=RectSort[j][2];
                RectSort1[y][3]=RectSort[j][3];
                y++;j++;
            }
            else j++;
        }
        if(y==1){deg[i]=-1;cv[i]=-1;IS++;}
        else {
            for(int i=0;i<y;i++) R[i]=RectSort1[i][3];
               qsort(R,n,sizeof(int),compare);
               for(int i=0,j=n-1;i<j;i++,j--){  //y2 in desc.
                     swap(&R[i],&R[j]);
                }
            cv[i]=maxclique(RectSort1,R,y,CR);
        }

    }
    // cout<<"degrees="<<endl;
    // for(i=0;i<n;i++) cout<<deg[i]<<" ";
      //cout<<endl;
           i=x;
           while(cv[i]<=-1 && i<n) {i++;}
           if(i==n) return IS;       // this function always return here so don't think about p
           x=i;
           min=cv[i];
           f=i;
           i++;
           for(;i<n;i++){
              if(cv[i]<=-1) continue;
              if(min>cv[i]){
                f=i;
                min=cv[i];
              }
    
           }
           //if(min==0) {for(int i=0;i<n;i++) if(deg[i]==0) {IS++;deg[i]=-1;}}
        if(min>2)
           for(i=x;i<n;i++){
               if(min==cv[i]){
                   deg[i]=0;
                   for(k=0;k<n;k++)  deg[i]=deg[i]+A[i][k];
               }
           }
           for(i=x;i<n;i++){if(min==cv[i]){min1=deg[i];f=i;break;}}
           for(i=f+1;i<n;i++){
               if(cv[i]<0) continue;
               if(min==cv[i] && min1>deg[i]) {
                   min1=deg[i];
                   f=i;
                }
           }
    
           IS++;
           deg[f]=-1;
           cv[f]=-1;
           //cout<<"selected rectangle in this pass="<<f+1<<endl;
        //    cout<<"Deleted rectangles="<<endl; 
        //    cout<<RectSort[f][0]<<" "<<RectSort[f][1]<<" "<<RectSort[f][2]<<" "<<RectSort[f][3]<<endl;
        //cout<<"deleted rectangles= ";
           for(j=x;j<n;j++){
                    if(A[f][j]==1){
                        //cout<<j+1<<"  ";
                       deg[j]=-1;cv[j]=-1;
                       for(k=x;k<n;k++){
                            A[k][j]=0;
                       }
                   }
                 
           }

        //    cout<<endl;
        //    cout<<endl;
           //for(j=0;j<n;j++) A[j][f]=0;
           p++;
      
    //cout<<"p="<<p<<endl;
    //for(i=0;i<n;i++) if(deg[i]deg[i]=0;
    }while(p<n);
    return IS;  
}
int bruteforce(int RectSort[][4],int n,int AIS,int CR[]){
    int A[n][n],IS=0,p=0,n1,RectSort1[n][5],y,mc;   //Adjacency matrix
    int deg[n],i,j;
    for(i=0;i<n;i++){
          A[i][i]=0;
        for(j=i+1;j<n;j++){
            if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
            else {
                 A[i][j]=1;
                 A[j][i]=1;
            }
        }
    }
    for(i=0;i<n;i++){
        deg[i]=0;
        for(j=0;j<n;j++){
            deg[i]=deg[i]+A[i][j];
        }
    }
    for(i=0;i<n;i++){
        if(deg[i]==0){
            p++;
            deg[i]=-1;
        }
    } 
    IS=IS+p;        // Add Deg of 0 rectangles directly
    n1=n-p;int Adj[n-p][n];          //info of All clique
    int k=0;
    while(n1>0){
        y=0;
        for(i=0;i<n;i++){
            if(deg[i]!=-1){
                RectSort1[y][0]=RectSort[i][0];
                RectSort1[y][1]=RectSort[i][1];
                RectSort1[y][2]=RectSort[i][2];
                RectSort1[y][3]=RectSort[i][3];
                RectSort1[y][4]=i;               //   
                y++;
            }
        }
        int R[y];
        for(int i=0;i<y;i++) R[i]=RectSort1[i][3];
        qsort(R,n,sizeof(int),compare);
        for(int i=0,j=n-1;i<j;i++,j--){  //y2 in desc.
            swap(&R[i],&R[j]);
        }

        mc=maxclique(RectSort1,R,y,CR);
        n1=n1-mc;
        for(i=0;i<y;i++){
            if(CR[i]==1){
                deg[RectSort1[i][4]]=-1;
                Adj[k][RectSort1[i][4]]=1;
            }
        }
        for(int i=0;i<n;i++) CR[i]=0;

    }

}
int main()
 {
       int n,a,i,j,c,IS1,IS2,IS3,IS4,IS5,IS6,IS7,IS8,IS9,count=0,count1=0,count2=0,k=0,z=0,IS[7];
    int lower,upper;
    int width,height;
    //cout<<"no. of Rectangles\n";
    //cin>>n;
    n =5;
    int Rect[n][4];int RectSort[n][4],CR[n];       //CR[n] is Rectangles responsible for clique
    for(int i=0;i<n;i++) CR[i]=0;
    //cout<<"Enter lower limit and upper limit(means Range) for upper left coordinate\n";
    //cin>>lower>>upper;// range of upper left point will be given by this
    lower  = -5;
    upper = 5;
    //cout<<"Enter max width and height\n";
    //cin>>width>>height;
    width = height = 5;
    //for(int i=0;i<32000;i++){
    RandRect(n,Rect,lower,upper,width,height); // input rectangle
    //printf("Before sorting\n");
    //print(n,Rect);
    for(int i=0;i<n;i++){
      for(int j=0;j<4;j++){
        RectSort[i][j]=Rect[i][j];
      }
    }
    quickSort(RectSort, 0, n - 1);
    for(int i=0,j=n-1;i<j;i++,j--){     // converting decsending order
      swap(&RectSort[i][0],&RectSort[j][0]);
      swap(&RectSort[i][1],&RectSort[j][1]);
      swap(&RectSort[i][2],&RectSort[j][2]);
      swap(&RectSort[i][3],&RectSort[j][3]);
    }
    //printf("After sorting\n");
    //print(n,RectSort);
/*
    int R[n];  // array of y2
    for(int i=0;i<n;i++) R[i]=RectSort[i][3];
    qsort(R,n,sizeof(int),compare);
    for(int i=0,j=n-1;i<j;i++,j--){  //y2 in desc.
        swap(&R[i],&R[j]);
    }

    cout<<endl;


	ofstream fout;
	fout.open("rectpoints.txt");
	//fout.open("rectpoints.txt",ios::app);

		for(int i=0;i<n;i++)
		{
			fout<<RectSort[i][0]<<" "<<RectSort[i][1]<<" "<<RectSort[i][2]<<" "<<RectSort[i][3]<<" "<<endl;
		}
	
	fout.close();
*/
	/*ifstream fin;
	fin.open("rectpoints.txt");
	for(int i= 0;i<5;i++)
	{
		fin>>RectSort[i][0]>>RectSort[i][1]>>RectSort[i][2]>>RectSort[i][3];
	}
	fin.close();*/

  // array of y2
    // for(int i=0;i<n;i++) R[i]=RectSort[i][3];
    // qsort(R,n,sizeof(int),compare);
    // for(int i=0,j=n-1;i<j;i++,j--){  //y2 in desc.
    //     swap(&R[i],&R[j]);
    // }
    // cout<<"y2="<<endl;
    // for(int i=0;i<n;i++) cout<<R[i]<<endl;
    // RectSort[0][0]=-4;RectSort[0][1]=4;RectSort[0][2]=-2;RectSort[0][3]=1;
    // RectSort[1][0]=-2;RectSort[1][1]=1;RectSort[1][2]=-1;RectSort[1][3]=-1;
    // RectSort[2][0]=-1;RectSort[2][1]=0;RectSort[2][2]=2;RectSort[2][3]=-5;
    // RectSort[3][0]=4;RectSort[3][1]=-1;RectSort[3][2]=5;RectSort[3][3]=-5;
    // RectSort[4][0]=1;RectSort[4][1]=-3;RectSort[4][2]=6;RectSort[4][3]=-8;

    // RectSort[0][0]=2;RectSort[0][1]=5;RectSort[0][2]=4;RectSort[0][3]=2;
    // RectSort[1][0]=-1;RectSort[1][1]=4;RectSort[1][2]=4;RectSort[1][3]=0;
    // RectSort[2][0]=3;RectSort[2][1]=4;RectSort[2][2]=8;RectSort[2][3]=0;
    // RectSort[3][0]=2;RectSort[3][1]=1;RectSort[3][2]=5;RectSort[3][3]=-2;
    // RectSort[4][0]=-2;RectSort[4][1]=1;RectSort[4][2]=0;RectSort[4][3]=-4;

    // RectSort[0][0]=-4;RectSort[0][1]=5;RectSort[0][2]=-3;RectSort[0][3]=2;  // input for 10 rectangles
    // RectSort[1][0]=-2;RectSort[1][1]=3;RectSort[1][2]=0;RectSort[1][3]=-2;
    // RectSort[2][0]=2;RectSort[2][1]=3;RectSort[2][2]=6;RectSort[2][3]=-2;
    // RectSort[3][0]=2;RectSort[3][1]=3;RectSort[3][2]=5;RectSort[3][3]=-2;
    // RectSort[4][0]=1;RectSort[4][1]=2;RectSort[4][2]=2;RectSort[4][3]=0;
    //     RectSort[5][0]=-5;RectSort[5][1]=0;RectSort[5][2]=-2;RectSort[5][3]=-1;
    // RectSort[6][0]=-3;RectSort[6][1]=-1;RectSort[6][2]=0;RectSort[6][3]=-3;
    // RectSort[7][0]=0;RectSort[7][1]=-4;RectSort[7][2]=5;RectSort[7][3]=-8;
    // RectSort[8][0]=0;RectSort[8][1]=-4;RectSort[8][2]=3;RectSort[8][3]=-7;
    // RectSort[9][0]=4;RectSort[9][1]=-5;RectSort[9][2]=7;RectSort[9][3]=-6;

    // RectSort[0][0]=2;RectSort[0][1]=3;RectSort[0][2]=5;RectSort[0][3]=-1;
    // RectSort[1][0]=3;RectSort[1][1]=2;RectSort[1][2]=7;RectSort[1][3]=-1;
    // RectSort[2][0]=-3;RectSort[2][1]=0;RectSort[2][2]=0;RectSort[2][3]=-4;
    // RectSort[3][0]=-2;RectSort[3][1]=0;RectSort[3][2]=1;RectSort[3][3]=-3;
    // RectSort[4][0]=-5;RectSort[4][1]=-3;RectSort[4][2]=0;RectSort[4][3]=-8;
    //RectSort[5][0]=-5;RectSort[5][1]=-3;RectSort[5][2]=0;RectSort[5][3]=-8;
    //print(n,RectSort);
     int R[n];
    for(int i=0;i<n;i++) R[i]=RectSort[i][3];
    qsort(R,n,sizeof(int),compare);
    for(int i=0,j=n-1;i<j;i++,j--){  //y2 in desc.
        swap(&R[i],&R[j]);
    }
    // cout<<"y2="<<endl;
    //for(int i=0;i<n;i++) cout<<R[i]<<endl;
    c= maxclique(RectSort,R,n,CR); cout<<"Clique="<<c<<endl;
    //cout<<"Rectangles responsible for maxclique are = ";
    // if(c==1) CR[0]=1;
    // for(int i=0;i<n;i++) {if(CR[i]==1) {cout<<i+1<<"  ";}}
    //cout<<endl;
    IS[0]=mindeg(RectSort,n);
    cout<<"IS by Min Deg IS1="<<IS1<<endl;
    IS[1]=maxdeg(RectSort,n);
    //if(IS1!=IS2){ cout<<"wrong output"<<endl;cout<<endl; print(n,RectSort);cout<<endl;c=maxclique(RectSort,R,n);cout<<"Clique="<<c<<endl;cout<<"IS by Min Deg="<<IS1<<endl;cout<<"IS by Max Deg="<<IS2<<endl;break;if(IS1>IS2) {count1++;if(k<(IS1-IS2)) {k=IS1-IS2;z=1;}}else {count2++;if(k<=(IS2-IS1)){k=IS2-IS1;z=2;}}}
    cout<<"IS by Max Deg IS2="<<IS2<<endl;
    // IS3=mindeg1(RectSort,n);
    // cout<<"IS by Min Deg1="<<IS3<<endl;
    //IS4=mindegVector(RectSort,n);
    //cout<<"IS by Min Deg Vector="<<IS4<<endl;
    //cout<<"Alok Kumar";
    IS[2]=mindeg(Rect,n);cout<<"By min deg Rect IS5="<<IS5<<endl;
    IS[3]=maxdeg(Rect,n);cout<<"By max deg Rect IS6="<<IS6<<endl;
    IS[4]=mindeg_minclique(RectSort,n,CR);cout<<"IS by Min Deg Min clique IS7="<<IS7<<endl;    // don't use Rect here instead of RectSort because in this function, we need RectSort
    IS[5]=maxdeg_maxclique(RectSort,n,CR);cout<<"IS by Max Deg Max clique IS8="<<IS8<<endl;
    IS[6]=minclique_mindeg(RectSort,n,CR);cout<<"IS by Min clique Min Deg IS9="<<IS9<<endl;
    int AIS=IS[0];            // AIS is approx IS
    for(int i=1;i<7;i++){
        if(AIS<IS[i]){
            AIS=IS[i];
        }
    }
    bruteforce(RectSort,n,AIS,CR);
    //count=count1+count2;
    //cout<<"count1="<<count1<<"  "<<"count2="<<count2<<"  "<<"total="<<count<<"  k="<<k<<"  z="<<z<<endl;
    //if(IS1!=IS7){cout<<"IS by Min Deg IS1="<<IS1<<endl;cout<<"IS by Min Deg Min clique IS7="<<IS7<<endl;break;}
    return 0;
 //}
}













