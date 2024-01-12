// #include "Image.h"

// int main(int argc, char** argv){
//     Image test("test.jpg");
//     test.write("new.png");
//     Image copy = test;
//     for(int i=0;i<copy.w*copy.channels;++i){
//         copy.data[i] = 255;
//     }
//     copy.write("copy.png");
//     Image blank(100,100,3);
//     blank.write("blank.jpg");
//     test.adjustBrightness(130); 
//     test.write("brightened.png");
//     test.convertToGrayscale();
//     test.write("grayscale.png");
//     test.invertColors();
//     test.write("inverted.png");
//     test.rotate90Degrees();
//     test.write("rotated.png");
//     test.crop(50, 50, 200, 150); 
//     test.write("cropped.png");
//     return 0;
// }

// #include "Image.h"
// #include <iostream>

// int main(int argc, char** argv) {
//     Image test("test.jpg");
//     test.write("new.png");

//     int choice = 0;
//     while (choice != 6) {
//         std::cout << "Choose an operation:\n";
//         std::cout << "1. Adjust Brightness\n";
//         std::cout << "2. Convert to Grayscale\n";
//         std::cout << "3. Invert Colors\n";
//         std::cout << "4. Rotate 90 Degrees\n";
//         std::cout << "5. Crop\n";
//         std::cout << "6. Exit\n";

//         std::cin >> choice;

//         switch (choice) {
//             case 1:
//                 test.adjustBrightness(130);
//                 test.write("brightened.png");
//                 break;
//             case 2:
//                 test.convertToGrayscale();
//                 test.write("grayscale.png");
//                 break;
//             case 3:
//                 test.invertColors();
//                 test.write("inverted.png");
//                 break;
//             case 4:
//                 test.rotate90Degrees();
//                 test.write("rotated.png");
//                 break;
//             case 5:
//                 test.crop(50, 50, 200, 150);
//                 test.write("cropped.png");
//                 break;
//             case 6:
//                 std::cout << "Exiting the program.\n";
//                 break;
//             default:
//                 std::cout << "Invalid choice. Try again.\n";
//                 break;
//         }
//     }

//     return 0;
// }

#include "Image.h"
#include <iostream>

int main(int argc, char** argv) {
    Image original("test.jpg");
    original.write("original.png");

    int choice = 0;
    while (choice != 7) {
        std::cout << "Choose an operation:\n";
        std::cout << "1. Adjust Brightness\n";
        std::cout << "2. Convert to Grayscale\n";
        std::cout << "3. Invert Colors\n";
        std::cout << "4. Rotate 90 Degrees\n";
        std::cout << "5. Crop\n";
        std::cout << "6. Display Original Image\n";
        std::cout << "7. Exit\n";

        std::cin >> choice;

        // Create a new workingCopy for each iteration
        Image workingCopy = original;

        switch (choice) {
            case 1:
                workingCopy.adjustBrightness(130);
                workingCopy.write("brightened.png");
                break;
            case 2:
                workingCopy.convertToGrayscale();
                workingCopy.write("grayscale.png");
                break;
            case 3:
                workingCopy.invertColors();
                workingCopy.write("inverted.png");
                break;
            case 4:
                workingCopy.rotate90Degrees();
                workingCopy.write("rotated.png");
                break;
            case 5:
                workingCopy.crop(50, 50, 200, 150);
                workingCopy.write("cropped.png");
                break;
            case 6:
                original.write("original.png");
                break;
            case 7:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    }

    return 0;
}
