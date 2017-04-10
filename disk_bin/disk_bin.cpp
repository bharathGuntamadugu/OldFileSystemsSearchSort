
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
  int * disk_binary(char * filename, int * S);

  int lenarr_key;
  int lenarr_seek;

  char * keyfile="key.pc.db";
  char * seekfile="seek.pc.db";

int main(  )
{
  SYSTEMTIME  beg;
  
  lenarr_key =length_arr(keyfile);
  lenarr_seek=length_arr(seekfile);

  //printf("%d\n",lenarr_key);  
  //printf("%d\n",lenarr_seek);
  int * S=new int [lenarr_seek];
  int * K=new int [lenarr_key]; 

  copy_to_array("seek.pc.db", S);
  GetLocalTime( &beg );
  printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
  beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
  int * hit=disk_binary("key.pc.db", S);
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
int * disk_binary(char * filename, int * S)
{
  int i=0;
  int * hit=new int [lenarr_seek];
  fp.open( filename, ios::in | ios::binary );
  
 for (int j=0;j<=lenarr_seek-1;j++)
 {

  hit[j]=0;	 	 
  fp.seekg(0,ios::beg);
  int start=fp.tellg();
  fp.seekg(-1*sizeof(int),ios::end);
  int last_byte=fp.tellg();
  int last=((last_byte)/sizeof(int));
  fp.seekg(0,ios::beg);


  while(last>=start)
  {
  int mid=start+((last-start)/2);
  fp.seekg((mid)* sizeof(int));
  fp.read( (char *) &val, (int) sizeof( int ) );
  if(S[j]>val)
  {
  start=mid+1;
  }
  else if(S[j]<val)
  {
  last=mid-1;
  }
  else  
  {
  hit[j]=1;
  break;
  }
  }

  
  //while( !fp.eof() ) {
	
		// 
  //  //cout << *(arr_type+i) << "\n";
  //  fp.read( (char *) &val, (int) sizeof( int ) );
  }
//  cout<<j<<"\n";
  //cout<<i<<"\n";
  fp.close();
  return hit;
}



