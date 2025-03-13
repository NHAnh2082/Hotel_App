/********************************************************
 * @file    Menu.hpp
 * @brief   Hiển thị menu điều khiển.
 * @version 1.0
 * @date    2025-02-10
 * @author  Anh Nguyen
 ********************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include "Menu_Item.hpp"
#include "UI.hpp"
#include "Std_Types.hpp"
#include <vector>

/**
 * @class Menu
 * @brief Lớp quản lý menu và điều hướng người dùng.
 */
class Menu 
{
    private:
        string title_;               /**< Tiêu đề của menu */
        vector<MenuItem> items_;     /**< Danh sách các mục menu */

    public:
        /**
         * @brief Constructor khởi tạo menu với tiêu đề và danh sách mục.
         * @param[in] title Tiêu đề của menu.
         * @param[in] items Danh sách các mục menu.
         */
        Menu(const string &title, initializer_list<MenuItem> items)
            : title_(title), items_(items) {}

        /**
         * @brief Hiển thị menu và xử lý lựa chọn từ người dùng.
         */
        void showMenu() 
        {
            int choice;
            do 
            {
                // Hiển thị tiêu đề của menu
                UI::showMessage("\n===== " + title_ + " =====");

                // Hiển thị từng mục menu
                for (const auto& item : items_) 
                {
                    UI::showMessage(to_string(item.getChoice()) + ". " + item.getDescription());
                }

                // Lấy lựa chọn từ người dùng
                choice = UI::getUserChoice("Vui lòng chọn tính năng: ");

                // Thực hiện hành động cho lựa chọn
                bool validChoice = false;
                for (const auto& item : items_) 
                {
                    if (item.getChoice() == choice) 
                    {
                        item.executeAction();  // Thực hiện hành động
                        validChoice = true;
                        break;
                    }
                }

                // Thông báo nếu lựa chọn không hợp lệ
                if (!validChoice) 
                {
                    UI::showMessage("Lựa chọn không hợp lệ, vui lòng chọn lại.");
                }

            } while (choice != 0);  // Quay lại nếu lựa chọn không phải là thoát
        }
};

#endif // MENU_HPP
