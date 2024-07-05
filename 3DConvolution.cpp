
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;


//CV_8UC1 is used to define a single-channel matrix where each pixel value is an unsigned 8bit integer
//used for grayscale imgs

void store3DImage(const Mat& img, int*** arr)
{
    int icol = img.cols, irow = img.rows;
    int i3d = 1;

    if (icol == 0 || irow == 0 || i3d == 0) {
        cout << "Error, Image cannot be stored" << endl;
    }

    int x = 0;
    while (x < irow)
    {
        int y = 0;
        while (y < icol)
        {
            int z = 0;
            while (z < i3d)
            {
                arr[x][y][z] = img.at<uchar>(x, y * i3d + z);   //offset of m-image 
                z++;
            }
            y++;
        }
        x++;
    }


}


///////////////DISPLAY
void print3DImage(int*** arr, int rows, int cols)
{
    if (cols || rows == 0)
        cout << "Error, Image cannot be displayed" << endl;



    int x = 0;
    while (x < rows)
    {
        int y = 0;
        while (y < cols)
        {
            int z = 0;
            while (z < 1)
            {
                cout << arr[x][y][z] << " ";
                z++;
            }
            cout << endl;
            y++;
        }
        cout << endl;
        x++;
    }

}



void apply3DConvolutionFeatureExtraction(int*** arr, int rows, int cols)
{
    const int size = 3, l_ro = rows - 1, l_co = cols - 1;

    int featureExt_Karr[size][size] =
    {
        {0, 1, 0},
        {1, -4, 1},
        {0, 1, 0}
    };

    int*** arr2 = new int** [rows];

    for (int i = 0; i < rows; ++i)
    {
        arr2[i] = new int* [cols];

        for (int j = 0; j < cols; ++j)
        {
            arr2[i][j] = new int[1];
        }
    }


    for (int i = 1; i < l_ro; i++)
    {
        for (int j = 1; j < l_co; j++)
        {
            int sum = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    sum += arr[i + x][j + y][0] * featureExt_Karr[x + 1][y + 1]; // Convolution
                }
            }

            arr2[i][j][0] = saturate_cast<uchar>(abs(sum));
        }
    }

    for (int x = 1; x < l_ro; x++)
    {
        for (int y = 1; y < l_co; y++)
        {
            arr[x][y][0] = arr2[x][y][0];
        }
    }


}




/////////////////////////////EDGE

void apply3DConvolutionEdgeDetection(int*** arr, int rows, int cols, Mat& edgeDetected)
{
    const int l_ro = rows - 1, l_co = cols - 1;
    int xax = 0, yax = 0;

    int sharp[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };


    for (int i = 1; i < l_ro; i++)
    {
        for (int j = 1; j < l_co; j++)
        {
            xax = 0, yax = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int store1 = sharp[k + 1][l + 1];
                    int store2 = sharp[l + 1][k + 1];

                    xax += arr[i + k][j + l][0] * store1;
                    yax += arr[i + k][j + l][0] * store2;
                }
            }


            int store3 = (xax * xax + yax * yax);
            edgeDetected.at<uchar>(i, j) = saturate_cast<uchar>(sqrt(store3));
        }
    }
}



/////////////////////////////BLURNG

void apply3DConvolution(int*** arr, int rows, int cols)
{
    const int size = 3, dpt = 1;

    float Karr[size][size][size] =
    {
        {{1.f / 27, 1.f / 27, 1.f / 27}, {1.f / 27, 1.f / 27, 1.f / 27}, {1.f / 27, 1.f / 27, 1.f / 27}},
        {{1.f / 27, 1.f / 27, 1.f / 27}, {1.f / 27, 1.f / 27, 1.f / 27}, {1.f / 27, 1.f / 27, 1.f / 27}},
        {{1.f / 27, 1.f / 27, 1.f / 27}, {1.f / 27, 1.f / 27, 1.f / 27}, {1.f / 27, 1.f / 27, 1.f / 27}}
    };





    int*** barr = new int** [rows];
    for (int i = 0; i < rows; i++)
    {
        barr[i] = new int* [cols];

        for (int j = 0; j < cols; j++)
        {
            barr[i][j] = new int[dpt];
        }

    }

    float blur_sum, store, store2;

    const int l_ro = rows - 1, l_co = cols - 1;

    for (int x = 1; x < l_ro; x++)
    {
        for (int y = 1; y < l_co; y++)
        {

            blur_sum = 0.0 * 1.0;

            for (int z = 0; z <= 1; z++)
            {
                for (int xk = 0; xk <= 1; xk++)
                {
                    for (int yk = 0; yk < 1; yk++)
                    {
                        store = Karr[z + 1][xk + 1][yk + 1];
                        store2 = barr[x + z][y + xk][0];


                        blur_sum = blur_sum + (store * store2); // Convolution
                    }

                }
            }

            barr[x][y][0] = saturate_cast<uchar>(blur_sum);
        }
    }

}

