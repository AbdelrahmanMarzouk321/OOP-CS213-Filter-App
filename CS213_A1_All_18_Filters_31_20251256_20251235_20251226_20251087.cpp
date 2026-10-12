#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "Image_class.h"

using namespace std;

// 1. GRAYSCALE FILTER

void grayscaleFilter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int avg =
                (img(i, j, 0) +
                 img(i, j, 1) +
                 img(i, j, 2)) /
                3;

            img.setPixel(i, j, 0, avg);
            img.setPixel(i, j, 1, avg);
            img.setPixel(i, j, 2, avg);
        }
    }

    cout << "Grayscale applied successfully!\n";
}

// 2. BLACK AND WHITE FILTER

void blackAndWhiteFilter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int avg =
                (img(i, j, 0) +
                 img(i, j, 1) +
                 img(i, j, 2)) /
                3;

            int bw;

            if (avg > 128)
                bw = 255;
            else
                bw = 0;

            img.setPixel(i, j, 0, bw);
            img.setPixel(i, j, 1, bw);
            img.setPixel(i, j, 2, bw);
        }
    }

    cout << "Black and White applied successfully!\n";
}

// 3. INVERT FILTER

void invertFilter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            for (int k = 0; k < img.channels; k++)
            {
                img(i, j, k) =
                    255 - img(i, j, k);
            }
        }
    }

    cout << "Invert filter applied successfully!\n";
}

// 4. FRAME FILTER

void frameFilter(Image &img)
{
    int frame = 20;

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            if (i < frame ||
                i >= img.width - frame ||
                j < frame ||
                j >= img.height - frame)
            {
                for (int k = 0; k < img.channels; k++)
                {
                    img(i, j, k) = 0;
                }
            }
        }
    }

    cout << "Frame applied successfully!\n";
}

// 5. FLIP FILTER

void flipFilter(Image &img)
{
    int flipChoice;

    cout << "\n";
    cout << "1. Horizontal Flip (Mirror)\n";
    cout << "2. Vertical Flip\n";
    cout << "Enter your choice: ";

    cin >> flipChoice;

    // Horizontal Flip
    if (flipChoice == 1)
    {
        for (int i = 0; i < img.width / 2; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < img.channels; k++)
                {
                    unsigned char temp =
                        img(i, j, k);

                    img(i, j, k) =
                        img(img.width - 1 - i, j, k);

                    img(img.width - 1 - i, j, k) =
                        temp;
                }
            }
        }

        cout << "Horizontal Flip applied successfully!\n";
    }

    // Vertical Flip
    else if (flipChoice == 2)
    {
        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height / 2; j++)
            {
                for (int k = 0; k < img.channels; k++)
                {
                    unsigned char temp =
                        img(i, j, k);

                    img(i, j, k) =
                        img(i, img.height - 1 - j, k);

                    img(i, img.height - 1 - j, k) =
                        temp;
                }
            }
        }

        cout << "Vertical Flip applied successfully!\n";
    }

    else
    {
        cout << "Invalid flip choice.\n";
    }
}

// 6. ROTATE FILTER

void rotateFilter(Image &img)
{
    int rotateChoice;

    cout << "\n";
    cout << "1. Rotate 90 degrees clockwise\n";
    cout << "2. Rotate 90 degrees counter-clockwise\n";
    cout << "Enter your choice: ";

    cin >> rotateChoice;

    // 90 degrees clockwise

    if (rotateChoice == 1)
    {
        Image rotated(img.height, img.width);

        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < img.channels; k++)
                {
                    rotated(
                        img.height - 1 - j,
                        i,
                        k) = img(i, j, k);
                }
            }
        }

        img = std::move(rotated);

        cout << "Rotated 90 degrees clockwise successfully!\n";
    }

    // 90 degrees counter-clockwise

    else if (rotateChoice == 2)
    {
        Image rotated(img.height, img.width);

        for (int i = 0; i < img.width; i++)
        {
            for (int j = 0; j < img.height; j++)
            {
                for (int k = 0; k < img.channels; k++)
                {
                    rotated(
                        j,
                        img.width - 1 - i,
                        k) = img(i, j, k);
                }
            }
        }

        img = std::move(rotated);

        cout << "Rotated 90 degrees counter-clockwise successfully!\n";
    }

    else
    {
        cout << "Invalid rotate choice.\n";
    }
}

// 7. DARKEN / LIGHTEN FILTER

void darkenAndLightenFilter(Image &img)
{
    int degree;

    cout << "\n";
    cout << "Enter degree ";
    cout << "(positive for lighten, negative for darken): ";

    cin >> degree;

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            for (int k = 0; k < img.channels; k++)
            {
                int newValue =
                    img(i, j, k) + degree;

                if (newValue > 255)
                    newValue = 255;

                if (newValue < 0)
                    newValue = 0;

                img(i, j, k) =
                    newValue;
            }
        }
    }

    cout << "Darken/Lighten applied successfully!\n";
}

