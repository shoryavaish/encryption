#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
int main(int argc,char *argv[])
{   char *c,y,ch,a[4],temp[100];
    int l=0,i=0,j=1,k,m=0;
	ifstream ifile;

	if(argc!=2)
	  cout<<"Fewer arguments\n";

	ifile.open(argv[1],ios::binary);

    if(ifile.fail())
	  cout<<"file not open:";

    while(argv[1][m]!='\0')
    {
        temp[m]=argv[1][m];
        m++;
            }
    temp[m]='\0';
  cout<<temp;
  //DECRYPTION
if(strcmp(strchr(argv[1],'.'),".sk")==0)
	{
	  ifile.read((char*)&ch,sizeof(ch));
	  while(ch!='*')
	  {
	      k=i+j;
	      i=j;
	      j=k;
	      ch=ch-k;
	      a[l++]=ch;
	      ifile.read((char*)&ch,sizeof(ch));
	  }
	  a[l]='\0';
	  c=a;
	  strcpy(strchr(argv[1],'.'),c);

	  ofstream ofile(argv[1],ios::binary);
	  if(ofile.fail())
        {cout<<"Out file not opened:";
          exit(0);
        }
	  while(ifile.read((char*)&ch,sizeof(ch))!='\0')
	  {
	      k=i+j;
	      i=j;
          j=k;
	      ch=ch-k;
	      ofile.write((char*)&ch,sizeof(ch));
	  }
	  cout<<"File is Decrypted...";
	  ofile.close();
	}
	//CRYPTION
	else
	{

		c=strchr(argv[1],'.');
		while(*c!='\0')
        {
            a[l++]=*c;
            c++;
        }
	    strcpy(strchr(argv[1],'.'),".sk");
		ofstream ofile(argv[1],ios::binary);
		y='*';
        l=0;
	    while(l<=3)
	    {
	    	k=i+j;
			i=j;
			j=k;
			a[l]+=k;
			ofile.write((char*)&a[l],sizeof(a[l]));
			l++;
		}
		ofile.write((char*)&y,sizeof(y));
		while(ifile.read((char*)&ch,sizeof(ch))!='\0')
		{
			k=i+j;
			i=j;
			j=k;
			ch=ch+k;
			ofile.write((char*)&ch,sizeof(ch));
		}
        cout<<"File is encrypted...";
		ofile.close();
   }
   ifile.close();
   char t[100];
   sprintf(t,"del %s",temp);
   cout<<t;
   system(t);
		return 0;
}
