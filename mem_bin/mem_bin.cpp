
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>

using std::cout;
using std::ifstream;
using std::ios;

ifstream  fp;  
int val;  

int length_arr(char *filename);
int copy_to_array(char * filename,int * arr_type);
int main( int argc, char *argv[] )
{
  SYSTEMTIME  beg;
  char * keyfile="key.pc.db";
  char * seekfile="seek.pc.db";
  int lenarr_key =length_arr(keyfile);
  int lenarr_seek=length_arr(seekfile);
  //printf("%d\n",lenarr_key);  
  //printf("%d\n",lenarr_seek);
  int * S=new int [lenarr_seek];
  int * K=new int [lenarr_key]; 
  int * hit=new int [lenarr_seek];
  copy_to_array("seek.pc.db", S);
  GetLocalTime( &beg );
  printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
  beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
  copy_to_array("key.pc.db", K);
  
  for (int i=0;i<=lenarr_seek-1;i++)
  {
	   int start= 0;
	   int last=lenarr_key-1 ;
	   hit[i]=0;
		while(last>=start)
		{
		  int mid_point = start+((last-start)/2);
		   	
		  if (S[i]<K[mid_point])
		  {
		  last=mid_point-1;
		  }
		  else if (S[i]==K[mid_point])
		  {
		  hit[i]=1;
		  break;
		  }
		  else
		  {
		  start=mid_point+1;
		  }
		}
  }
  GetLocalTime( &beg );
  printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
  beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
  for (int i=0;i<=lenarr_seek-1;i++)
  printf( "%6d: %d\n", S[ i ], hit[ i ] );
  _getch();
  return 1;
}	
  
int length_arr(char * filename)
{
  //cout<<filename; 	
  fp.open( filename, ios::in | ios::binary );
  int first_byte_addr=fp.tellg();
  fp.seekg(0,ios::end);
  int last_byte_addr=fp.tellg();
  int tot_elements=(last_byte_addr-first_byte_addr)/sizeof(int);
  fp.close();
  return tot_elements;
}

int copy_to_array(char * filename, int * arr_type)
{
  int i=0; 	
  fp.open( filename, ios::in | ios::binary );
  fp.seekg(0,ios::beg);
  fp.read( (char *) &val, (int) sizeof( int ) );
  while( !fp.eof() ) {
	*(arr_type+i)=val;

    //cout << *(arr_type+i) << "\n";
    fp.read( (char *) &val, (int) sizeof( int ) );
	i++;
  }
  //cout<<i<<"\n";
  fp.close();
  return 0;
}




