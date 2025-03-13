/********************************************************
 * @file    UI.hpp
 * @brief   Lớp hỗ trợ nhập xuất dữ liệu người dùng.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef UI_HPP
#define UI_HPP

#include "Std_Types.hpp"

/**
 * @class UI
 * @brief Lớp cung cấp các phương thức nhập xuất dữ liệu từ người dùng.
 */
class UI 
{
    public:
        /**
         * @brief Lấy lựa chọn từ người dùng dưới dạng số nguyên.
         * @param[in] prompt Thông điệp hiển thị cho người dùng.
         * @return int - Giá trị người dùng nhập vào.
         */
        static int getUserChoice(const string &prompt);

        /**
         * @brief Lấy lựa chọn từ người dùng dưới dạng số thực.
         * @param[in] prompt Thông điệp hiển thị cho người dùng.
         * @return float - Giá trị số thực người dùng nhập vào.
         */
        static float getUserChoiceFloat(const string &prompt);

        /**
         * @brief Hiển thị thông báo đến người dùng.
         * @param[in] message Chuỗi thông báo cần hiển thị.
         */
        static void showMessage(const string &message);

        /**
         * @brief Lấy chuỗi dữ liệu nhập từ người dùng.
         * @param[in] prompt Thông điệp hiển thị cho người dùng.
         * @return std::string - Chuỗi nhập vào từ người dùng.
         */
        static string getInputString(const string &prompt);
};

#endif // UI_HPP
