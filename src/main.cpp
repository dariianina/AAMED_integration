#include <experimental/filesystem>
#include <fstream>
#include <string>
#include <set>
#include <stdexcept>
#include "FLED.h"
using namespace std;
namespace fs = experimental::filesystem;
/* 
Created by daria
12/10/20
*/

void processImage(string filepath, string savePath, bool doOutput);
void outputToTxt(ofstream &ellipseCoordFile, string savePath, float** ellipses, int& ellipsesCount);


int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		try
		{
			string filepath = argv[1];

			string saveDir = "ellipse_cache";
			if (!fs::is_directory(saveDir) || !fs::exists(saveDir))
			{
				fs::create_directory(saveDir);
			}

			string fileFormat = filepath.substr(filepath.find_last_of(".") + 1);
			string savePath = "";
			if(fileFormat == "png" or fileFormat == "jpg"
			 or fileFormat == "jpeg" or fileFormat == "bmp" or fileFormat == "tiff") 
			{
				savePath = filepath;
				savePath = savePath.replace(filepath.find_last_of(".") + 1, fileFormat.length(), "txt");
			}
			else
			{
				cout << "File format is wrong: "<< fileFormat << " . Accepting png, jpg, jpeg, bmp, tiff." << endl;
				return 0;
			}
			size_t last_pos = -1;
			size_t found_pos = savePath.find("/");
			do
			{
				try
				{
					savePath = savePath.replace(found_pos, 1, "__");
				}
				catch (const out_of_range& oor)
				{
					break;
				}
				last_pos = found_pos;
				size_t found_pos = savePath.find("/");
			}
			while(found_pos!= -1 && found_pos < savePath.length() && found_pos != last_pos);

			if(argc > 2) savePath = argv[2];
			else savePath = saveDir + "/" + savePath;
			processImage(filepath, savePath, true);
		}
		catch (const out_of_range& oor) 
		{
			cerr << "Out of Range error: arguments of main " << oor.what() << endl;
		}
		return 0;
	}
    else cout << "Pass the file path." << endl;
	return 0;
}

void processImage(string filepath, string savePath, bool doOutput)
{
	Mat imgC, imgG;
	try{
	imgC = cv::imread(filepath);
	cv::cvtColor(imgC, imgG, CV_RGB2GRAY);
	cv::resize(imgG, imgG, cv::Size(imgG.cols * 0.5, imgG.rows * 0.5), 0, 0, CV_INTER_LINEAR);
	}
	catch( cv::Exception& e )
	{
	const char* err_msg = e.what();
    cout << "OpenCV exception caught. File is probably not found. " << err_msg << endl;
    return;
    }
	AAMED aamed(540, 960);
	aamed.SetParameters(CV_PI / 3, 3.4, 0.77);
	aamed.run_FLED(imgG);

	int ellipsesCount = 0;
	float** ellipses = aamed.getEllipses(ellipsesCount);
	if(ellipsesCount==0) return;
	ofstream ellipseCoordFile;
	if(doOutput) outputToTxt(ellipseCoordFile, savePath, ellipses, ellipsesCount);
}

void outputToTxt(ofstream &ellipseCoordFile, string savePath, float** ellipses, int& ellipsesCount)
{
	ellipseCoordFile.open(savePath);
	if (!ellipseCoordFile)
	{
		cout << "Problem with the output to the file " + savePath + ".";
		return;
	}
			
	for(int i = 0; i < ellipsesCount; i++)
	{
		ellipseCoordFile << to_string(ellipses[i][0]) + " " + to_string(ellipses[i][1])
			 + " " + to_string(ellipses[i][2]) + " " + to_string(ellipses[i][3])
			 + " " + to_string(ellipses[i][4]) + " " + to_string(ellipses[i][5]) + "\n";
	}		
	ellipseCoordFile.close();

}