// run this:
// mex mexReadDPX8.cpp DPX.cpp DPXHeader.cpp InStream.cpp Reader.cpp Codec.cpp ElementReadStream.cpp

#include "mex.h"
#include "matrix.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "DPX.h"

using namespace std;

void readDPXresolution(char* filename, int& height, int& width)
{
    // open the image
	InStream img;
	if (!img.Open(filename))
	{
		cout << "Unable to open file " << filename << endl;
	}
    
    dpx::Reader dpx;
	dpx.SetInStream(&img);
	if (!dpx.ReadHeader())
	{
		cout << "Unable to read header" << endl;
	}
    
    height = dpx.header.Height();
	width = dpx.header.Width();
	
	img.Close();
    
}

void readDPX(char* filename, char* arr)
{
	int offset = 1;
// 	bool write8bit = false;
	bool write8bit = true;

	// open the image
	InStream img;
	if (!img.Open(filename))
	{
		cout << "Unable to open file " << filename << endl;
	}
	
	dpx::Reader dpx;
	dpx.SetInStream(&img);
	if (!dpx.ReadHeader())
	{
		cout << "Unable to read header" << endl;
	}

	// data size, override if user specifies
	dpx::DataSize size = dpx.header.ComponentDataSize(0);
	int nob = dpx.header.ComponentByteCount(0);
	if (write8bit)
	{
		size = dpx::kByte;
		nob = 1;
	}

	if (dpx.ReadImage(arr, size, dpx.header.ImageDescriptor(0)) == false)
	{
		cout << "unable to read image data " << size << endl;
	}

	img.Close();
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //
    char* filename = mxArrayToString(prhs[0]);
    
    int height = 0;
    int width = 0;
    readDPXresolution(filename, height, width);
    
    int elements = height * width * 3;
    vector<unsigned char> arr(elements,0);
    
	readDPX( filename, reinterpret_cast<char*>(&(arr[0])) );
    
    //
    UINT8_T *dynamicData;
    mwSize index, index_color, index_width, index_height;
    
    // Create a local array and load data
    dynamicData = (UINT8_T*)mxCalloc(elements, sizeof(UINT8_T));

    // save arr to dynamicData: 
    index = 0;
    for ( index_color = 0; index_color < 3; index_color++ )
    {
        for ( index_width = 0; index_width < width; index_width++ )
        {
            for ( index_height = 0; index_height < height; index_height++ )
            { 
                dynamicData[index] = arr[ (width*index_height+index_width)*3+index_color ];
                index++;
            }
        }
    }
    
    // Create a 3-D mxArray; you will allocate the memory dynamically
    mwSize ndim = 3;
    mwSize dims[] = {height,width,3};
    plhs[0] = mxCreateNumericArray(ndim, dims, mxUINT8_CLASS, mxREAL);

    // Point mxArray to dynamicData
    mxSetData(plhs[0], dynamicData);
    
    int flag = mxSetDimensions(plhs[0], dims, ndim);
    
    // must be removed
    // mxFree(dynamicData); 
    
}