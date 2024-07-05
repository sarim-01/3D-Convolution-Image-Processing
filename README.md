
# Image Processing using 3D Convolution

This project entails using C++ and OpenCV to implement 3D convolution operations for blurring, edge detection, and feature extraction on 3D grayscale images. It ensures accurate border handling and image integrity through zero-padding.


## Installation

To initiate 3D convolution, you need to install the OpenCV library. Follow the installation guide at:

https://opencv.org/releases/

```bash
  cd https://github.com/sarim-01/3D-Convolution-Image-Processing
```
    
Download and execute the file:

- https://github.com/sarim-01/3D-Convolution-Image-Processing/blob/main/3DConvolution.cpp
## Usage/Examples

  #### 1.  Loading  a 3D Image:
  Make sure your 3D grayscale image is in TIFF format and resides within the project directory.

Utilize the provided function in your code to load the image.

```javascript
// ------- Load image
    Mat img = imread("path/to/your/image.file", IMREAD_GRAYSCALE);

    if (img.empty())
    {
        cout << "Error: Image cannot be loaded!" << endl;
        return -1;
    }
```


  #### 2.  3D Convolution Applications:
- For Image Blurring:

```javascript
 apply3DConvolution(arr, r_img, c_img);   
```


- For Image Edge Detection:

```javascript
 apply3DConvolutionEdgeDetection(arr, r_img, c_img, edgeDetected);
```


- For Image Feature Extraction:

```javascript
  apply3DConvolutionFeatureExtraction(arr, r_img, c_img);
```
## Features

- Load 3D images in TIFF format.
- Apply blurring convolution.
- Perform edge detection convolution.
- Execute feature extraction convolution.
- Manage image borders appropriately.
- Save processed images.


## Screenshots
- Blurred Image
![Blurred](https://github.com/sarim-01/3D-Convolution-Image-Processing/assets/174796399/ee098a01-9c1a-4710-aba4-62336b637a2f)


- Edge Detected Image:
![Edge_Detected](https://github.com/sarim-01/3D-Convolution-Image-Processing/assets/174796399/86804a4d-9a5b-4208-8a9f-704490a57953)


- Feature Extracted Image:
![Feature_Extracted](https://github.com/sarim-01/3D-Convolution-Image-Processing/assets/174796399/43c550f4-dff8-47bb-826a-f8407813ede3)

## Contributing

Contributions are always welcome!

See `contributing.md` for ways to get started.



## Documentation

[Documentation](https://docs.opencv.org/4.x/index.html)