// 8. RESIZE FILTER

void resizeFilter(Image &img)
{
    int newWidth;
    int newHeight;

    cout << "Enter new width: ";
    cin >> newWidth;

    cout << "Enter new height: ";
    cin >> newHeight;

    if (newWidth <= 0 || newHeight <= 0)
    {
        cout << "Invalid dimensions.\n";
        return;
    }

    Image resized(
        newWidth,
        newHeight);

    for (int i = 0; i < newWidth; i++)
    {
        for (int j = 0; j < newHeight; j++)
        {
            int old_i =
                i * img.width / newWidth;

            int old_j =
                j * img.height / newHeight;

            for (int k = 0; k < img.channels; k++)
            {
                resized(i, j, k) =
                    img(old_i, old_j, k);
            }
        }
    }

    img = std::move(resized);

    cout << "Resize applied successfully!\n";
}

int clampValue(int value)
{
    if (value > 255)
        return 255;

    if (value < 0)
        return 0;

    return value;
}

void mergeFilter(Image &img)
{
    string secondFilename;

    cout << "\n";
    cout << "Enter the second image file name to merge: ";

    cin >> secondFilename;

    try
    {
        Image second(secondFilename);

        int mergeChoice;

        cout << "\n";
        cout << "1. Merge the common area of both images\n";
        cout << "2. Resize the second image to the first image size\n";
        cout << "Enter your choice: ";

        cin >> mergeChoice;

        int channels = img.channels;

        if (second.channels < channels)
            channels = second.channels;

        if (mergeChoice == 1)
        {
            int newWidth = img.width;
            int newHeight = img.height;

            if (second.width < newWidth)
                newWidth = second.width;

            if (second.height < newHeight)
                newHeight = second.height;

            Image merged(newWidth, newHeight);

            for (int i = 0; i < newWidth; i++)
            {
                for (int j = 0; j < newHeight; j++)
                {
                    for (int k = 0; k < channels; k++)
                    {
                        merged(i, j, k) =
                            (img(i, j, k) +
                             second(i, j, k)) /
                            2;
                    }
                }
            }

            img = std::move(merged);

            cout << "Merge (common area) applied successfully!\n";
        }

        else if (mergeChoice == 2)
        {
            for (int i = 0; i < img.width; i++)
            {
                for (int j = 0; j < img.height; j++)
                {
                    int old_i =
                        i * second.width / img.width;

                    int old_j =
                        j * second.height / img.height;

                    for (int k = 0; k < channels; k++)
                    {
                        img(i, j, k) =
                            (img(i, j, k) +
                             second(old_i, old_j, k)) /
                            2;
                    }
                }
            }

            cout << "Merge (resized) applied successfully!\n";
        }

        else
        {
            cout << "Invalid merge choice.\n";
        }
    }
    catch (...)
    {
        cout << "Could not load the second image.\n";
    }
}

void detectEdgesFilter(Image &img)
{
    int threshold = 120;

    Image gray(img.width, img.height);

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int avg =
                (img(i, j, 0) +
                 img(i, j, 1) +
                 img(i, j, 2)) /
                3;

            for (int k = 0; k < gray.channels; k++)
            {
                gray(i, j, k) = avg;
            }
        }
    }

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int value = 255;

            if (i > 0 && j > 0 &&
                i < img.width - 1 &&
                j < img.height - 1)
            {
                int gx =
                    -gray(i - 1, j - 1, 0) +
                    gray(i + 1, j - 1, 0) -
                    2 * gray(i - 1, j, 0) +
                    2 * gray(i + 1, j, 0) -
                    gray(i - 1, j + 1, 0) +
                    gray(i + 1, j + 1, 0);

                int gy =
                    -gray(i - 1, j - 1, 0) -
                    2 * gray(i, j - 1, 0) -
                    gray(i + 1, j - 1, 0) +
                    gray(i - 1, j + 1, 0) +
                    2 * gray(i, j + 1, 0) +
                    gray(i + 1, j + 1, 0);

                if (gx < 0)
                    gx = -gx;

                if (gy < 0)
                    gy = -gy;

                if (gx + gy > threshold)
                    value = 0;
            }

            for (int k = 0; k < img.channels; k++)
            {
                img(i, j, k) = value;
            }
        }
    }

    cout << "Detect Edges applied successfully!\n";
}

