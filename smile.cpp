#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

#define sigLen 4

//const regex PNG_SIGNATURE (".*PNG\n*.*"/*.?\n.?\n\0\0\0.+"*/); // This the PNG signature

bool isJPEG(string header, string ext);
bool isPNG(string header, string ext);

enum extension{jpeg,png,err};

struct Image{
	string path;
	fstream raw;
	enum extension ext;
	
};

int main(int argc, char * const argv[]){
	if(argc == 1){
		cerr << "No arguments given!" << endl;
		return -1;
	} 
	
	struct Image image;
  image.path = argv[argc-1];
  
  image.raw.open(image.path, ios::in | ios::app);  //Open file using user-defined path
  if (image.raw.is_open()){  //Check if image file opened
    char header[sigLen];
    image.raw.read(header,sigLen);
    string ext = image.path.substr(image.path.find_last_of(".")+1);
    //cout << "Header: " << header << " Extension: " << ext << endl;
  	image.ext = isJPEG(header, ext)? jpeg : isPNG(header, ext)? png : err;
  	switch (image.ext){
  		case jpeg:
  			cout << "This file is a JPEG" << endl;
  			break;
  		case png:
  			 cout << "This file is a PNG" << endl;
  			 break;
  		default:
  			cout << "This file is not a recognized image" << endl;
  			return -1;
  	}
  	char option = 'q';
  	for(int x=1;x<argc-1;x++){
			//cout << argv[x] << endl;
			string arg = argv[x];
			if (arg.length() == 2 && arg.at(0) == '-'){
				option = arg.at(1);
				//cout << "Selection: " << option << endl;
			}
			else{
				//cout << "Selection: " << option << endl;
				switch(option){
					case 'k':
						cout << "Keyword: " << arg << endl;
						break;
					case 'c':
						cout << "This is the creator name option" << endl;
						break;
					default:
						cout << "invalid option" << endl;
				}
			}
		}
  } 
  else cerr << "Your file couldn't be opened" << endl;

  image.raw.close();
  return 0;
}

bool isJPEG(string header, string ext){
  const char JPEG_SIGNATURE[sigLen] = {-1,-40,-1,-32}; // This is the "magic" number at the start of every jpg file
  return header == JPEG_SIGNATURE && (ext == "jpg" || ext == "jpeg");
}
bool isPNG(string header, string ext){
  return header.substr(1,3) == "PNG" && ext == "png";
}
