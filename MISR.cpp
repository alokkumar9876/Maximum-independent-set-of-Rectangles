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
//int n;
//int RectSort[50][4];
//Node* head=NULL;
//Node* last=head;    // pointing to last node
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
int intervalAlgo2(int RectSort[][4],Node* head, int p,int x1[],int x2[],int n,int mc){
    //cout<<"p="<<p<<endl;
    // int x2[p];
    // int x1[p];
    //int CR1[n]; for(int i=0;i<n;i++) CR1[i]=0;
    //if(p==1) {CR1[head->index]=1;} //we write it here because if p==1 then condition if(mc<c)  will not true and noone will be in CR
    int c=0;
    int l=0;
    int k=0;
    //int z;
    //static int mc=1; //maxclique size initially
    
    //int minn = 10; //set it to the maximum possible value
    //int maxx = -10;
    //cout<<"mc="<<mc<<endl;;
    Node* temp=head;
    for(int i=0;i<p;i++){
    x1[i]=RectSort[temp->index][0];//cout<<x1[i]<<" ";
    //x1[i][1]=temp->index;
        x2[i]=RectSort[temp->index][2];//cout<<x2[i]<<endl;
        //x2[i][1]=temp->index;
        //minn = min(minn,x1[i]);
        //maxx = max(maxx,x2[i]);
        temp=temp->next;
    }

    qsort(x2,p,sizeof(int),compare);
    qsort(x1,p,sizeof(int),compare);
     while(l<=p-1){
        //for(;x1[k]<x2[l],k<=p-1;c++,k++) cout<<k<<"alok"<<c<<endl;
        while(x1[k]<x2[l] && k<=p-1){
            k++;c++;
        }
        //if(k>p) c--;
     if(mc<c) mc=c;
    //  cout<<"CR = ";
    //  for(int i=0;i<n;i++) cout<<CR[i]<<" ";
    // cout<<endl;
     if(k>p-1) {
         //cout<<"mci1="<<mc<<" ";
         return mc;

     }

     while(x2[l]==x2[l+1] && l<p){c--;l++;}
     l++;c--;

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
//Node* temp;
//Node* t;Node* u;
int maxclique2(int RectSort[][4],int R[],int n){
Node* head=NULL;
Node* last=head;
Node* temp;
Node* t;Node* u;    
        int i=0;                                      
        int j=0;
        int mc=1;
        int s=1;
        int x1[n],x2[n];
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
        
        if(head!=NULL){s=intervalAlgo2(RectSort,head,p,x1,x2,n,mc);}
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
    // if(mc==1){
    //     CR[0]=1;
    // }
    return mc;
      
}
int intervalAlgo1(int RectSort[][5],Node* head, int p,int x1[][2],int x2[][2],int *CR,int n,int mc){
    //cout<<"p="<<p<<endl;
    // int x2[p];
    // int x1[p];
    int CR1[n]; for(int i=0;i<n;i++) {CR1[i]=0;}
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
//Node* temp;
//Node* t;Node* u;
int maxclique1(int RectSort[][5],int R[],int n,int *CR){
Node* head=NULL;
Node* last=head;
Node* temp;
Node* t;Node* u;    
        int i=0;                                      
        int j=0;
        int mc=1;
        int s=1;
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
        
        if(head!=NULL){s=intervalAlgo1(RectSort,head,p,x1,x2,CR,n,mc);}
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
        if(mc==1){
            CR[0]=1;
        }
       return mc;
  
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
//Node* temp;
//Node* t;Node* u;
int maxclique(int RectSort[][4],int R[],int n,int *CR){
Node* head=NULL;
Node* last=head;
Node* temp;
Node* t;Node* u;    
        int i=0;                                      
        int j=0;
        int mc=1;
        int s=1;
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
    if(mc==1){
        CR[0]=1;
    }
    return mc;
      
}
void print1(int n, int Rect[][5])
{int j,i;
  for (i=0;i<n;i++){
      j=0;
      while(j<5){
        if(Rect[i][j]<0)
        cout<<Rect[i][j]<<"   ";
        else  cout<<" "<<Rect[i][j]<<"   ";
        j++;
      }
      cout<<"\n";
    }
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
    
    for(i=0;i<n;i++){
        deg[i]=0;
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
           if(i==n) return IS;       // this function always return here so don't worry about p
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
           if(min==0){
               for(int i=x;i<n;i++){
                   if(deg[i]==0){
                       IS++;
                       deg[i]=-1; 
                   }
               }
               continue;
           }
           else{
               IS++;
               deg[f]=-1;
           }
           
        //    cout<<"Deleted rectangles="<<endl; 
        //    cout<<RectSort[f][0]<<" "<<RectSort[f][1]<<" "<<RectSort[f][2]<<" "<<RectSort[f][3]<<endl;
           for(j=x;j<n;j++){
                    if(A[f][j]==1){
                       deg[j]=-1;
                       for(k=x;k<n;k++){
                            if(A[k][j]==1) deg[k]--;
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
    for(i=x;i<n;i++){
        if(deg[i]<0) continue;
        deg[i]=0;
        for(j=0;j<n;j++){
            deg[i]=deg[i]+A[i][j];
        }
        if(deg[i]==0){
            IS++;
            deg[i]=-1;
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
int mindeg2(int RectSort[][4],int n){
 int A;   //Adjacency matrix
 int deg[n],i,j;
    // for(i=0;i<n;i++){
    //       A[i][i]=0;
    //     for(j=i+1;j<n;j++){
    //         if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
    //         else {
    //              A[i][j]=1;
    //              A[j][i]=1;
    //         }
    //     }
    // }
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
    for(i=x;i<n;i++){
        if(deg[i]<0) continue;
        deg[i]=0;
        for(j=0;j<n;j++){
            if(deg[j]!=-1){
                if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) A=0;
                else A=1;
                deg[i]=deg[i]+A;
            }
        }
        if(deg[i]==0){
            IS++;
            deg[i]=-1;
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
                if(deg[j]!=-1){
                    if(RectSort[f][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[f][0] || RectSort[f][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[f][1]) A=0;
                    else A=1;
                    if(A==1){
                        //cout<<j+1<<"  ";
                       deg[j]=-1;
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
    // for(i=0;i<n;i++) cout<<deg[i]<<" ";
    // cout<<endl;
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
int maxdeg2(int RectSort[][4],int n){
 int A;   //Adjacency matrix
 int deg[n],i,j;
    // for(i=0;i<n;i++){
    //       A[i][i]=0;
    //     for(j=i+1;j<n;j++){
    //         if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
    //         else {
    //              A[i][j]=1;
    //              A[j][i]=1;
    //         }
    //     }
    // }
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
            if(i!=j){
            // if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) A=0;
            // else A=1;
            deg[i]=deg[i]+!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]);
            }
        }
    }
    // for(i=0;i<n;i++) cout<<deg[i]<<" ";
    // cout<<endl;
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
               if(deg[j]>0){
                    if(RectSort[f][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[f][0] || RectSort[f][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[f][1]) A=0;
                    else A=1;
                    if(A==1){
                      deg[j]--;
                   }
               }
                 
           }
           //for(j=0;j<n;j++) A[j][f]=0;
           //p++;
           //cout<<"p="<<p<<endl;
        }while(1);
    return IS;  
}
int mindeg_minclique(int RectSort[][4],int n){             // here don't try Rect from main because we need to pass this later for maxclique where we need RectSort       
int A,RectSort1[n][4],R[n];   //Adjacency matrix
 int deg[n],i,j;
 //for(int i=0;i<n;i++) CR[i]=0;
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
                    if(i!=j){
                    // if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) A=0;
                    // else A=1;
                    deg[i]=deg[i]+!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]);
                    }
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
           if(min==0){
               for(int i=x;i<n;i++){
                   if(deg[i]==0){
                       IS++;
                       deg[i]=-1;
                   }
               }
               continue;
           }
        if(min>1){
           j=0;
           for(i=x;i<n;i++){
               if(min==deg[i]){
                   ind[j]=i;j++;
               }
           }
           k=0;
           while(k<j){
               y=0;
               for(i=x;i<n;i++){
                   if(ind[k]==i){
                       RectSort1[y][0]=RectSort[i][0];RectSort1[y][1]=RectSort[i][1];RectSort1[y][2]=RectSort[i][2];RectSort1[y][3]=RectSort[i][3];y++;
                   }
                   else{
                       if(!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1])){     // no need to add condition deg[i]!=-1 because if deg[i]==-1 then A[ind[k]][i]==1 will not true
                           RectSort1[y][0]=RectSort[i][0];RectSort1[y][1]=RectSort[i][1];RectSort1[y][2]=RectSort[i][2];RectSort1[y][3]=RectSort[i][3];y++;
                       }
                   }
               }
               for(i=0;i<y;i++) R[i]=RectSort1[i][3];
               qsort(R,y,sizeof(int),compare);
               for(int i=0,j=y-1;i<j;i++,j--){  //y2 in desc.
                     swap(&R[i],&R[j]);
                }
               c[k]=maxclique2(RectSort1,R,y);k++;
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
    
        IS++;
        deg[f]=-1;
           //cout<<"selected rectangle in this pass="<<f+1<<endl;
        //    cout<<"Deleted rectangles="<<endl; 
        //    cout<<RectSort[f][0]<<" "<<RectSort[f][1]<<" "<<RectSort[f][2]<<" "<<RectSort[f][3]<<endl;
        //cout<<"deleted rectangles= ";
        for(j=x;j<n;j++){
                if(deg[j]!=-1){
                    if(RectSort[f][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[f][0] || RectSort[f][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[f][1]) A=0;
                    else A=1;
                    if(A==1){
                        //cout<<j+1<<"  ";
                       deg[j]=-1;
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
int maxdeg_maxclique(int RectSort[][4],int n){     // here don't try Rect from main because we need to pass this later for maxclique where we need RectSort
 int A,RectSort1[n][4],R[n];   //Adjacency matrix
 int deg[n],i,j;
 //for(int i=0;i<n;i++) CR[i]=0;
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
            if(i!=j){
            // if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) A=0;
            // else A=1;
            deg[i]=deg[i]+!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]);
            }
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
           for(i=x;i<n;i++){
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
                       if(!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) && deg[i]>0){
                           RectSort1[y][0]=RectSort[i][0];RectSort1[y][1]=RectSort[i][1];RectSort1[y][2]=RectSort[i][2];RectSort1[y][3]=RectSort[i][3];y++;
                       }
                   }
               }
               for(i=0;i<y;i++) R[i]=RectSort1[i][3];
               qsort(R,y,sizeof(int),compare);
               for(int i=0,j=y-1;i<j;i++,j--){  //y2 in desc.
                     swap(&R[i],&R[j]);
                }
               c[k]=maxclique2(RectSort1,R,y);k++;
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
               if(deg[j]>0){
                    if(RectSort[f][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[f][0] || RectSort[f][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[f][1]) A=0;
                    else A=1;
                    if(A==1){
                      deg[j]--;
                   }
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
    for(int i=0;i<n;i++) CR[i]=0;
    for(int i=0;i<n;i++){
        A[i][i]=0;
        for(int j=i+1;j<n;j++){
            if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
            else {
                 A[i][j]=1;
                 A[j][i]=1;
            }
        }
   }
    // cout<<"A="<<endl;
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<A[i][j]<<"   ";
    //     }
    //     cout<<endl;
    // }
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
    //cout<<"cv="<<endl;
    for(int i=0;i<n;i++) cv[i]=0;
    //cout<<endl;
            // for(i=0;i<n;i++) cout<<deg[i]<<" ";
            // cout<<endl;
    //for(i=0;i<n;i++) if(deg[i]deg[i]=0;
    do{
    for(i=x;i<n;i++){
        if(deg[i]<0) continue;
        y=0;
        j=x;
        while(j<i){             // for correct positioning of i in RectSort1
            if(A[i][j]==1 && cv[j]!=-1 ) {
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
            if(A[i][j]==1 && cv[j]!=-1) {
                deg[i]++;
                RectSort1[y][0]=RectSort[j][0];
                RectSort1[y][1]=RectSort[j][1];
                RectSort1[y][2]=RectSort[j][2];
                RectSort1[y][3]=RectSort[j][3];
                y++;j++;
            }
            else j++;
        }
        //cout<<"RectSort1="<<endl;!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1])
        // print(n,RectSort1);
        // cout<<endl;
        // cout<<"y="<<y<<endl;
        if(y==1){deg[i]=-1;cv[i]=-1;IS++;continue;}
        for(int i=0;i<y;i++) R[i]=RectSort1[i][3];
               qsort(R,y,sizeof(int),compare);
               for(int i=0,j=y-1;i<j;i++,j--){  //y2 in desc.
                     swap(&R[i],&R[j]);
                }
            //for(int i=0;i<n;i++) CR[i]=0;
            cv[i]=maxclique(RectSort1,R,y,CR);
    } 
    // cout<<"cv=";
    // for(int i=0;i<n;i++){
    //     cout<<cv[i]<<"   ";
    // }  
    // cout<<endl; 
    // cout<<"degrees="<<endl;
    // for(i=0;i<n;i++) cout<<deg[i]<<" ";
    //   cout<<endl;
           i=x;
           while(cv[i]==-1 && i<n) {i++;}
           if(i==n) return IS;       // this function always return here so don't think about p
           x=i;
           min=cv[i];
           f=i;
           i++;
           for(;i<n;i++){
              if(cv[i]==-1) continue;
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
int ISR3(int Adj[][400],int k,int RectSort[][4],int n){
    int ISR1,ISR2;
    if(k==1){                          // Base case
        // for(int i=0;i<n;i++){
        //     if(Adj[k][i]==1){
        //         if(vert[0]==-1) return 1;
        //         for(int j=0;j<k;j++){
        //            if(A[i][vert[j]]!=1){
        //                return 1;
        //            }
        //        }
        //     }
            
        // }
        for(int i=0;i<n;i++){
            if(Adj[0][i]==1){
                return 1;
            }
        }
        return 0;     
    }
    else {
        int Adj1[k-1][400];
        int i;        // when particular rectangle taking  
        for(i=0;i<n;i++){
            //vert[x]=i;
            if(Adj[k-1][i]==1){
                for(int j=0;j<k-1;j++){
                    for(int m=0;m<n;m++){
                       if(Adj[j][m]==1 && !(RectSort[i][2]<=RectSort[m][0] || RectSort[m][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[m][1]||RectSort[m][3]>=RectSort[i][1]))
                         Adj1[j][m]=0;
                       else Adj1[j][m]=Adj[j][m];
                    }
                }
                Adj[k-1][i]=0;
                break;
            }
           
        }
        if(i==n){
                if(k>1){
                    return ISR3(Adj,k-1,RectSort,n);
                }
                else {
                    return 0;
                }
        }
        ISR1=1+ISR3(Adj1,k-1,RectSort,n);
        if(ISR1==k) return k;
        ISR2=ISR3(Adj,k,RectSort,n);
        if(ISR2==k) return k;
        if(ISR1>ISR2) return ISR1;
        else return ISR2;
    }
}
int bruteforce3(int RectSort[][4],int n,int AIS,int CR[]){    // A is a adjacency matrix 
    int IS=0,p=0,n1,RectSort1[n][5],y,mc,z,x=0,R[n];   //Adjacency matrix
    int deg[n],i,j;
    for(int i=0;i<n;i++) {CR[i]=0;deg[i]=0;}
    for(i=0;i<n;i++){
        if(deg[i]==1){
            continue;
        }
        for(j=i+1;j<n;j++){
            //deg[i]=deg[i]+A[i][j];
            if(!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1])){         // only to find 0 deg rectangles, here no need of actual deg
                deg[i]=1;
                deg[j]=1;
            }
        }
    }
    for(i=0;i<n;i++){
        if(deg[i]==0){
            p++;
            deg[i]=-1;
        }
    } 
    // cout<<"Deg="<<endl;
    // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
    IS=IS+p;    // Add Deg of 0 rectangles directly
    //cout<<"IS="<<IS<<endl;       
    n1=n-p;
    int q=2*(n-p)/3;       // max possible raws in Adj
    int Adj[q+1][400];          //info of All clique
    int k=0;
    for(int i=0;i<q+1;i++){
        for(int j=0;j<n;j++){
            Adj[i][j]=0;
        }
    }
    // cout<<"k= "<<k<<"and Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    while(n1>0){
        y=0;
        for(i=x;i<n;i++){
            if(deg[i]!=-1){
                x=i;
                break;
            }
        }
        if(i==n){
            break;
        }
        for(i=x;i<n;i++){
            if(deg[i]==-1) continue;
            RectSort1[y][0]=RectSort[i][0];
            RectSort1[y][1]=RectSort[i][1];
            RectSort1[y][2]=RectSort[i][2];
            RectSort1[y][3]=RectSort[i][3];
            RectSort1[y][4]=i;               //  indexing from RectSort1 to RectSort
            y++;    
            
        }
        //cout<<"RectSort1="<<endl;
        //print1(y,RectSort1);
        //cout<<endl;
        //int R[y];
        for(int i=0;i<y;i++) R[i]=RectSort1[i][3];
        qsort(R,y,sizeof(int),compare);
        for(int i=0,j=y-1;i<j;i++,j--){  //y2 in desc.
            swap(&R[i],&R[j]);
        }
        //cout<<"y="<<y<<endl;
        int CR1[y];
        for(int i=0;i<y;i++) CR1[i]=0;
        mc=maxclique1(RectSort1,R,y,CR1);
        //cout<<"mc="<<mc<<endl;
        // cout<<"CR1="<<endl;
        // for(int i=0;i<y;i++) cout<<CR1[i]<<"  ";
        // cout<<endl;
        n1=n1-mc;
        for(i=0;i<y;i++){
            if(CR1[i]==1){
                z=RectSort1[i][4];
                deg[z]=-1;
                Adj[k][z]=1;
            }
        }
        // cout<<"Deg="<<endl;
        // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
        // cout<<endl;
        k++;
        //for(int i=0;i<y;i++) CR[i]=0;
    }
    // cout<<"k= "<<k<<"and Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"n1 = "<<n1<<endl;
    //cout<<"p="<<p<<"   "<<"k="<<k<<"   IS="<<IS<<endl;
    if(p+k==AIS){
        return AIS;             // max IS by brute force can be atmost p+k and that can not be less than AIS
    }
    //int vert[k];               // info of previous call rectangles
    //for(int i=0;i<k;i++) vert[i]=-1;
    // cout<<"Deg="<<endl;
    // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
    // cout<<endl;
    // cout<<"Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    z=ISR3(Adj,k,RectSort,n);
    return z+IS;
}
int ISR(int Adj[][100],int k,int RectSort[][4],int n){
    int ISR1,ISR2;
    if(k==1){                          // Base case
        // for(int i=0;i<n;i++){
        //     if(Adj[k][i]==1){
        //         if(vert[0]==-1) return 1;
        //         for(int j=0;j<k;j++){
        //            if(A[i][vert[j]]!=1){
        //                return 1;
        //            }
        //        }
        //     }
            
        // }
        for(int i=0;i<n;i++){
            if(Adj[0][i]==1){
                return 1;
            }
        }
        return 0;     
    }
    else {
        int Adj1[k-1][100];
        int i;        // when particular rectangle taking  
        for(i=0;i<n;i++){
            //vert[x]=i;
            if(Adj[0][i]==1){
                for(int j=1;j<k;j++){
                    for(int m=0;m<n;m++){
                       if(Adj[j][m]==1 && !(RectSort[i][2]<=RectSort[m][0] || RectSort[m][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[m][1]||RectSort[m][3]>=RectSort[i][1]))
                         Adj1[j-1][m]=0;
                       else Adj1[j-1][m]=Adj[j][m];
                    }
                }
                Adj[0][i]=0;
                break;
            }
           
        }
        if(i==n){
            for(int i=1;i<k;i++){
                for(int j=0;j<n;j++){
                    Adj[i-1][j]=Adj[i][j];
                }
            }
            return ISR(Adj,k-1,RectSort,n);
        }
        ISR1=1+ISR(Adj1,k-1,RectSort,n);
        if(ISR1==k) return ISR1;
        ISR2=ISR(Adj,k,RectSort,n);
        if(ISR2==k) return ISR2;
        if(ISR1>ISR2) return ISR1;
        else return ISR2;
    }
}
int bruteforce(int RectSort[][4],int n,int AIS,int CR[]){    // A is a adjacency matrix 
    int IS=0,p=0,n1,RectSort1[n][5],y,mc,z,x=0,R[n];   //Adjacency matrix
    int deg[n],i,j;
    for(int i=0;i<n;i++) {CR[i]=0;deg[i]=0;}
    for(i=0;i<n;i++){
        if(deg[i]==1){
            continue;
        }
        for(j=i+1;j<n;j++){
            //deg[i]=deg[i]+A[i][j];
            if(!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1])){         // only to find 0 deg rectangles, here no need of actual deg
                deg[i]=1;
                deg[i]=1;
            }
        }
    }
    for(i=0;i<n;i++){
        if(deg[i]==0){
            p++;
            deg[i]=-1;
        }
    } 
    // cout<<"Deg="<<endl;
    // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
    IS=IS+p;    // Add Deg of 0 rectangles directly
    //cout<<"IS="<<IS<<endl;       
    n1=n-p;
    int q=2*(n-p)/3;       // max possible raws in Adj
    int Adj[q+1][100];          //info of All clique
    int k=0;
    for(int i=0;i<q+1;i++){
        for(int j=0;j<n;j++){
            Adj[i][j]=0;
        }
    }
    // cout<<"k= "<<k<<"and Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    while(n1>0){
        y=0;
        for(i=x;i<n;i++){
            if(deg[i]!=-1){
                x=i;
                break;
            }
        }
        if(i==n){
            break;
        }
        for(i=x;i<n;i++){
            if(deg[i]==-1) continue;
            RectSort1[y][0]=RectSort[i][0];
            RectSort1[y][1]=RectSort[i][1];
            RectSort1[y][2]=RectSort[i][2];
            RectSort1[y][3]=RectSort[i][3];
            RectSort1[y][4]=i;               //  indexing from RectSort1 to RectSort
            y++;    
            
        }
        //cout<<"RectSort1="<<endl;
        //print1(y,RectSort1);
        //cout<<endl;
        //int R[y];
        for(int i=0;i<y;i++) R[i]=RectSort1[i][3];
        qsort(R,y,sizeof(int),compare);
        for(int i=0,j=y-1;i<j;i++,j--){  //y2 in desc.
            swap(&R[i],&R[j]);
        }
        //cout<<"y="<<y<<endl;
        int CR1[y];
        for(int i=0;i<y;i++) CR1[i]=0;
        mc=maxclique1(RectSort1,R,y,CR1);
        //cout<<"mc="<<mc<<endl;
        // cout<<"CR1="<<endl;
        // for(int i=0;i<y;i++) cout<<CR1[i]<<"  ";
        // cout<<endl;
        n1=n1-mc;
        for(i=0;i<y;i++){
            if(CR1[i]==1){
                z=RectSort1[i][4];
                deg[z]=-1;
                Adj[k][z]=1;
            }
        }
        // cout<<"Deg="<<endl;
        // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
        // cout<<endl;
        k++;
        //for(int i=0;i<y;i++) CR[i]=0;
    }
    // cout<<"k= "<<k<<"and Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"n1 = "<<n1<<endl;
    //cout<<"p="<<p<<"   "<<"k="<<k<<"   IS="<<IS<<endl;
    if(p+k==AIS){
        return AIS;             // max IS by brute force can be atmost p+k and that can not be less than AIS
    }
    //int vert[k];               // info of previous call rectangles
    //for(int i=0;i<k;i++) vert[i]=-1;
    // cout<<"Deg="<<endl;
    // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
    // cout<<endl;
    // cout<<"Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    z=ISR(Adj,k,RectSort,n);
    return z+IS;
}
void merge_X(int RectSort[][4],int i,int mid,int j, int ind[]){
    int count1=0;
    int count2=0;
    for(int k=i;k<=mid;k++){
        if(ind[k]==1){
            count1++;
        }
    }
    for(int k=mid+1;k<=j;k++){
        if(ind[k]==1){
            count2++;
        }
    }
    if(count1>=count2){
        int x=i;
        while(ind[x]==0){x++;}
        int max=RectSort[i][3];
        for(int k=x+1;k<=mid;k++){
            if(ind[k]==1 && max<RectSort[k][3]){
                max=RectSort[k][3];
            }
        }
        for(int k=mid+1;k<=j;k++){
            if(ind[k]==1){
                if(RectSort[k][1]>=max){
                    return;
                }
                for(int l=x;l<=mid;l++){
                    if(ind[l]==1){
                        if(!(RectSort[k][2]>=RectSort[l][0] || RectSort[l][2]>=RectSort[k][0] || RectSort[k][3]<=RectSort[l][1]||RectSort[l][3]<=RectSort[k][1])){
                            ind[k]=0;
                            break;
                        }   
                    }
                }
            }

        }
    }
    else{                            // here no use of min variable logic 
        int x=mid+1;
        while(ind[x]==0) {x++;}
        int min=RectSort[x][1];
        for(int k=i;k<=mid;k++){
            if(ind[k]==1){
                if(RectSort[k][3]<=min) continue;
                for(int l=mid+1;l<=j;l++){
                    if(ind[l]==1){
                        if(!(RectSort[k][2]>=RectSort[l][0] || RectSort[l][2]>=RectSort[k][0] || RectSort[k][3]<=RectSort[l][1]||RectSort[l][3]<=RectSort[k][1])){
                            ind[k]=0;
                            break;
                        }
                    }
                }
            }
        }
    }
}
void DAC_X(int RectSort[][4], int i, int j, int ind[]){
    if(j==i){
        ind[i]=1;
    }
    else if(j==i+1){
        if(RectSort[i][2]>=RectSort[j][0] || RectSort[j][2]>=RectSort[i][0] || RectSort[i][3]<=RectSort[j][1]||RectSort[j][3]<=RectSort[i][1]){
            ind[i]=1;
            ind[j]=1;
        }
        else {
            ind[i]=1;
            ind[j]=0;
        } 
    }
    else{
        int mid=(i+j)/2;
        DAC_X(RectSort,i,mid,ind);
        DAC_X(RectSort,mid+1,j,ind);
        merge_X(RectSort,i,mid,j,ind);
    }
}
void merge_Y(int RectSort[][4],int i,int mid,int j, int ind[]){
    int count1=0;
    int count2=0;
    for(int k=i;k<=mid;k++){
        if(ind[k]==1){
            count1++;
        }
    }
    for(int k=mid+1;k<=j;k++){
        if(ind[k]==1){
            count2++;
        }
    }
    if(count1>=count2){
        int x=i;
        while(ind[x]==0){x++;}
        int min=RectSort[x][3];
        for(int k=x+1;k<=mid;k++){
            if(ind[k]==1 && min>RectSort[k][3] ){
                min=RectSort[k][3];
            }
        }
        for(int k=mid+1;k<=j;k++){
            if(ind[k]==1){
                if(RectSort[k][1]<=min){
                    return;
                }
                for(int l=x;l<=mid;l++){
                    if(ind[l]==1){
                        if(!(RectSort[k][2]<=RectSort[l][0] || RectSort[l][2]<=RectSort[k][0] || RectSort[k][3]>=RectSort[l][1]||RectSort[l][3]>=RectSort[k][1])){
                            ind[k]=0;
                            break;
                        }
                    }
                }
            }
            
        }
    }
    else{                           // here no use of min variable logic 
        int x=mid+1;
        while(ind[x]==0){x++;}
        int max=RectSort[x][1];                      // this will be max because y1 is already sorted
        for(int k=i;k<=mid;k++){
            if(ind[k]==1){
                if(RectSort[k][3]>=max) continue;
                for(int l=mid+1;l<=j;l++){
                    if(ind[l]==1){
                        if(!(RectSort[k][2]<=RectSort[l][0] || RectSort[l][2]<=RectSort[k][0] || RectSort[k][3]>=RectSort[l][1]||RectSort[l][3]>=RectSort[k][1])){
                            ind[k]=0;
                            break;
                        }
                    }
                }
            }
        }
    }
}
void DAC_Y(int RectSort[][4], int i, int j, int ind[]){
    if(j==i){
        ind[i]=1;
    }
    else if(j==i+1){
        if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]){
            ind[i]=1;
            ind[j]=1;
        }
        else {
            ind[i]=1;
            ind[j]=0;
        } 
    }
    else{
        int mid=(i+j)/2;
        DAC_Y(RectSort,i,mid,ind);
        DAC_Y(RectSort,mid+1,j,ind);
        merge_Y(RectSort,i,mid,j,ind);
    }
}
// int* checking(int Adj[][400],int Adjind[],int i1,int last,int i,int k,int x,int n){     // i1 is no. of current elements currently in Adjind, last is where new element will be inserted if required in Adjind
//     if(i1==x){
//         return Adjind;
//         int Adj1[x][400];                     //Adj for which we need to run ISR algo
//         int y=0;                              // indexes for new Adj1
//         for(int i=0;i<last;i++){
//             if(Adjind[i]==1){
//                 for(int j=0;j<n;j++){
//                     Adj1[y][j]=Adj[i][j];
//                 }
//             }
//         }
//         IS=ISR(Adj,x,RectSort,n);
//         if(IS==x){
//             return 1;
//         }
//         else return 0;
//     }
//     else{
        
//     }
// }
// int kchoosemin+i(int Adj[][400],int k,int RectSort[][4],int n,int x,int j){    //x=AIS-p+i or x=min+i
//     if(x<k){
//         int Adjind[x];
//         int 
//         int *Adjind1=checking(Adj,Adjind,0,0,0,k,x,n);               // try all combinations of k choose x and check IS in that 

//         if(IS==1){
//             j=j*2;
//             x=x+2;
//             kchoosemin+i(Adj,k,RectSort,n,x,j);
//         }
//         else if(j==1){
//             return x-j;
//         }
//         else{
//             x=x-j;
//             j=1;
//             x=x+j;
//             kchoosemin+i(Adj,k,RectSort,n,x,j);
//         }                              
//     }
//     else if(x==k){
//         IS=ISR(Adj,k,RectSort,n);
//         if(IS==k){
//             return k;
//         }
//         else{
//             if(j!=1){
//                 x=x-j;
//                 j=1;
//                 x=x+j;
//                 kchoosemin+i(Adj,k,RectSort,n,x,j);
//             }
//             else{
//                 return x-j;
//             }
//         }  
//     }
//     else{
//         x=x-j;
//         j=1;
//         x=x+j;
//         kchoosemin+i(Adj,k,RectSort,n,x,j);
//     }
// }
void makeCombiUtil(vector<vector<int> >& ans,
    vector<int>& tmp, int n, int left, int k)
{
    // Pushing this vector to a vector of vector
    if (k == 0) {
        ans.push_back(tmp);
        return;
    }
 
    // i iterates from left to n. First time
    // left will be 1
    for (int i = left; i <= n; ++i)
    {
        tmp.push_back(i);
        makeCombiUtil(ans, tmp, n, i + 1, k - 1);
 
        // Popping out last inserted element
        // from the vector
        tmp.pop_back();
    }
}
 
// Prints all combinations of size k of numbers
// from 1 to n.
vector<vector<int> > makeCombi(int n, int k)
{
    vector<vector<int> > ans;
    vector<int> tmp;
    makeCombiUtil(ans, tmp, n, 1, k);
    return ans;
}

int kchoosemin(int Adj[][100],int k,int RectSort[][4],int n,int x){
    int Adj1[x][100];
    int k1=0;int IS;
    vector<vector<int> > ans = makeCombi(k, x);
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            //cout << ans.at(i).at(j) << " ";
            for(int w=0;w<n;w++){
                Adj1[k1][w]=Adj[ans.at(i).at(j)-1][w];
            }
            k1++;
        }
        IS=ISR(Adj1,x,RectSort,n);
        if(IS==x){
            return ISR(Adj,k,RectSort,n);
        }
        //cout << endl;
    }
    return x-1;
}
int ISR4(int Adj[][100],int k,int RectSort[][4],int n,int AIS, int p){
    int j=1;int IS;
    int min=AIS-p;
    int x=min+j;
    if(x==k){
        return ISR(Adj,k,RectSort,n);
    }
    else{
        return kchoosemin(Adj,k,RectSort,n,x);
    }
}

int bruteforce4(int RectSort[][4],int n,int AIS,int CR[]){    // A is a adjacency matrix 
    int IS=0,p=0,n1,RectSort1[n][5],y,mc,z,x=0,R[n];   //Adjacency matrix
    int deg[n],i,j;
    for(int i=0;i<n;i++) {CR[i]=0;deg[i]=0;}
    for(i=0;i<n;i++){
        if(deg[i]==1){
            continue;
        }
        for(j=i+1;j<n;j++){
            //deg[i]=deg[i]+A[i][j];
            if(!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1])){         // only to find 0 deg rectangles, here no need of actual deg
                deg[i]=1;
                deg[j]=1;
            }
        }
    }
    for(i=0;i<n;i++){
        if(deg[i]==0){
            p++;
            deg[i]=-1;
        }
    } 
    // cout<<"Deg="<<endl;
    // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
    IS=IS+p;    // Add Deg of 0 rectangles directly
    //cout<<"IS="<<IS<<endl;       
    n1=n-p;
    int q=2*(n-p)/3;       // max possible raws in Adj
    int Adj[q+1][100];          //info of All clique
    int k=0;
    for(int i=0;i<q+1;i++){
        for(int j=0;j<n;j++){
            Adj[i][j]=0;
        }
    }
    // cout<<"k= "<<k<<"and Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    while(n1>0){
        y=0;
        for(i=x;i<n;i++){
            if(deg[i]!=-1){
                x=i;
                break;
            }
        }
        if(i==n){
            break;
        }
        for(i=x;i<n;i++){
            if(deg[i]==-1) continue;
            RectSort1[y][0]=RectSort[i][0];
            RectSort1[y][1]=RectSort[i][1];
            RectSort1[y][2]=RectSort[i][2];
            RectSort1[y][3]=RectSort[i][3];
            RectSort1[y][4]=i;               //  indexing from RectSort1 to RectSort
            y++;    
            
        }
        //cout<<"RectSort1="<<endl;
        //print1(y,RectSort1);
        //cout<<endl;
        //int R[y];
        for(int i=0;i<y;i++) R[i]=RectSort1[i][3];
        qsort(R,y,sizeof(int),compare);
        for(int i=0,j=y-1;i<j;i++,j--){  //y2 in desc.
            swap(&R[i],&R[j]);
        }
        //cout<<"y="<<y<<endl;
        int CR1[y];
        for(int i=0;i<y;i++) CR1[i]=0;
        mc=maxclique1(RectSort1,R,y,CR1);
        //cout<<"mc="<<mc<<endl;
        // cout<<"CR1="<<endl;
        // for(int i=0;i<y;i++) cout<<CR1[i]<<"  ";
        // cout<<endl;
        n1=n1-mc;
        for(i=0;i<y;i++){
            if(CR1[i]==1){
                z=RectSort1[i][4];
                deg[z]=-1;
                Adj[k][z]=1;
            }
        }
        // cout<<"Deg="<<endl;
        // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
        // cout<<endl;
        k++;
        //for(int i=0;i<y;i++) CR[i]=0;
    }
    // cout<<"k= "<<k<<"and Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"n1 = "<<n1<<endl;
    //cout<<"p="<<p<<"   "<<"k="<<k<<"   IS="<<IS<<endl;
    if(p+k==AIS){
        return AIS;             // max IS by brute force can be atmost p+k and that can not be less than AIS
    }
    //int vert[k];               // info of previous call rectangles
    //for(int i=0;i<k;i++) vert[i]=-1;
    // cout<<"Deg="<<endl;
    // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
    // cout<<endl;
    // cout<<"Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    for(int i=0,j=k-1;j>i;i++,j--){          //now ISR function will give bettter results
        for(int p=0;p<n;p++){
            swap(&Adj[i][p],&Adj[j][p]);
        }
    }
    z=ISR4(Adj,k,RectSort,n,AIS,p);
    return z+IS;
}
int ISR5(int Adj[][20],int k,int RectSort[][4],int n){
    // cout<<"k="<<k<<endl;
    // cout<<"Adj="<<endl;
    //  for(int i=0;i<k;i++){
    //      cout<<"Adj[i][0]= "<<Adj[i][0]<<endl;
    //     for(int j=0;j<=Adj[i][0];j++){
    //         //cout<<"i="<<i<<"j="<<j<<endl;
    //         cout<<Adj[i][j]<<"  ";
    //      }
    //      cout<<endl;
    //  }
    int ISR1,ISR2,a,b;
    if(k==1){                          // Base case
        // for(int i=0;i<n;i++){
        //     if(Adj[k][i]==1){
        //         if(vert[0]==-1) return 1;
        //         for(int j=0;j<k;j++){
        //            if(A[i][vert[j]]!=1){
        //                return 1;
        //            }
        //        }
        //     }
            
        // }
        for(int i=1;i<=Adj[0][0];i++){
            if(Adj[0][i]!=-1){
                return 1;
            }
        }
        return 0;     
    }
    else {
        int Adj1[k-1][20];
        int i;        // when particular rectangle taking  
        for(i=1;i<=Adj[k-1][0];i++){
            //vert[x]=i;
            if(Adj[k-1][i]!=-1){
                for(int j=0;j<k-1;j++){
                    Adj1[j][0]=Adj[j][0];
                    for(int m=1;m<=Adj[j][0];m++){
                        a=Adj[k-1][i];b=Adj[j][m];
                        // if(a>19||a<0||b>19||b<0){
                        //     cout<<"j="<<j<<"  m="<<m<<endl;
                        //     cout<<"Adj[j][0]= "<<Adj[j][0]<<endl;
                        //     cout<<"Adj[j][m]= "<<Adj[j][m]<<endl;
                        //     cout<<"a="<<a<<"  b="<<b<<endl;
                        //     exit(1);
                        // }
                            
                       if(Adj[j][m]!=-1 && !(RectSort[a][2]<=RectSort[b][0] || RectSort[b][2]<=RectSort[a][0] || RectSort[a][3]>=RectSort[b][1]||RectSort[b][3]>=RectSort[a][1]))
                            Adj1[j][m]=-1;
                       else Adj1[j][m]=Adj[j][m];
                    }
                }
                
                Adj[k-1][i]=-1;
                break;
            }
           
        }
        if(i>Adj[k-1][0]){
            return ISR5(Adj,k-1,RectSort,n);
        }
        ISR1=1+ISR5(Adj1,k-1,RectSort,n);
        if(ISR1==k) return k;
        ISR2=ISR5(Adj,k,RectSort,n);
        if(ISR2==k) return k;
        if(ISR1>ISR2) return ISR1;
        else return ISR2;
    }
}
int bruteforce5(int RectSort[][4],int n,int AIS,int CR[]){    // A is a adjacency matrix 
    int IS=0,p=0,n1,RectSort1[n][5],y,mc,z,x=0,R[n];   //Adjacency matrix
    int deg[n],i,j;
    for(int i=0;i<n;i++) {CR[i]=0;deg[i]=0;}
    for(i=0;i<n;i++){
        if(deg[i]==1){
            continue;
        }
        for(j=i+1;j<n;j++){
            //deg[i]=deg[i]+A[i][j];
            if(!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1])){         // only to find 0 deg rectangles, here no need of actual deg
                deg[i]=1;
                deg[j]=1;
            }     
        }
    }
    //cout<<"deg0="<<endl;
    for(i=0;i<n;i++){
        if(deg[i]==0){
            p++;
            deg[i]=-1;
            //cout<<i+1<<"   ";
        }
    } 
    //cout<<endl;
    //cout<<"p= "<<p<<endl;
    // cout<<"Deg="<<endl;
    // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
    IS=IS+p;    // Add Deg of 0 rectangles directly
    //cout<<"IS="<<IS<<endl;     
    if(p==n){
        return n;
    }  
    n1=n-p;
    int q=2*(n-p)/3;       // max possible raws in Adj
    int Adj[q+1][20];          //info of All clique
    int k=0;
    // for(int i=0;i<q+1;i++){
    //     for(int j=0;j<n;j++){
    //         Adj[i][j]=0;
    //     }
    // }
    // cout<<"k= "<<k<<"and Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    while(n1>0){
        y=0;
        for(i=x;i<n;i++){
            if(deg[i]!=-1){
                x=i;
                break;
            }
        }
        if(i==n){
            break;
        }
        for(i=x;i<n;i++){
            if(deg[i]==-1) continue;
            RectSort1[y][0]=RectSort[i][0];
            RectSort1[y][1]=RectSort[i][1];
            RectSort1[y][2]=RectSort[i][2];
            RectSort1[y][3]=RectSort[i][3];
            RectSort1[y][4]=i;               //  indexing from RectSort1 to RectSort
            y++;    
            
        }
        //cout<<"RectSort1="<<endl;
        //print1(y,RectSort1);
        //cout<<endl;
        //int R[y];
        for(int i=0;i<y;i++) R[i]=RectSort1[i][3];
        qsort(R,y,sizeof(int),compare);
        for(int i=0,j=y-1;i<j;i++,j--){  //y2 in desc.
            swap(&R[i],&R[j]);
        }
        //cout<<"y="<<y<<endl;
        int CR1[y];
        for(int i=0;i<y;i++) CR1[i]=0;
        mc=maxclique1(RectSort1,R,y,CR1);
        //cout<<"mc="<<mc<<endl;
        // cout<<"CR1="<<endl;
        // for(int i=0;i<y;i++) cout<<CR1[i]<<"  ";
        // cout<<endl;
        n1=n1-mc;
        Adj[k][0]=mc;
        int a=1;
        for(i=0;i<y;i++){
            if(CR1[i]==1){
                z=RectSort1[i][4];
                deg[z]=-1;
                Adj[k][a]=z;
                a++;
            }
        }
        // cout<<"Deg="<<endl;
        // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
        // cout<<endl;
        k++;
        //for(int i=0;i<y;i++) CR[i]=0;
    }
    // cout<<"k= "<<k<<endl;
    // cout<<"Adj="<<endl;
    //  for(int i=0;i<k;i++){
    //     for(int j=0;j<=Adj[i][0];j++){
    //          cout<<Adj[i][j]<<"  ";
    //      }
    //      cout<<endl;
    //  }
    // cout<<"n1 = "<<n1<<endl;
    //cout<<"p="<<p<<"   "<<"k="<<k<<"   IS="<<IS<<endl;
    if(p+k==AIS){
        return AIS;             // max IS by brute force can be atmost p+k and that can not be less than AIS
    }
    //int vert[k];               // info of previous call rectangles
    //for(int i=0;i<k;i++) vert[i]=-1;
    // cout<<"Deg="<<endl;
    // for(int i=0;i<n;i++) cout<<deg[i]<<"  ";
    // cout<<endl;
    // cout<<"Adj="<<endl;
    // for(int i=0;i<k;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<Adj[i][j]<<"  ";
    //     }
    //     cout<<endl;
    // }
    z=ISR5(Adj,k,RectSort,n);
    return z+IS;
}
int ISR6(int RectSort[][4],int A[],int f,int l){
    if(l==f){
        return 1;
    }
    int ISR1=0,ISR2=0;
    int A1[l-f];int l1=0;
    int i=A[f],j;
    for(int k=f+1;k<=l;k++){
        j=A[f+1];
        if(!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1])){  
            continue;
        }
        else{
            A1[l1]=j;
            l1++;   
        }
    }
    l1--;
    if(l1-(f+1)+1>0){
        ISR1=1+ISR6(RectSort,A1,0,l1);
        if(ISR1==l-f+1) return ISR1;
    }
    if(l-(f+1)+1>0){
        ISR2=ISR6(RectSort,A,f+1,l);
        if(ISR2==l-f) return ISR2;
    }
    if(ISR1>ISR2) return ISR1;
    else return ISR2;
}
int bruteforce6(int RectSort[][4],int n){
    int deg[n],i,j,A[n],p=0,IS;
    for(int i=0;i<n;i++) {deg[i]=0;}
    for(i=0;i<n;i++){
        if(deg[i]==1){
            continue;
        }
        for(j=i+1;j<n;j++){
            //deg[i]=deg[i]+A[i][j];
            if(!(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1])){         // only to find 0 deg rectangles, here no need of actual deg
                deg[i]=1;
                deg[j]=1;
            }     
        }
    }
    //cout<<"deg0="<<endl;
    int l=0;              // last index of value present in A
    for(i=0;i<n;i++){
        if(deg[i]==0){
            p++;
            //deg[i]=-1;
            //cout<<i+1<<"   ";
        }
        else {
            A[l]=i;
            l++;
        }
    }
    l--; 
    IS=p;
    if(l>=0){
        int z=ISR6(RectSort,A,0,l);
        return z+IS;
    } 
    else return IS;   
}
int main()
 {  time_t start, end;
    int a,i,j,c,IS1,IS2,IS3,IS4,IS5,IS6,IS7,IS8,IS9,count=0,count1=0,count2=0,k=0,z=0,ISR,IS[7],AIS;
    int IS_DAC;int ISR3;int ISR4;int ISR5;
    int lower,upper;
    int width,height;
    double time_taken;
    //cout<<"no. of Rectangles\n";
    //cin>>n;
    int n = 5;
    //cout<<"n = "<<n<<endl;
    int Rect[n][4];int CR[n];       //CR[n] is Rectangles responsible for clique
    int RectSort[n][4];int ind[n];int R[n];
    for(int i=0;i<n;i++) CR[i]=0;
    //cout<<"Enter lower limit and upper limit(means Range) for upper left coordinate\n";
    //cin>>lower>>upper;// range of upper left point will be given by this
    lower  = -5;
    upper = 5;
    //cout<<"Enter max width and height\n";
    //cin>>width>>height;
    width = height = 5;
    //height = 1;  // for unit height rectangles
    //for(unsigned long long int i=0;i<999999;i++){
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
        // RectSort[0][0]=-5;RectSort[0][1]=5;RectSort[0][2]=-1;RectSort[0][3]=2;
        // RectSort[1][0]=2;RectSort[1][1]=3;RectSort[1][2]=7;RectSort[1][3]=2;
        // RectSort[2][0]=3;RectSort[2][1]=0;RectSort[2][2]=8;RectSort[2][3]=-4;
        // RectSort[3][0]=-2;RectSort[3][1]=0;RectSort[3][2]=0;RectSort[3][3]=-5;
        // RectSort[4][0]=4;RectSort[4][1]=-5;RectSort[4][2]=8;RectSort[4][3]=-6;

        // RectSort[0][0]=2;RectSort[0][1]=5;RectSort[0][2]=4;RectSort[0][3]=2;
        // RectSort[1][0]=-1;RectSort[1][1]=4;RectSort[1][2]=4;RectSort[1][3]=0;
        // RectSort[2][0]=3;RectSort[2][1]=4;RectSort[2][2]=8;RectSort[2][3]=0;
        // RectSort[3][0]=2;RectSort[3][1]=1;RectSort[3][2]=5;RectSort[3][3]=-2;
        // RectSort[4][0]=-2;RectSort[4][1]=1;RectSort[4][2]=0;RectSort[4][3]=-4;

        // RectSort[0][0]=1;RectSort[0][1]=5;RectSort[0][2]=3;RectSort[0][3]=1;  // input for 10 rectangles
        // RectSort[1][0]=-5;RectSort[1][1]=4;RectSort[1][2]=-3;RectSort[1][3]=1;
        // RectSort[2][0]=1;RectSort[2][1]=3;RectSort[2][2]=6;RectSort[2][3]=-2;
        // RectSort[3][0]=0;RectSort[3][1]=2;RectSort[3][2]=4;RectSort[3][3]=-1;
        // RectSort[4][0]=2;RectSort[4][1]=1;RectSort[4][2]=6;RectSort[4][3]=-4;
        //     RectSort[5][0]=4;RectSort[5][1]=1;RectSort[5][2]=6;RectSort[5][3]=-4;
        // RectSort[6][0]=1;RectSort[6][1]=0;RectSort[6][2]=5;RectSort[6][3]=-2;
        // RectSort[7][0]=-2;RectSort[7][1]=-3;RectSort[7][2]=1;RectSort[7][3]=-6;
        // RectSort[8][0]=2;RectSort[8][1]=-4;RectSort[8][2]=4;RectSort[8][3]=-6;
        // RectSort[9][0]=3;RectSort[9][1]=-5;RectSort[9][2]=6;RectSort[9][3]=-9;

         RectSort[0][0]=-1;RectSort[0][1]=4;RectSort[0][2]=4;RectSort[0][3]=2;
         RectSort[1][0]=-3;RectSort[1][1]=2;RectSort[1][2]=-1;RectSort[1][3]=-1;
         RectSort[2][0]=-2;RectSort[2][1]=0;RectSort[2][2]=0;RectSort[2][3]=-2;
         RectSort[3][0]=5;RectSort[3][1]=-3;RectSort[3][2]=6;RectSort[3][3]=-7;
         RectSort[4][0]=5;RectSort[4][1]=-3;RectSort[4][2]=6;RectSort[4][3]=-6;
        //RectSort[5][0]=-5;RectSort[5][1]=-3;RectSort[5][2]=0;RectSort[5][3]=-8;
        cout<<"Input="<<endl;
        print(n,RectSort);
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
        //IS1=mindeg(RectSort,n);cout<<"IS by Min Deg IS0="<<IS1<<endl;
        IS[0]=mindeg2(RectSort,n);cout<<"IS by Min Deg RectSort IS[0]="<<IS[0]<<endl;   // logic is exactly same as mindeg but space is O(n) here but in mindeg there is O(n2) because of A[n][n]
        //IS[2]=mindeg2(Rect,n);cout<<"By min deg Rect IS[2]="<<IS[2]<<endl;
        IS[4]=mindeg_minclique(RectSort,n);cout<<"IS by Min Deg Min clique IS[4]="<<IS[4]<<endl;
        //IS2=maxdeg(RectSort,n); cout<<"IS by Max Deg IS2="<<IS2<<endl;
        IS[1]=maxdeg2(RectSort,n);cout<<"IS by Max Deg RectSort IS[1]="<<IS[1]<<endl;
        //if(IS1!=IS2){ cout<<"wrong output"<<endl;cout<<endl; print(n,RectSort);cout<<endl;c=maxclique(RectSort,R,n);cout<<"Clique="<<c<<endl;cout<<"IS by Min Deg="<<IS1<<endl;cout<<"IS by Max Deg="<<IS2<<endl;break;if(IS1>IS2) {count1++;if(k<(IS1-IS2)) {k=IS1-IS2;z=1;}}else {count2++;if(k<=(IS2-IS1)){k=IS2-IS1;z=2;}}}
        //IS3=mindeg1(RectSort,n); cout<<"IS by Min Deg1="<<IS3<<endl;
        //cout<<"IS by Min Deg Vector="<<IS4<<endl;
        //cout<<"Alok Kumar";
    
        //IS[3]=maxdeg2(Rect,n);cout<<"By max deg Rect IS[3]="<<IS[3]<<endl;
            // don't use Rect here instead of RectSort because in this function, we need RectSort
        IS[5]=maxdeg_maxclique(RectSort,n);cout<<"IS by Max Deg Max clique IS[5]="<<IS[5]<<endl;
        //for(int i=0;i<n;i++) ind[i]=0;
        DAC_Y(RectSort,0,n-1,ind);      // dividing Y-axis via X-axis
        IS_DAC=0;
        for(int i=0;i<n;i++){
            if(ind[i]==1){
                IS_DAC++;
            }
        }
        cout<<"IS by DAC_Y Dividing Y-axis is = "<<IS_DAC<<endl;
        int RectSort1[n][4];    // Coordinate changing to apply logic dividing X-axis via Y-axis bacause we can use quicksort function directly
        for(int i=0;i<n;i++){
            RectSort1[i][0]=RectSort[i][1];
            RectSort1[i][1]=RectSort[i][0];
            RectSort1[i][2]=RectSort[i][3];
            RectSort1[i][3]=RectSort[i][2];
        }
        quickSort(RectSort1, 0, n - 1);
        //print(n,RectSort1);
        // for(int i=0,j=n-1;i<j;i++,j--){     // converting decsending order but don't convert in descending order because we need x coordinate in ascending order
        //   swap(&RectSort1[i][0],&RectSort1[j][0]);
        //   swap(&RectSort1[i][1],&RectSort1[j][1]);
        //   swap(&RectSort1[i][2],&RectSort1[j][2]);
        //   swap(&RectSort1[i][3],&RectSort1[j][3]);
        // }
        //for(int i=0;i<n;i++) ind[i]=0;
        DAC_X(RectSort1,0,n-1,ind);
        IS_DAC=0;
        for(int i=0;i<n;i++){
            if(ind[i]==1){
                IS_DAC++;
            }
        }
        cout<<"IS by DAC_X Dividing X-axis is = "<<IS_DAC<<endl;
        //IS[6]=minclique_mindeg(RectSort,n,CR);cout<<"IS by Min clique Min Deg IS9="<<IS[6]<<endl;
        
        // AIS=IS[0];            // AIS is approx IS
        // for(int i=1;i<6;i++){
        //     if(AIS<IS[i]){
        //         AIS=IS[i];
        //     }
        // }
        // cout<<"AIS= "<<AIS<<endl;
        // int A[500][500];
        // for(int i=0;i<n;i++){
        //     A[i][i]=0;
        //     for(int j=i+1;j<n;j++){
        //         if(RectSort[i][2]<=RectSort[j][0] || RectSort[j][2]<=RectSort[i][0] || RectSort[i][3]>=RectSort[j][1]||RectSort[j][3]>=RectSort[i][1]) {A[i][j]=0;A[j][i]=0;}
        //         else {
        //              A[i][j]=1;
        //              A[j][i]=1;
        //         }
        //     }
        // } 
        //  time(&start);  
        //ISR=bruteforce(RectSort,n,AIS,CR);cout<<"Brute force IS = "<<ISR<<endl;
        // time(&end);
        // time_taken = double(end - start);
        // cout << "Time taken by program is : " << fixed
        //     << time_taken << setprecision(5);
        // cout << " sec " << endl;
        //  time(&start);
        // ISR3=bruteforce3(RectSort,n,AIS,CR);cout<<"Brute force3 IS = "<<ISR3<<endl; // start from k-1 in Adj
        // //if(AIS!=ISR){cout<<"AIS="<<AIS<<endl;cout<<"ISR="<<ISR<<endl;cout<<"input="<<endl;print(n,RectSort);cout<<endl;break;}
    
        // time(&end);
        // time_taken = double(end - start);
        // cout << "Time taken by program is : " << fixed
        //     << time_taken << setprecision(5);
        // cout << " sec " << endl;
        // time(&start);
        // ISR4=bruteforce4(RectSort,n,AIS,CR);cout<<"Brute force4 IS = "<<ISR4<<endl;    // k choose x logic applied 
        // time(&end);
        // time_taken = double(end - start);
        // cout << "Time taken by program is : " << fixed
        //     << time_taken << setprecision(5);
        // cout << " sec " << endl;
        time(&start);
        ISR5=bruteforce5(RectSort,n,AIS,CR);cout<<"Brute force5 IS = "<<ISR5<<endl;
        //ISR3=bruteforce3(RectSort,n,AIS,CR);cout<<"Brute force3 IS = "<<ISR3<<endl; // start from k-1 in Adj
        time(&end);
        time_taken = double(end - start);
        cout << "Time taken by program is : " << fixed
            << time_taken << setprecision(5);
        cout << " sec " << endl;

    
        //int ISR6=bruteforce6(RectSort,n);cout<<"Brute force6 IS = "<<ISR6<<endl;
        // if(ISR3!=AIS){
        //     cout<<"MIS!=AIS"<<endl;;
        //     print(n,RectSort);
        //     break;
        // }
        // if(ISR3!=ISR4){
        //     print(n,RectSort);
        //     cout<<endl;
        //     cout<<"ISR3!=ISR4";
        // }
    //}// same code run many times
    //count=count1+count2;
    //cout<<"count1="<<count1<<"  "<<"count2="<<count2<<"  "<<"total="<<count<<"  k="<<k<<"  z="<<z<<endl;
    //if(IS1!=IS7){cout<<"IS by Min Deg IS1="<<IS1<<endl;cout<<"IS by Min Deg Min clique IS7="<<IS7<<endl;break;}
    return 0;
 
}