void cropFilter(Image &img)
{
    int startX;
    int startY;
    int cropWidth;
    int cropHeight;

    cout << "\n";
    cout << "Image size is "
         << img.width << " x " << img.height << "\n";

    cout << "Enter starting x: ";
    cin >> startX;

    cout << "Enter starting y: ";
    cin >> startY;

    cout << "Enter crop width: ";
    cin >> cropWidth;

    cout << "Enter crop height: ";
    cin >> cropHeight;

    if (startX < 0 || startY < 0 ||
        cropWidth <= 0 || cropHeight <= 0 ||
        startX + cropWidth > img.width ||
        startY + cropHeight > img.height)
    {
        cout << "Invalid crop dimensions.\n";
        return;
    }

    Image cropped(cropWidth, cropHeight);

    for (int i = 0; i < cropWidth; i++)
    {
        for (int j = 0; j < cropHeight; j++)
        {
            for (int k = 0; k < img.channels; k++)
            {
                cropped(i, j, k) =
                    img(startX + i, startY + j, k);
            }
        }
    }

    img = std::move(cropped);

    cout << "Crop applied successfully!\n";
}

void blurFilter(Image &img)
{
    int radius;

    cout << "\n";
    cout << "Enter blur level (1 to 20): ";

    cin >> radius;

    if (radius < 1 || radius > 20)
    {
        cout << "Invalid blur level.\n";
        return;
    }

    int size = 2 * radius + 1;

    Image temp(img.width, img.height);

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            for (int k = 0; k < img.channels; k++)
            {
                int sum = 0;

                for (int d = -radius; d <= radius; d++)
                {
                    int x = i + d;

                    if (x < 0)
                        x = 0;

                    if (x > img.width - 1)
                        x = img.width - 1;

                    sum += img(x, j, k);
                }

                temp(i, j, k) = sum / size;
            }
        }
    }

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            for (int k = 0; k < img.channels; k++)
            {
                int sum = 0;

                for (int d = -radius; d <= radius; d++)
                {
                    int y = j + d;

                    if (y < 0)
                        y = 0;

                    if (y > img.height - 1)
                        y = img.height - 1;

                    sum += temp(i, y, k);
                }

                img(i, j, k) = sum / size;
            }
        }
    }

    cout << "Blur applied successfully!\n";
}

void sunlightFilter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int red = img(i, j, 0) * 115 / 100 + 10;
            int green = img(i, j, 1) * 110 / 100 + 10;
            int blue = img(i, j, 2) * 85 / 100;

            img(i, j, 0) = clampValue(red);
            img(i, j, 1) = clampValue(green);
            img(i, j, 2) = clampValue(blue);
        }
    }

    cout << "Sunlight filter applied successfully!\n";
}

void tvFilter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {

            int noise = rand() % 41 - 20;

            for (int k = 0; k < img.channels; k++)
            {
                int newValue =
                    img(i, j, k) + noise;

                if (j % 4 < 2)
                    newValue = newValue * 70 / 100;

                img(i, j, k) =
                    clampValue(newValue);
            }
        }
    }

    cout << "TV filter applied successfully!\n";
}

void purpleFilter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int red = img(i, j, 0) * 110 / 100;
            int green = img(i, j, 1) * 70 / 100;
            int blue = img(i, j, 2) * 120 / 100;

            img(i, j, 0) = clampValue(red);
            img(i, j, 1) = clampValue(green);
            img(i, j, 2) = clampValue(blue);
        }
    }

    cout << "Purple filter applied successfully!\n";
}

void infraredFilter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int avg =
                (img(i, j, 0) +
                 img(i, j, 1) +
                 img(i, j, 2)) /
                3;

            img(i, j, 0) = 255;
            img(i, j, 1) = avg;
            img(i, j, 2) = avg;
        }
    }

    cout << "Infrared filter applied successfully!\n";
}

void skewFilter(Image &img)
{
    double angle;

    cout << "\n";
    cout << "Enter skew angle in degrees (1 to 80): ";

    cin >> angle;

    if (angle < 1 || angle > 80)
    {
        cout << "Invalid angle.\n";
        return;
    }

    double radians = angle * 3.14159265358979 / 180.0;

    double slope = tan(radians);

    int extra = (int)((img.height - 1) * slope);

    Image skewed(img.width + extra, img.height);

    for (int i = 0; i < skewed.width; i++)
    {
        for (int j = 0; j < skewed.height; j++)
        {
            for (int k = 0; k < skewed.channels; k++)
            {
                skewed(i, j, k) = 255;
            }
        }
    }

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int shift =
                (int)((img.height - 1 - j) * slope);

            for (int k = 0; k < img.channels; k++)
            {
                skewed(i + shift, j, k) =
                    img(i, j, k);
            }
        }
    }

    img = std::move(skewed);

    cout << "Skew applied successfully!\n";
}

