#include "openHL/openHL.hxx"
#include <iostream>

using namespace hl;

// 功能菜单
void showMenu()
{
    std::cout << "\n===========================\n";
    std::cout << "        图像处理工具        \n";
    std::cout << "===========================\n";
    std::cout << "请选择功能：\n";
    std::cout << "1. 将图像转换为灰度图\n";
    // std::cout << "2. 将图像转换为反转灰度图\n";
    std::cout << "3. 分离图像通道\n";
    std::cout << "4. 直方图处理\n";
    std::cout << "5. 图像平滑处理\n";
    std::cout << "6. 阈值分割\n";
    std::cout << "0. 退出\n";
    std::cout << "===========================\n";
    std::cout << "请输入数字来运行功能：";
}

int main()
{
    ushort choice;

    do {
        showMenu();
        std::cin >> choice;

        if (choice == 1)
        {
            // 转换为灰度图像
            Mat rgb, rgb_gray;
            rgb = imread("../Test/rgb.bmp", IMREAD_UNCHANGED);
            cvtColor(rgb, rgb_gray, COLOR_BGR2GRAY);
            imwrite("../Test/rgb_gray.bmp", rgb_gray);
            std::cout << "已将图像转换为灰度图，保存为 rgb_gray.bmp\n";
        }
        // else if (choice == 2)
        // {
        //     // 转换为反转灰度图像
        //     Mat rgb, rgb_gray_inverted;
        //     rgb = imread("rgb.bmp");
        //     cvtColor(&rgb, &rgb_gray_inverted, COLOR_BGR2GRAY_INVERTED);
        //     imwrite("rgb_gray_inverted.bmp", &rgb_gray_inverted);
        //     printf("已将图像转换为反转灰度图，保存为 rgb_gray_inverted.bmp\n");
        //     release(&rgb);
        //     release(&rgb_gray_inverted);
        // }
        else if (choice == 3)
        {
            // 分离通道
            Mat rgb;
            Mat splited_array[3];
            rgb = imread("../Test/rgb.bmp", IMREAD_UNCHANGED);
            split(rgb, splited_array);
            imwrite("../Test/rgb_B.bmp", splited_array[0]);
            imwrite("../Test/rgb_G.bmp", splited_array[1]);
            imwrite("../Test/rgb_R.bmp", splited_array[2]);
            std::cout << "已分离图像通道，分别保存为 rgb_B.bmp, rgb_G.bmp, rgb_R.bmp\n";
        }
        else if (choice == 4)
        {
            // 直方图处理
            Mat dim, dim_equalized, dim_equalized_hist, dim_hist, dim_hist_img, dim_equalized_hist_img;

            dim = imread("../Test/dim.bmp", IMREAD_GRAYSCALE);
            equalizeHist(dim, dim_equalized);

            int          channels[] = {0};
            int          histSize[] = {256};
            float        range[]    = {0, 256};
            const float* ranges[]   = {range};

            calcHist(&dim, 1, channels, Mat(), dim_hist, 1, histSize, ranges);
            calcHist(&dim_equalized, 1, channels, Mat(), dim_equalized_hist, 1, histSize, ranges);
            drawHist(dim_hist, dim_hist_img, 4, 1024);
            drawHist(dim_equalized_hist, dim_equalized_hist_img, 4, 1024);
            imwrite("../Test/dim_hist_img.bmp", dim_hist_img);
            imwrite("../Test/dim_equalized_hist_img.bmp", dim_equalized_hist_img);
            imwrite("../Test/dim_equalized.bmp", dim_equalized);
            std::cout << "已生成直方图均衡化图像，保存为 dim_equalized.bmp\n";
        }
        else if (choice == 5)
        {
            Mat noise = imread("../Test/noise.bmp", IMREAD_GRAYSCALE);
            Mat noise_medianblur, noise_blur;

            medianBlur(noise, noise_medianblur, 5);
            blur(noise, noise_blur, Size(5, 5));
            imwrite("../Test/noise_medianblur.bmp", noise_medianblur);
            imwrite("../Test/noise_blur.bmp", noise_blur);
        }
        else if (choice == 6)
        {
            Mat lena = imread("../Test/lena.bmp", IMREAD_GRAYSCALE);

            Mat          lena_hist;
            int          channels[] = {0};
            int          histSize[] = {256};
            float        range[]    = {0, 256};
            const float* ranges[]   = {range};

            calcHist(&lena, 1, channels, Mat(), lena_hist, 1, histSize, ranges);

            Mat lena_threshold_T, lena_threshold_Iter, lena_threshold_Otsu;
            Mat lena_threshold_T_hist_img, lena_threshold_Iter_hist_img, lena_threshold_Otsu_hist_img;

            drawHist_T(lena_hist, lena_threshold_T_hist_img, 4, 1024, static_cast<uchar>(threshold(lena, lena_threshold_T, 80, 255, THRESH_BINARY)));
            // drawHist_T(lena_hist, lena_threshold_Iter_hist_img, 4, 1024, static_cast<uchar>(threshold(lena, lena_threshold_Iter, 114, 255, THRESH_BINARY)));
            drawHist_T(lena_hist, lena_threshold_Otsu_hist_img, 4, 1024, static_cast<uchar>(threshold(lena, lena_threshold_Otsu, 0, 255, THRESH_OTSU)));

            imwrite("../Test/lena_threshold_T.bmp", lena_threshold_T);
            // imwrite("../Test/lena_threshold_Iter.bmp", lena_threshold_Iter);
            imwrite("../Test/lena_threshold_Otsu.bmp", lena_threshold_Otsu);

            imwrite("../Test/lena_threshold_T_hist.bmp", lena_threshold_T_hist_img);
            // imwrite("../Test/lena_threshold_Iter_hist.bmp", lena_threshold_Iter_hist_img);
            imwrite("../Test/lena_threshold_Otsu_hist.bmp", lena_threshold_Otsu_hist_img);

            std::cout << "已进行阈值分割.\n";
        }
        else if (choice == 0)
            std::cout
                << "已退出。\n";
        else std::cout << "输入错误，请重新输入。\n";
    }
    while (choice != 0);

    return 0;
}
