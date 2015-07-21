//Contestant ID: 02-0861-0001
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>

using namespace std;

//This program is meant to analyze GPS coordinates and used to calculate distances between locations.
//Contains a pause method for judge viewing.
namespace PauseMethod
{
	//pauses the console for judge viewing :).
	void pause()
	{
		string w;
		getline(cin, w);
	}
}


namespace StringSplitFunctions
{
	//Not the most efficient but decent implementations for a competitition.

	//Replaces part of the string with another string.
	//Pass in the original, and the delimiter.
	//Replaces delimiter with the 'replaceWith' parameter.
	void replacePart(string& original, string delim, string replaceWith)
	{
		while (original.find(delim) != -1)
		{
			original.replace(original.find(delim), delim.size(), replaceWith);
		}
	}


	//splits the string and puts it in a vector to be returned :).
	//using this to split up the commas on the lines.
	void splitString(vector<string>& returner, string str, string delim, char op = 0)
	{
		string op2("");
		op2 += op;
		replacePart(str, delim, op2);
		istringstream stream(str);

		while (stream)
		{
			string n;

			getline(stream, n, op);

			if (n.size() == 0 || (n[0] == 0 && n.size() == 1)) //avoids returning empty strings.
			{
				//nothing
			}
			else
			{
				//something.
				returner.push_back(n);
			}
		}


	}
}


//This is the class GPSPoint that is used to compute distances between the coordinates.
class GPSPoint
{
public:
	GPSPoint() :
		m_latitude(0),
		m_longitude(0)
	{

	}

	//Constructors take input to initialize data.
	GPSPoint(double latitude, double longitude) : 
													m_latitude(latitude), //initializing.
													m_longitude(longitude)
	{

	}

	//Copy constructor.
	GPSPoint(const GPSPoint& g) :
							m_latitude(g.latitude()), //initializing
							m_longitude(g.longitude())
	{

	}

	~GPSPoint()
	{

	}


	
	//Calculates the distance between the GPS coordinates in sequential order.
	static double CalculateTotalDistance(vector<GPSPoint>& vecs)
	{
		//return 0;
		return CalculateTotalDistance((GPSPoint*)&vecs[0], vecs.size()); //gets the data pointer from the vector.
	}


	
	//Calculates the distance between the GPS Coordinates in sequential order.
	static double CalculateTotalDistance(GPSPoint* arr, int count)
	{

		double total = 0;
		GPSPoint last;
		for (int i = 0; i < count; i++)
		{
			if (i == 0)
			{
				//Don't calculate with it xP.
			}
			else
			{
				total += arr[i].distanceTravelled(last);
			}

			last = arr[i];
		}


		return total;

	}
	

	//set latitude
	void latitude(double x)
	{
		m_latitude = x;
	}

	//get latitude
	double latitude() const
	{
		return m_latitude;
	}

	//set longitude
	void longitude(double x)
	{
		m_longitude = x;
	}
	
	//get longitude
	double longitude() const
	{
		return m_longitude;
	}


	//Haversine formula implementation :)
	//Gets the distance travelled between these points.
	double distanceTravelled(const GPSPoint& g)
	{
		//r is the radius of the earth
		double r = 6370;

		double sineLat = dsin((g.latitude() - latitude())/2); // sine of the latitudes
		double sineLon = dsin((g.longitude() - longitude()) / 2); // sine of the longitudes


		double cosineLatitude1 = dcos(latitude()); //cosines
		double cosineLatitude2 = dcos(g.latitude());

		//square them.
		sineLat *= sineLat; 
		sineLon *= sineLon;

		//compute the inner section of the Haversine forumula.
		double inner = sineLat + cosineLatitude1 * cosineLatitude2 * sineLon;
		//compute the distance.
		double d = 2 * r * asin(sqrt(inner));

		return d;
	}

private:
	double m_latitude, m_longitude;

	//converts degrees to radians.
	double dcos(double v)
	{
		return cos(v * 3.14159265 / 180);
	}

	//converts degrees to radians.
	double dsin(double v)
	{
		return sin(v * 3.14159265/180);
	}

};


//Issue Addressed
//Issue: Without proper input example data, how are we supposed to know if the algorithm implementation works completely?
//I implemented the formula and I'm getting answers I would expect.
//But I can't be sure.

//But one thing. I am concerned that the true distance between NY and France may not correlate with this problem.
//Try testing the two coordinates you had with the algorithm.
//Also, did the algorithm online use data that includes routing distance of planes? Like Google?
//The implementation has similar results, but a bit smaller of a distance. Could the radius inaccuracy be a factor?
//There are just inaccuracies that could affect the prompt.

//This is the main method that will be executed upon calling the program
int main(int argC, char* args[])
{
	//file input.
	ifstream input("335-C++-Student Data.txt"); //issue : the prompt has a different file name than the data from the flash drive.
	//ifstream input("Student Data 335.txt"); //uncomment this and comment the line above in case of this situation.


	/*
	//Prompt inaccuracies may have affected the distance :\ 
	GPSPoint a(48.8567, 2.3508);
	GPSPoint b(40.7127, 74.0059);
	
	cout << a.distanceTravelled(b) << endl;
	//5514.04
	*/

	if (input.good() && !input.bad())
	{
		//The File exists!

		
		vector<GPSPoint> points;  //array is utilized to hold poijts
		
		//loop until end of the file.
		while (!input.eof())
		{
			string line;
			getline(input, line); //gets a line from the file and puts into 'line'.

			//gets a vector to split strings into.
			vector<string> arr;
			StringSplitFunctions::splitString(arr, line, ","); //split it up.

			//gets the latitude and longitude as doubles.
			double lat = stod(arr[0]);
			double lon = stod(arr[1]); 

			GPSPoint point(lat, lon); //creates the point.
			points.push_back(point);
	
		}


		//Output the answer.
		cout << "The distance travelled is : ";
		printf("%.2f", GPSPoint::CalculateTotalDistance(points));
		cout << " km." << endl;
	}
	else
	{
		//the file is not accessible.
		cout << "The input file is not accessible." << endl;
	}


	input.close(); //closes the file.
	PauseMethod::pause(); //pauses execution for judge viewing.
	return 0;
}