void oilPaintingFilter(Image &img)
{
    int radius = 3;
    int levels = 20;

    Image original(img.width, img.height);

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            for (int k = 0; k < img.channels; k++)
            {
                original(i, j, k) = img(i, j, k);
            }
        }
    }

    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            int count[20] = {0};
            int sumRed[20] = {0};
            int sumGreen[20] = {0};
            int sumBlue[20] = {0};

            for (int x = i - radius; x <= i + radius; x++)
            {
                for (int y = j - radius; y <= j + radius; y++)
                {
                    if (x < 0 || y < 0 ||
                        x >= img.width ||
                        y >= img.height)
                        continue;

                    int red = original(x, y, 0);
                    int green = original(x, y, 1);
                    int blue = original(x, y, 2);

                    int intensity =
                        ((red + green + blue) / 3) *
                        (levels - 1) / 255;

                    count[intensity]++;
                    sumRed[intensity] += red;
                    sumGreen[intensity] += green;
                    sumBlue[intensity] += blue;
                }
            }

            int best = 0;

            for (int level = 1; level < levels; level++)
            {
                if (count[level] > count[best])
                    best = level;
            }

            img(i, j, 0) = sumRed[best] / count[best];
            img(i, j, 1) = sumGreen[best] / count[best];
            img(i, j, 2) = sumBlue[best] / count[best];
        }
    }

    cout << "Oil Painting applied successfully!\n";
}

// MAIN

int main()
{
    srand(time(0));

    string filename;

    cout << "Welcome to Baby Photoshop!\n";

    cout << "Enter the image file name to load: ";

    cin >> filename;

    string outputFilename;

    cout << "\nEnter the output image file name to save ";
    cout << "(e.g., output.jpg): ";

    cin >> outputFilename;

    int choice;
    Image img(filename);

    do
    {
        cout << "\n";
        cout << "====================================\n";
        cout << "       BABY PHOTOSHOP MENU\n";
        cout << "====================================\n";

        cout << "1. Grayscale filter\n";
        cout << "2. Black and White filter\n";
        cout << "3. Invert Image filter\n";
        cout << "4. Frame filter\n";
        cout << "5. Flip Image filter\n";
        cout << "6. Rotate Image filter\n";
        cout << "7. Darken and Lighten Image filter\n";
        cout << "8. Resize Image filter\n";
        cout << "9. Merge Images filter\n";
        cout << "10. Detect Image Edges filter\n";
        cout << "11. Crop Images filter\n";
        cout << "12. Blur Images filter\n";
        cout << "13. Sunlight filter\n";
        cout << "14. TV filter\n";
        cout << "15. Purple filter\n";
        cout << "16. Infrared filter\n";
        cout << "17. Skewing filter (bonus)\n";
        cout << "18. Oil Painting filter (bonus)\n";
        cout << "0. Exit & save\n";

        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            grayscaleFilter(img);
            img.saveImage(outputFilename);
            break;

        case 2:
            blackAndWhiteFilter(img);
            img.saveImage(outputFilename);
            break;

        case 3:
            invertFilter(img);
            img.saveImage(outputFilename);
            break;

        case 4:
            frameFilter(img);
            img.saveImage(outputFilename);
            break;

        case 5:
            flipFilter(img);
            img.saveImage(outputFilename);
            break;

        case 6:
            rotateFilter(img);
            img.saveImage(outputFilename);
            break;

        case 7:
            darkenAndLightenFilter(img);
            img.saveImage(outputFilename);
            break;

        case 8:
            resizeFilter(img);
            img.saveImage(outputFilename);
            break;

        case 9:
            mergeFilter(img);
            img.saveImage(outputFilename);
            break;

        case 10:
            detectEdgesFilter(img);
            img.saveImage(outputFilename);
            break;

        case 11:
            cropFilter(img);
            img.saveImage(outputFilename);
            break;

        case 12:
            blurFilter(img);
            img.saveImage(outputFilename);
            break;

        case 13:
            sunlightFilter(img);
            img.saveImage(outputFilename);
            break;

        case 14:
            tvFilter(img);
            img.saveImage(outputFilename);
            break;

        case 15:
            purpleFilter(img);
            img.saveImage(outputFilename);
            break;

        case 16:
            infraredFilter(img);
            img.saveImage(outputFilename);
            break;

        case 17:
            skewFilter(img);
            img.saveImage(outputFilename);
            break;

        case 18:
            oilPaintingFilter(img);
            img.saveImage(outputFilename);
            break;

        case 0:
            cout << "Exiting program & save...\n";
            break;

        default:
            cout << "Invalid choice, please try again.\n";
        }

    } while (choice != 0);

    // SAVE IMAGE

    cout << "Image saved successfully. Goodbye!\n";

    return 0;
}