int main()
{
    // Load image
    Mat img = imread("F:/Data Structure'/Assingment/DS Assignment01/image-1.tiff", IMREAD_GRAYSCALE);
    if (img.empty())
    {
        cout << "Error: Image cannot be loaded!" << endl;
        return -1;
    }

    //image dimensions
    cout << "Rows of img: " << img.rows << endl;
    cout << "Columns of img: " << img.cols << endl;

    int r_img = img.rows, c_img = img.cols;
    int*** arr = new int** [r_img];      //DMA FOR IMG
    for (int i = 0; i < r_img; ++i)
    {
        arr[i] = new int* [c_img];
        for (int j = 0; j < c_img; ++j)
        {
            arr[i][j] = new int[1];
        }
    }

    if (!arr)
    {
        cout << "Error: Memory allocation failed!" << endl;
        return -1;
    }

    // Store 3D
    store3DImage(img, arr);

    namedWindow("Grayscale", WINDOW_AUTOSIZE);    //wndows
    namedWindow("Blurred", WINDOW_AUTOSIZE);
    namedWindow("Edge-detected", WINDOW_AUTOSIZE);
    namedWindow("Feature-Extracted", WINDOW_AUTOSIZE);

    imshow("Grayscale", img);
    apply3DConvolution(arr, r_img, c_img);   //3dd convl

    // Blur
    Mat blurImg(r_img, c_img, CV_8UC1);

    if (blurImg.empty())
    {
        cout << "Error: Unable to create blurred image!" << endl;
        return -1;
    }

    for (int i = 0; i < r_img; ++i)
    {
        for (int j = 0; j < c_img; ++j)
        {
            blurImg.at<uchar>(i, j) = arr[i][j][0];
        }
    }
    imshow("Blurred", blurImg);

    if (!imwrite("Blurred.png", blurImg))
    {
        cout << "Error: Unable to write blurred image!" << endl;
        return -1;
    }


    // Edge detection
    Mat edgeDetected(r_img, c_img, CV_8UC1);

    if (edgeDetected.empty())
    {
        cout << "Error: Unable to create edge-detected image!" << endl;
        return -1;
    }

    apply3DConvolutionEdgeDetection(arr, r_img, c_img, edgeDetected);
    imshow("Edge-detected", edgeDetected);

    if (!imwrite("Edge_Detected.png", edgeDetected))
    {
        cout << "Error: Unable to write edge-detected image!" << endl;
        return -1;
    }

    // Feature extraction
    apply3DConvolutionFeatureExtraction(arr, r_img, c_img);
    Mat featureEx(r_img, c_img, CV_8UC1);

    if (featureEx.empty())
    {
        cout << "Error: Unable to create feature-extracted image!" << endl;
        return -1;
    }

    for (int i = 0; i < r_img; ++i)
    {
        for (int j = 0; j < c_img; ++j)
        {
            featureEx.at<uchar>(i, j) = arr[i][j][0];
        }
    }

    imshow("Feature-Extracted", featureEx);
    if (!imwrite("Feature_Extracted.png", featureEx))
    {
        cout << "Error: Unable to write feature-extracted image!" << endl;
        return -1;
    }

    waitKey(0);
    destroyAllWindows();

    // Deallocate memory
    for (int i = 0; i < r_img; ++i)
    {
        for (int j = 0; j < c_img; ++j) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}